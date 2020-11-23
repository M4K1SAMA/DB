#pragma once
#include "filesystem/utils/pagedef.h"

struct RID {
	uint page;
	uint slot;
};

enum AttrType{
    INTEGER,
    FLOAT,
    STRING
};
