/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     DATABASE = 258,
     DATABASES = 259,
     TABLE = 260,
     TABLES = 261,
     SHOW = 262,
     CREATE = 263,
     DROP = 264,
     USE = 265,
     PRIMARY = 266,
     KEY = 267,
     NOT = 268,
     NULL_TOKEN = 269,
     INSERT = 270,
     INTO = 271,
     VALUES = 272,
     DELETE = 273,
     FROM = 274,
     WHERE = 275,
     UPDATE = 276,
     SET = 277,
     SELECT = 278,
     IS = 279,
     INT = 280,
     VARCHAR = 281,
     DEFAULT = 282,
     CONSTRAINT = 283,
     CHANGE = 284,
     ALTER = 285,
     ADD = 286,
     RENAME = 287,
     DESC = 288,
     INDEX = 289,
     AND = 290,
     DATE = 291,
     FLOAT = 292,
     FOREIGN = 293,
     REFERENCES = 294,
     ON = 295,
     TO = 296,
     SEP = 297,
     EXIT = 298,
     EQ = 299,
     LT = 300,
     LE = 301,
     GT = 302,
     GE = 303,
     NE = 304,
     VALUE_FLOAT = 305,
     VALUE_INT = 306,
     VALUE_STRING = 307,
     IDENTIFIER = 308
   };
#endif
/* Tokens.  */
#define DATABASE 258
#define DATABASES 259
#define TABLE 260
#define TABLES 261
#define SHOW 262
#define CREATE 263
#define DROP 264
#define USE 265
#define PRIMARY 266
#define KEY 267
#define NOT 268
#define NULL_TOKEN 269
#define INSERT 270
#define INTO 271
#define VALUES 272
#define DELETE 273
#define FROM 274
#define WHERE 275
#define UPDATE 276
#define SET 277
#define SELECT 278
#define IS 279
#define INT 280
#define VARCHAR 281
#define DEFAULT 282
#define CONSTRAINT 283
#define CHANGE 284
#define ALTER 285
#define ADD 286
#define RENAME 287
#define DESC 288
#define INDEX 289
#define AND 290
#define DATE 291
#define FLOAT 292
#define FOREIGN 293
#define REFERENCES 294
#define ON 295
#define TO 296
#define SEP 297
#define EXIT 298
#define EQ 299
#define LT 300
#define LE 301
#define GT 302
#define GE 303
#define NE 304
#define VALUE_FLOAT 305
#define VALUE_INT 306
#define VALUE_STRING 307
#define IDENTIFIER 308




/* Copy the first part of user declarations.  */
#line 1 "bison.y"

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


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif

#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 216 of yacc.c.  */
#line 231 "bison.tab.c"

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int i)
#else
static int
YYID (i)
    int i;
#endif
{
  return i;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  43
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   202

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  59
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  87
/* YYNRULES -- Number of states.  */
#define YYNSTATES  204

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   308

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      54,    55,    58,     2,    56,     2,    57,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     8,    12,    14,    16,    18,    20,
      22,    24,    27,    31,    35,    38,    41,    48,    52,    55,
      61,    67,    74,    81,    86,    95,    99,   109,   116,   122,
     128,   135,   142,   149,   161,   169,   186,   194,   196,   200,
     203,   208,   213,   220,   226,   237,   239,   244,   246,   248,
     252,   258,   260,   264,   266,   268,   270,   272,   276,   280,
     285,   289,   291,   293,   297,   299,   301,   303,   305,   307,
     309,   311,   313,   317,   323,   325,   327,   329,   333,   335,
     339,   341,   345,   347,   349,   351,   353,   355
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      60,     0,    -1,    61,    -1,    62,    42,    -1,    61,    62,
      42,    -1,    63,    -1,    64,    -1,    65,    -1,    66,    -1,
      67,    -1,    43,    -1,     7,     4,    -1,     8,     3,    84,
      -1,     9,     3,    84,    -1,    10,    84,    -1,     7,     6,
      -1,     8,     5,    85,    54,    68,    55,    -1,     9,     5,
      85,    -1,    33,    85,    -1,    15,    16,    85,    17,    71,
      -1,    18,    19,    85,    20,    75,    -1,    21,    85,    22,
      79,    20,    75,    -1,    23,    80,    19,    82,    20,    75,
      -1,    23,    80,    19,    82,    -1,     8,    34,    89,    40,
      85,    54,    83,    55,    -1,     9,    34,    89,    -1,    30,
       5,    85,    31,    34,    89,    54,    83,    55,    -1,    30,
       5,    85,     9,    34,    89,    -1,    30,     5,    85,    31,
      69,    -1,    30,     5,    85,     9,    86,    -1,    30,     5,
      85,    29,    86,    69,    -1,    30,     5,    85,    32,    41,
      85,    -1,    30,     5,    85,     9,    11,    12,    -1,    30,
       5,    85,    31,    28,    88,    11,    12,    54,    83,    55,
      -1,    30,     5,    85,     9,    11,    12,    88,    -1,    30,
       5,    85,    31,    28,    87,    38,    12,    54,    83,    55,
      39,    85,    54,    83,    55,    -1,    30,     5,    85,     9,
      38,    12,    87,    -1,    69,    -1,    68,    56,    69,    -1,
      86,    70,    -1,    86,    70,    13,    14,    -1,    86,    70,
      27,    73,    -1,    86,    70,    13,    14,    27,    73,    -1,
      11,    12,    54,    83,    55,    -1,    38,    12,    54,    86,
      55,    39,    85,    54,    86,    55,    -1,    25,    -1,    26,
      54,    51,    55,    -1,    36,    -1,    37,    -1,    54,    72,
      55,    -1,    71,    56,    54,    72,    55,    -1,    73,    -1,
      72,    56,    73,    -1,    51,    -1,    50,    -1,    52,    -1,
      14,    -1,    76,    77,    78,    -1,    76,    24,    14,    -1,
      76,    24,    13,    14,    -1,    75,    35,    74,    -1,    74,
      -1,    86,    -1,    85,    57,    86,    -1,    44,    -1,    49,
      -1,    46,    -1,    48,    -1,    45,    -1,    47,    -1,    73,
      -1,    76,    -1,    86,    44,    73,    -1,    79,    56,    86,
      44,    73,    -1,    58,    -1,    81,    -1,    76,    -1,    81,
      56,    76,    -1,    85,    -1,    82,    56,    85,    -1,    86,
      -1,    83,    56,    86,    -1,    53,    -1,    53,    -1,    53,
      -1,    53,    -1,    53,    -1,    53,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    42,    42,    45,    46,    48,    49,    50,    51,    52,
      53,    58,    62,    65,    68,    71,    75,    84,    87,    90,
      95,    98,   101,   104,   109,   112,   115,   118,   123,   130,
     133,   136,   139,   142,   145,   148,   149,   152,   156,   173,
     179,   186,   200,   215,   219,   227,   230,   234,   238,   243,
     246,   252,   255,   261,   268,   275,   282,   289,   294,   300,
     308,   312,   317,   321,   327,   330,   333,   336,   339,   342,
     347,   351,   357,   363,   372,   375,   381,   384,   390,   393,
     399,   402,   408,   413,   418,   423,   428,   433
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "DATABASE", "DATABASES", "TABLE",
  "TABLES", "SHOW", "CREATE", "DROP", "USE", "PRIMARY", "KEY", "NOT",
  "NULL_TOKEN", "INSERT", "INTO", "VALUES", "DELETE", "FROM", "WHERE",
  "UPDATE", "SET", "SELECT", "IS", "INT", "VARCHAR", "DEFAULT",
  "CONSTRAINT", "CHANGE", "ALTER", "ADD", "RENAME", "DESC", "INDEX", "AND",
  "DATE", "FLOAT", "FOREIGN", "REFERENCES", "ON", "TO", "SEP", "EXIT",
  "EQ", "LT", "LE", "GT", "GE", "NE", "VALUE_FLOAT", "VALUE_INT",
  "VALUE_STRING", "IDENTIFIER", "'('", "')'", "','", "'.'", "'*'",
  "$accept", "program", "stmts", "stmt", "sysStmt", "dbStmt", "tbStmt",
  "idxStmt", "alterStmt", "fieldList", "field", "type", "valueLists",
  "valueList", "value", "whereClause", "whereList", "col", "op", "expr",
  "setClause", "selector", "colList", "tableList", "columnList", "dbName",
  "tbName", "colName", "fkName", "pkName", "idxName", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,    40,    41,    44,    46,    42
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    59,    60,    61,    61,    62,    62,    62,    62,    62,
      62,    63,    64,    64,    64,    64,    65,    65,    65,    65,
      65,    65,    65,    65,    66,    66,    66,    66,    67,    67,
      67,    67,    67,    67,    67,    67,    67,    68,    68,    69,
      69,    69,    69,    69,    69,    70,    70,    70,    70,    71,
      71,    72,    72,    73,    73,    73,    73,    74,    74,    74,
      75,    75,    76,    76,    77,    77,    77,    77,    77,    77,
      78,    78,    79,    79,    80,    80,    81,    81,    82,    82,
      83,    83,    84,    85,    86,    87,    88,    89
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     3,     1,     1,     1,     1,     1,
       1,     2,     3,     3,     2,     2,     6,     3,     2,     5,
       5,     6,     6,     4,     8,     3,     9,     6,     5,     5,
       6,     6,     6,    11,     7,    16,     7,     1,     3,     2,
       4,     4,     6,     5,    10,     1,     4,     1,     1,     3,
       5,     1,     3,     1,     1,     1,     1,     3,     3,     4,
       3,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     5,     1,     1,     1,     3,     1,     3,
       1,     3,     1,     1,     1,     1,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    10,     0,     2,     0,     5,     6,     7,     8,     9,
      11,    15,     0,     0,     0,     0,     0,     0,    82,    14,
       0,     0,    83,     0,    84,    74,    76,     0,    75,     0,
      62,     0,    18,     1,     0,     3,    12,     0,    87,     0,
      13,    17,    25,     0,     0,     0,     0,     0,     0,     0,
       4,     0,     0,     0,     0,    84,     0,     0,    23,    78,
      77,    63,     0,     0,     0,     0,     0,     0,     0,    37,
       0,     0,     0,    19,    61,    20,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    29,     0,     0,     0,    28,
       0,     0,     0,    16,     0,    45,     0,    47,    48,    39,
       0,    56,    54,    53,    55,     0,    51,     0,     0,     0,
      64,    68,    66,    69,    67,    65,     0,    21,     0,    72,
      22,    79,    32,    27,     0,    30,    85,     0,     0,     0,
      31,     0,     0,    38,     0,     0,     0,     0,    80,    49,
       0,     0,    60,     0,    58,    70,    71,    57,     0,    86,
      34,    85,    36,     0,     0,     0,     0,     0,     0,    40,
      41,    24,     0,    52,     0,    59,    73,     0,     0,     0,
      43,     0,    46,     0,    81,    50,     0,     0,    26,     0,
      42,     0,     0,     0,     0,    33,     0,     0,     0,     0,
      44,     0,     0,    35
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    12,    13,    14,    15,    16,    17,    18,    19,    78,
      79,   109,    83,   115,   116,    84,    85,    86,   126,   157,
      66,    37,    38,    68,   147,    29,    39,    40,   137,   138,
      49
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -134
static const yytype_int16 yypact[] =
{
      79,    65,     2,    87,   -39,    15,     3,   -18,   -40,    51,
     -18,  -134,    70,    79,    38,  -134,  -134,  -134,  -134,  -134,
    -134,  -134,   -39,   -18,    32,   -39,   -18,    32,  -134,  -134,
     -18,   -18,  -134,    77,    44,  -134,  -134,    89,    54,    85,
    -134,   -18,  -134,  -134,    97,  -134,  -134,    71,  -134,    95,
    -134,  -134,  -134,   121,   125,   103,   -18,   104,   103,    82,
    -134,     6,   -18,    94,   104,  -134,   -10,   105,     1,  -134,
    -134,  -134,    -5,   103,     9,   117,   147,   148,   -16,  -134,
      80,   107,    31,   106,  -134,   128,    83,   104,   103,    31,
     104,   -18,   152,    32,   153,  -134,     6,   113,    32,  -134,
     -18,   114,   115,  -134,     6,  -134,   116,  -134,  -134,    -2,
     103,  -134,  -134,  -134,  -134,    23,  -134,   118,   104,    90,
    -134,  -134,  -134,  -134,  -134,  -134,    24,   128,   123,  -134,
     128,  -134,   120,  -134,   122,  -134,   160,   136,   165,   124,
    -134,   103,   103,  -134,   126,   166,    31,    68,  -134,  -134,
      31,    31,  -134,   167,  -134,  -134,  -134,  -134,    31,  -134,
    -134,  -134,  -134,   171,   172,   103,    78,   130,   131,   161,
    -134,  -134,   103,  -134,    81,  -134,  -134,   133,   135,    88,
    -134,   140,  -134,    31,  -134,  -134,   103,   103,  -134,   -18,
    -134,    91,    96,   137,   154,  -134,   103,   -18,   139,   138,
    -134,   103,    98,  -134
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -134,  -134,  -134,   182,  -134,  -134,  -134,  -134,  -134,  -134,
     -44,  -134,  -134,    45,   -85,    84,   -24,    -6,  -134,  -134,
    -134,  -134,  -134,  -134,  -133,    93,    -7,   -46,    63,    66,
     -26
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -87
static const yytype_int16 yytable[] =
{
      33,    52,    36,    42,   129,    22,    92,    23,   166,    67,
      87,   145,    71,    34,    28,    80,    47,    76,    35,    51,
      76,    90,    31,    53,    54,   146,    95,    96,    80,    93,
      99,    30,   179,    94,    59,    32,    24,    97,   111,   103,
     104,   155,   128,    98,    77,   111,    88,    77,    65,    69,
      80,    70,   135,   191,   192,    81,    41,    91,    80,    65,
     143,   170,    65,   127,   148,   173,   130,   133,   202,    20,
      43,    21,   139,   176,   112,   113,   114,    34,   149,   150,
      45,   112,   113,   114,   131,    48,     1,     2,     3,     4,
      25,    72,    26,   140,     5,   148,   167,     6,   190,    55,
       7,   -83,     8,   153,   154,   105,   106,   119,    56,     9,
      57,    73,    10,    74,    75,    46,   107,   108,    50,   148,
     156,    27,    11,   171,   172,    61,   184,   120,   121,   122,
     123,   124,   125,   180,   172,    62,   185,   150,    63,    60,
     148,   148,    58,   188,   172,    64,   194,   172,    82,    89,
     198,   195,   172,   203,   172,   148,    65,    34,   100,   101,
     102,   110,   117,   118,   132,   134,   136,   158,   141,   142,
     144,   -86,   151,   159,   163,   161,   164,   168,   165,   189,
     169,   175,   193,   177,   178,   181,   182,   186,   183,   187,
     199,   196,   201,   197,   200,    44,   174,   162,   160,     0,
       0,     0,   152
};

static const yytype_int16 yycheck[] =
{
       7,    27,     8,    10,    89,     3,    11,     5,   141,    55,
      20,    13,    58,    53,    53,    61,    23,    11,    58,    26,
      11,    20,    19,    30,    31,    27,    72,    73,    74,    34,
      74,    16,   165,    38,    41,    53,    34,    28,    14,    55,
      56,   126,    88,    34,    38,    14,    56,    38,    53,    56,
      96,    57,    96,   186,   187,    62,     5,    56,   104,    53,
     104,   146,    53,    87,   110,   150,    90,    93,   201,     4,
       0,     6,    98,   158,    50,    51,    52,    53,    55,    56,
      42,    50,    51,    52,    91,    53,     7,     8,     9,    10,
       3,     9,     5,   100,    15,   141,   142,    18,   183,    22,
      21,    57,    23,    13,    14,    25,    26,    24,    19,    30,
      56,    29,    33,    31,    32,    22,    36,    37,    25,   165,
     126,    34,    43,    55,    56,    54,   172,    44,    45,    46,
      47,    48,    49,    55,    56,    40,    55,    56,    17,    42,
     186,   187,    57,    55,    56,    20,    55,    56,    54,    44,
     196,    55,    56,    55,    56,   201,    53,    53,    41,    12,
      12,    54,    56,    35,    12,    12,    53,    44,    54,    54,
      54,    11,    54,    53,    38,    53,    11,    51,    54,    39,
      14,    14,   189,    12,    12,    55,    55,    54,    27,    54,
     197,    54,    54,    39,    55,    13,   151,   134,   132,    -1,
      -1,    -1,   118
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     7,     8,     9,    10,    15,    18,    21,    23,    30,
      33,    43,    60,    61,    62,    63,    64,    65,    66,    67,
       4,     6,     3,     5,    34,     3,     5,    34,    53,    84,
      16,    19,    53,    85,    53,    58,    76,    80,    81,    85,
      86,     5,    85,     0,    62,    42,    84,    85,    53,    89,
      84,    85,    89,    85,    85,    22,    19,    56,    57,    85,
      42,    54,    40,    17,    20,    53,    79,    86,    82,    85,
      76,    86,     9,    29,    31,    32,    11,    38,    68,    69,
      86,    85,    54,    71,    74,    75,    76,    20,    56,    44,
      20,    56,    11,    34,    38,    86,    86,    28,    34,    69,
      41,    12,    12,    55,    56,    25,    26,    36,    37,    70,
      54,    14,    50,    51,    52,    72,    73,    56,    35,    24,
      44,    45,    46,    47,    48,    49,    77,    75,    86,    73,
      75,    85,    12,    89,    12,    69,    53,    87,    88,    89,
      85,    54,    54,    69,    54,    13,    27,    83,    86,    55,
      56,    54,    74,    13,    14,    73,    76,    78,    44,    53,
      88,    53,    87,    38,    11,    54,    83,    86,    51,    14,
      73,    55,    56,    73,    72,    14,    73,    12,    12,    83,
      55,    55,    55,    27,    86,    55,    54,    54,    55,    39,
      73,    83,    83,    85,    55,    55,    54,    39,    86,    85,
      55,    54,    83,    55
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *bottom, yytype_int16 *top)
#else
static void
yy_stack_print (bottom, top)
    yytype_int16 *bottom;
    yytype_int16 *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      fprintf (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      fprintf (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The look-ahead symbol.  */
int yychar;

/* The semantic value of the look-ahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  int yystate;
  int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Look-ahead token as an internal (translated) token number.  */
  int yytoken = 0;
#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  yytype_int16 yyssa[YYINITDEPTH];
  yytype_int16 *yyss = yyssa;
  yytype_int16 *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  YYSTYPE *yyvsp;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     look-ahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to look-ahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a look-ahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid look-ahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the look-ahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 10:
#line 53 "bison.y"
    {
                smm->Exit();
        ;}
    break;

  case 11:
#line 58 "bison.y"
    {
                smm->ShowDBs();
        ;}
    break;

  case 12:
#line 62 "bison.y"
    {
                smm->CreateDB((yyvsp[(3) - (3)]).s);
        ;}
    break;

  case 13:
#line 65 "bison.y"
    { 
                smm->DropDB((yyvsp[(3) - (3)]).s);
        ;}
    break;

  case 14:
#line 68 "bison.y"
    { 
                smm->UseDB((yyvsp[(2) - (2)]).s);
        ;}
    break;

  case 15:
#line 71 "bison.y"
    { 
                smm->ShowTables();
        ;}
    break;

  case 16:
#line 75 "bison.y"
    {
                TableInfo tableInfo;
                tableInfo.name = (yyvsp[(3) - (6)]).s;
                tableInfo.attrNum = (yyvsp[(5) - (6)]).attrList.size();
                tableInfo.foreignNum = tableInfo.recordSize = tableInfo.primarySize = 0;
                tableInfo.attrs = (yyvsp[(5) - (6)]).attrList;

                smm->CreateTable(tableInfo);
        ;}
    break;

  case 17:
#line 84 "bison.y"
    {
                smm->DropTable((yyvsp[(3) - (3)]).s);
        ;}
    break;

  case 18:
#line 87 "bison.y"
    { 
                smm->Desc((yyvsp[(2) - (2)]).s); 
        ;}
    break;

  case 19:
#line 90 "bison.y"
    {
                // cout << "insert " << endl;
                qlm->Insert((yyvsp[(3) - (5)]).s, (yyvsp[(5) - (5)]).valLists);
                // cout << "insert finish" << endl;
        ;}
    break;

  case 20:
#line 95 "bison.y"
    {
                qlm->Delete((yyvsp[(3) - (5)]).s, (yyvsp[(5) - (5)]).whereList);
        ;}
    break;

  case 21:
#line 98 "bison.y"
    {
                qlm->Update((yyvsp[(2) - (6)]).s, (yyvsp[(4) - (6)]).setList, (yyvsp[(6) - (6)]).whereList);
        ;}
    break;

  case 22:
#line 101 "bison.y"
    {
                qlm->Select((yyvsp[(2) - (6)]).selector, (yyvsp[(4) - (6)]).stringList, (yyvsp[(6) - (6)]).whereList);
        ;}
    break;

  case 23:
#line 104 "bison.y"
    {
                qlm->Select((yyvsp[(2) - (4)]).selector, (yyvsp[(4) - (4)]).stringList, vector<Where>());
        ;}
    break;

  case 24:
#line 109 "bison.y"
    {
                // smm->CreateIndex($5.s, $7.stringList);
        ;}
    break;

  case 25:
#line 112 "bison.y"
    {
                // smm->DropIndex($3.s);
        ;}
    break;

  case 26:
#line 115 "bison.y"
    {
                smm->CreateIndex((yyvsp[(3) - (9)]).s, (yyvsp[(6) - (9)]).s, (yyvsp[(8) - (9)]).stringList);
        ;}
    break;

  case 27:
#line 118 "bison.y"
    {
                smm->DropIndex((yyvsp[(3) - (6)]).s, (yyvsp[(6) - (6)]).s);
        ;}
    break;

  case 28:
#line 123 "bison.y"
    {
                if ((yyvsp[(5) - (5)]).type == PRIM) {
                        smm->AddPrimary((yyvsp[(3) - (5)]).s, (yyvsp[(5) - (5)]).stringList);
                } else if ((yyvsp[(5) - (5)]).type == FIELD) {
                        smm->AddColumn((yyvsp[(3) - (5)]).s, (yyvsp[(5) - (5)]).attr);
                }
        ;}
    break;

  case 29:
#line 130 "bison.y"
    {
                smm->DropColumn((yyvsp[(3) - (5)]).s, (yyvsp[(5) - (5)]).s);
        ;}
    break;

  case 30:
#line 133 "bison.y"
    {

        ;}
    break;

  case 31:
#line 136 "bison.y"
    {
                smm->Rename((yyvsp[(3) - (6)]).s, (yyvsp[(6) - (6)]).s);
        ;}
    break;

  case 32:
#line 139 "bison.y"
    {
                smm->DropPrimary((yyvsp[(3) - (6)]).s);
        ;}
    break;

  case 33:
#line 142 "bison.y"
    {
                smm->AddPrimary((yyvsp[(3) - (11)]).s, (yyvsp[(10) - (11)]).stringList);
        ;}
    break;

  case 34:
#line 145 "bison.y"
    {
                smm->DropPrimary((yyvsp[(3) - (7)]).s);
        ;}
    break;

  case 37:
#line 152 "bison.y"
    {
                (yyval).type = FIELD_LIST;
                (yyval).attrList.push_back((yyvsp[(1) - (1)]).attr);
        ;}
    break;

  case 38:
#line 156 "bison.y"
    {
                (yyval).type = FIELD_LIST;
                (yyval).attrList = (yyvsp[(1) - (3)]).attrList;
                if ((yyvsp[(3) - (3)]).type == PRIM) {
                        for (auto &attr: (yyval).attrList) {
                                if(find((yyvsp[(3) - (3)]).stringList.begin(), (yyvsp[(3) - (3)]).stringList.end(), attr.name) != (yyvsp[(3) - (3)]).stringList.end()) {
                                        attr.primary = true;
                                }
                        }
                } else if ((yyvsp[(3) - (3)]).type == FOR) {
                        
                } else {
                        (yyval).attrList.push_back((yyvsp[(3) - (3)]).attr);
                }
        ;}
    break;

  case 39:
#line 173 "bison.y"
    {
                (yyval) = (yyvsp[(2) - (2)]);
                (yyval).type = FIELD;
                (yyval).attr.name = (yyvsp[(1) - (2)]).s;
                (yyval).attr.notNull = (yyval).attr.primary = (yyval).attr.foreign = (yyval).attr.def = false;
        ;}
    break;

  case 40:
#line 179 "bison.y"
    {
                (yyval) = (yyvsp[(2) - (4)]);
                (yyval).type = FIELD;
                (yyval).attr.name = (yyvsp[(1) - (4)]).s;
                (yyval).attr.notNull = true;
                (yyval).attr.primary = (yyval).attr.foreign = (yyval).attr.def = false;
        ;}
    break;

  case 41:
#line 186 "bison.y"
    {
                (yyval) = (yyvsp[(2) - (4)]);
                (yyval).type = FIELD;
                (yyval).attr.name = (yyvsp[(1) - (4)]).s;
                (yyval).attr.notNull = (yyval).attr.primary = (yyval).attr.foreign = false;
                (yyval).attr.def = true;
                if ((yyval).attr.type == INTEGER) {
                        (yyval).attr.defint = (int)(yyvsp[(4) - (4)]).val.i;
                } else if ((yyvsp[(2) - (4)]).attr.type == FLOAT_T) {
                        (yyval).attr.deffloat = (double)(yyvsp[(4) - (4)]).val.f;
                } else if ((yyvsp[(2) - (4)]).attr.type == STRING) {
                        (yyval).attr.defstring = (yyvsp[(4) - (4)]).val.s;
                }
        ;}
    break;

  case 42:
#line 200 "bison.y"
    {
                (yyval) = (yyvsp[(2) - (6)]);
                (yyval).type = FIELD;
                (yyval).attr.name = (yyvsp[(1) - (6)]).s;
                (yyval).attr.notNull = true;
                (yyval).attr.primary = (yyval).attr.foreign = false;
                (yyval).attr.def = true;
                if ((yyval).attr.type == INTEGER) {
                        (yyval).attr.defint = (int)(yyvsp[(6) - (6)]).val.i;
                } else if ((yyvsp[(2) - (6)]).attr.type == FLOAT_T) {
                        (yyval).attr.deffloat = (double)(yyvsp[(6) - (6)]).val.f;
                } else if ((yyvsp[(2) - (6)]).attr.type == STRING) {
                        (yyval).attr.defstring = (yyvsp[(6) - (6)]).val.s;
                }
        ;}
    break;

  case 43:
#line 215 "bison.y"
    {
                (yyval).type = PRIM;
                (yyval).stringList = (yyvsp[(4) - (5)]).stringList;
        ;}
    break;

  case 44:
#line 219 "bison.y"
    {
                (yyval).type = FOR;
                (yyval).s = (yyvsp[(4) - (10)]).s;
                (yyval).col.tab = (yyvsp[(7) - (10)]).s;
                (yyval).col.attr = (yyvsp[(9) - (10)]).s;
        ;}
    break;

  case 45:
#line 227 "bison.y"
    { 
                (yyval).attr.type = INTEGER;
        ;}
    break;

  case 46:
#line 230 "bison.y"
    { 
                (yyval).attr.type = STRING; 
                (yyval).attr.length = (yyvsp[(3) - (4)]).val.i;
        ;}
    break;

  case 47:
#line 234 "bison.y"
    { 
                (yyval).attr.type = STRING; 
                (yyval).attr.length = 10;
        ;}
    break;

  case 48:
#line 238 "bison.y"
    { 
                (yyval).attr.type = FLOAT_T; 
        ;}
    break;

  case 49:
#line 243 "bison.y"
    {
                (yyval).valLists.push_back((yyvsp[(2) - (3)]).valList);
        ;}
    break;

  case 50:
#line 246 "bison.y"
    {
                (yyval) = (yyvsp[(1) - (5)]);
                (yyval).valLists.push_back((yyvsp[(4) - (5)]).valList);
        ;}
    break;

  case 51:
#line 252 "bison.y"
    {
                (yyval).valList.push_back((yyvsp[(1) - (1)]).val);
        ;}
    break;

  case 52:
#line 255 "bison.y"
    {
                (yyval) = (yyvsp[(1) - (3)]);
                (yyval).valList.push_back((yyvsp[(3) - (3)]).val);
        ;}
    break;

  case 53:
#line 261 "bison.y"
    {
                (yyval).val.isNull = false;
                (yyval).val.type = INTEGER;
                (yyval).val.i = (yyvsp[(1) - (1)]).val.i;
                // $$ = $1;
                // cout << "INT " << $1.i << endl;
        ;}
    break;

  case 54:
#line 268 "bison.y"
    { 
                (yyval).val.isNull = false;
                (yyval).val.type = FLOAT_T;
                (yyval).val.f = (yyvsp[(1) - (1)]).val.f;
                // $$ = $1;
                // cout << "FLOAT " << $1.f << endl;
        ;}
    break;

  case 55:
#line 275 "bison.y"
    { 
                (yyval).val.isNull = false;
                (yyval).val.type = STRING;
                (yyval).val.s = (yyvsp[(1) - (1)]).val.s.substr(1, (yyvsp[(1) - (1)]).val.s.length() - 2);
                // $$ = $1;
                // cout << "STRING " << $1.s << endl;
                ;}
    break;

  case 56:
#line 282 "bison.y"
    { 
                (yyval).val.isNull = true;
                // $$ = $1;
                // cout << "NULL" << endl; 
        ;}
    break;

  case 57:
#line 289 "bison.y"
    {
                (yyval).where.col = (yyvsp[(1) - (3)]).col;
                (yyval).where.op = (yyvsp[(2) - (3)]).op;
                (yyval).where.expr = (yyvsp[(3) - (3)]).expr;
        ;}
    break;

  case 58:
#line 294 "bison.y"
    {
                (yyval).where.col = (yyvsp[(1) - (3)]).col;
                (yyval).where.op = EQ_OP;
                (yyval).where.expr.isVal = true;
                (yyval).where.expr.val.isNull = true;
        ;}
    break;

  case 59:
#line 300 "bison.y"
    {
                (yyval).where.col = (yyvsp[(1) - (4)]).col;
                (yyval).where.op = NE_OP;
                (yyval).where.expr.isVal = true;
                (yyval).where.expr.val.isNull = true;
        ;}
    break;

  case 60:
#line 308 "bison.y"
    {
                (yyval).whereList = (yyvsp[(1) - (3)]).whereList;
                (yyval).whereList.push_back((yyvsp[(3) - (3)]).where);
        ;}
    break;

  case 61:
#line 312 "bison.y"
    {
                (yyval).whereList.push_back((yyvsp[(1) - (1)]).where);
        ;}
    break;

  case 62:
#line 317 "bison.y"
    {
                (yyval).col.tab = "";
                (yyval).col.attr = (yyvsp[(1) - (1)]).s;
        ;}
    break;

  case 63:
#line 321 "bison.y"
    {
                (yyval).col.tab = (yyvsp[(1) - (3)]).s;
                (yyval).col.attr = (yyvsp[(3) - (3)]).s;
        ;}
    break;

  case 64:
#line 327 "bison.y"
    { 
        (yyval) = (yyvsp[(1) - (1)]);
        ;}
    break;

  case 65:
#line 330 "bison.y"
    { 
        (yyval) = (yyvsp[(1) - (1)]);
        ;}
    break;

  case 66:
#line 333 "bison.y"
    { 
        (yyval) = (yyvsp[(1) - (1)]);
        ;}
    break;

  case 67:
#line 336 "bison.y"
    { 
        (yyval) = (yyvsp[(1) - (1)]);
        ;}
    break;

  case 68:
#line 339 "bison.y"
    { 
        (yyval) = (yyvsp[(1) - (1)]);
        ;}
    break;

  case 69:
#line 342 "bison.y"
    { 
        (yyval) = (yyvsp[(1) - (1)]);
        ;}
    break;

  case 70:
#line 347 "bison.y"
    {
                (yyval).expr.isVal = true;
                (yyval).expr.val = (yyvsp[(1) - (1)]).val;
        ;}
    break;

  case 71:
#line 351 "bison.y"
    {
                (yyval).expr.isVal = false;
                (yyval).expr.col = (yyvsp[(1) - (1)]).col;
        ;}
    break;

  case 72:
#line 357 "bison.y"
    {
                Set tmp;
                tmp.col.attr = (yyvsp[(1) - (3)]).s;
                tmp.val = (yyvsp[(3) - (3)]).val;
                (yyval).setList.push_back(tmp);
        ;}
    break;

  case 73:
#line 363 "bison.y"
    {
                Set tmp;
                tmp.col.attr = (yyvsp[(3) - (5)]).s;
                tmp.val = (yyvsp[(5) - (5)]).val;
                (yyval).setList = (yyvsp[(1) - (5)]).setList;
                (yyval).setList.push_back(tmp);
        ;}
    break;

  case 74:
#line 372 "bison.y"
    {
                (yyval).selector.all = true;
        ;}
    break;

  case 75:
#line 375 "bison.y"
    {
                (yyval).selector.all = false;
                (yyval).selector.cols = (yyvsp[(1) - (1)]).colList;
        ;}
    break;

  case 76:
#line 381 "bison.y"
    {
                (yyval).colList.push_back((yyvsp[(1) - (1)]).col);
        ;}
    break;

  case 77:
#line 384 "bison.y"
    {
                (yyval) = (yyvsp[(1) - (3)]);
                (yyval).colList.push_back((yyvsp[(3) - (3)]).col);
        ;}
    break;

  case 78:
#line 390 "bison.y"
    {
                (yyval).stringList.push_back((yyvsp[(1) - (1)]).s);
        ;}
    break;

  case 79:
#line 393 "bison.y"
    {
                (yyval) = (yyvsp[(1) - (3)]);
                (yyval).stringList.push_back((yyvsp[(3) - (3)]).s);
        ;}
    break;

  case 80:
#line 399 "bison.y"
    {
                (yyval).stringList.push_back((yyvsp[(1) - (1)]).s);
        ;}
    break;

  case 81:
#line 402 "bison.y"
    {
                (yyval) = (yyvsp[(1) - (3)]);
                (yyval).stringList.push_back((yyvsp[(3) - (3)]).s);
        ;}
    break;

  case 82:
#line 408 "bison.y"
    { 
        (yyval) = (yyvsp[(1) - (1)]); 
        ;}
    break;

  case 83:
#line 413 "bison.y"
    { 
        (yyval) = (yyvsp[(1) - (1)]); 
        ;}
    break;

  case 84:
#line 418 "bison.y"
    { 
        (yyval) = (yyvsp[(1) - (1)]); 
        ;}
    break;

  case 85:
#line 423 "bison.y"
    { 
        (yyval) = (yyvsp[(1) - (1)]); 
        ;}
    break;

  case 86:
#line 428 "bison.y"
    { 
        (yyval) = (yyvsp[(1) - (1)]); 
        ;}
    break;

  case 87:
#line 433 "bison.y"
    { 
        (yyval) = (yyvsp[(1) - (1)]); 
        ;}
    break;


/* Line 1267 of yacc.c.  */
#line 2237 "bison.tab.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse look-ahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse look-ahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEOF && yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}


#line 438 "bison.y"


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

