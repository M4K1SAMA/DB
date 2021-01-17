#pragma once
#include "filesystem/utils/pagedef.h"

struct RID {
    uint page;
    uint slot;
};

enum AttrType { INTEGER, FLOAT_T, STRING };

enum CompOp { EQ_OP, LT_OP, GT_OP, LE_OP, GE_OP, NE_OP, NO_OP };
