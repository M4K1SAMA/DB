#include <iostream>

#include "RM_FileHandle.h"
#include "RM_Manager.h"
#include "RM_Scan.h"
using namespace std;

int main() {
    FileManager fm;
    BufPageManager bpm(&fm);
    RM_Manager rm(&fm, &bpm);
    rm.CreateFile("a", 4);
    int fID;
    rm.OpenFile("a", fID);
    RM_FileHandle fh(&fm, &bpm, fID);

    RID rid;
    BufType Rec = new uint[1];
    Rec[0] = 100;
    int inserts = 100000;
    while (inserts--) {
        int i = 10 - inserts - 1;
        fh.InsertRec(Rec, rid);
        cout << Rec[0] << ' ' << rid.page << ' ' << rid.slot << endl;
    }
    rm.CloseFile(fID);
    bpm.close();
    // rm.OpenFile("a", fID);
    // RM_FileHandle rfh(&fm, &bpm, fID);
    // RM_Scan scanner(&fm, &bpm);
    // scanner.OpenScan(&rfh);
    // int *data = new int;
    // while (scanner.GetNextRec(data, rid)) {
    //     cout << data[0] << ' ' << rid.slot << endl;
    // }

    // cout << fh.header.pageNum << endl;
    // for (int i = 0; i < 1984; ++i) {
    //     RID rid = {2, i};
    //     fh.DeleteRec(rid);
    // }
    // for (int i = 0; i < 1984; ++i) {
    //     RID rid = {2, i};
    //     fh.DeleteRec(rid);
    // }
    // for (int i = 0; i < 1000; ++i) {
    //     Rec[0] = 114514810;
    //     fh.InsertRec(Rec, rid);
    //     // cout << rid.page << ' ' << rid.slot << endl;
    // }
    // cout << fh.header.pageNum << endl;
    // scanner.OpenScan(&fh);

    // BufType buf = new uint[1];
    // while (scanner.GetNextRec(buf, rid)) {
    //     cout << buf[0] << ' ' << rid.page << ' ' << rid.slot << endl;
    // }
    // rm.DestroyFile("1.txt");
}
