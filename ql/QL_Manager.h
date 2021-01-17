#pragma once
#include <cstring>
#include <iostream>

#include "../sm/SM_Manager.h"

using namespace std;

class QL_Manager {
   private:
    SM_Manager *smm;

    // void find(string tbName, unordered_set<RID> &hits,
    //           vector<Where> whereList) {
    //     int tidx = -1;
    //     for (int i = 0; i < smm->tableNum; ++i) {
    //         if (smm->tables[i].name == tbName) {
    //             tidx = i;
    //         }
    //     }
    //     if (tidx == -1) {
    //         cout << tbName << " not found" << endl;
    //     }

    //     for (auto &where : whereList) {
    //     }
    // }

    void taByCol(Col col, int &tidx, int &aidx) {
        tidx = -1;
        aidx = -1;
        if (col.tab != "") {
            for (int i = 0; i < smm->tableNum; ++i) {
                if (smm->tables[i].name == col.tab) {
                    tidx = i;
                }
            }
            if (tidx == -1) {
                cout << col.tab << " not found" << endl;
                tidx = aidx = -1;
                return;
            }
            for (int i = 0; i < smm->tables[tidx].attrNum; ++i) {
                if (smm->tables[tidx].attrs[i].name == col.attr) {
                    aidx = i;
                }
            }
            if (aidx == -1) {
                cout << col.tab << '.' << col.attr << " not found" << endl;
                tidx = aidx = -1;
                return;
            }
        } else {
            for (int i = 0; i < smm->tableNum; ++i) {
                for (int j = 0; j < smm->tables[i].attrNum; ++j) {
                    if (smm->tables[i].attrs[j].name == col.attr) {
                        if (tidx != -1) {
                            cout << "duplicate attr" << endl;
                            tidx = aidx = -1;
                            return;
                        } else {
                            tidx = i;
                            aidx = j;
                        }
                    }
                }
            }
        }
        return;
    }

   public:
    QL_Manager(SM_Manager *_smm) : smm(_smm) {}

    ~QL_Manager() {}

    bool Insert(const string &name, vector<vector<LiteralVal>> valLists) {
        int tidx = -1;
        for (int i = 0; i < smm->tableNum; ++i) {
            if (smm->tables[i].name == name) {
                tidx = i;
            }
        }
        if (tidx == -1) {
            cout << name << " not found" << endl;
        }
        int recordSize = smm->tables[tidx].recordSize;
        char data[recordSize];
        memset(data, 0, recordSize);
        for (auto &valList : valLists) {
            int offset = 4;
            for (int i = 0; i < valList.size(); ++i) {
                LiteralVal val = valList[i];
                if (val.isNull) {
                    if (smm->tables[tidx].attrs[i].notNull) {
                        cout << smm->tables[tidx].attrs[i].name
                             << " should not be NULL" << endl;
                        return false;
                    }
                    data[i >> 3] |= (1 << (i & 7));
                    cout << "NULL ";
                } else {
                    switch (smm->tables[tidx].attrs[i].type) {
                        case INTEGER:
                            if (val.type == STRING) {
                                cout << smm->tables[tidx].attrs[i].name
                                     << " should be INT but given STRING"
                                     << endl;
                                return false;
                            } else if (val.type == FLOAT_T) {
                                cout << smm->tables[tidx].attrs[i].name
                                     << " should be INT but given FLOAT"
                                     << endl;
                                return false;
                            }
                            memcpy(data + offset, &val.i, 4);
                            // cout << val.i << ' ';
                            break;
                        case FLOAT_T:
                            if (val.type == STRING) {
                                cout << smm->tables[tidx].attrs[i].name
                                     << " should be FLOAT but given STRING"
                                     << endl;
                                return false;
                            }
                            if (val.type == INTEGER) {
                                float f = (float)val.i;
                                memcpy(data + offset, &f, 4);
                            } else if (val.type == FLOAT_T) {
                                memcpy(data + offset, &val.f, 4);
                            }
                            // cout << val.f << ' ';
                            break;
                        case STRING:
                            if (val.type != STRING) {
                                cout << smm->tables[tidx].attrs[i].name
                                     << " should be STRING" << endl;
                                return false;
                            }
                            memcpy(data + offset, val.s.c_str(),
                                   val.s.length());
                            // cout << val.s << ' ';
                            break;
                    }
                }
                offset += smm->tables[tidx].attrs[i].length;
            }
            // cout << endl;
        }
        RM_FileHandle rfh(smm->fm, smm->bpm, smm->fileId[name]);
        RID rid;
        rfh.InsertRec((BufType)data, rid);
        smm->bpm->close();
        return true;
    }

    bool Select(Selector selector, vector<string> tableList,
                vector<Where> whereList) {
        vector<vector<string>> datas(tableList.size(), vector<string>());
        unordered_map<string, int> name2idx;
        if (!selector.all) {
            for (auto &col : selector.cols) {
                if (col.tab == "") {
                    int tidx, aidx;
                    taByCol(col, tidx, aidx);
                    if (tidx == -1) return false;
                    col.tab = smm->tables[tidx].name;
                }
            }
        }
        for (auto &where : whereList) {
            if (where.col.tab == "") {
                int tidx, aidx;
                taByCol(where.col, tidx, aidx);
                if (tidx == -1) return false;
                where.col.tab = smm->tables[tidx].name;
            }
            if (!where.expr.isVal && where.expr.col.tab == "") {
                int tidx, aidx;
                taByCol(where.expr.col, tidx, aidx);
                if (tidx == -1) return false;
                where.expr.col.tab = smm->tables[tidx].name;
            }
        }
        for (int i = 0; i < tableList.size(); ++i) {
            int tidx = -1;
            name2idx[tableList[i]] = i;
            for (int j = 0; j < smm->tableNum; ++j) {
                if (smm->tables[j].name == tableList[i]) {
                    tidx = j;
                }
            }
            if (tidx == -1) {
                cout << tableList[i] << " not found" << endl;
            }
            RM_FileHandle rfh(smm->fm, smm->bpm, smm->fileId[tableList[i]]);
            RM_Scan scanner(smm->fm, smm->bpm);
            scanner.OpenScan(&rfh);
            char data[smm->tables[tidx].recordSize];
            memset(data, 0, smm->tables[tidx].recordSize);
            RID rid;
            while (scanner.GetNextRec((BufType)data, rid)) {
                bool ok = true;
                for (auto &where : whereList) {
                    if (!where.expr.isVal || (where.col.tab != tableList[i]))
                        continue;
                    int aidx = -1;
                    for (int j = 0; j < smm->tables[tidx].attrNum; ++j) {
                        AttrInfo attr = smm->tables[tidx].attrs[j];
                        if (where.col.attr == attr.name) {
                            aidx = j;
                            break;
                        }
                    }
                    if (aidx != -1) {
                        char value[smm->tables[tidx].attrs[aidx].length];
                        memset(value, 0, smm->tables[tidx].attrs[aidx].length);
                        if (where.expr.val.isNull) {
                            // value = nullptr;
                        } else {
                            switch (smm->tables[tidx].attrs[aidx].type) {
                                case INTEGER:
                                    *((int *)value) = where.expr.val.i;
                                    break;
                                case FLOAT_T:
                                    *((float *)value) = where.expr.val.f;
                                    break;
                                case STRING:
                                    memcpy(
                                        value, where.expr.val.s.c_str(),
                                        smm->tables[tidx].attrs[aidx].length);
                                    break;
                            }
                        }
                        ok = Check(
                            (char *)data, smm->tables[tidx].attrs[aidx].offset,
                            aidx, smm->tables[tidx].attrs[aidx].type,
                            smm->tables[tidx].attrs[aidx].length, where.op,
                            where.expr.val.isNull ? nullptr : (void *)value);
                        if (!ok) break;
                    }
                }
                if (!ok) {
                    continue;
                }
                // char *tmp = new char[smm->tables[tidx].recordSize];
                // memcpy(tmp, data, smm->tables[tidx].recordSize);
                datas[i].push_back(string(data, smm->tables[tidx].recordSize));
            }
        }
        // cout << "fetch over" << endl;
        int cur = 0;
        int num = 1;
        for (auto &d : datas) {
            num *= d.size();
            // cout << d.size() << ' ';
        }
        // cout << endl;
        vector<int> idxs(datas.size(), 0);
        // cout << "check and output" << endl;
        int res = 0;
        while (cur < num) {
            int ccur = cur;
            for (int i = datas.size() - 1; i >= 0; --i) {
                idxs[i] = ccur % datas[i].size();
                ccur /= datas[i].size();
            }
            // check conditions
            bool ok = true;
            for (auto &where : whereList) {
                if (!where.expr.isVal) {
                    int tidx1, aidx1;
                    int tidx2, aidx2;
                    taByCol(where.col, tidx1, aidx1);
                    taByCol(where.expr.col, tidx2, aidx2);
                    int idx1 = name2idx[smm->tables[tidx1].name];
                    int idx2 = name2idx[smm->tables[tidx2].name];
                    if (smm->tables[tidx1].attrs[aidx1].type !=
                        smm->tables[tidx2].attrs[aidx2].type) {
                        cout << "type not matched" << endl;
                        return false;
                    }
                    const char *data1 = datas[idx1][idxs[idx1]].c_str();
                    const char *data2 = datas[idx2][idxs[idx2]].c_str();
                    int offset2 = smm->tables[tidx2].attrs[aidx2].offset;
                    const char *value = data2 + offset2;
                    ok = Check((char *)data1,
                               smm->tables[tidx1].attrs[aidx1].offset, aidx1,
                               smm->tables[tidx1].attrs[aidx1].type,
                               smm->tables[tidx1].attrs[aidx1].length, where.op,
                               value);
                    if (!ok) break;
                }
            }
            if (ok) {
                ++res;
                if (selector.all) {
                    for (int i = 0; i < tableList.size(); ++i) {
                        int tidx = -1;
                        for (int j = 0; j < smm->tableNum; ++j) {
                            if (smm->tables[j].name == tableList[i]) {
                                tidx = j;
                            }
                        }
                        // if (tidx == -1) {
                        //     cout << tableList[i] << " not found" << endl;
                        // }
                        const char *data = datas[i][idxs[i]].c_str();
                        int offset = 4;
                        for (int j = 0; j < smm->tables[tidx].attrNum; ++j) {
                            AttrInfo attr = smm->tables[tidx].attrs[j];
                            if ((data[j >> 3] & (1 << (j & 7)))) {
                                cout << "NULL ";
                            } else {
                                switch (attr.type) {
                                    case INTEGER:
                                        cout << *((int *)(data + offset))
                                             << ' ';
                                        break;
                                    case FLOAT_T:
                                        cout << *((float *)(data + offset))
                                             << ' ';
                                        break;
                                    case STRING:
                                        char stringbuf[attr.length + 1];
                                        memset(stringbuf, 0, attr.length + 1);
                                        memcpy(stringbuf, data + offset,
                                               attr.length);
                                        cout << '\'' << stringbuf << '\''
                                             << ' ';
                                }
                            }
                            offset += attr.length;
                        }
                    }
                    cout << endl;
                } else {
                    for (auto &col : selector.cols) {
                        string tab = col.tab;
                        int idx = name2idx[tab];
                        const char *data = datas[idx][idxs[idx]].c_str();
                        int tidx = -1, aidx = -1;
                        taByCol(col, tidx, aidx);
                        AttrInfo attr = smm->tables[tidx].attrs[aidx];
                        switch (attr.type) {
                            case INTEGER:
                                cout << *((int *)(data + attr.offset)) << ' ';
                                break;
                            case FLOAT_T:
                                cout << *((float *)(data + attr.offset)) << ' ';
                                break;
                            case STRING:
                                char stringbuf[attr.length + 1];
                                memset(stringbuf, 0, attr.length + 1);
                                memcpy(stringbuf, data + attr.offset,
                                       attr.length);
                                cout << '\'' << stringbuf << '\'' << ' ';
                                break;
                        }
                    }
                    cout << endl;
                }
            }
            ++cur;
        }
        cout << res << " results" << endl;

        return true;
    }

    bool Update(string tbName, vector<Set> setList, vector<Where> whereList) {
        int tidx = -1;
        for (int i = 0; i < smm->tableNum; ++i) {
            if (smm->tables[i].name == tbName) {
                tidx = i;
            }
        }
        if (tidx == -1) {
            cout << tbName << " not found" << endl;
            return false;
        }
        RM_FileHandle rfh(smm->fm, smm->bpm, smm->fileId[tbName]);
        RM_Scan scanner(smm->fm, smm->bpm);
        scanner.OpenScan(&rfh);
        char data[smm->tables[tidx].recordSize];
        memset(data, 0, smm->tables[tidx].recordSize);
        RID rid;
        while (scanner.GetNextRec((BufType)data, rid)) {
            bool ok = true;
            for (auto &where : whereList) {
                string colName = where.col.attr;
                void *value;
                int aidx = -1;
                for (int i = 0; i < smm->tables[tidx].attrNum; ++i) {
                    if (smm->tables[tidx].attrs[i].name == colName) {
                        aidx = i;
                    }
                }
                AttrInfo attr = smm->tables[tidx].attrs[aidx];
                // char *v = new char[smm->tables[tidx].attrs[aidx].length];
                if (where.expr.val.isNull) {
                    value = nullptr;
                } else {
                    switch (where.expr.val.type) {
                        case INTEGER:
                            value = (void *)&where.expr.val.i;
                            break;
                        case FLOAT_T:
                            value = (void *)&where.expr.val.f;
                            break;
                        case STRING:
                            value = (void *)where.expr.val.s.c_str();
                            break;
                    }
                }
                ok = Check(data, attr.offset, aidx, attr.type, attr.length,
                           where.op, value);
            }
            if (!ok) {
                continue;
            }
            for (auto &set : setList) {
                int aidx = -1;
                for (int i = 0; i < smm->tables[tidx].attrNum; ++i) {
                    if (smm->tables[tidx].attrs[i].name == set.col.attr) {
                        aidx = i;
                    }
                }
                AttrInfo attr = smm->tables[tidx].attrs[aidx];
                if (set.val.isNull) {
                    data[aidx >> 3] |= (1 << (aidx & 7));
                } else {
                    switch (attr.type) {
                        case INTEGER:
                            memcpy(data + attr.offset, &set.val.i, attr.length);
                            break;
                        case FLOAT_T:
                            memcpy(data + attr.offset, &set.val.f, attr.length);
                            break;
                        case STRING:
                            memcpy(data + attr.offset, set.val.s.c_str(),
                                   attr.length);
                            break;
                    }
                }
            }
            rfh.UpdateRec(rid, (BufType)data);
        }
        return true;
    }

    bool Delete(string tbName, vector<Where> whereList) {
        cout << "Delete" << endl;
        int tidx = -1;
        for (int i = 0; i < smm->tableNum; ++i) {
            if (smm->tables[i].name == tbName) {
                tidx = i;
            }
        }
        if (tidx == -1) {
            cout << tbName << " not found" << endl;
        }
        RM_FileHandle rfh(smm->fm, smm->bpm, smm->fileId[tbName]);
        RM_Scan scanner(smm->fm, smm->bpm);
        scanner.OpenScan(&rfh);
        char *data = new char[smm->tables[tidx].recordSize];
        RID rid;
        while (scanner.GetNextRec((BufType)data, rid)) {
            bool ok = true;
            for (auto &where : whereList) {
                string colName = where.col.attr;
                void *value;
                int aidx = -1;
                for (int i = 0; i < smm->tables[tidx].attrNum; ++i) {
                    if (smm->tables[tidx].attrs[i].name == colName) {
                        aidx = i;
                    }
                }
                AttrInfo attr = smm->tables[tidx].attrs[aidx];
                // char *v = new char[smm->tables[tidx].attrs[aidx].length];
                if (where.expr.val.isNull) {
                    value = nullptr;
                } else {
                    switch (where.expr.val.type) {
                        case INTEGER:
                            value = (void *)&where.expr.val.i;
                            break;
                        case FLOAT_T:
                            value = (void *)&where.expr.val.f;
                            break;
                        case STRING:
                            value = (void *)where.expr.val.s.c_str();
                            break;
                    }
                }
                ok = Check(data, attr.offset, aidx, attr.type, attr.length,
                           where.op, value);
            }
            if (!ok) {
                continue;
            }
            rfh.DeleteRec(rid);
        }
        return true;
    }

    bool Check(char *data, int attrOffset, int attrIndex, AttrType attrType,
               int length, CompOp op, const void *value) {
        char *d = data + attrOffset;
        switch (op) {
            case EQ_OP:
                if (value == nullptr) {
                    return data[attrIndex >> 3] & (1 << (attrIndex & 7));
                } else {
                    switch (attrType) {
                        case INTEGER:
                            return *((int *)d) == *((int *)value);
                        case FLOAT_T:
                            return *((float *)d) == *((float *)value);
                        case STRING:
                            // cout << "compare " << string(d, length) << " and
                            // "
                            //      << string((char *)value, length) << endl;
                            return strncmp(d, (char *)value, length) == 0;
                    }
                }
            case LT_OP:
                switch (attrType) {
                    case INTEGER:
                        return *((int *)d) < *((int *)value);
                    case FLOAT_T:
                        return *((float *)d) < *((float *)value);
                    case STRING:
                        return strncmp(d, (char *)value, length) < 0;
                }
            case GT_OP:
                switch (attrType) {
                    case INTEGER:
                        return *((int *)d) > *((int *)value);
                    case FLOAT_T:
                        return *((float *)d) > *((float *)value);
                    case STRING:
                        return strncmp(d, (char *)value, length) > 0;
                }
            case LE_OP:
                switch (attrType) {
                    case INTEGER:
                        return *((int *)d) <= *((int *)value);
                    case FLOAT_T:
                        return *((float *)d) <= *((float *)value);
                    case STRING:
                        return strncmp(d, (char *)value, length) <= 0;
                }
            case GE_OP:
                switch (attrType) {
                    case INTEGER:
                        return *((int *)d) >= *((int *)value);
                    case FLOAT_T:
                        return *((float *)d) >= *((float *)value);
                    case STRING:
                        return strncmp(d, (char *)value, length) >= 0;
                }
            case NE_OP:
                if (value == nullptr) {
                    return data[attrIndex >> 3] & (1 << (attrIndex & 7));
                } else {
                    switch (attrType) {
                        case INTEGER:
                            return *((int *)d) != *((int *)value);
                        case FLOAT_T:
                            return *((float *)d) != *((float *)value);
                        case STRING:
                            return strncmp(d, (char *)value, length) != 0;
                    }
                }
            case NO_OP:
                return true;
        }
    }
};
