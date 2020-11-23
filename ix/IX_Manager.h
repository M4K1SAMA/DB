#include "ix.h"

class IX_Manager {
    FileManager *fm;
    BufPageManager *bpm;

public:

    IX_Manager(FileManager *_fm, BufPageManager *_bpm): fm(_fm), bpm(_bpm) {

    }

    ~IX_Manager() {

    }

    bool CreateIndex(const char *fileName, int idx, AttrType attrType, int attrLen) {
        const char *fullName = (string(fileName) + string(".") + to_string(idx)).c_str();
        if (!fm->createFile(fullName))
            return false;
        int fID;
        if(!fm->openFile(fullName, fID))
            return false;
        File_Header fh;
        fh.attrType = attrType;
        fh.attrLen = attrLen;
        fh.capacity = (PAGE_SIZE - sizeof(Page_Header)) / (sizeof(uint) * 3 + attrLen) - 1 - 3;
        fh.order = (PAGE_SIZE - sizeof(Page_Header)) / (sizeof(uint) + attrLen) - 1 - 3;
        fh.root = 1;
        fh.nodeNum = 2;
        int index;
        BufType buf = bpm->getPage(fID, 0, index);
        memcpy(buf, &fh, sizeof(fh));
        bpm->markDirty(index);
        bpm->writeBack(index);
        Page_Header ph;
        ph.isLeaf = true;
        ph.next = ph.prev = 0;
        ph.eleNum = 0;
        ph.parent = 0;
        buf = bpm->getPage(fID, 1, index);
        memcpy(buf, &ph, sizeof(ph));
        bpm->markDirty(index);
        bpm->writeBack(index);
        fm->closeFile(fID);
        return true;
    }

    bool DestroyIndex(const char *fileName, int idx) {
        return !remove((fileName + string(".") + to_string(idx)).c_str());
    }

    bool OpenIndex(const char *fileName, int idx, int &fID) {
        return fm->openFile((fileName + string(".") + to_string(idx)).c_str(), fID);
    }

    bool CloseIndex(int fID) {
        bpm->close();
        return !fm->closeFile(fID);
    }

};
