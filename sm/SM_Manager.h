#pragma once
#include <dirent.h>

#include "../ix/IX_Handle.h"
#include "../ix/IX_Manager.h"
#include "../rm/RM_FileHandle.h"
#include "../rm/RM_Manager.h"
#include "../rm/RM_Scan.h"
#include "SM.h"

class SM_Manager {
   private:
    friend class QL_Manager;
    RM_Manager *rmm;
    IX_Manager *ixm;
    BufPageManager *bpm;
    FileManager *fm;
    vector<TableInfo> tables;
    unordered_map<string, int> fileId;
    string root;
    string cdb;
    int tableNum;

   public:
    SM_Manager(RM_Manager *_rmm, IX_Manager *_ixm, BufPageManager *_bpm,
               FileManager *_fm)
        : rmm(_rmm), ixm(_ixm), bpm(_bpm), fm(_fm) {
        char *buf = new char[100];
        root = getcwd(buf, 100);
        cout << "root " << root << endl;
        cdb = "";
    }

    ~SM_Manager() {}

    void Exit() {
        cout << "Exit" << endl;
        bpm->close();
        exit(0);
    }

    void WBMeta() {
        ofstream meta("METADATA");
        meta << tableNum << endl;
        for (int i = 0; i < tableNum; ++i) {
            meta << tables[i];
        }
        return;
    }

    void ShowDBs() {
        DIR *directory_pointer = opendir(root.c_str());
        struct dirent *entry;
        while ((entry = readdir(directory_pointer)) != NULL) {
            if (entry->d_name[0] == '.') continue;
            printf("%s ", entry->d_name);
        }
    }

    bool CreateDB(string DBName) {
        system(("mkdir " + root + "/" + DBName).c_str());
        chdir(DBName.c_str());
        ofstream ofs("METADATA");
        ofs << 0 << endl;
        ofs.close();
        chdir("..");
        return true;
    }

    bool DropDB(string DBName) {
        cout << "Drop" << endl;
        if (DBName == cdb) {
            cdb = "";
            chdir("..");
        }
        system(("rm -r " + root + "/" + DBName).c_str());
        return true;
    }

    bool UseDB(const string _DBName) {
        if (cdb != "") {
            Close();
        }
        cdb = _DBName;
        chdir(_DBName.c_str());
        ifstream meta("METADATA");
        if (!meta.is_open()) {
            return false;
        }
        tables.clear();
        fileId.clear();
        meta >> tableNum;
        for (int i = 0; i < tableNum; ++i) {
            TableInfo table;
            meta >> table;
            tables.push_back(table);
            int fID;
            rmm->OpenFile(table.name.c_str(), fID);
            fileId[table.name] = fID;
        }
        meta.close();
        return true;
    }

    bool Close() {
        cout << "Close" << endl;
        ofstream meta("METADATA");
        if (!meta.is_open()) {
            return false;
        }
        meta << tableNum << endl;
        for (int i = 0; i < tableNum; ++i) {
            meta << tables[i];
            if (!rmm->CloseFile(fileId[tables[i].name])) {
                return false;
            }
        }
        tables.clear();
        fileId.clear();
        meta.close();
        chdir("..");
        cdb = "";
        return true;
    }

    void ShowTables() {
        for (int i = 0; i < tableNum; ++i) {
            cout << tables[i].name << endl;
        }
        return;
    }

    bool CreateTable(TableInfo &tableInfo) {
        if (cdb == "") {
            cout << "not in a db" << endl;
            return false;
        }
        uint recordSize = 4;
        for (int i = 0; i < tableNum; ++i) {
            if (strncmp(tables[i].name.c_str(), tableInfo.name.c_str(), 10) ==
                0) {
                return false;
            }
        }
        for (int i = 0; i < tableInfo.attrNum; ++i) {
            tableInfo.attrs[i].offset = recordSize;
            if (tableInfo.attrs[i].type == INTEGER)
                tableInfo.attrs[i].length = 4;
            else if (tableInfo.attrs[i].type == FLOAT_T)
                tableInfo.attrs[i].length = 4;
            recordSize += tableInfo.attrs[i].length;
            if (tableInfo.attrs[i].primary) tableInfo.attrs[i].notNull = true;
            if (tableInfo.attrs[i].ref != "") {
                if (tableInfo.attrs[i].ref == tableInfo.name) {
                    return false;
                }
                bool flag = false;
                for (int i = 0; i < tableNum; ++i) {
                    if (tables[i].name == tableInfo.attrs[i].ref) {
                        for (int k = 0; k < tables[i].attrNum; ++k) {
                            if (tables[i].attrs[k].primary &&
                                tables[i].attrs[k].name ==
                                    tableInfo.attrs[i].foreignKeyName) {
                                tableInfo.attrs[i].type =
                                    tables[i].attrs[k].type;
                                tableInfo.attrs[i].length =
                                    tables[i].attrs[k].length;
                                flag = true;
                                break;
                            }
                        }
                        if (flag) break;
                    }
                }
            }
        }
        tables.push_back(tableInfo);
        tables[tableNum].recordSize = recordSize;
        tables[tableNum].primarySize = 0;
        tables[tableNum].primary.clear();
        tables[tableNum].foreign.clear();
        tables[tableNum].foreignSet.clear();
        tables[tableNum].foreignNum = 0;
        // cout << tables[tableNum].attrNum << " attrs" << endl;
        for (int i = 0; i < tables[tableNum].attrNum; ++i) {
            // cout << tables[tableNum].attrs[i].name << endl;
            if (tables[tableNum].attrs[i].primary) {
                // cout << " is primary " << endl;
                tables[tableNum].primary.push_back(i);
                tables[tableNum].attrs[i].idxName = "pk";
            }
            // cout << "ref is " << tables[tableNum].attrs[i].ref << endl;
            // cout << 3;
            if (tables[tableNum].attrs[i].ref != "") {
                // cout << " has foreign" << endl;
                string ref = tables[tableNum].attrs[i].ref;
                if (tables[tableNum].foreignSet.find(ref) ==
                    tables[tableNum].foreignSet.end()) {
                    tables[tableNum].foreignSet.insert(ref);
                    tables[tableNum].foreign.push_back(ref);
                    ++tables[tableNum].foreignNum;
                }
            }
            // cout << 2;
        }
        rmm->CreateFile(tableInfo.name.c_str(), recordSize);
        int fID;
        rmm->OpenFile(tableInfo.name.c_str(), fID);
        fileId[tableInfo.name] = fID;
        // cout << tableInfo.name << " is " << fID << endl;
        if (tables[tableNum].primary.size() != 0) {
            int size = 0;
            for (auto &prim : tables[tableNum].primary) {
                // cout << size << ' ' << prim << endl;
                size += tables[tableNum].attrs[prim].length;
            }
            // cout << tables[tableNum].primarySize << ' ' << size << endl;

            tables[tableNum].primarySize = size;

            ixm->CreateIndex(tableInfo.name.c_str(), "pk", STRING, size);
        }
        ++tableNum;
        WBMeta();
        return true;
    }

    bool DropTable(const string &name) {
        int idx = -1;
        for (int i = 0; i < tableNum; ++i) {
            if (tables[i].name != name &&
                tables[i].foreignSet.find(name) != tables[i].foreignSet.end()) {
                return false;
            } else if (tables[i].name == name) {
                idx = i;
            }
        }
        if (idx == -1) {
            return false;
        }
        if (!rmm->CloseFile(fileId[tables[idx].name])) {
            return false;
        }
        if (!rmm->DestroyFile(name.c_str())) {
            return false;
        }
        tables.erase(tables.begin() + idx);
        --tableNum;
        WBMeta();
        return true;
    }

    bool Desc(const string &name) {
        int idx = -1;
        for (int i = 0; i < tableNum; ++i) {
            if (tables[i].name == name) {
                idx = i;
            }
        }
        if (idx == -1) {
            cout << name << " not found" << endl;
            return false;
        }
        cout << "Field | Type | Null | Key | Default" << endl;
        for (auto &attr : tables[idx].attrs) {
            cout << attr.name << " | ";
            switch (attr.type) {
                case INTEGER:
                    cout << "INT";
                    break;
                case STRING:
                    cout << "STRING";
                    break;
                case FLOAT_T:
                    cout << "FLOAT";
                    break;
            }
            cout << " | " << !attr.notNull << " | " << attr.primary << " | ";
            if (attr.def) {
                switch (attr.type) {
                    case INTEGER:
                        cout << attr.defint;
                        break;
                    case STRING:
                        cout << attr.defstring;
                        break;
                    case FLOAT_T:
                        cout << attr.deffloat;
                        break;
                }
            } else {
                cout << "NULL";
            }
            cout << endl;
        }
        return true;
    }

    // TODO
    bool CreateIndex(const string &name, string idxName,
                     const vector<string> &attrs) {
        string attr = attrs[0];
        int tidx = -1;
        for (int i = 0; i < tables.size(); ++i) {
            if (tables[i].name == name) tidx = i;
        }
        if (tidx == -1) {
            cout << name << " not found" << endl;
            return false;
        }
        int aidx = -1;
        for (int i = 0; i < tables[tidx].attrs.size(); ++i) {
            if (tables[tidx].attrs[i].name == attr) {
                aidx = i;
                if (tables[tidx].attrs[i].indexed) {
                    cout << tables[tidx].attrs[i].name << " already indexed"
                         << endl;
                    return false;
                }
            }
        }
        if (aidx == -1) {
            cout << attr << " not found" << endl;
            return false;
        }
        int fID = fileId[name];
        RM_FileHandle rfh(fm, bpm, fID);

        RM_Scan scanner(fm, bpm);
        scanner.OpenScan(&rfh);
        tables[tidx].attrs[aidx].idxName = idxName;
        tables[tidx].attrs[aidx].indexed = true;
        ixm->CreateIndex(name.c_str(), idxName, tables[tidx].attrs[aidx].type,
                         tables[tidx].attrs[aidx].length);
        int indexfID;
        ixm->OpenIndex(name.c_str(), idxName, indexfID);
        IX_Handle ih(fm, bpm, indexfID);
        char *data = new char[rfh.header.recordSize];
        RID rid;
        while (scanner.GetNextRec(data, rid)) {
            char *to_insert = data + tables[tidx].attrs[aidx].offset;
            ih.InsertEntry(to_insert, rid);
        }
        delete[] data;
        ixm->CloseIndex(indexfID);
        WBMeta();
        return true;
    }

    // TODO
    bool DropIndex(const string &name, const string &idxName) {
        int tidx = -1;
        for (int i = 0; i < tableNum; ++i) {
            if (tables[i].name == name) {
                tidx = i;
            }
        }
        if (tidx == -1) {
            return false;
        }
        int aidx = -1;
        for (int i = 0; i < tables[tidx].attrNum; ++i) {
            if (tables[tidx].attrs[i].idxName == idxName) {
                if (!tables[tidx].attrs[i].indexed) {
                    return false;
                }
                tables[tidx].attrs[aidx].indexed = false;
                tables[tidx].attrs[i].idxName = "";
            }
        }
        if (aidx == -1) {
            return false;
        }
        ixm->DestroyIndex(name.c_str(), idxName);
        WBMeta();
        return true;
    }

    bool AddPrimary(const string &tableName, const vector<string> &attrs) {
        int tidx = -1;
        for (int i = 0; i < tableNum; ++i) {
            if (tables[i].name == tableName) {
                tidx = i;
            }
        }
        if (tidx == -1) {
            return false;
        }
        if (tables[tidx].primary.size() != 0) {
            cout << "primary already exists" << endl;
            return false;
        }
        int primarySize = 0;
        for (const string &attrName : attrs) {
            int aidx = -1;
            for (int i = 0; i < tables[tidx].attrNum; ++i) {
                if (tables[tidx].attrs[i].name == attrName) {
                    aidx = i;
                }
            }
            if (aidx == -1) {
                cout << attrName << " not found" << endl;
                tables[tidx].primary.clear();
                return false;
            }
            tables[tidx].primary.push_back(aidx);
            primarySize += tables[tidx].attrs[aidx].length;
        }

        vector<string> datas;
        vector<RID> rids;
        char data[tables[tidx].recordSize];
        char prim[primarySize];
        int fID = fileId[tableName];
        RM_FileHandle rfh(fm, bpm, fID);
        RM_Scan scanner(fm, bpm);
        scanner.OpenScan(&rfh);
        RID rid;
        while (scanner.GetNextRec(data, rid)) {
            memset(prim, 0, primarySize);
            int offset = 0;
            for (int i = 0; i < attrs.size(); ++i) {
                int aidx = -1;
                for (int i = 0; i < tables[tidx].attrNum; ++i) {
                    if (tables[tidx].attrs[i].name == attrs[i]) {
                        aidx = i;
                    }
                }
                memcpy(prim + offset, data + tables[tidx].attrs[aidx].offset,
                       tables[tidx].attrs[aidx].length);
                offset += tables[tidx].attrs[aidx].length;
            }
            string s = string(prim);
            for (auto &data : datas) {
                if (data == s) {
                    cout << "duplicate lines" << endl;
                    tables[tidx].primary.clear();

                    return false;
                }
            }
            datas.push_back(s);
            rids.push_back(rid);
        }

        for (auto &aidx : tables[tidx].primary) {
            tables[tidx].attrs[aidx].primary = true;
            tables[tidx].attrs[aidx].idxName = "pk";
        }

        // TODO CREATE INDEX
        ixm->CreateIndex(tableName.c_str(), "pk", STRING, primarySize);
        ixm->OpenIndex(tableName.c_str(), "pk", fID);
        IX_Handle ih(fm, bpm, fID);
        for (int i = 0; i < datas.size(); ++i) {
            ih.InsertEntry(datas[i].c_str(), rids[i]);
        }
        WBMeta();
        return true;
    }

    bool DropPrimary(const string &name) {
        int tidx = -1;
        for (int i = 0; i < tableNum; ++i) {
            if (name == tables[tidx].name) {
                tidx = i;
            }
        }
        if (tidx == -1) {
            cout << name << " not found" << endl;
        }
        for (auto &aidx : tables[tidx].primary) {
            tables[tidx].attrs[aidx].primary = false;
            tables[tidx].attrs[aidx].idxName = "";
        }
        tables[tidx].primary.clear();
        ixm->DestroyIndex(name.c_str(), "pk");
        WBMeta();
        return true;
    }

    bool AddColumn(const string &name, AttrInfo attr) {
        int tidx = -1;
        for (int i = 0; i < tableNum; ++i) {
            if (name == tables[tidx].name) {
                tidx = i;
            }
        }
        if (tidx == -1) {
            cout << name << " not found" << endl;
        }

        switch (attr.type) {
            case INTEGER:
                attr.length = 4;
                break;
            case FLOAT_T:
                attr.length = 4;
                break;
            case STRING:
                break;
        }
        if (attr.primary) {
            attr.notNull = true;
            tables[tidx].primary.push_back(tables[tidx].attrNum);
            attr.idxName = "pk";
            tables[tidx].primarySize += attr.length;
        }
        attr.offset = tables[tidx].recordSize;
        tables[tidx].recordSize += attr.length;

        tables[tidx].attrs.push_back(attr);
        rmm->CreateFile("tmp", tables[tidx].recordSize);
        int newfID;
        rmm->OpenFile("tmp", newfID);
        fileId["tmp"] = newfID;

        RM_FileHandle rfh1(fm, bpm, fileId[name]);
        RM_FileHandle rfh2(fm, bpm, fileId["tmp"]);

        RM_Scan scanner(fm, bpm);
        scanner.OpenScan(&rfh1);
        char data[tables[tidx].recordSize];
        memset(data, 0, tables[tidx].recordSize);

        RID rid;
        while (scanner.GetNextRec(data, rid)) {
            data[tables[tidx].attrNum >> 3] |=
                (1 << (tables[tidx].attrNum & 7));
            rfh2.InsertRec((BufType)data, rid);
        }
        ++tables[tidx].attrNum;
        DropTable(name);
        Rename("tmp", name);

        WBMeta();

        return true;
    }

    bool DropColumn(const string &name, const string &colName) {
        int tidx = -1;
        for (int i = 0; i < tableNum; ++i) {
            if (name == tables[tidx].name) {
                tidx = i;
            }
        }
        if (tidx == -1) {
            cout << name << " not found" << endl;
        }
        int aidx = -1;
        for (int i = 0; i < tables[tidx].attrNum; ++i) {
            if (tables[tidx].attrs[i].name == colName) {
                aidx = i;
            }
        }
        if (aidx == -1) {
            cout << colName << " not found" << endl;
        }
        AttrInfo attr = tables[tidx].attrs[aidx];

        switch (attr.type) {
            case INTEGER:
                attr.length = 4;
                break;
            case FLOAT_T:
                attr.length = 4;
                break;
            case STRING:
                break;
        }
        if (tables[tidx].attrs[aidx].primary) {
            cout << "can't drop primary" << endl;
            return false;
        }
        tables[tidx].recordSize -= attr.length;

        tables[tidx].attrs.push_back(attr);
        rmm->CreateFile("tmp", tables[tidx].recordSize);
        int newfID;
        rmm->OpenFile("tmp", newfID);
        fileId["tmp"] = newfID;

        RM_FileHandle rfh1(fm, bpm, fileId[name]);
        RM_FileHandle rfh2(fm, bpm, fileId["tmp"]);

        RM_Scan scanner(fm, bpm);
        scanner.OpenScan(&rfh1);
        char data[tables[tidx].recordSize];
        memset(data, 0, tables[tidx].recordSize);

        RID rid;
        while (scanner.GetNextRec(data, rid)) {
            data[tables[tidx].attrNum >> 3] |=
                (1 << (tables[tidx].attrNum & 7));
            rfh2.InsertRec((BufType)data, rid);
        }
        ++tables[tidx].attrNum;
        DropTable(name);
        Rename("tmp", name);

        WBMeta();

        return true;
    }

    bool Rename(string table1, string table2) {
        for (int i = 0; i < tableNum; ++i) {
            if (tables[i].name == table1) {
                tables[i].name = table2;
                rename((root + "/" + cdb + "/" + table1).c_str(),
                       (table2).c_str());
                fileId[table2] = fileId[table1];
                fileId.erase(table1);
                WBMeta();
                return true;
            }
        }
        cout << table1 << " not found" << endl;
        return false;
    }
};
