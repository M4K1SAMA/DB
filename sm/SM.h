#pragma once
#include <unistd.h>

#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../def.h"
using namespace std;

struct AttrInfo {
    string name;
    AttrType type;
    uint length;
    bool foreign;
    bool primary;
    bool notNull;
    bool indexed;
    bool def;
    int defint;
    float deffloat;
    string defstring;
    string idxName;
    string ref;
    string foreignKeyName;

    uint offset;
};

struct TableInfo {
    string name;
    uint attrNum;
    uint foreignNum;
    uint recordSize;
    uint primarySize;
    vector<int> primary;
    vector<AttrInfo> attrs;
    vector<string> foreign;
    unordered_set<string> foreignSet;
};

inline ifstream &operator>>(ifstream &ifs, AttrInfo &attr) {
    ifs >> attr.name >> attr.offset;
    attr.notNull = attr.primary = attr.indexed = attr.def = false;
    // attr.defaultValue = nullptr;
    attr.ref = attr.foreignKeyName = "";
    string tmp;
    ifs >> tmp;
    if (tmp == "INT") {
        attr.type = INTEGER;
        attr.length = 4;
    } else if (tmp == "FLOAT") {
        attr.type = FLOAT_T;
        attr.length = 4;
    } else if (tmp == "STRING") {
        attr.type = STRING;
        ifs >> attr.length;
    }
    while (true) {
        ifs >> tmp;
        if (tmp == "NOTNULL")
            attr.notNull = true;
        else if (tmp == "PRIMARY")
            attr.primary = true;
        else if (tmp == "DEFAULT") {
            if (attr.type == INTEGER) {
                // int *def;
                ifs >> attr.defint;
                // attr.defaultValue = def;
            } else if (attr.type == FLOAT_T) {
                // float *def;
                ifs >> attr.deffloat;
                // attr.defaultValue = def;
            } else if (attr.type == STRING) {
                string _def;
                getline(ifs, _def);
                char *def = new char[attr.length + 1];
                memcpy(def, _def.c_str(), attr.length + 1);
                attr.defstring = def;
            }
        } else if (tmp == "FOREIGN")
            ifs >> attr.ref >> attr.foreignKeyName;
        else if (tmp == "IX")
            attr.indexed = true;
        else if (tmp == "FIN")
            break;
    }
    return ifs;
}

inline ifstream &operator>>(ifstream &ifs, TableInfo &table) {
    ifs >> table.name >> table.attrNum >> table.foreignNum >>
        table.recordSize >> table.primarySize;
    table.attrs.clear();
    table.foreign.clear();
    table.foreignSet.clear();
    table.primary.clear();
    for (int i = 0; i < table.attrNum; ++i) {
        AttrInfo attr;
        ifs >> attr;
        table.attrs.push_back(attr);
        if (attr.primary) table.primary.push_back(i);
        if (table.foreignSet.find(attr.ref) == table.foreignSet.end()) {
            table.foreign.push_back(attr.ref);
            table.foreignSet.insert(attr.ref);
        }
    }
    return ifs;
}

inline ofstream &operator<<(ofstream &ofs, AttrInfo attr) {
    ofs << attr.name << endl << attr.offset << endl;
    if (attr.type == INTEGER)
        ofs << "INT" << endl;
    else if (attr.type == FLOAT_T)
        ofs << "FLOAT" << endl;
    else if (attr.type == STRING) {
        ofs << "STRING" << endl;
        ofs << attr.length << endl;
    }
    if (attr.notNull) ofs << "NOTNULL\n";
    if (attr.primary) ofs << "PRIMARY" << endl;
    if (attr.def) {
        if (attr.type == INTEGER)
            ofs << attr.defint << endl;
        else if (attr.type == FLOAT_T)
            ofs << attr.deffloat << endl;
        else if (attr.type == STRING)
            ofs << attr.defstring << endl;
    }
    if (attr.ref != "")
        ofs << "FOREIGN" << endl
            << attr.ref << endl
            << attr.foreignKeyName << endl;
    if (attr.indexed) ofs << "IX" << endl;
    ofs << "FIN" << endl;
    return ofs;
}

inline ofstream &operator<<(ofstream &ofs, TableInfo table) {
    ofs << table.name << endl << table.attrNum << endl;
    ofs << table.foreignNum << endl << table.recordSize << endl;
    ofs << table.primarySize << endl;
    for (int i = 0; i < table.attrNum; ++i) {
        ofs << table.attrs[i];
    }
    return ofs;
}
