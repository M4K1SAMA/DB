#pragma once
#include <string>
#include <vector>

#include "../def.h"
#include "../sm/SM.h"
using namespace std;

enum Type { VALUE, OP, TYPE, FIELD, FIELD_LIST, PRIM, FOR, ID };

struct Col {
    string tab;
    string attr;
};

struct LiteralVal {
    bool isNull;
    AttrType type;
    float f;
    int i;
    string s;
};

struct Expr {
    bool isVal;
    LiteralVal val;
    Col col;
};

struct Where {
    Col col;
    CompOp op;
    Expr expr;
};

struct Set {
    Col col;
    LiteralVal val;
};

struct Selector {
    bool all;
    vector<Col> cols;
};

struct TokenVal {
    Type type;

    string s;
    LiteralVal val;
    vector<LiteralVal> valList;
    vector<vector<LiteralVal> > valLists;
    CompOp op;
    Col col;
    Selector selector;
    vector<Col> colList;
    AttrInfo attr;
    vector<AttrInfo> attrList;
    Where where;
    vector<Where> whereList;
    Set set;
    vector<Set> setList;
    Expr expr;

    vector<string> stringList;
};

#define YYSTYPE TokenVal
