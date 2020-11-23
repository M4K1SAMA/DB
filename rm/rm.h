#pragma once

#include <cstring>
#include <cstdio>
#include "../filesystem/utils/pagedef.h"
#include "../filesystem/fileio/FileManager.h"
#include "../filesystem/bufmanager/BufPageManager.h"
#include "../def.h"

struct File_Header
{
	uint recordSize;
	uint pageNum;
	uint recordPerPage;
	uint bitmapSize;
	uint firstFreePage;

};
