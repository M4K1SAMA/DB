#pragma once
#include <unistd.h>

#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "../ix/IX_Handle.h"
#include "../ix/IX_Manager.h"
#include "../rm/RM_FileHandle.h"
#include "../rm/RM_Manager.h"

struct TableInfo {
    char name[100];
    uint attrNum;
    uint foreignNum;
    uint recordSize;
    uint primarySize;
    vector<int> primary;
    vector<AttrInfo> attrs;
    vector<string> foreign;
    unordered_set<string> foreignSet;
};

struct AttrInfo {
    char name[100];
    AttrType type;
    uint length;
    bool isPrimary;
    bool notNull;
    bool indexed;
    void *defaultValue;
    string ref;
    string foreignKeyName;
    uint offset;
};

ifstream &operator>>(ifstream &ifs, AttrInfo &attr) {
    ifs >> attr.name >> attr.offset;
    attr.notNull = attr.isPrimary = attr.indexed = false;
    attr.defaultValue = nullptr;
    attr.ref = attr.foreignKeyName = "";
    string tmp;
    ifs >> tmp;
    if (tmp == "INT") {
        attr.type = INTEGER;
        attr.length = 4;
    } else if (tmp == "FLOAT") {
        attr.type = FLOAT;
        attr.length = 4;
    } else if (tmp == "STRING") {
        attr.type = STRING;
        attr.length = 8;
    }
    while (true) {
        ifs >> tmp;
        if (tmp == "NOTNULL")
            attr.notNull = true;
        else if (tmp == "PRIMARY")
            attr.isPrimary = true;
        else if (tmp == "DEFAULT") {
            if (attr.type == INTEGER) {
                int *def;
                ifs >> *def;
                attr.defaultValue = def;
            } else if (attr.type == FLOAT) {
                float *def;
                ifs >> *def;
                attr.defaultValue = def;
            } else if (attr.type == STRING) {
                string _def;
                getline(ifs, _def);
                char *def = new char[attr.length + 1];
                memcpy(def, _def.c_str(), attr.length + 1);
                attr.defaultValue = def;
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

ifstream &operator>>(ifstream &ifs, TableInfo &table) {
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
        if (attr.isPrimary) table.primary.push_back(i);
        if (table.foreignSet.find(attr.ref) == table.foreignSet.end()) {
            table.foreign.push_back(attr.ref);
            table.foreignSet.insert(attr.ref);
        }
    }
    return ifs;
}

ofstream &operator<<(ofstream &ofs, AttrInfo attr) {
    ofs << attr.name << '\n' << attr.offset << '\n';
    if (attr.type == INTEGER)
        ofs << "INT\n";
    else if (attr.type == FLOAT)
        ofs << "FLOAT\n";
    else if (attr.type == STRING)
        ofs << "STRING\n";
    if (attr.notNull) ofs << "NOTNULL\n";
    if (attr.isPrimary) ofs << "PRIMARY\n";
    if (attr.defaultValue) {
        if (attr.type == INTEGER)
            ofs << *((int *)attr.defaultValue) << '\n';
        else if (attr.type == FLOAT)
            ofs << *((float *)attr.defaultValue) << '\n';
        else if (attr.type == STRING)
            ofs << *((char *)attr.defaultValue) << '\n';
    }
    if (attr.ref != "")
        ofs << "FOREIGN\n" << attr.ref << '\n' << attr.foreignKeyName << '\n';
    if (attr.indexed) ofs << "IX\n";
    ofs << "FIN\n";
    return ofs;
}

ofstream &operator<<(ofstream &ofs, TableInfo table) {
    ofs << table.name << '\n' << table.attrNum << '\n';
    ofs << table.foreignNum << '\n' << table.recordSize << '\n';
    ofs << table.primarySize << '\n';
    for (int i = 0; i < table.attrNum; ++i) {
        ofs << table.attrs[i];
    }
    return ofs;
}
