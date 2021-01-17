#pragma once
#include "RM.h"

inline bool getBit(BufType bitmap, int pos) {
    return bitmap[pos >> 5] & (1 << (pos & 31));
}

inline void setBit(BufType bitmap, int pos) {
    bitmap[pos >> 5] |= (1 << (pos & 31));
}

inline void resetBit(BufType bitmap, int pos) {
    bitmap[pos >> 5] &= ~(1 << (pos & 31));
}

inline int firstIdle(BufType bitmap, uint size) {
    for (uint i = 0; i < size; ++i) {
        if (!getBit(bitmap, i)) return i;
    }
    return -1;
}

class RM_FileHandle {
    FileManager *fm;
    BufPageManager *bpm;

   public:
    RM_File_Header header;
    int fID;
    RM_FileHandle(FileManager *_fm, BufPageManager *_bpm, int _fID)
        : fm(_fm), bpm(_bpm), fID(_fID) {
        int idx;
        BufType b = bpm->getPage(fID, 0, idx);
        memcpy(&header, b, sizeof(RM_File_Header));
    }

    ~RM_FileHandle() {}

    bool GetRec(const RID &rid, BufType data) const {
        int idx;
        BufType page = bpm->getPage(fID, rid.page, idx);
        bpm->access(idx);
        if (!getBit(page + 2, rid.slot)) return false;
        memcpy(
            data,
            (char *)page + 8 + header.bitmapSize + rid.slot * header.recordSize,
            header.recordSize);
        return true;
    }

    bool InsertRec(const BufType Rec, RID &rid) {
        int idx;
        rid.page = header.firstFreePage;
        BufType page = bpm->getPage(fID, rid.page, idx);
        if (rid.page > header.pageNum) {
            assert(rid.page == header.pageNum + 1);
            memset(page, 0, PAGE_SIZE);
            page[0] = rid.page + 1;
            ++header.pageNum;
        }
        rid.slot = firstIdle(page + 2, (header.bitmapSize << 3));
        memcpy(
            (char *)page + 8 + header.bitmapSize + rid.slot * header.recordSize,
            Rec, header.recordSize);
        setBit(page + 2, rid.slot);
        if (++(page[1]) == header.recordPerPage) header.firstFreePage = page[0];
        bpm->markDirty(idx);
        page = bpm->getPage(fID, 0, idx);
        memcpy(page, &header, sizeof(RM_File_Header));
        bpm->markDirty(idx);
        return true;
    }

    bool DeleteRec(const RID &rid) {
        int idx;
        BufType page = bpm->getPage(fID, rid.page, idx);
        if (!getBit(page + 2, rid.slot)) return false;
        resetBit(page + 2, rid.slot);
        bpm->markDirty(idx);
        --(page[1]);
        if (page[1] == 0) {
            if (rid.page == header.pageNum) {
                cout << "delete last page" << endl;
                memset(page, 0, PAGE_SIZE);
            } else if (rid.page < header.pageNum) {
                BufType tail = bpm->getPage(fID, header.pageNum, idx);
                bpm->markDirty(idx);
                memcpy(page, tail, PAGE_SIZE);
                page[0] = header.pageNum;
                cout << "swap tail and " << rid.page << endl;
                cout << header.pageNum << endl;
            }
            --header.pageNum;
        }
        if ((page[1]) == header.recordPerPage - 1) {
            page[0] = header.firstFreePage;
            header.firstFreePage = rid.page;
            // cout << "first changed to " << header.firstFreePage << endl;
        }
        BufType head = bpm->getPage(fID, 0, idx);
        memcpy(head, &header, sizeof(RM_File_Header));
        bpm->markDirty(idx);
        return true;
    }

    bool UpdateRec(const RID &rid, const BufType Rec) {
        int idx;
        BufType page = bpm->getPage(fID, rid.page, idx);
        memcpy(
            (char *)page + 8 + header.bitmapSize + rid.slot * header.recordSize,
            Rec, header.recordSize);
        bpm->markDirty(idx);
        return true;
    }
};
