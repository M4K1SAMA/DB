#include "IX_Handle.h"
#include "IX_Manager.h"


int main() {
    FileManager fm;
    BufPageManager bpm(&fm);
    IX_Manager im(&fm, &bpm);
    im.CreateIndex("1", 1, INTEGER, 4);
    int fID;
    im.OpenIndex("1", 1, fID);
    IX_Handle ih(&fm, &bpm, fID);
    int data = 114514;
    RID rid;
    rid.page = 1;
    rid.slot = 0;
    ih.InsertEntry(&data, rid);
    
}
