#pragma once
#include <algorithm>

#include "IX.h"

#define INTERNAL 5
#define LEAF 5

class IX_Handle {
    FileManager *fm;
    BufPageManager *bpm;
    int fID;
    IX_File_Header header;
    Internal internals[INTERNAL];
    bool inter_used[INTERNAL];
    Leaf leafs[LEAF];
    bool leaf_used[LEAF];

    Internal *make_internal(BufType page) {
        Internal *ret = nullptr;
        for (int i = 0; i < INTERNAL; ++i) {
            if (!inter_used[i]) {
                ret = internals + i;
                ret->ph = (Page_Header *)page;
                // memcpy(&(ret->ph), page, sizeof(Page_Header));
                ret->child = page + sizeof(Page_Header) / sizeof(uint);
                ret->attr = ret->child + header.order + 2;
                inter_used[i] = true;
                break;
            }
        }
        if (!ret) cout << "fail to alloc internal" << endl;
        return ret;
    }

    void release_internal(Internal *internal) {
        for (int i = 0; i < INTERNAL; ++i) {
            if (internals + i == internal) {
                inter_used[i] = false;
                return;
            }
        }
        return;
    }

    Leaf *make_leaf(BufType page) {
        Leaf *ret = nullptr;
        for (int i = 0; i < LEAF; ++i) {
            if (!leaf_used[i]) {
                ret = leafs + i;
                ret->ph = (Page_Header *)page;
                ret->page = page + sizeof(Page_Header) / sizeof(uint);
                ret->slot = ret->page + header.capacity + 1;
                ret->attr = ret->slot + header.capacity + 1;
                leaf_used[i] = true;
                break;
            }
        }
        if (!ret) cout << "fail to alloc leaf" << endl;
        return ret;
    }

    void release_leaf(Leaf *leaf) {
        for (int i = 0; i < LEAF; ++i) {
            if (leafs + i == leaf) {
                leaf_used[i] = false;
                return;
            }
        }
        return;
    }

    void write_back_file_header() {
        int index;
        BufType h = bpm->getPage(fID, 0, index);
        memcpy(h, &header, sizeof(IX_File_Header));
        bpm->markDirty(index);
    }

   public:
    IX_Handle(FileManager *_fm, BufPageManager *_bpm, int _fID)
        : fm(_fm), bpm(_bpm), fID(_fID) {
        memset(inter_used, 0, sizeof(bool) * 3);
        memset(leaf_used, 0, sizeof(bool) * 2);
        int index;
        BufType buf = bpm->getPage(fID, 0, index);
        // header = (File_Header *)buf;
        memcpy(&header, buf, sizeof(IX_File_Header));
    }

    ~IX_Handle() {}

    bool InsertEntry(const void *pdata, const RID &rid) {
        // cout << "inserting " << rid.page << endl;
        uint id = header.root;
        Page_Header *curheader;
        BufType page;
        int index;
        while (true) {
            page = bpm->getPage(fID, id, index);
            curheader = (Page_Header *)page;
            bpm->access(index);
            if (curheader->isLeaf) {
                bpm->markDirty(index);
                // cout << "via leaf " << id << endl;
                Leaf *leaf = make_leaf(page);
                if (header.attrType == INTEGER) {
                    int *attr_start = (int *)(leaf->attr);
                    int data = *((int *)(pdata));
                    int i = lower_bound(attr_start,
                                        attr_start + curheader->eleNum, data) -
                            attr_start;
                    memmove(attr_start + i + 1, attr_start + i,
                            (curheader->eleNum - i) * header.attrLen);
                    attr_start[i] = data;
                    BufType page_start = leaf->page, slot_start = leaf->slot;
                    memmove(page_start + i + 1, page_start + i,
                            (curheader->eleNum - i) * sizeof(uint));
                    page_start[i] = rid.page;
                    memmove(slot_start + i + 1, slot_start + i,
                            (curheader->eleNum - i) * sizeof(uint));
                    slot_start[i] = rid.slot;
                    // for (int i = 0; i < curheader->eleNum + 1; ++i)
                    // {
                    //     // cout << attr_start[i] << ' ';
                    // }
                    // // cout << endl;
                } else if (header.attrType == FLOAT_T) {
                    float *attr_start = (float *)(leaf->attr);
                    float data = *((float *)(pdata));
                    int i = lower_bound(attr_start,
                                        attr_start + curheader->eleNum, data) -
                            attr_start;
                    memmove(attr_start + i + 1, attr_start + i,
                            (curheader->eleNum - i) * header.attrLen);
                    attr_start[i] = data;
                    BufType page_start = leaf->page, slot_start = leaf->slot;
                    memmove(page_start + i + 1, page_start + i,
                            (curheader->eleNum - i) * sizeof(uint));
                    page_start[i] = rid.page;
                    memmove(slot_start + i + 1, slot_start + i,
                            (curheader->eleNum - i) * sizeof(uint));
                    slot_start[i] = rid.slot;
                } else if (header.attrType == STRING) {
                    char *attr_start = (char *)(leaf->attr);
                    string data((char *)pdata, header.attrLen);
                    vector<string> strs;
                    for (int i = 0; i < curheader->eleNum; ++i) {
                        strs.push_back(string(attr_start + i * header.attrLen,
                                              header.attrLen));
                    }
                    int i = lower_bound(strs.begin(), strs.end(), data) -
                            strs.begin();
                    memmove(attr_start + (i + 1) * header.attrLen,
                            attr_start + i * header.attrLen,
                            (curheader->eleNum - i) * header.attrLen);
                    memcpy(attr_start + i * header.attrLen, data.c_str(),
                           header.attrLen);
                    BufType page_start = leaf->page, slot_start = leaf->slot;
                    memmove(page_start + i + 1, page_start + i,
                            (curheader->eleNum - i) * sizeof(uint));
                    page_start[i] = rid.page;
                    memmove(slot_start + i + 1, slot_start + i,
                            (curheader->eleNum - i) * sizeof(uint));
                    slot_start[i] = rid.slot;
                }
                ++curheader->eleNum;
                release_leaf(leaf);
                while ((curheader->isLeaf &&
                        curheader->eleNum == header.capacity + 1) ||
                       (!curheader->isLeaf &&
                        curheader->eleNum == header.order + 1)) {
                    // cout << id << " overflow" << endl;
                    // page = bpm->getPage(fID, id, index);
                    bpm->markDirty(index);
                    int parentId = curheader->parent;
                    BufType parentPage;
                    Internal *parent;
                    if (parentId == 0) {
                        // root overflow
                        parentId = ++header.lastPage;
                        write_back_file_header();
                        // cout << "new root " << parentId << endl;
                        curheader->parent = parentId;
                        header.root = parentId;
                        parentPage = bpm->getPage(fID, parentId, index);
                        Page_Header *ph = (Page_Header *)parentPage;
                        ph->next = ph->prev = 0;
                        ph->parent = 0;
                        ph->isLeaf = false;
                        ph->eleNum = 0;
                        parent = make_internal(parentPage);
                        parent->child[0] = id;
                        bpm->access(index);
                        bpm->markDirty(index);
                    } else {
                        // not root
                        parentPage = bpm->getPage(fID, parentId, index);
                        parent = make_internal(parentPage);
                        bpm->markDirty(index);
                    }
                    uint n = 0;
                    while (parent->child[n] != id && n <= parent->ph->eleNum)
                        ++n;
                    memmove(parent->child + n + 2, parent->child + n + 1,
                            (parent->ph->eleNum - n) * sizeof(uint));
                    memmove((char *)parent->attr + header.attrLen * (n + 1),
                            (char *)parent->attr + header.attrLen * n,
                            header.attrLen * (parent->ph->eleNum - n));
                    int splitId = ++header.lastPage;
                    write_back_file_header();
                    parent->child[n + 1] = splitId;
                    ++parent->ph->eleNum;
                    BufType splitPage = bpm->getPage(fID, splitId, index);
                    bpm->markDirty(index);
                    if (curheader->isLeaf) {
                        // cout << "leaf split " << id << " and " << splitId
                        // << endl;
                        Leaf *news = make_leaf(splitPage);
                        Leaf *origin = make_leaf(page);
                        news->ph->isLeaf = true;
                        news->ph->eleNum =
                            curheader->eleNum - (curheader->eleNum >> 1);
                        news->ph->parent = curheader->parent;
                        curheader->eleNum >>= 1;
                        // cout << "src " << endl;
                        // for (int i = 0; i < curheader->eleNum; ++i) {
                        //     // cout << ((int *)origin->attr)[i] << ' ';
                        // }
                        // cout << endl;

                        memcpy((char *)(parent->attr) + n * header.attrLen,
                               (char *)(origin->attr) +
                                   (curheader->eleNum - 1) * header.attrLen,
                               header.attrLen);
                        release_internal(parent);
                        memcpy(news->attr,
                               (char *)origin->attr +
                                   header.attrLen * (curheader->eleNum),
                               news->ph->eleNum * header.attrLen);
                        memcpy(news->page, origin->page + curheader->eleNum,
                               sizeof(uint) * news->ph->eleNum);
                        memcpy(news->slot, origin->slot + curheader->eleNum,
                               sizeof(uint) * news->ph->eleNum);
                        // cout << "dst " << endl;
                        for (int i = 0; i < news->ph->eleNum; ++i) {
                            // cout << ((int *)news->attr)[i] << ' ';
                        }
                        // cout << endl;
                        news->ph->next = origin->ph->next;
                        news->ph->prev = id;
                        // int *tmp = (int *)origin->attr;
                        // tmp = (int *)news->attr;
                        if (origin->ph->next != 0) {
                            BufType tmp =
                                bpm->getPage(fID, origin->ph->next, index);
                            bpm->markDirty(index);
                            Leaf *nex = make_leaf(tmp);
                            nex->ph->prev = splitId;
                            bpm->markDirty(index);
                            release_leaf(nex);
                        }
                        origin->ph->next = splitId;
                        release_leaf(news);
                        release_leaf(origin);
                    } else {
                        // cout << "internal split " << id << " and " <<
                        // splitId
                        // << endl;
                        Internal *news = make_internal(splitPage);
                        Internal *origin = make_internal(page);
                        news->ph->isLeaf = false;
                        news->ph->eleNum =
                            curheader->eleNum - (curheader->eleNum >> 1) - 1;
                        news->ph->parent = curheader->parent;
                        curheader->eleNum >>= 1;
                        // cout << "src " << endl;
                        // for (int i = 0; i < curheader->eleNum; ++i) {
                        //     // cout << ((int *)origin->attr)[i] << ' ';
                        // }
                        // // cout << endl;
                        // for (int i = 0; i <= curheader->eleNum; ++i) {
                        //     // cout << origin->child[i] << ' ';
                        // }
                        // cout << endl;
                        memcpy((char *)(parent->attr) + n * header.attrLen,
                               (char *)(origin->attr) +
                                   (curheader->eleNum) * header.attrLen,
                               header.attrLen);
                        release_internal(parent);
                        memcpy(news->attr,
                               (char *)origin->attr +
                                   header.attrLen * (curheader->eleNum + 1),
                               news->ph->eleNum * header.attrLen);
                        memcpy(news->child,
                               origin->child + curheader->eleNum + 1,
                               sizeof(uint) * (news->ph->eleNum + 1));
                        // cout << "dst " << endl;
                        // for (int i = 0; i < news->ph->eleNum; ++i) {
                        //     // cout << ((int *)news->attr)[i] << ' ';
                        // }
                        // // cout << endl;
                        // for (int i = 0; i <= news->ph->eleNum; ++i) {
                        //     // cout << news->child[i] << ' ';
                        // }
                        // cout << endl;
                        for (int i = 0; i <= news->ph->eleNum; ++i) {
                            Page_Header *ph = (Page_Header *)bpm->getPage(
                                fID, news->child[i], index);
                            bpm->markDirty(index);
                            ph->parent = splitId;
                        }
                        release_internal(news);
                        release_internal(origin);
                    }
                    id = parentId;
                    page = bpm->getPage(fID, id, index);
                    curheader = (Page_Header *)page;
                }
                write_back_file_header();
                break;
            } else {
                // cout << "via internal " << id << " with " <<
                // curheader->eleNum << " elements" << endl;
                Internal *internal = make_internal(page);
                if (header.attrType == INTEGER) {
                    int *start = (int *)(internal->attr);
                    int data = *((int *)(pdata));
                    auto l =
                        lower_bound(start, start + curheader->eleNum, data);
                    // for (int i = 0; i < curheader->eleNum; ++i)
                    // {
                    //     // cout << start[i] << ' ';
                    // }
                    // // cout << endl;
                    // for (int i = 0; i < curheader->eleNum + 1; ++i)
                    // cout << internal->child[i] << ' ';
                    // cout << endl;
                    id = internal->child[l - start];
                } else if (header.attrType == FLOAT_T) {
                    float *start = (float *)(internal->attr);
                    float data = *((float *)(pdata));
                    auto l =
                        lower_bound(start, start + curheader->eleNum, data);
                    id = internal->child[l - start];
                } else if (header.attrType == STRING) {
                    char *attr_start = (char *)(internal->attr);
                    string data((char *)pdata, header.attrLen);
                    vector<string> strs;
                    for (int i = 0; i < curheader->eleNum; ++i) {
                        strs.push_back(string(attr_start + i * header.attrLen,
                                              header.attrLen));
                    }
                    int i = lower_bound(strs.begin(), strs.end(), data) -
                            strs.begin();
                    id = internal->child[i];
                }
                release_internal(internal);
            }
        }
        // cout << "finished inserting " << rid.page << endl
        //  << endl;
        return true;
    }

    bool DeleteEntry(void *pdata, const RID &rid) {
        bool ret = false;
        // cout << "deleting " << *(int *)(pdata) << endl;
        uint id = header.root;
        while (true) {
            int index;
            BufType page = bpm->getPage(fID, id, index);
            Page_Header *curheader;
            // memcpy(&curheader, page, sizeof(Page_Header));
            curheader = (Page_Header *)page;
            if (curheader->isLeaf) {
                // cout << id << " is a leaf" << endl;
                Leaf *leaf = make_leaf(page);
                // cout << "via leaf " << id << " with " <<
                // curheader->eleNum << " elements" << endl;
                if (header.attrType == INTEGER) {
                    int *start = (int *)(leaf->attr);
                    for (int i = 0; i < curheader->eleNum; ++i) {
                        // cout << start[i] << ' ';
                    }
                    // cout << endl;
                    int data = *((int *)(pdata));
                    auto i =
                        lower_bound(start, start + curheader->eleNum, data) -
                        start;
                    if (i < curheader->eleNum && start[i] == data &&
                        leaf->page[i] == rid.page &&
                        leaf->slot[i] == rid.slot) {
                        // cout << "found " << start[i] << " at " << i << "
                        // in leaf " << id << endl;
                        memmove(start + i, start + i + 1,
                                (curheader->eleNum - i - 1) * sizeof(int));
                        memmove(leaf->page + i, leaf->page + i + 1,
                                (curheader->eleNum - i - 1) * sizeof(uint));
                        memmove(leaf->slot + i, leaf->slot + i + 1,
                                (curheader->eleNum - i - 1) * sizeof(uint));
                        bpm->markDirty(index);
                        ret = true;
                    }
                } else if (header.attrType == FLOAT_T) {
                    float *start = (float *)(leaf->attr);
                    float data = *((float *)(pdata));
                    auto i =
                        lower_bound(start, start + curheader->eleNum, data) -
                        start;
                    if (i < curheader->eleNum && start[i] == data &&
                        leaf->page[i] == rid.page &&
                        leaf->slot[i] == rid.slot) {
                        memmove(start + i, start + i + 1,
                                (curheader->eleNum - i - 1) * sizeof(float));
                        memmove(leaf->page + i, leaf->page + i + 1,
                                (curheader->eleNum - i - 1) * sizeof(uint));
                        memmove(leaf->slot + i, leaf->slot + i + 1,
                                (curheader->eleNum - i - 1) * sizeof(uint));
                        bpm->markDirty(index);
                        ret = true;
                    }
                } else if (header.attrType == STRING) {
                    char *start = (char *)(leaf->attr);
                    string data((char *)pdata, header.attrLen);
                    vector<string> strs;
                    for (int i = 0; i < curheader->eleNum; ++i) {
                        strs.push_back(
                            string(start + i * header.attrLen, header.attrLen));
                    }
                    int i = lower_bound(strs.begin(), strs.end(), data) -
                            strs.begin();
                    if (i < curheader->eleNum &&
                        strncmp(start + i * header.attrLen, data.c_str(),
                                header.attrLen) == 0 &&
                        leaf->page[i] == rid.page &&
                        leaf->slot[i] == rid.slot) {
                        memmove(start + i * header.attrLen,
                                start + (i + 1) * header.attrLen,
                                (curheader->eleNum - i - 1) * header.attrLen);
                        memmove(leaf->page + i, leaf->page + i + 1,
                                (curheader->eleNum - i - 1) * sizeof(uint));
                        memmove(leaf->slot + i, leaf->slot + i + 1,
                                (curheader->eleNum - i - 1) * sizeof(uint));
                        bpm->markDirty(index);
                        ret = true;
                    }
                }
                release_leaf(leaf);
                curheader->eleNum--;
                if (curheader->eleNum == 0) {
                    // cout << "node " << id << " is empty" << endl;
                    int pre = curheader->prev;
                    int nex = curheader->next;
                    if (pre) {
                        BufType b = bpm->getPage(fID, pre, index);
                        Page_Header *h = (Page_Header *)b;
                        h->next = curheader->next;
                        bpm->markDirty(index);
                    }
                    if (nex) {
                        BufType b = bpm->getPage(fID, nex, index);
                        Page_Header *h = (Page_Header *)b;
                        h->prev = curheader->prev;
                        bpm->markDirty(index);
                    }
                    // curheader = (Page_Header *)bpm->getPage(fID,
                    // curheader->parent, index);
                }
                while (curheader->eleNum == 0) {
                    // cout << "node " << id << " is empty" << endl;
                    int parentId = curheader->parent;
                    BufType parentPage = bpm->getPage(fID, parentId, index);
                    Internal *parent = make_internal(parentPage);
                    bpm->markDirty(index);
                    uint n = 0;
                    while (parent->child[n] != id && n <= parent->ph->eleNum)
                        ++n;
                    if (curheader->isLeaf) {
                        uint attr_to_delete = n == parent->ph->eleNum
                                                  ? parent->ph->eleNum - 1
                                                  : n;
                        memmove(parent->child + n, parent->child + n + 1,
                                (parent->ph->eleNum - n) * sizeof(uint));
                        memmove((char *)parent->attr +
                                    attr_to_delete * header.attrLen,
                                (char *)parent->attr +
                                    (attr_to_delete + 1) * header.attrLen,
                                (parent->ph->eleNum - attr_to_delete - 1) *
                                    header.attrLen);
                        --parent->ph->eleNum;
                    } else {
                        parent->child[n] = id;
                    }
                    release_internal(parent);
                    id = parentId;
                    curheader = (Page_Header *)bpm->getPage(fID, id, index);
                }
                // cout << "finished deleting " << *(int *)(pdata) << endl;
                return ret;
            } else {
                // cout << "via internal " << id << " with " <<
                // curheader->eleNum << " elements" << endl;
                Internal *internal = make_internal(page);
                int *tmp = (int *)internal->attr;
                // for (int i = 0; i < curheader->eleNum; ++i)
                // {
                //     // cout << tmp[i] << ' ';
                // }
                // // cout << endl;
                // for (int i = 0; i <= curheader->eleNum; ++i)
                // {
                //     // cout << internal->child[i] << ' ';
                // }
                // cout << endl;
                if (header.attrType == INTEGER) {
                    int *start = (int *)(internal->attr);
                    int data = *((int *)(pdata));
                    auto l =
                        lower_bound(start, start + curheader->eleNum, data);
                    id = internal->child[l - start];
                } else if (header.attrType == FLOAT_T) {
                    float *start = (float *)(internal->attr);
                    float data = *((float *)(pdata));
                    auto l =
                        lower_bound(start, start + curheader->eleNum, data);
                    id = internal->child[l - start];
                } else if (header.attrType == STRING) {
                    char *start = (char *)(internal->attr);
                    string data((char *)pdata, header.attrLen);
                    vector<string> strs;
                    for (int i = 0; i < curheader->eleNum; ++i) {
                        strs.push_back(
                            string(start + i * header.attrLen, header.attrLen));
                    }
                    int i = lower_bound(strs.begin(), strs.end(), data) -
                            strs.begin();
                    id = internal->child[i];
                }
                // cout << "go " << id << endl;
                release_internal(internal);
            }
        }
        // cout << "finished deleting " << *(int *)(pdata) << endl;
        return ret;
    }

    bool SearchEntry(void *pdata, RID &rid) {
        uint id = header.root;
        int index;
        BufType page = bpm->getPage(fID, id, index);
        Page_Header *curheader = (Page_Header *)page;
        while (!curheader->isLeaf) {
            Internal *internal = make_internal(page);
            if (header.attrType == INTEGER) {
                int *attr_start = (int *)(internal->attr);
                int data = *((int *)(pdata));
                int i = lower_bound(attr_start, attr_start + curheader->eleNum,
                                    data) -
                        attr_start;
                id = internal->child[i];
            } else if (header.attrType == FLOAT_T) {
                float *attr_start = (float *)(internal->attr);
                float data = *((float *)(pdata));
                int i = lower_bound(attr_start, attr_start + curheader->eleNum,
                                    data) -
                        attr_start;
                id = internal->child[i];
            } else if (header.attrType == STRING) {
                char *start = (char *)(internal->attr);
                string data((char *)pdata, header.attrLen);
                vector<string> strs;
                for (int i = 0; i < curheader->eleNum; ++i) {
                    strs.push_back(
                        string(start + i * header.attrLen, header.attrLen));
                }
                int i =
                    lower_bound(strs.begin(), strs.end(), data) - strs.begin();
                id = internal->child[i];
            }
            release_internal(internal);
            page = bpm->getPage(fID, id, index);
            curheader = (Page_Header *)page;
        }
        Leaf *leaf = make_leaf(page);
        if (header.attrType == INTEGER) {
            int *attr_start = (int *)(leaf->attr);
            int data = *((int *)(pdata));
            int i =
                lower_bound(attr_start, attr_start + curheader->eleNum, data) -
                attr_start;
            if (i < curheader->eleNum && data == attr_start[i]) {
                rid.page = leaf->page[i];
                rid.slot = leaf->slot[i];
                release_leaf(leaf);
                return true;
            }
        } else if (header.attrType == FLOAT_T) {
            float *attr_start = (float *)(leaf->attr);
            float data = *((float *)(pdata));
            int i =
                lower_bound(attr_start, attr_start + curheader->eleNum, data) -
                attr_start;
            if (i < curheader->eleNum && data == attr_start[i]) {
                rid.page = leaf->page[i];
                rid.slot = leaf->slot[i];
                release_leaf(leaf);
                return true;
            }
        } else if (header.attrType == STRING) {
            char *attr_start = (char *)(leaf->attr);
            string data((char *)pdata, header.attrLen);
            vector<string> strs;
            for (int i = 0; i < curheader->eleNum; ++i) {
                strs.push_back(
                    string(attr_start + i * header.attrLen, header.attrLen));
            }
            int i = lower_bound(strs.begin(), strs.end(), data) - strs.begin();
            if (i < curheader->eleNum &&
                strncmp(data.c_str(), attr_start + i * header.attrLen,
                        header.attrLen) == 0) {
                rid.page = leaf->page[i];
                rid.slot = leaf->slot[i];
                release_leaf(leaf);
                return true;
            }
        }
        release_leaf(leaf);
        return false;
    }
};
