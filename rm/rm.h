#pragma once

#include <cstdio>
#include <cstring>

#include "../def.h"
#include "../filesystem/bufmanager/BufPageManager.h"
#include "../filesystem/fileio/FileManager.h"
#include "../filesystem/utils/pagedef.h"

struct File_Header {
    uint recordSize;
    uint pageNum;
    uint recordPerPage;
    uint bitmapSize;
    uint firstFreePage;
};
