#include "rm.h"

bool bit(BufType bitmap, int pos) {
    return bitmap[pos >> 5] & (1 << (pos & 31));
}

void set(BufType bitmap, int pos) {
    bitmap[pos >> 5] |=  (1 << (pos & 31));
}

void reset(BufType bitmap, int pos) {
    bitmap[pos >> 5] &=  ~(1 << (pos & 31));
}

int firstIdle(BufType bitmap, uint size) {
    for (uint i = 0; i < size; ++i) {
        if (!bit(bitmap, i)) return i;
    }
    return -1;
}

class RM_FileHandle {
    FileManager *fm;
    BufPageManager *bpm;
    int fID;
    File_Header header;

public:
    RM_FileHandle (FileManager *_fm, BufPageManager *_bpm, int _fID): fm(_fm), bpm(_bpm), fID(_fID) {
        int idx;
        BufType b = bpm->getPage(fID, 0, idx);
        memcpy(&header, b, sizeof(File_Header));
        bpm->access(idx);
    }

    ~RM_FileHandle () {

    }

    bool GetRec (const RID &rid, BufType data) const {
        int idx;
        BufType page = bpm->getPage(fID, rid.page, idx);
        bpm->access(idx);
        if (!bit(page + 2, rid.slot)) return false;
        memcpy(data, page + 2 + ((header.bitmapSize + rid.slot * header.recordSize) >> 2), header.recordSize);
        return true;
    }

    bool InsertRec (const BufType Rec, RID &rid) {
        int idx;
        rid.page = header.firstFreePage;
        BufType page = bpm->getPage(fID, rid.page, idx);
        if (page[0] == 0) {
            page[0] = rid.page + 1;
        }
        rid.slot = firstIdle(page + 2, (header.bitmapSize << 3));
        memcpy(page + 2 + ((header.bitmapSize + rid.slot * header.recordSize) >> 2), Rec, header.recordSize);
        set(page + 2, rid.slot);
        if (++(page[1]) == header.recordPerPage)
            header.firstFreePage = page[0];
        bpm->markDirty(idx);
        page = bpm->getPage(fID, 0, idx);
        memcpy(page, &header, sizeof(File_Header));
        bpm->markDirty(idx);
        return true;
    }

    bool DeleteRec (const RID &rid) {
        int idx;
        BufType page = bpm->getPage(fID, rid.page, idx);
        reset(page + 2, rid.slot);
        bpm->markDirty(idx);
        if ((page[1])-- == header.recordPerPage) {
            page[0] = header.firstFreePage;
            header.firstFreePage = rid.page;
        }
        BufType head = bpm->getPage(fID, 0, idx);
        memcpy(head, &head, sizeof(File_Header));
        bpm->markDirty(idx);
        return true;
    }

    bool UpdateRec (const RID &rid, const BufType Rec) {
        int idx;
        BufType page = bpm->getPage(fID, rid.page, idx);
        memcpy(page + 2 + header.bitmapSize / 4 + rid.slot * header.recordSize / 4, Rec, header.recordSize);
        bpm->markDirty(idx);
        return true;
    }

};
