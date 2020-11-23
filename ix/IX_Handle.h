#include "ix.h"
#include <algorithm>

class IX_Handle
{
    FileManager *fm;
    BufPageManager *bpm;
    int fID;
    File_Header header;
public:
    IX_Handle(FileManager *_fm, BufPageManager *_bpm, int _fID): fm(_fm), bpm(_bpm), fID(_fID) {
        int index;
        BufType buf = bpm->getPage(fID, 0, index);
        memcpy(&header, buf, sizeof(File_Header));
    }

    ~IX_Handle() {

    }

    bool InsertEntry(void *pdata, const RID &rid) {
        uint id = header.root;
        while (true) {
            int index;
            BufType page = bpm->getPage(fID, id, index);
            bpm->access(index);
            Page_Header curheader;
            memcpy(&curheader, page, sizeof(Page_Header));
            if (curheader.isLeaf) {
                Leaf leaf = make_leaf(page);
                if (header.attrType == INTEGER) {
                    int* start = (int*)(leaf.attr);
                    int data = *((int*)(pdata));
                    auto l = lower_bound(start, start + curheader.eleNum, data);
                    memmove(l + 1, l, (curheader.eleNum - (l - start)) * sizeof(int));
                    *l = data;
                } else if (header.attrType == FLOAT) {
                    float* start = (float*)(leaf.attr);
                    float data = *((float*)(pdata));
                    auto l = lower_bound(start, start + curheader.eleNum, data);
                    memmove(l + 1, l, (curheader.eleNum - (l - start)) * sizeof(float));
                    *l = data;
                }
                //STRING
                cout << id << " is a leaf." << endl;
                cout << header.capacity << endl;
                ++curheader.eleNum;
                while (curheader.eleNum == header.capacity + 1) {
                    cout << "overflow" << endl;
                    int parent = curheader.parent;
                    BufType parentPage;
                    Internal p;
                    if (parent == 0) {
                        //root
                        parent = header.nodeNum++;
                        curheader.parent = parent;
                        header.root = parent;
                        parentPage = bpm->getPage(fID, parent, index);
                        Page_Header ph;
                        ph.parent = 0;
                        ph.isLeaf = false;
                        ph.eleNum = 1;
                        memcpy(parentPage, &ph, sizeof(Page_Header));
                        Internal internal = make_internal(parentPage);
                        internal.child[0] = id;
                        BufType motoattr = curheader.isLeaf ? (page + sizeof(Page_Header) / sizeof(uint) + 2 * (header.capacity + 1)) : (page + sizeof(Page_Header) / sizeof(uint) + header.order + 1);
                        memcpy(internal.attr, motoattr, header.attrLen);
                        p = make_internal(parentPage);
                    } else {
                        //not root
                        parentPage = bpm->getPage(fID, parent, index);
                        p = make_internal(parentPage);
                    }
                    int n = 0;
                    for (; n < p.ph.eleNum; ) {
                        if (p.child[n] == id) {
                            break;
                        }
                        ++n;
                    }
                    for (int i = p.ph.eleNum; i > n; --i) {
                        p.child[i] = p.child[i - 1];
                        memcpy((char*)p.attr + (i - 1) * header.attrLen, (char*)p.attr + (i - 1) * header.attrLen, header.attrLen);
                    }
                    int newNode = header.nodeNum++;
                    p.child[n + 1] = newNode;
                    p.ph.eleNum++;
                    memcpy(parentPage, &p.ph, sizeof(Page_Header));

                    BufType newPage = bpm->getPage(fID, newNode, index);
                    if (curheader.isLeaf) {
                        Leaf news = make_leaf(newPage);
                        news.ph.isLeaf = true;
                        news.ph.eleNum = curheader.eleNum - curheader.eleNum / 2;
                        news.ph.parent = curheader.parent;
                        curheader.eleNum /= 2;
                        Leaf origin = make_leaf(page);
                        memcpy(news.attr, origin.attr, news.ph.eleNum * header.attrLen);
                        memcpy(news.page, origin.page, sizeof(uint) * news.ph.eleNum);
                        memcpy(news.slot, origin.slot, sizeof(uint) * news.ph.eleNum);
                        news.ph.next = origin.ph.next;
                        if (origin.ph.next != 0) {
                            BufType tmp = bpm->getPage(fID, origin.ph.next, index);
                            Leaf nex = make_leaf(tmp);
                            nex.ph.prev = newNode;
                            memcmp(tmp, &(nex.ph), sizeof(Page_Header));
                        }
                        origin.ph.next = newNode;
                    } else {
                        Internal news = make_internal(newPage);
                        news.ph.isLeaf = false;
                        news.ph.eleNum = curheader.eleNum - curheader.eleNum / 2;
                        news.ph.parent = curheader.parent;
                        curheader.eleNum /= 2;
                        Internal origin = make_internal(page);
                        memcpy(news.attr, origin.attr, news.ph.eleNum * header.attrLen);
                        memcpy(news.child, origin.child, sizeof(uint) * (news.ph.eleNum + 1));
                        for (int i = 0; i < news.ph.eleNum; ++i) {
                            BufType c = bpm->getPage(fID, news.child[i], index);
                            Page_Header ph;
                            memcpy(&ph, c, sizeof(Page_Header));
                            ph.parent = newNode;
                            memcpy(c, &ph, sizeof(Page_Header));
                        }
                    }
                    id = parent;
                    BufType b = bpm->getPage(fID, id, index);
                    memcpy(&curheader, b, sizeof(Page_Header));
                }
                BufType buf = bpm->getPage(fID, 0, index);
                memcpy(buf, &header, sizeof(File_Header));
                bpm->markDirty(index);
            } else {
                Internal internal;
                internal.child = page + sizeof(Page_Header) / sizeof(uint);
                internal.attr = internal.child + header.order + 1;
                if (header.attrType == INTEGER) {
                    int* start = (int*)(internal.attr);
                    int data = *((int*)(pdata));
                    auto l = lower_bound(start, start + curheader.eleNum, data);
                    id = internal.child[l - start];
                } else if (header.attrType == FLOAT) {
                    float* start = (float*)(internal.attr);
                    float data = *((float*)(pdata));
                    auto l = lower_bound(start, start + curheader.eleNum, data);
                    id = internal.child[l - start];
                }
            }
            break;
        }
        return true;
    }

    bool DeleteEntry(void *pdata, const RID &rid) {
        int id = header.root;
        while (true) {
            int index;
            BufType page = bpm->getPage(fID, id, index);
            Page_Header curheader;
            memcpy(&curheader, page, sizeof(Page_Header));
            if (curheader.isLeaf) {
                Leaf leaf = make_leaf(page);
                if (header.attrType == INTEGER) {
                    int* start = (int*)(leaf.attr);
                    int data = *((int*)(pdata));
                    auto l = lower_bound(start, start + curheader.eleNum, data);
                    memmove(l, l + 1, (curheader.eleNum - (l - start)) * sizeof(int));
                } else if (header.attrType == FLOAT) {
                    float* start = (float*)(leaf.attr);
                    float data = *((float*)(pdata));
                    auto l = lower_bound(start, start + curheader.eleNum, data);
                    memmove(l, l + 1, (curheader.eleNum - (l - start)) * sizeof(float));
                }
                curheader.eleNum--;
                if (curheader.eleNum == 0) {
                    int pre = curheader.prev;
                    int nex = curheader.next;
                    if (pre) {
                        BufType b = bpm->getPage(fID, pre, index);
                        Leaf p = make_leaf(b);
                        p.ph.next = curheader.next;
                        memcpy(b, &(p.ph), sizeof(Page_Header));
                    }
                    if (nex) {
                        BufType b = bpm->getPage(fID, nex, index);
                        Leaf n = make_leaf(b);
                        n.ph.prev = curheader.prev;
                        memcpy(b, &(n.ph), sizeof(Page_Header));
                    }
                }
                while (curheader.eleNum == 0) {
                    int parent = curheader.parent;
                    BufType page = bpm->getPage(fID, parent, index);
                    Page_Header ph;
                    memcpy(&ph, page, sizeof(Page_Header));
                    Internal inter = make_internal(page);
                    int n = 0;
                    for (; n < inter.ph.eleNum; ) {
                        if (inter.child[n] == id) {
                            break;
                        }
                        ++n;
                    }
                    memmove((char*)inter.child + n + 1, (char*)inter.child + n + 2, inter.ph.eleNum - n);
                    memmove((char*)inter.attr + n, (char*)inter.attr + n + 1, inter.ph.eleNum - n);
                    inter.ph.eleNum--;
                    id = parent;
                    BufType b = bpm->getPage(fID, id, index);
                    memcpy(&curheader, b, sizeof(Page_Header));
                }
            } else {
                Internal internal;
                internal.child = page + sizeof(Page_Header) / sizeof(uint);
                internal.attr = internal.child + header.order + 1;
                if (header.attrType == INTEGER) {
                    int* start = (int*)(internal.attr);
                    int data = *((int*)(pdata));
                    auto l = lower_bound(start, start + curheader.eleNum, data);
                    id = internal.child[l - start];
                } else if (header.attrType == FLOAT) {
                    float* start = (float*)(internal.attr);
                    float data = *((float*)(pdata));
                    auto l = lower_bound(start, start + curheader.eleNum, data);
                    id = internal.child[l - start];
                }
            }
        }
        return true;
    }

    Leaf make_leaf(BufType page) {
        Leaf ret;
        memcpy(&(ret.ph), page, sizeof(Page_Header));
        ret.page = page + sizeof(Page_Header) / sizeof(uint);
        ret.slot = ret.page + header.capacity + 1;
        ret.attr = ret.slot + header.capacity + 1;
        return ret;
    }

    Internal make_internal(BufType page) {
        Internal ret;
        memcpy(&(ret.ph), page, sizeof(Page_Header));
        ret.child = page + sizeof(Page_Header) / sizeof(uint);
        ret.attr = ret.child + header.order + 1;
        return ret;
    }
};
