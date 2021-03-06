/* A Bison parser, made by GNU Bison 2.4.2.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2006, 2009-2010 Free Software
   Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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
#define YYBISON_VERSION "2.4.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0



/* Copy the first part of user declarations.  */


#include "stdafx.h"
#include "dab_header.h"

#define QCODEX(xxx) QCODE(q_yy_pos(scanner), (xxx))

int bisonfprintf(FILE * file, const char * format, ...);
#define YYERROR_VERBOSE 1
#define YYFPRINTF bisonfprintf

int isatty(int foo) { return -1; }

size_t q_yy_pos(void*scanner);

void dab_Parse(char *buf, qValue **result, const std::string & filename, std::vector<qError> & errors, dab_Module * module)
{
    parse_parm  pp;

    pp.buf = buf;
    pp.length = strlen(buf);
    pp.pos = 0;
    pp.filename = filename;
    pp.errorsfound = 0;
    pp.module = module;
    
    *result = 0;
    yylex_init(&pp.yyscanner);
    yyset_extra(&pp, pp.yyscanner);
    yyparse(&pp, pp.yyscanner);
    *result = pp.result;
    yylex_destroy(pp.yyscanner);
    
    errors = pp.errors;
}




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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INT = 258,
     FLOAT = 259,
     BOOL = 260,
     NAME = 261,
     RETURN = 262,
     IF = 263,
     ELSE = 264,
     WHILE = 265,
     FOR = 266,
     STRUCT = 267,
     EXTERN = 268,
     STRING = 269,
     VARARG = 270,
     BREAK = 271,
     TYPEDEF = 272,
     CONST = 273,
     CAST = 274,
     MINUSMINUS = 275,
     PLUSPLUS = 276,
     DIVEQ = 277,
     MULEQ = 278,
     MINUSEQ = 279,
     PLUSEQ = 280,
     BAND = 281,
     BOR = 282,
     NEQ = 283,
     EQ = 284,
     DEREF = 285,
     ADDROF = 286,
     EQNEG = 287,
     POS = 288,
     NEG = 289,
     PACC = 290
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */



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
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
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
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  18
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   419

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  55
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  87
/* YYNRULES -- Number of states.  */
#define YYNSTATES  196

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   290

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    38,     2,     2,     2,     2,    32,     2,
      50,    51,    36,    35,    54,    34,    47,    37,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    48,
      30,    49,    31,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    44,     2,    45,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    52,    33,    53,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    39,    40,    41,    42,    43,
      46
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint16 yyprhs[] =
{
       0,     0,     3,     5,     6,     9,    12,    14,    16,    20,
      26,    35,    45,    52,    59,    64,    68,    69,    73,    75,
      80,    84,    86,    87,    92,    96,    99,   104,   108,   111,
     113,   119,   127,   133,   143,   146,   150,   153,   157,   160,
     163,   166,   168,   170,   173,   178,   182,   186,   190,   194,
     198,   201,   204,   208,   212,   216,   220,   224,   228,   232,
     236,   240,   244,   248,   252,   255,   258,   262,   264,   266,
     268,   274,   276,   278,   280,   282,   286,   288,   290,   293,
     296,   301,   305,   309,   311,   314,   317,   321
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      56,     0,    -1,    57,    -1,    -1,    57,    58,    -1,    57,
       1,    -1,    58,    -1,     1,    -1,    72,     6,    48,    -1,
      72,     6,    49,    70,    48,    -1,    13,    59,    72,     6,
      50,    62,    51,    48,    -1,    44,     6,    45,    72,     6,
      50,    62,    51,    48,    -1,    72,     6,    50,    62,    51,
      66,    -1,    12,     6,    52,    61,    53,    48,    -1,    17,
      72,     6,    48,    -1,    50,    60,    51,    -1,    -1,    60,
      54,    14,    -1,    14,    -1,    61,    72,     6,    48,    -1,
      72,     6,    48,    -1,    63,    -1,    -1,    63,    54,    72,
       6,    -1,    63,    54,    15,    -1,    72,     6,    -1,     6,
      50,    71,    51,    -1,     6,    50,    51,    -1,    68,    48,
      -1,    66,    -1,     8,    50,    69,    51,    65,    -1,     8,
      50,    69,    51,    65,     9,    65,    -1,    10,    50,    69,
      51,    65,    -1,    11,    50,    68,    48,    69,    48,    68,
      51,    65,    -1,    64,    48,    -1,     7,    69,    48,    -1,
      16,    48,    -1,    52,    67,    53,    -1,    52,    53,    -1,
      67,    65,    -1,    67,     1,    -1,    65,    -1,     1,    -1,
      72,     6,    -1,    72,     6,    49,    69,    -1,    73,    49,
      69,    -1,    73,    25,    69,    -1,    73,    24,    69,    -1,
      73,    23,    69,    -1,    73,    22,    69,    -1,    73,    21,
      -1,    73,    20,    -1,    69,    29,    69,    -1,    69,    28,
      69,    -1,    69,    31,    69,    -1,    69,    30,    69,    -1,
      69,    26,    69,    -1,    69,    27,    69,    -1,    69,    32,
      69,    -1,    69,    33,    69,    -1,    69,    35,    69,    -1,
      69,    34,    69,    -1,    69,    36,    69,    -1,    69,    37,
      69,    -1,    34,    69,    -1,    38,    69,    -1,    50,    69,
      51,    -1,    70,    -1,    73,    -1,    64,    -1,    19,    30,
      72,    31,    69,    -1,     3,    -1,     4,    -1,    14,    -1,
       5,    -1,    71,    54,    69,    -1,    69,    -1,     6,    -1,
      72,    36,    -1,    18,    72,    -1,    72,    30,     3,    31,
      -1,    73,    47,     6,    -1,    73,    46,     6,    -1,     6,
      -1,    32,    73,    -1,    36,    73,    -1,    50,    73,    51,
      -1,    73,    44,    69,    45,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    67,    67,    68,    72,    73,    74,    75,    79,    80,
      81,    82,    83,    84,    85,    89,    90,    94,    95,    99,
     100,   103,   103,   106,   107,   108,   112,   113,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   129,   130,   134,
     135,   136,   137,   141,   142,   143,   144,   145,   146,   147,
     148,   149,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   175,   176,   177,   178,   182,   183,   187,   188,   189,
     190,   194,   195,   196,   197,   198,   199,   200
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "FLOAT", "BOOL", "NAME", "RETURN",
  "IF", "ELSE", "WHILE", "FOR", "STRUCT", "EXTERN", "STRING", "VARARG",
  "BREAK", "TYPEDEF", "CONST", "CAST", "MINUSMINUS", "PLUSPLUS", "DIVEQ",
  "MULEQ", "MINUSEQ", "PLUSEQ", "BAND", "BOR", "NEQ", "EQ", "'<'", "'>'",
  "'&'", "'|'", "'-'", "'+'", "'*'", "'/'", "'!'", "DEREF", "ADDROF",
  "EQNEG", "POS", "NEG", "'['", "']'", "PACC", "'.'", "';'", "'='", "'('",
  "')'", "'{'", "'}'", "','", "$accept", "result", "program", "definition",
  "optionaalearglist", "earglist", "strmember", "arglistnull", "arglist",
  "funcall", "instr", "block", "seq", "expr", "math", "constant",
  "paramlist", "type", "var", 0
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
      60,    62,    38,   124,    45,    43,    42,    47,    33,   285,
     286,   287,   288,   289,    91,    93,   290,    46,    59,    61,
      40,    41,   123,   125,    44
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    55,    56,    56,    57,    57,    57,    57,    58,    58,
      58,    58,    58,    58,    58,    59,    59,    60,    60,    61,
      61,    62,    62,    63,    63,    63,    64,    64,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    66,    66,    67,
      67,    67,    67,    68,    68,    68,    68,    68,    68,    68,
      68,    68,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
      69,    70,    70,    70,    70,    71,    71,    72,    72,    72,
      72,    73,    73,    73,    73,    73,    73,    73
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     2,     1,     1,     3,     5,
       8,     9,     6,     6,     4,     3,     0,     3,     1,     4,
       3,     1,     0,     4,     3,     2,     4,     3,     2,     1,
       5,     7,     5,     9,     2,     3,     2,     3,     2,     2,
       2,     1,     1,     2,     4,     3,     3,     3,     3,     3,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     2,     3,     1,     1,     1,
       5,     1,     1,     1,     1,     3,     1,     1,     2,     2,
       4,     3,     3,     1,     2,     2,     3,     4
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     7,    77,     0,    16,     0,     0,     0,     0,     0,
       6,     0,     0,     0,     0,     0,    79,     0,     1,     5,
       4,     0,     0,    78,     0,    18,     0,     0,     0,     0,
       8,     0,    22,     0,     0,     0,    15,     0,     0,    14,
       0,    71,    72,    74,    73,     0,     0,    21,     0,    80,
       0,     0,     0,    17,    22,     0,     9,     0,     0,    25,
      13,     0,    20,     0,    22,     0,    12,    24,     0,    19,
       0,     0,    42,    83,     0,     0,     0,     0,     0,     0,
       0,     0,    38,     0,    41,    29,     0,     0,     0,     0,
      23,    10,     0,     0,    83,     0,     0,     0,     0,    69,
       0,    67,    68,     0,     0,     0,    36,    83,    84,    85,
       0,    34,    40,    37,    39,    28,    43,    51,    50,     0,
       0,     0,     0,     0,     0,     0,     0,    11,    27,    76,
       0,     0,    64,    65,     0,    68,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    35,     0,
       0,    83,     0,    86,     0,    49,    48,    47,    46,     0,
      82,    81,    45,    26,     0,     0,    66,    56,    57,    53,
      52,    55,    54,    58,    59,    61,    60,    62,    63,     0,
       0,     0,    44,    87,    75,     0,    30,    32,     0,    70,
       0,     0,    31,     0,     0,    33
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     8,     9,    10,    14,    26,    34,    46,    47,    99,
      84,    85,    86,    87,   100,   101,   130,    88,   102
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -104
static const yytype_int16 yypact[] =
{
     212,  -104,  -104,     2,   -40,     5,     5,     6,    21,   232,
    -104,    57,   -26,    17,     5,    67,  -104,   -12,  -104,  -104,
    -104,   187,    38,  -104,     5,  -104,    62,    71,     3,     5,
    -104,   254,     5,    22,     9,    74,  -104,    47,    26,  -104,
      76,  -104,  -104,  -104,  -104,    37,    35,    36,   164,  -104,
      51,   185,    60,  -104,     5,    61,  -104,    65,    66,  -104,
    -104,    80,  -104,    91,     5,    39,  -104,  -104,   198,  -104,
      95,    98,  -104,    29,   121,   102,   104,   115,   118,    16,
      16,    16,  -104,   125,  -104,  -104,   140,   127,   210,   242,
    -104,  -104,   141,    64,   146,   176,   121,   121,   121,  -104,
     316,  -104,   173,   121,   121,    24,  -104,  -104,   173,   173,
      -8,  -104,  -104,  -104,  -104,  -104,   154,  -104,  -104,   121,
     121,   121,   121,   121,   202,   204,   121,  -104,  -104,   382,
      69,     5,  -104,  -104,   266,    -8,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,  -104,   278,
     304,   225,   163,  -104,   121,   382,   382,   382,   382,   362,
    -104,  -104,   382,  -104,   121,   138,  -104,   291,   349,   247,
     247,   237,   237,   323,   217,   -20,   -20,  -104,  -104,   191,
     191,   121,   382,  -104,   382,   121,   205,  -104,   339,  -104,
     191,    24,  -104,   188,   191,  -104
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -104,  -104,  -104,   233,  -104,  -104,  -104,   -51,  -104,   -58,
     -85,   190,  -104,  -103,    41,   229,  -104,     0,   -61
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -78
static const yytype_int16 yytable[] =
{
      11,   114,   152,    63,    89,    15,    16,    83,    12,    11,
      13,     2,    17,    71,    27,     2,   146,   147,   108,   109,
     110,    18,   107,     6,    35,    89,    24,     6,    83,    40,
     151,    25,    48,    29,    51,   -77,   123,   135,   124,   125,
      72,    33,     6,   153,    89,    73,    74,    75,    79,    76,
      77,    39,    80,    49,    48,    78,    79,     6,    68,   -77,
      80,    53,    50,    21,    48,   -77,    81,    41,    42,    43,
      94,    79,     2,    28,    81,    80,    54,    38,    44,    93,
      52,    67,    55,    95,     6,    56,    57,    22,   193,    81,
      58,    65,    82,    23,   186,   187,    79,    22,    96,    60,
      80,    22,    97,    23,    22,   192,    22,    23,    62,   195,
      23,    64,    23,    36,    98,   128,    37,    65,    89,    89,
     163,    83,    83,   164,    41,    42,    43,    94,    69,    89,
      89,   165,    83,    89,   129,    44,    83,   132,   133,   134,
      95,   112,    70,    91,   149,   150,    73,    74,    75,    92,
      76,    77,   103,    79,   104,    96,    78,    80,     6,    97,
     155,   156,   157,   158,   159,   105,   106,   162,    22,   185,
      59,    98,    79,   111,    23,   115,    80,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   177,   178,   127,
      81,    61,    65,   113,    22,   182,    93,    73,    74,    75,
      23,    76,    77,   154,    90,   184,   131,    78,   160,     6,
     161,   181,    -3,     1,   190,    22,   116,   123,     2,   124,
     125,    23,   188,    79,     3,     4,   189,    80,    22,     5,
       6,   -77,    -2,    19,    23,    30,    31,    32,     2,   194,
      22,    81,    20,    65,     3,     4,    23,    66,     0,     5,
       6,   144,   145,   146,   147,   -77,     7,    41,    42,    43,
      45,   -77,   117,   118,   119,   120,   121,   122,    44,   142,
     143,   144,   145,   146,   147,     0,     7,   140,   141,   142,
     143,   144,   145,   146,   147,     0,   123,     0,   124,   125,
       0,   126,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,     0,   166,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,   179,
     136,   137,   138,   139,   140,   141,   142,   143,   144,   145,
     146,   147,   136,   137,   138,   139,   140,   141,   142,   143,
     144,   145,   146,   147,     0,   180,   143,   144,   145,   146,
     147,     0,     0,     0,   148,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   191,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147,
       0,     0,     0,     0,     0,     0,     0,   183,   136,   137,
     138,   139,   140,   141,   142,   143,   144,   145,   146,   147
};

static const yytype_int16 yycheck[] =
{
       0,    86,   105,    54,    65,     5,     6,    65,     6,     9,
      50,     6,     6,    64,    14,     6,    36,    37,    79,    80,
      81,     0,     6,    18,    24,    86,    52,    18,    86,    29,
       6,    14,    32,    45,    34,     6,    44,    98,    46,    47,
       1,     3,    18,    51,   105,     6,     7,     8,    32,    10,
      11,    48,    36,    31,    54,    16,    32,    18,    58,    30,
      36,    14,    53,     6,    64,    36,    50,     3,     4,     5,
       6,    32,     6,     6,    50,    36,    50,     6,    14,    50,
       6,    15,     6,    19,    18,    48,    51,    30,   191,    50,
      54,    52,    53,    36,   179,   180,    32,    30,    34,    48,
      36,    30,    38,    36,    30,   190,    30,    36,    48,   194,
      36,    50,    36,    51,    50,    51,    54,    52,   179,   180,
      51,   179,   180,    54,     3,     4,     5,     6,    48,   190,
     191,   131,   190,   194,    93,    14,   194,    96,    97,    98,
      19,     1,    51,    48,   103,   104,     6,     7,     8,    51,
      10,    11,    50,    32,    50,    34,    16,    36,    18,    38,
     119,   120,   121,   122,   123,    50,    48,   126,    30,    31,
       6,    50,    32,    48,    36,    48,    36,   136,   137,   138,
     139,   140,   141,   142,   143,   144,   145,   146,   147,    48,
      50,     6,    52,    53,    30,   154,    50,     6,     7,     8,
      36,    10,    11,    49,     6,   164,    30,    16,     6,    18,
       6,    48,     0,     1,     9,    30,     6,    44,     6,    46,
      47,    36,   181,    32,    12,    13,   185,    36,    30,    17,
      18,     6,     0,     1,    36,    48,    49,    50,     6,    51,
      30,    50,     9,    52,    12,    13,    36,    57,    -1,    17,
      18,    34,    35,    36,    37,    30,    44,     3,     4,     5,
      31,    36,    20,    21,    22,    23,    24,    25,    14,    32,
      33,    34,    35,    36,    37,    -1,    44,    30,    31,    32,
      33,    34,    35,    36,    37,    -1,    44,    -1,    46,    47,
      -1,    49,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    -1,    51,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    51,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    -1,    51,    33,    34,    35,    36,
      37,    -1,    -1,    -1,    48,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    48,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    45,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,     6,    12,    13,    17,    18,    44,    56,    57,
      58,    72,     6,    50,    59,    72,    72,     6,     0,     1,
      58,     6,    30,    36,    52,    14,    60,    72,     6,    45,
      48,    49,    50,     3,    61,    72,    51,    54,     6,    48,
      72,     3,     4,     5,    14,    70,    62,    63,    72,    31,
      53,    72,     6,    14,    50,     6,    48,    51,    54,     6,
      48,     6,    48,    62,    50,    52,    66,    15,    72,    48,
      51,    62,     1,     6,     7,     8,    10,    11,    16,    32,
      36,    50,    53,    64,    65,    66,    67,    68,    72,    73,
       6,    48,    51,    50,     6,    19,    34,    38,    50,    64,
      69,    70,    73,    50,    50,    50,    48,     6,    73,    73,
      73,    48,     1,    53,    65,    48,     6,    20,    21,    22,
      23,    24,    25,    44,    46,    47,    49,    48,    51,    69,
      71,    30,    69,    69,    69,    73,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    48,    69,
      69,     6,    68,    51,    49,    69,    69,    69,    69,    69,
       6,     6,    69,    51,    54,    72,    51,    69,    69,    69,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    51,
      51,    48,    69,    45,    69,    31,    65,    65,    69,    69,
       9,    48,    65,    68,    51,    65
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
   Once GCC version 2 has supplanted version 1, this can go.  However,
   YYFAIL appears to be in use.  Nevertheless, it is formally deprecated
   in Bison 2.4.2's NEWS entry, where a plan to phase it out is
   discussed.  */

#define YYFAIL		goto yyerrlab
#if defined YYFAIL
  /* This is here to suppress warnings from the GCC cpp's
     -Wunused-macros.  Normally we don't worry about that warning, but
     some users do, and we want to make it easy for users to remove
     YYFAIL uses, which will produce warnings from Bison 2.5.  */
#endif

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
      yyerror (parm, scanner, YY_("syntax error: cannot back up")); \
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
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, scanner)
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
		  Type, Value, parm, scanner); \
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
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, parse_parm *parm, void *scanner)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, parm, scanner)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    parse_parm *parm;
    void *scanner;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (parm);
  YYUSE (scanner);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, parse_parm *parm, void *scanner)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, parm, scanner)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    parse_parm *parm;
    void *scanner;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, parm, scanner);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
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
yy_reduce_print (YYSTYPE *yyvsp, int yyrule, parse_parm *parm, void *scanner)
#else
static void
yy_reduce_print (yyvsp, yyrule, parm, scanner)
    YYSTYPE *yyvsp;
    int yyrule;
    parse_parm *parm;
    void *scanner;
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
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       , parm, scanner);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule, parm, scanner); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, parse_parm *parm, void *scanner)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, parm, scanner)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    parse_parm *parm;
    void *scanner;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (parm);
  YYUSE (scanner);

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
int yyparse (parse_parm *parm, void *scanner);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */





/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

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
yyparse (parse_parm *parm, void *scanner)
#else
int
yyparse (parm, scanner)
    parse_parm *parm;
    void *scanner;
#endif
#endif
{
/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

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
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
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

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
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

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
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
        case 2:

    { parm->result = (yyvsp[(1) - (1)]); ;}
    break;

  case 3:

    { parm->result = qtree_program_start(0); ;}
    break;

  case 4:

    { (yyval) = qtree_program_append((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 5:

    { (yyval) = (yyvsp[(1) - (2)]); yyclearin; yyerrok; ;}
    break;

  case 6:

    { (yyval) = qtree_program_start((yyvsp[(1) - (1)])); ;}
    break;

  case 7:

    { yyclearin; yyerrok; ;}
    break;

  case 8:

    { (yyval) = QCODEY((yyvsp[(2) - (3)]), qtree_globalvar((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]), 0)); ;}
    break;

  case 9:

    { (yyval) = QCODEY((yyvsp[(2) - (5)]), qtree_globalvar((yyvsp[(1) - (5)]), (yyvsp[(2) - (5)]), (yyvsp[(4) - (5)]))); ;}
    break;

  case 10:

    { (yyval) = QCODEY((yyvsp[(4) - (8)]), new qExternFunc((yyvsp[(2) - (8)]), (yyvsp[(3) - (8)]), (yyvsp[(4) - (8)]), (yyvsp[(6) - (8)]))); ;}
    break;

  case 11:

    { (yyval) = QCODEY((yyvsp[(4) - (9)]), new qExternFunc((yyvsp[(2) - (9)]), (yyvsp[(4) - (9)]), (yyvsp[(5) - (9)]), (yyvsp[(7) - (9)]), 1)); ;}
    break;

  case 12:

    { (yyval) = QCODEY((yyvsp[(2) - (6)]), qtree_function((yyvsp[(1) - (6)]), (yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]), (yyvsp[(6) - (6)]))); ;}
    break;

  case 13:

    { (yyval) = QCODEY((yyvsp[(2) - (6)]), qtree_struct((yyvsp[(2) - (6)]), (yyvsp[(4) - (6)]))); ;}
    break;

  case 14:

    { (yyval) = QCODEY((yyvsp[(3) - (4)]), new qTypedef((yyvsp[(3) - (4)]), (yyvsp[(2) - (4)]))); ;}
    break;

  case 15:

    { (yyval) = (yyvsp[(2) - (3)]); ;}
    break;

  case 16:

    { (yyval) = 0; ;}
    break;

  case 17:

    { (yyval) = qtree_seq_append((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 18:

    { (yyval) = qtree_seq_start((yyvsp[(1) - (1)])); ;}
    break;

  case 19:

    { (yyval) = qtree_seq_append((yyvsp[(1) - (4)]), QCODEY((yyvsp[(3) - (4)]), qtree_smember((yyvsp[(2) - (4)]), (yyvsp[(3) - (4)])))); ;}
    break;

  case 20:

    { (yyval) = qtree_seq_start(qtree_smember((yyvsp[(1) - (3)]), (yyvsp[(2) - (3)]))); ;}
    break;

  case 22:

    { (yyval) = 0; ;}
    break;

  case 23:

    { (yyval) = qtree_seq_append((yyvsp[(1) - (4)]), qtree_declare((yyvsp[(3) - (4)]), (yyvsp[(4) - (4)]))); ;}
    break;

  case 24:

    { (yyval) = qtree_seq_append((yyvsp[(1) - (3)]), qtree_vararg()); ;}
    break;

  case 25:

    { (yyval) = qtree_seq_start(qtree_declare((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]))); ;}
    break;

  case 26:

    { (yyval) = QCODEY((yyvsp[(1) - (4)]), qtree_funcall((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]))); ;}
    break;

  case 27:

    { (yyval) = QCODEY((yyvsp[(1) - (3)]), qtree_funcall((yyvsp[(1) - (3)]), 0)); ;}
    break;

  case 30:

    { (yyval) = qtree_if((yyvsp[(3) - (5)]), (yyvsp[(5) - (5)]), 0); ;}
    break;

  case 31:

    { (yyval) = qtree_if((yyvsp[(3) - (7)]), (yyvsp[(5) - (7)]), (yyvsp[(7) - (7)])); ;}
    break;

  case 32:

    { (yyval) = qtree_while((yyvsp[(3) - (5)]), (yyvsp[(5) - (5)])); ;}
    break;

  case 33:

    { (yyval) = qtree_for((yyvsp[(3) - (9)]), (yyvsp[(5) - (9)]), (yyvsp[(7) - (9)]), (yyvsp[(9) - (9)])); ;}
    break;

  case 35:

    { (yyval) = qtree_return((yyvsp[(2) - (3)])); ;}
    break;

  case 36:

    { (yyval) = QCODEX(new qBreak()); ;}
    break;

  case 37:

    { (yyval) = qtree_block((yyvsp[(2) - (3)])); ;}
    break;

  case 38:

    { (yyval) = 0; ;}
    break;

  case 39:

    { (yyval) = qtree_seq_append((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)])); ;}
    break;

  case 40:

    { (yyval) = (yyvsp[(1) - (2)]); yyclearin; yyerrok; ;}
    break;

  case 41:

    { (yyval) = qtree_seq_start((yyvsp[(1) - (1)])); ;}
    break;

  case 42:

    { yyclearin; yyerrok; ;}
    break;

  case 43:

    { (yyval) = QCODEY((yyvsp[(1) - (2)]), qtree_declare((yyvsp[(1) - (2)]), (yyvsp[(2) - (2)]))); ;}
    break;

  case 44:

    { (yyval) = QCODEY((yyvsp[(1) - (4)]), qtree_declare_value((yyvsp[(1) - (4)]), (yyvsp[(2) - (4)]), (yyvsp[(4) - (4)]))); ;}
    break;

  case 45:

    { (yyval) = QCODEY((yyvsp[(1) - (3)]), qtree_assign((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]))); ;}
    break;

  case 46:

    { (yyval) = QCODEY((yyvsp[(1) - (3)]), qtree_assign((yyvsp[(1) - (3)]), qtree_binop("add", (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])))); ;}
    break;

  case 47:

    { (yyval) = QCODEY((yyvsp[(1) - (3)]), qtree_assign((yyvsp[(1) - (3)]), qtree_binop("sub", (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])))); ;}
    break;

  case 48:

    { (yyval) = QCODEY((yyvsp[(1) - (3)]), qtree_assign((yyvsp[(1) - (3)]), qtree_binop("mul", (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])))); ;}
    break;

  case 49:

    { (yyval) = QCODEY((yyvsp[(1) - (3)]), qtree_assign((yyvsp[(1) - (3)]), qtree_binop("div", (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])))); ;}
    break;

  case 50:

    { (yyval) = QCODEY((yyvsp[(1) - (2)]), qtree_assign((yyvsp[(1) - (2)]), qtree_binop("add", (yyvsp[(1) - (2)]), qtree_constant_int(1)))); ;}
    break;

  case 51:

    { (yyval) = QCODEY((yyvsp[(1) - (2)]), qtree_assign((yyvsp[(1) - (2)]), qtree_binop("sub", (yyvsp[(1) - (2)]), qtree_constant_int(1)))); ;}
    break;

  case 52:

    { (yyval) = QCODEY((yyvsp[(1) - (3)]), qtree_binop("eq",   (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]))); ;}
    break;

  case 53:

    { (yyval) = QCODEY((yyvsp[(1) - (3)]), qtree_binop("neq",  (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]))); ;}
    break;

  case 54:

    { (yyval) = QCODEY((yyvsp[(1) - (3)]), qtree_binop("gt",   (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]))); ;}
    break;

  case 55:

    { (yyval) = QCODEY((yyvsp[(1) - (3)]), qtree_binop("lt",   (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]))); ;}
    break;

  case 56:

    { (yyval) = QCODEY((yyvsp[(1) - (3)]), qtree_binop("band", (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]))); ;}
    break;

  case 57:

    { (yyval) = QCODEY((yyvsp[(1) - (3)]), qtree_binop("bor",  (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]))); ;}
    break;

  case 58:

    { (yyval) = QCODEY((yyvsp[(1) - (3)]), qtree_binop("and",  (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]))); ;}
    break;

  case 59:

    { (yyval) = QCODEY((yyvsp[(1) - (3)]), qtree_binop("or",   (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]))); ;}
    break;

  case 60:

    { (yyval) = QCODEY((yyvsp[(1) - (3)]), qtree_binop("add",  (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]))); ;}
    break;

  case 61:

    { (yyval) = QCODEY((yyvsp[(1) - (3)]), qtree_binop("sub",  (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]))); ;}
    break;

  case 62:

    { (yyval) = QCODEY((yyvsp[(1) - (3)]), qtree_binop("mul",  (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]))); ;}
    break;

  case 63:

    { (yyval) = QCODEY((yyvsp[(1) - (3)]), qtree_binop("div",  (yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]))); ;}
    break;

  case 64:

    { (yyval) = QCODEY((yyvsp[(2) - (2)]), qtree_unop("neg",   (yyvsp[(2) - (2)]))); ;}
    break;

  case 65:

    { (yyval) = QCODEY((yyvsp[(2) - (2)]), qtree_unop("not", (yyvsp[(2) - (2)]))); ;}
    break;

  case 66:

    { (yyval) = (yyvsp[(2) - (3)]); ;}
    break;

  case 70:

    { (yyval) = QCODEY((yyvsp[(5) - (5)]), new qConvert((yyvsp[(3) - (5)])->neu_type, (yyvsp[(5) - (5)]), "!!")); ;}
    break;

  case 75:

    { (yyval) = qtree_seq_append((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)])); ;}
    break;

  case 76:

    { (yyval) = qtree_seq_start((yyvsp[(1) - (1)])); ;}
    break;

  case 77:

    { (yyval) = QCODEY((yyvsp[(1) - (1)]), qtree_type(parm->module, (yyvsp[(1) - (1)]))); ;}
    break;

  case 78:

    { (yyval) = QCODEY((yyvsp[(1) - (2)]), new qTypeHolder((yyvsp[(1) - (2)])->neu_type->createPointer())); ;}
    break;

  case 79:

    { (yyval) = QCODEY((yyvsp[(2) - (2)]), new qTypeHolder((yyvsp[(2) - (2)])->neu_type->CreateConst())); ;}
    break;

  case 80:

    { (yyval) = QCODEY((yyvsp[(1) - (4)]), new qTypeHolder((yyvsp[(1) - (4)])->neu_type->CreateArray((yyvsp[(3) - (4)])))); ;}
    break;

  case 81:

    { (yyval) = QCODEY((yyvsp[(1) - (3)]), qtree_subvariable((yyvsp[(1) - (3)]), (yyvsp[(3) - (3)]))); ;}
    break;

  case 82:

    { (yyval) = QCODEY((yyvsp[(1) - (3)]), qtree_subvariable(new qDereference((yyvsp[(1) - (3)])), (yyvsp[(3) - (3)]))); ;}
    break;

  case 83:

    { (yyval) = QCODEY((yyvsp[(1) - (1)]), qtree_variable((yyvsp[(1) - (1)]))); ;}
    break;

  case 84:

    { (yyval) = QCODEY((yyvsp[(2) - (2)]), new qPointer((yyvsp[(2) - (2)]))); ;}
    break;

  case 85:

    { (yyval) = QCODEY((yyvsp[(2) - (2)]), new qDereference((yyvsp[(2) - (2)]))); ;}
    break;

  case 86:

    { (yyval) = (yyvsp[(2) - (3)]); ;}
    break;

  case 87:

    { (yyval) = QCODEY((yyvsp[(1) - (4)]), new qArrayAccess((yyvsp[(1) - (4)]), (yyvsp[(3) - (4)]))); ;}
    break;



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
      yyerror (parm, scanner, YY_("syntax error"));
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
	    yyerror (parm, scanner, yymsg);
	  }
	else
	  {
	    yyerror (parm, scanner, YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
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
		      yytoken, &yylval, parm, scanner);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
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
		  yystos[yystate], yyvsp, parm, scanner);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

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

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (parm, scanner, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, parm, scanner);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, parm, scanner);
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





