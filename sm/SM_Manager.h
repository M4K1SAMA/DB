#include "SM.h"

class SM_Manager {
   private:
    RM_Manager *rmm;
    IX_Manager *ixm;
    BufPageManager *bpm;
    FileManager *fm;
    vector<TableInfo> tables;
    unordered_map<string, int> fileId;
    int tableNum;

   public:
    SM_Manager(RM_Manager *_rmm, IX_Manager *_ixm, BufPageManager *_bpm,
               FileManager *_fm)
        : rmm(_rmm), ixm(_ixm), bpm(_bpm), fm(_fm) {}

    ~SM_Manager() {}

    bool Open(const char *DBName) {
        chdir(DBName);
        ifstream meta("META.DB");
        if (!meta.is_open()) {
            return false;
        }
        tables.clear();
        fileId.clear();
        meta >> tableNum;
        for (int i = 0; i < tableNum; ++i) {
            TableInfo table;
            meta >> table;
            int fID;
            rmm->OpenFile(table.name, fID);
            fileId[table.name] = fID;
        }
        meta.close();
        return true;
    }

    bool Close() {
        ofstream meta("META.DB");
        if (!meta.is_open()) {
            return false;
        }
        meta << tableNum << '\n';
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
        return true;
    }

    bool CreateTable(TableInfo &tableInfo) {
        uint recordSize = 0;
        for (int i = 0; i < tableNum; ++i) {
            if (strncmp(tables[i].name, tableInfo.name, 10) == 0) {
                return false;
            }
        }
        for (int i = 0; i < tableInfo.attrNum; ++i) {
            tableInfo.attrs[i].offset = recordSize >> 2;
            if (tableInfo.attrs[i].type == INTEGER)
                tableInfo.attrs[i].length = 4;
            else if (tableInfo.attrs[i].type == FLOAT)
                tableInfo.attrs[i].length = 4;
            recordSize += tableInfo.attrs[i].length;
            if (tableInfo.attrs[i].isPrimary) tableInfo.attrs[i].notNull = true;
            if (tableInfo.attrs[i].ref != "") {
                if (tableInfo.attrs[i].ref == tableInfo.name) {
                    return false;
                }
                bool flag = false;
                for (int i = 0; i < tableNum; ++i) {
                    if (tables[i].name == tableInfo.attrs[i].ref) {
                        for (int k = 0; k < tables[i].attrNum; ++k) {
                            if (tables[i].attrs[k].isPrimary &&
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
        for (int i = 0; i < tables[tableNum].attrNum; ++i) {
            if (tables[tableNum].attrs[i].isPrimary)
                tables[tableNum].primary.push_back(i);
            if (tables[tableNum].attrs[i].ref != "") {
                string ref = tables[tableNum].attrs[i].ref;
                if (tables[tableNum].foreignSet.find(ref) ==
                    tables[tableNum].foreignSet.end()) {
                    tables[tableNum].foreignSet.insert(ref);
                    tables[tableNum].foreign.push_back(ref);
                    ++tables[tableNum].foreignNum;
                }
            }
        }
        rmm->CreateFile(tableInfo.name, recordSize);
        int fID;
        rmm->OpenFile(tableInfo.name, fID);
        if (tables[tableNum].primary.size() != 0) {
            int size = 0;
            for (auto prim : tables[tableNum].primary) {
                size += tables[tableNum].attrs[prim].length;
            }
            tables[tableNum].primarySize = size;
            ixm->CreateIndex(tableInfo.name, 0, STRING, size);
        }
        ++tableNum;
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
        return true;
    }

    bool CreateIndex(const string &name, const string &attr) {
        int tidx = -1;
        for (int i = 0; i < tables.size(); ++i) {
            if (tables[i].name == name) tidx = i;
        }
        if (tidx == -1) {
            return false;
        }
        int aidx = -1;
        for (int i = 0; i < tables[tidx].attrs.size(); ++i) {
            if (tables[tidx].attrs[i].name == attr) {
                aidx = i;
                if (!tables[idx].attrs[i].notNull ||
                    tables[idx].attrs[i].indexed) {
                    return false;
                }
            }
        }
        if (!aidx == -1) {
            return false;
        }
        int fID = fileId[name];
        RM_FileHandle rfh(fm, bpm, fID);
        RM_Scan scan(fm, bpm);
        scan.OpenScan(rfh);
        tables[tidx].attrs[aidx].indexed = true;
        ixm->CreateIndex(name.c_str(), aidx, tables[tidx].attrs[aidx].type,
                         tables[tidx].attrs[aidx].length);
        int indexfID;
        ixm->OpenIndex(name.c_str(), aidx, indexfID);
        IX_Handle ih(fm, bpm, indexfID);
        BufType entry = new uint[rfh.header.recordSize];

        while (true) {
            int page, slot;
            bool finished = scan.GetNext(page, slot, data);
            BufType to_insert = entry + tables[tidx].attrs[aidx].offset;
            RID rid = {page, slot};
            ih.InsertEntry(to_insert, rid);
            if (finished) break;
        }
        delete[] entry;
        ixm->CloseIndex(indexfID);
    }

    bool DropIndex(const string &name, const string &attr) {
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
            if (tables[tidx].attrs[i].name == attr) {
                if (!tables[tidx].attrs[i].indexed) {
                    return false;
                }
                aidx = i;
            }
        }
        if (aidx == -1) {
            return false;
        }
        tables[tidx].attrs[aidx].indexed = false;
        ixm->DestroyIndex(name.c_str(), aidx);
        return true;
    }
};
