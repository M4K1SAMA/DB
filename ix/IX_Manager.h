#pragma once
#include "IX.h"

class IX_Manager {
    FileManager *fm;
    BufPageManager *bpm;

   public:
    IX_Manager(FileManager *_fm, BufPageManager *_bpm) : fm(_fm), bpm(_bpm) {}

    ~IX_Manager() {}

    bool CreateIndex(const char *fileName, string idxName, AttrType attrType,
                     int attrLen) {
        const char *fullName =
            (string(fileName) + string(".") + idxName).c_str();
        if (!fm->createFile(fullName)) return false;
        int fID;
        if (!fm->openFile(fullName, fID)) return false;
        IX_File_Header fh;
        fh.attrType = attrType;
        fh.attrLen = attrLen;
        fh.capacity =
            (PAGE_SIZE - sizeof(Page_Header)) / (sizeof(uint) * 2 + attrLen) -
            1 - 3;
        fh.order =
            (PAGE_SIZE - sizeof(Page_Header)) / (sizeof(uint) + attrLen) - 1 -
            3;
        // cout << fh.capacity << ' ' << fh.order << endl;
        fh.root = 1;
        fh.lastPage = 1;
        int index;
        BufType buf = bpm->getPage(fID, 0, index);
        memcpy(buf, &fh, sizeof(fh));
        bpm->markDirty(index);
        bpm->writeBack(index);
        buf = bpm->getPage(fID, 1, index);
        Page_Header *ph = (Page_Header *)buf;
        ph->isLeaf = true;
        ph->next = ph->prev = 0;
        ph->eleNum = 0;
        ph->parent = 0;
        // memcpy(buf, &ph, sizeof(ph));
        bpm->markDirty(index);
        bpm->writeBack(index);
        fm->closeFile(fID);
        return true;
    }

    bool DestroyIndex(const char *fileName, string idxName) {
        return !remove((fileName + string(".") + idxName).c_str());
    }

    bool OpenIndex(const char *fileName, string idxName, int &fID) {
        return fm->openFile((fileName + string(".") + idxName).c_str(), fID);
    }

    bool CloseIndex(int fID) {
        bpm->close();
        return !fm->closeFile(fID);
    }
};
