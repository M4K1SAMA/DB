#pragma once
#include "../def.h"
#include "RM_FileHandle.h"

class RM_Scan {
   private:
    FileManager *fm;
    BufPageManager *bpm;
    RM_FileHandle *fh;
    RID pos;
    int attrOffset;
    int attrIndex;
    AttrType attrType;
    int length;
    CompOp op;
    void *value;

   public:
    RM_Scan(FileManager *_fm, BufPageManager *_bpm) : fm(_fm), bpm(_bpm) {}
    ~RM_Scan() {}

    bool OpenScan(RM_FileHandle *_fh) {
        fh = _fh;
        pos.page = 1;
        pos.slot = 0;
        op = NO_OP;
        return true;
    }

    bool OpenScan(RM_FileHandle *_fh, int _attrOffset, int _attrIndex,
                  AttrType _attrType, int _length, CompOp _op, void *_value) {
        fh = _fh;
        pos.page = 1;
        pos.slot = 0;
        attrOffset = _attrOffset;
        attrIndex = _attrIndex;
        attrType = _attrType;
        length = _length;
        op = _op;
        value = _value;
        return true;
    }

    bool GetNextRec(void *data, RID &rid) {
        int idx;
        BufType buf = bpm->getPage(fh->fID, pos.page, idx);
        // cout << "size " << fh->header.pageNum << endl;
        // while (true) {
        while ((!getBit(buf + 2, pos.slot) || !Check(data, pos)) &&
               pos.page <= fh->header.pageNum) {
            if ((pos.page == fh->header.pageNum &&
                 pos.slot == fh->header.recordPerPage - 1)) {
                return false;
            }
            if (pos.slot == fh->header.recordPerPage - 1) {
                ++pos.page;
                buf = bpm->getPage(fh->fID, pos.page, idx);
                pos.slot = 0;
            } else {
                ++pos.slot;
            }
        }
        if (pos.page > fh->header.pageNum) return false;
        rid.page = pos.page;
        rid.slot = pos.slot;
        fh->GetRec(rid, (BufType)data);
        // if (!Check(data)) {
        //     // cout << "invalid" << endl;
        //     continue;
        // } else {
        if (pos.slot == fh->header.recordPerPage - 1) {
            ++pos.page;
            buf = bpm->getPage(fh->fID, pos.page, idx);
            pos.slot = 0;
        } else {
            ++pos.slot;
        }
        return true;
    }
    // }

    //     return true;
    // }

    bool Check(void *buf, RID rid) {
        fh->GetRec(rid, (BufType)buf);
        char *d = (char *)buf + attrOffset;
        switch (op) {
            case EQ_OP:
                switch (attrType) {
                    case INTEGER:
                        return *((int *)d) == *((int *)value);
                    case FLOAT_T:
                        return *((float *)d) == *((float *)value);
                    case STRING:
                        return strncmp(d, (char *)value, length) == 0;
                }
            case LT_OP:
                switch (attrType) {
                    case INTEGER:
                        return *((int *)d) < *((int *)value);
                    case FLOAT_T:
                        return *((float *)d) < *((float *)value);
                    case STRING:
                        return strncmp(d, (char *)value, length) < 0;
                }
            case GT_OP:
                switch (attrType) {
                    case INTEGER:
                        return *((int *)d) > *((int *)value);
                    case FLOAT_T:
                        return *((float *)d) > *((float *)value);
                    case STRING:
                        return strncmp(d, (char *)value, length) > 0;
                }
            case LE_OP:
                switch (attrType) {
                    case INTEGER:
                        return *((int *)d) <= *((int *)value);
                    case FLOAT_T:
                        return *((float *)d) <= *((float *)value);
                    case STRING:
                        return strncmp(d, (char *)value, length) <= 0;
                }
            case GE_OP:
                switch (attrType) {
                    case INTEGER:
                        return *((int *)d) >= *((int *)value);
                    case FLOAT_T:
                        return *((float *)d) >= *((float *)value);
                    case STRING:
                        return strncmp(d, (char *)value, length) >= 0;
                }
            case NE_OP:
                switch (attrType) {
                    case INTEGER:
                        return *((int *)d) != *((int *)value);
                    case FLOAT_T:
                        return *((float *)d) != *((float *)value);
                    case STRING:
                        return strncmp(d, (char *)value, length) != 0;
                }
            case NO_OP:
                return true;
        }
    }
};
