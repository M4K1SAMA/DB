#pragma once

#include <cstring>
#include <cstdio>
#include "../filesystem/utils/pagedef.h"
#include "../filesystem/fileio/FileManager.h"
#include "../filesystem/bufmanager/BufPageManager.h"
#include "../def.h"

struct File_Header
{
	AttrType attrType;
	uint attrLen;
	uint order;
	uint capacity;
	uint root;
	uint nodeNum;
};

struct Page_Header
{
	bool isLeaf;
	uint eleNum;
	uint prev, next;
	uint parent;
};

struct Internal
{
	Page_Header ph;
	BufType child;
	void* attr;
};

struct Leaf
{
	Page_Header ph;
	BufType page;
	BufType slot;
	void *attr;
};
