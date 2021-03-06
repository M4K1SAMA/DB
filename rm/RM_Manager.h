#pragma once
#include "RM.h"

class RM_Manager {
    FileManager *fm;
    BufPageManager *bpm;

   public:
    RM_Manager(FileManager *_fm, BufPageManager *_bpm) : fm(_fm), bpm(_bpm) {}

    ~RM_Manager() {}

    bool CreateFile(const char *fileName, int recordSize) {
        if (recordSize > PAGE_SIZE) return false;
        fm->createFile(fileName);
        int fID;
        fm->openFile(fileName, fID);
        // cout << "Create and open file " << fileName << ' ' << fID << endl;
        RM_File_Header header;
        header.recordSize = recordSize;
        header.pageNum = 0;
        header.recordPerPage =
            ((PAGE_SIZE << 3) - 64) / (1 + (recordSize << 3));
        // cout << header.recordPerPage << " records" << endl;
        header.bitmapSize = ((header.recordPerPage) >> 3) + 1;
        header.firstFreePage = 1;
        int idx;
        BufType b = bpm->getPage(fID, 0, idx);
        bpm->markDirty(idx);
        memcpy(b, &header, sizeof(RM_File_Header));
        bpm->close();
        fm->closeFile(fID);
        return true;
    }

    bool DestroyFile(const char *fileName) { return !(remove(fileName)); }

    bool OpenFile(const char *fileName, int &fID) {
        return fm->openFile(fileName, fID);
    }

    bool CloseFile(int fID) {
        bpm->close();
        return !fm->closeFile(fID);
    }
};
