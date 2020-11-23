#include "RM_FileHandle.h"
#include "RM_Manager.h"
#include <iostream>
using namespace std;

int main() {
	FileManager fm;
	BufPageManager bpm(&fm);
	RM_Manager rm(&fm, &bpm);
	rm.CreateFile("1.txt", 4);
	int fID;
	rm.OpenFile("1.txt", fID);
	RM_FileHandle fh(&fm, &bpm, fID);
	RID rid;
	BufType Rec = new uint[1];
	Rec[0] = 12729;
	fh.InsertRec(Rec, rid);
	fh.InsertRec(Rec, rid);
	fh.InsertRec(Rec, rid);
	fh.InsertRec(Rec, rid);

	BufType ret = new uint[1];
	fh.GetRec(rid, ret);
	cout << ret[0] << endl;
	rm.DestroyFile("1.txt");
}
