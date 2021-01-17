

#include "../def.h"
#include "../ix/IX_Handle.h"
#include "../ix/IX_Manager.h"
#include "../rm/RM_FileHandle.h"
#include "../rm/RM_Manager.h"
#include "../rm/RM_Scan.h"
#include "QL_Manager.h"

extern int yylex();
extern int yyparse();
QL_Manager* ql;

int main() {
    FileManager* fm = new FileManager();
    BufPageManager* bpm = new BufPageManager(fm);
    RM_Manager* rmm = new RM_Manager(fm, bpm);
    IX_Manager* ixm = new IX_Manager(fm, bpm);
    SM_Manager* smm = new SM_Manager(rmm, ixm, bpm, fm);
    ql = new QL_Manager(smm);
    int token;
    while (token = yyparse()) {
    }
}
