
%option noyywrap
%option caseless
%{
#define YYSTYPE TokenVal
#include "bison.tab.h"

#include "structs.h"
#include <iostream>
using namespace std;
%}

VALUE_STRING '[^']*'
IDENTIFIER [A-Za-z][_0-9A-Za-z]*

VALUE_INT [0-9]+
VALUE_FLOAT (-?[0-9]+)(\.[0-9]+)?
%%
{VALUE_INT} { 
    // yylval.intval = atoi(yytext); return VALUE_INT;
    // cout << "lex " << yytext << endl;
    yylval.type = VALUE; yylval.val.isNull = false; yylval.val.type = INTEGER; yylval.val.i = atoi(yytext); return VALUE_INT; 
    }
{VALUE_FLOAT} { 
    // yylval.floatval = atof(yytext); return VALUE_FLOAT;
    yylval.type = VALUE; yylval.val.isNull = false; yylval.val.type = FLOAT_T; yylval.val.f = atof(yytext); return VALUE_FLOAT; 
    }
{VALUE_STRING} { 
    // yylval.strval = yytext; return VALUE_STRING;
    yylval.type = VALUE; yylval.val.isNull = false; yylval.val.type = STRING; yylval.val.s = yytext; return VALUE_STRING; 
    }
[';'] { return SEP; }
['.,*()'] { return yytext[0]; }
[\n \t] {} 
">=" { yylval.type = OP; yylval.op = GE_OP; return GE; }
"<=" { yylval.type = OP; yylval.op = LE_OP; return LE; }
"<>" { yylval.type = OP; yylval.op = NE_OP; return NE; }
">" { yylval.type = OP; yylval.op = GT_OP; return GT; }
"<" { yylval.type = OP; yylval.op = LT_OP; return LT; }
"=" { yylval.type = OP; yylval.op = EQ_OP; return EQ; }

EXIT {return EXIT;}
DATABASE {return DATABASE;}
DATABASES {return DATABASES;}
TABLE {return TABLE;}
TABLES {return TABLES;}
SHOW {return SHOW;}
CREATE {return CREATE;}
DROP {return DROP;}
USE {return USE;}
PRIMARY {return PRIMARY;}
KEY {return KEY;}
NOT {return NOT;}
NULL {return NULL_TOKEN;}
INSERT {return INSERT;}
INTO {return INTO;}
VALUES {return VALUES;}
DELETE {return DELETE;}
FROM {return FROM;}
WHERE {return WHERE;}
UPDATE {return UPDATE;}
SET {return SET;}
SELECT {return SELECT;}
IS {return IS;}
INT {return INT;}
VARCHAR {return VARCHAR;}
DEFAULT {return DEFAULT;}
CONSTRAINT {return CONSTRAINT;}
CHANGE {return CHANGE;}
ALTER {return ALTER;}
ADD {return ADD;}
RENAME {return RENAME;}
DESC {return DESC;}
INDEX {return INDEX;}
AND {return AND;}
DATE {return DATE;}
FLOAT {return FLOAT;}
FOREIGN {return FOREIGN;}
REFERENCES {return REFERENCES;}
ON {return ON;}
TO {return TO;}
{IDENTIFIER} { 
    // yylval.strval = yytext; return IDENTIFIER;
    yylval.type = ID; yylval.s = yytext; return IDENTIFIER; 
    }
%%
