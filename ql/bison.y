%{
        // #define YYSTYPE Val
        #include "structs.h"
        #include <iostream>
        // #include "../def.h"
        // #include "../ix/IX_Handle.h"
        // #include "../ix/IX_Manager.h"
        // #include "../rm/RM_FileHandle.h"
        // #include "../rm/RM_Manager.h"
        // #include "../rm/RM_Scan.h"
        #include "QL_Manager.h"
        using namespace std;
        
        extern int yylex();
        QL_Manager* qlm;
        SM_Manager *smm;
        void yyerror(const char *s) { cout << s << endl; }
%}

%token DATABASE	DATABASES	TABLE	TABLES	SHOW	CREATE
DROP	USE	PRIMARY	KEY	NOT	NULL_TOKEN
INSERT	INTO	VALUES	DELETE	FROM	WHERE
UPDATE	SET	SELECT	IS	INT	VARCHAR
DEFAULT	CONSTRAINT	CHANGE	ALTER	ADD	RENAME
DESC       	INDEX	AND	DATE         	FLOAT	FOREIGN
REFERENCES       	ON	TO      SEP     EXIT
%token EQ
%token LT 
%token LE 
%token GT
%token GE 
%token NE  
%token VALUE_FLOAT
%token VALUE_INT
%token VALUE_STRING
%token IDENTIFIER


%start program
%%

program : stmts;
        ;

stmts : stmt SEP
        | stmts stmt SEP;

stmt : sysStmt
        | dbStmt
        | tbStmt
        | idxStmt
        | alterStmt
        | EXIT {
                smm->Exit();
        }
;

sysStmt : SHOW DATABASES {
                smm->ShowDBs();
        }

dbStmt  : CREATE DATABASE dbName {
                smm->CreateDB($3.s);
        }
        | DROP DATABASE dbName { 
                smm->DropDB($3.s);
        }
        | USE dbName { 
                smm->UseDB($2.s);
        }
        | SHOW TABLES { 
                smm->ShowTables();
        };

tbStmt  : CREATE TABLE tbName '('fieldList')' {
                TableInfo tableInfo;
                tableInfo.name = $3.s;
                tableInfo.attrNum = $5.attrList.size();
                tableInfo.foreignNum = tableInfo.recordSize = tableInfo.primarySize = 0;
                tableInfo.attrs = $5.attrList;

                smm->CreateTable(tableInfo);
        }
        | DROP TABLE tbName {
                smm->DropTable($3.s);
        }
        | DESC tbName { 
                smm->Desc($2.s); 
        }
        | INSERT INTO tbName VALUES valueLists {
                // cout << "insert " << endl;
                qlm->Insert($3.s, $5.valLists);
                // cout << "insert finish" << endl;
        }
        | DELETE FROM tbName WHERE whereList {
                qlm->Delete($3.s, $5.whereList);
        }
        | UPDATE tbName SET setClause WHERE whereList {
                qlm->Update($2.s, $4.setList, $6.whereList);
        }
        | SELECT selector FROM tableList WHERE whereList {
                qlm->Select($2.selector, $4.stringList, $6.whereList);
        }
        | SELECT selector FROM tableList {
                qlm->Select($2.selector, $4.stringList, vector<Where>());
        }
;

idxStmt : CREATE INDEX idxName ON tbName '(' columnList ')' {
                // smm->CreateIndex($5.s, $7.stringList);
        }
        | DROP INDEX idxName {
                // smm->DropIndex($3.s);
        }
        | ALTER TABLE tbName ADD INDEX idxName'('columnList')' {
                smm->CreateIndex($3.s, $6.s, $8.stringList);
        }
        | ALTER TABLE tbName DROP INDEX idxName {
                smm->DropIndex($3.s, $6.s);
        }
;

alterStmt : ALTER TABLE tbName ADD field {
                if ($5.type == PRIM) {
                        smm->AddPrimary($3.s, $5.stringList);
                } else if ($5.type == FIELD) {
                        smm->AddColumn($3.s, $5.attr);
                }
        }
        | ALTER TABLE tbName DROP colName {
                smm->DropColumn($3.s, $5.s);
        }
        | ALTER TABLE tbName CHANGE colName field {

        }
        | ALTER TABLE tbName RENAME TO tbName {
                smm->Rename($3.s, $6.s);
        }
        | ALTER TABLE tbName DROP PRIMARY KEY {
                smm->DropPrimary($3.s);
        }
        | ALTER TABLE tbName ADD CONSTRAINT pkName PRIMARY KEY'('columnList')' {
                smm->AddPrimary($3.s, $10.stringList);
        }
        | ALTER TABLE tbName DROP PRIMARY KEY pkName {
                smm->DropPrimary($3.s);
        }
        | ALTER TABLE tbName ADD CONSTRAINT fkName FOREIGN KEY '('columnList')' REFERENCES tbName'('columnList')'
        | ALTER TABLE tbName DROP FOREIGN KEY fkName
;

fieldList  : field {
                $$.type = FIELD_LIST;
                $$.attrList.push_back($1.attr);
        }
        | fieldList','field {
                $$.type = FIELD_LIST;
                $$.attrList = $1.attrList;
                if ($3.type == PRIM) {
                        for (auto &attr: $$.attrList) {
                                if(find($3.stringList.begin(), $3.stringList.end(), attr.name) != $3.stringList.end()) {
                                        attr.primary = true;
                                }
                        }
                } else if ($3.type == FOR) {
                        
                } else {
                        $$.attrList.push_back($3.attr);
                }
        }
        ;

field  : colName type {
                $$ = $2;
                $$.type = FIELD;
                $$.attr.name = $1.s;
                $$.attr.notNull = $$.attr.primary = $$.attr.foreign = $$.attr.def = false;
        }
        | colName type NOT NULL_TOKEN {
                $$ = $2;
                $$.type = FIELD;
                $$.attr.name = $1.s;
                $$.attr.notNull = true;
                $$.attr.primary = $$.attr.foreign = $$.attr.def = false;
        }
        | colName type DEFAULT value {
                $$ = $2;
                $$.type = FIELD;
                $$.attr.name = $1.s;
                $$.attr.notNull = $$.attr.primary = $$.attr.foreign = false;
                $$.attr.def = true;
                if ($$.attr.type == INTEGER) {
                        $$.attr.defint = (int)$4.val.i;
                } else if ($2.attr.type == FLOAT_T) {
                        $$.attr.deffloat = (double)$4.val.f;
                } else if ($2.attr.type == STRING) {
                        $$.attr.defstring = $4.val.s;
                }
        }
        | colName type NOT NULL_TOKEN DEFAULT value {
                $$ = $2;
                $$.type = FIELD;
                $$.attr.name = $1.s;
                $$.attr.notNull = true;
                $$.attr.primary = $$.attr.foreign = false;
                $$.attr.def = true;
                if ($$.attr.type == INTEGER) {
                        $$.attr.defint = (int)$6.val.i;
                } else if ($2.attr.type == FLOAT_T) {
                        $$.attr.deffloat = (double)$6.val.f;
                } else if ($2.attr.type == STRING) {
                        $$.attr.defstring = $6.val.s;
                }
        }
        | PRIMARY KEY '('columnList')' {
                $$.type = PRIM;
                $$.stringList = $4.stringList;
        }
        | FOREIGN KEY '('colName')' REFERENCES tbName'('colName')' {
                $$.type = FOR;
                $$.s = $4.s;
                $$.col.tab = $7.s;
                $$.col.attr = $9.s;
        }
;

type  : INT { 
                $$.attr.type = INTEGER;
        }
        | VARCHAR '('VALUE_INT')' { 
                $$.attr.type = STRING; 
                $$.attr.length = $3.val.i;
        }
        | DATE { 
                $$.attr.type = STRING; 
                $$.attr.length = 10;
        }
        | FLOAT { 
                $$.attr.type = FLOAT_T; 
        }
;

valueLists  : '('valueList')' {
                $$.valLists.push_back($2.valList);
        }
        | valueLists',' '('valueList')' {
                $$ = $1;
                $$.valLists.push_back($4.valList);
        }
;

valueList  : value {
                $$.valList.push_back($1.val);
        }
        | valueList',' value {
                $$ = $1;
                $$.valList.push_back($3.val);
        }
;

value  : VALUE_INT      {
                $$.val.isNull = false;
                $$.val.type = INTEGER;
                $$.val.i = $1.val.i;
                // $$ = $1;
                // cout << "INT " << $1.i << endl;
        }
	| VALUE_FLOAT   { 
                $$.val.isNull = false;
                $$.val.type = FLOAT_T;
                $$.val.f = $1.val.f;
                // $$ = $1;
                // cout << "FLOAT " << $1.f << endl;
        }
        | VALUE_STRING  { 
                $$.val.isNull = false;
                $$.val.type = STRING;
                $$.val.s = $1.val.s.substr(1, $1.val.s.length() - 2);
                // $$ = $1;
                // cout << "STRING " << $1.s << endl;
                }
        | NULL_TOKEN    { 
                $$.val.isNull = true;
                // $$ = $1;
                // cout << "NULL" << endl; 
        }
;

whereClause  : col op expr {
                $$.where.col = $1.col;
                $$.where.op = $2.op;
                $$.where.expr = $3.expr;
        }
        | col IS NULL_TOKEN {
                $$.where.col = $1.col;
                $$.where.op = EQ_OP;
                $$.where.expr.isVal = true;
                $$.where.expr.val.isNull = true;
        }
        | col IS NOT NULL_TOKEN {
                $$.where.col = $1.col;
                $$.where.op = NE_OP;
                $$.where.expr.isVal = true;
                $$.where.expr.val.isNull = true;
        }
;

whereList : whereList AND whereClause {
                $$.whereList = $1.whereList;
                $$.whereList.push_back($3.where);
        }
        | whereClause {
                $$.whereList.push_back($1.where);
        }
;

col : colName {
                $$.col.tab = "";
                $$.col.attr = $1.s;
        }
        |tbName'.'colName {
                $$.col.tab = $1.s;
                $$.col.attr = $3.s;
        }
;

op  : EQ  { 
        $$ = $1;
        }
    | NE { 
        $$ = $1;
        }
    | LE { 
        $$ = $1;
        }
    | GE { 
        $$ = $1;
        }
    | LT  { 
        $$ = $1;
        }
    | GT  { 
        $$ = $1;
        }
;

expr  :  value {
                $$.expr.isVal = true;
                $$.expr.val = $1.val;
        }
        | col {
                $$.expr.isVal = false;
                $$.expr.col = $1.col;
        }
;

setClause  : colName EQ value {
                Set tmp;
                tmp.col.attr = $1.s;
                tmp.val = $3.val;
                $$.setList.push_back(tmp);
        }
        | setClause',' colName EQ value {
                Set tmp;
                tmp.col.attr = $3.s;
                tmp.val = $5.val;
                $$.setList = $1.setList;
                $$.setList.push_back(tmp);
        }
;

selector  : '*' {
                $$.selector.all = true;
        }
        | colList {
                $$.selector.all = false;
                $$.selector.cols = $1.colList;
        }
;

colList : col {
                $$.colList.push_back($1.col);
        }
        | colList ',' col {
                $$ = $1;
                $$.colList.push_back($3.col);
        }
;

tableList  : tbName {
                $$.stringList.push_back($1.s);
        }
        | tableList','tbName {
                $$ = $1;
                $$.stringList.push_back($3.s);
        }
;

columnList  : colName {
                $$.stringList.push_back($1.s);
        }
        | columnList','colName {
                $$ = $1;
                $$.stringList.push_back($3.s);
        }
;

dbName  : IDENTIFIER { 
        $$ = $1; 
        }
;

tbName  : IDENTIFIER { 
        $$ = $1; 
        }
;

colName : IDENTIFIER { 
        $$ = $1; 
        }
;

fkName : IDENTIFIER { 
        $$ = $1; 
        }
;

pkName : IDENTIFIER { 
        $$ = $1; 
        }
;

idxName : IDENTIFIER { 
        $$ = $1; 
        }
;

%%

int main() {
        MyBitMap::initConst();
        FileManager* fm = new FileManager();
        BufPageManager* bpm = new BufPageManager(fm);
        RM_Manager* rmm = new RM_Manager(fm, bpm);
        IX_Manager* ixm = new IX_Manager(fm, bpm);
        smm = new SM_Manager(rmm, ixm, bpm, fm);
        qlm = new QL_Manager(smm);
        int token;
        while(yyparse())
        bpm->close();
}
