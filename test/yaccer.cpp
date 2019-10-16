/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "yaccer.y" /* yacc.c:339  */


#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "node.hpp"
using namespace std;
extern int yylex();
extern int yylineno;
void yyerror(char*s);


#define ACCESS(x) (*(*x))

int yylex();
void yyerror(char* s);

Node* createNode(char* name);
void addChildToParent(Node** parent, Node* child);
void printTree(Node* root); 


#line 91 "yaccer.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "yaccer.hpp".  */
#ifndef YY_YY_YACCER_HPP_INCLUDED
# define YY_YY_YACCER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    LIT_INT = 258,
    INT = 259,
    TRUE = 260,
    FALSE = 261,
    BOOLEAN = 262,
    BREAK = 263,
    CLASS = 264,
    CONTINUE = 265,
    VOID = 266,
    EXTENDS = 267,
    RETURN = 268,
    IF = 269,
    ELSE = 270,
    WHILE = 271,
    THIS = 272,
    TOK_NULL = 273,
    NEW = 274,
    ERROR = 275,
    LIT_STR = 276,
    ARR = 277,
    THIS_DOT = 278,
    ID = 279,
    EQ = 280,
    DIFF = 281,
    LESS_EQ = 282,
    GREAT_EQ = 283,
    AND = 284,
    OR = 285,
    PREC_UNARY_OP = 286,
    FILLED_BRACK = 287,
    PREC_ELSELESS_IF = 288
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 26 "yaccer.y" /* yacc.c:355  */

  struct Node* nodePointer;
  char* string;

#line 170 "yaccer.cpp" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_YACCER_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 187 "yaccer.cpp" /* yacc.c:358  */

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
#else
typedef signed char yytype_int8;
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
# elif ! defined YYSIZE_T
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
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
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

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   494

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  20
/* YYNRULES -- Number of rules.  */
#define YYNRULES  74
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  167

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   288

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    49,     2,     2,     2,    38,     2,     2,
      43,    44,    36,    34,    48,    35,    25,    37,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    46,
      26,    47,    27,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    50,     2,    51,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    42,     2,    45,     2,     2,     2,     2,
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
      28,    29,    30,    31,    32,    33,    39,    40,    41
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    54,    54,    63,    83,    89,    96,   114,   121,   129,
     136,   145,   159,   179,   185,   192,   199,   206,   215,   224,
     232,   239,   246,   253,   260,   269,   280,   289,   297,   303,
     309,   316,   322,   333,   340,   349,   358,   367,   376,   385,
     394,   403,   412,   421,   430,   439,   448,   457,   464,   469,
     474,   479,   484,   489,   495,   503,   512,   518,   523,   528,
     533,   540,   546,   555,   560,   567,   572,   582,   589,   598,
     605,   612,   617,   625,   633
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "LIT_INT", "INT", "TRUE", "FALSE",
  "BOOLEAN", "BREAK", "CLASS", "CONTINUE", "VOID", "EXTENDS", "RETURN",
  "IF", "ELSE", "WHILE", "THIS", "TOK_NULL", "NEW", "ERROR", "LIT_STR",
  "ARR", "THIS_DOT", "ID", "'.'", "'<'", "'>'", "EQ", "DIFF", "LESS_EQ",
  "GREAT_EQ", "AND", "OR", "'+'", "'-'", "'*'", "'/'", "'%'",
  "PREC_UNARY_OP", "FILLED_BRACK", "PREC_ELSELESS_IF", "'{'", "'('", "')'",
  "'}'", "';'", "'='", "','", "'!'", "'['", "']'", "$accept", "goal",
  "mainclass", "classdecs", "classdec", "classmembers", "vardec",
  "methoddec", "params", "paramsrest", "param", "extendsopt", "blockstmts",
  "stmt", "expr", "type", "object", "exprlist", "exprlistopt",
  "filledbracks", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,    46,    60,    62,   280,   281,
     282,   283,   284,   285,    43,    45,    42,    47,    37,   286,
     287,   288,   123,    40,    41,   125,    59,    61,    44,    33,
      91,    93
};
# endif

#define YYPACT_NINF -132

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-132)))

#define YYTABLE_NINF -61

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-61)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -6,   -12,    18,    14,   -15,  -132,    23,  -132,    14,    46,
      58,  -132,    49,    53,    43,    44,  -132,    -2,    62,  -132,
    -132,  -132,  -132,    45,    -2,    -2,   -16,    66,  -132,  -132,
    -132,  -132,     9,    65,    -2,  -132,   181,    50,    51,    48,
       6,  -132,  -132,  -132,  -132,  -132,     0,  -132,    69,  -132,
     181,   181,   181,   181,   331,    67,    55,    70,    -2,  -132,
    -132,    76,    87,  -132,  -132,   284,    78,   397,  -132,   100,
     181,   181,   181,   181,   181,   181,   181,   181,   181,   181,
     181,   181,   181,  -132,   181,    75,    97,    97,    48,   181,
     181,  -132,  -132,    83,   456,   456,   456,   456,   456,   456,
      26,    26,    29,    29,  -132,  -132,  -132,   206,   181,    81,
      82,   172,    86,    88,    47,    97,  -132,    97,    85,    97,
     308,    54,    89,  -132,  -132,    91,  -132,   181,  -132,   233,
    -132,  -132,  -132,   353,   181,   181,    92,   260,  -132,    93,
    -132,   109,   181,    35,  -132,  -132,   104,  -132,  -132,   417,
     437,  -132,  -132,    98,   375,  -132,   139,   139,   181,  -132,
     121,  -132,   106,   139,   105,  -132,  -132
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     5,     0,     1,     0,     2,     5,     0,
      19,     4,     0,     0,     0,     0,    18,     9,     0,    58,
      57,    59,    60,     0,     9,     9,     0,     0,     6,     7,
       8,    56,     0,     0,    14,    10,     0,     0,     0,    16,
       0,    48,    50,    51,    65,    52,     0,    49,     0,    63,
       0,     0,     0,     0,     0,    53,     0,     0,     0,    13,
      17,    60,    61,    64,    54,    70,     0,     0,    55,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    11,     0,    47,    22,    22,    16,    72,
       0,    68,    67,     0,    35,    34,    38,    39,    37,    36,
      41,    40,    42,    43,    45,    44,    46,     0,     0,     0,
       0,     0,     0,     0,    63,    22,    33,    22,     0,    22,
       0,     0,     0,    15,    71,     0,    69,    72,    74,     0,
      29,    28,    31,     0,     0,     0,     0,    70,    20,     0,
      21,     0,     0,     0,    12,    62,     0,    73,    30,     0,
       0,    23,     3,     0,     0,    66,     0,     0,    72,    27,
      24,    26,     0,     0,    66,    25,    32
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -132,  -132,  -132,   146,  -132,    59,    -4,  -132,  -132,    71,
     103,  -132,   -86,  -131,   -36,    34,  -132,   -41,  -108,  -132
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,     7,     8,    23,   117,    25,    38,    59,
      39,    14,   118,   119,   120,   121,    55,   124,   125,    85
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      54,   122,    19,     1,    19,    20,    31,    20,    32,    21,
      66,    21,     4,    24,    64,    65,    67,    68,     5,   146,
      24,    24,    22,     6,    61,   160,   161,     9,    31,   136,
      60,   138,   165,   140,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,    10,   107,   126,
     162,    26,    34,    65,    65,    35,    36,    12,    26,    26,
      78,    79,    80,    81,    82,    80,    81,    82,    40,   -60,
      13,   -60,   129,    15,    66,   133,    31,    16,   143,   137,
      62,    35,    36,    29,    30,    17,    27,    18,    33,    37,
      28,    65,    40,    63,    56,    57,    58,    86,   149,   150,
      41,    19,    42,    43,    20,   109,   154,   110,    21,    31,
     111,   112,    87,   113,    44,    45,    46,    84,    47,    89,
      48,   114,    65,    91,    93,   108,   127,   130,   131,   134,
     139,   135,    50,   153,   144,   145,   163,   151,   152,   115,
      52,   158,    41,   116,    42,    43,    53,   109,   155,   110,
     164,   166,   111,   112,    11,   113,    44,    45,    46,   123,
      47,    88,    48,    49,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    50,    41,     0,    42,    43,     0,
       0,   115,    52,     0,    41,   116,    42,    43,    53,    44,
      45,    46,     0,    47,     0,    48,    49,     0,    44,    45,
      46,     0,    47,     0,    48,    49,     0,    50,     0,     0,
       0,     0,     0,     0,    51,    52,    50,     0,   132,     0,
       0,    53,     0,    51,    52,     0,     0,     0,     0,     0,
      53,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   128,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   147,   141,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,     0,
       0,     0,     0,     0,     0,     0,     0,   142,    90,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    90,   141,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,     0,     0,     0,
       0,     0,     0,     0,     0,   142,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
       0,     0,     0,     0,     0,     0,     0,    83,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,     0,     0,     0,     0,     0,     0,     0,   148,
      69,    70,    71,    72,    73,    74,    75,    76,    77,    78,
      79,    80,    81,    82,     0,     0,     0,     0,     0,     0,
       0,   159,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,     0,     0,     0,     0,
       0,    92,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,     0,     0,     0,     0,
       0,   156,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,     0,     0,     0,     0,
       0,   157,   -61,   -61,   -61,   -61,   -61,   -61,    76,    77,
      78,    79,    80,    81,    82
};

static const yytype_int16 yycheck[] =
{
      36,    87,     4,     9,     4,     7,    22,     7,    24,    11,
      51,    11,    24,    17,    50,    51,    52,    53,     0,   127,
      24,    25,    24,     9,    24,   156,   157,    42,    22,   115,
      24,   117,   163,   119,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    24,    84,    90,
     158,    17,    43,    89,    90,    46,    47,    11,    24,    25,
      34,    35,    36,    37,    38,    36,    37,    38,    34,    22,
      12,    24,   108,    24,   115,   111,    22,    24,    24,   115,
      46,    46,    47,    24,    25,    42,    24,    43,    22,    24,
      45,   127,    58,    24,    44,    44,    48,    42,   134,   135,
       3,     4,     5,     6,     7,     8,   142,    10,    11,    22,
      13,    14,    42,    16,    17,    18,    19,    50,    21,    43,
      23,    24,   158,    45,    24,    50,    43,    46,    46,    43,
      45,    43,    35,    24,    45,    44,    15,    45,    45,    42,
      43,    43,     3,    46,     5,     6,    49,     8,    44,    10,
      44,    46,    13,    14,     8,    16,    17,    18,    19,    88,
      21,    58,    23,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    35,     3,    -1,     5,     6,    -1,
      -1,    42,    43,    -1,     3,    46,     5,     6,    49,    17,
      18,    19,    -1,    21,    -1,    23,    24,    -1,    17,    18,
      19,    -1,    21,    -1,    23,    24,    -1,    35,    -1,    -1,
      -1,    -1,    -1,    -1,    42,    43,    35,    -1,    46,    -1,
      -1,    49,    -1,    42,    43,    -1,    -1,    -1,    -1,    -1,
      49,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    51,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    48,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    48,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    47,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    46,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    46,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,
      -1,    44,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,
      -1,    44,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,
      -1,    44,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     9,    53,    54,    24,     0,     9,    55,    56,    42,
      24,    55,    11,    12,    63,    24,    24,    42,    43,     4,
       7,    11,    24,    57,    58,    59,    67,    24,    45,    57,
      57,    22,    24,    22,    43,    46,    47,    24,    60,    62,
      67,     3,     5,     6,    17,    18,    19,    21,    23,    24,
      35,    42,    43,    49,    66,    68,    44,    44,    48,    61,
      24,    24,    67,    24,    66,    66,    69,    66,    66,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    46,    50,    71,    42,    42,    62,    43,
      48,    45,    44,    24,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    50,     8,
      10,    13,    14,    16,    24,    42,    46,    58,    64,    65,
      66,    67,    64,    61,    69,    70,    69,    43,    51,    66,
      46,    46,    46,    66,    43,    43,    64,    66,    64,    45,
      64,    25,    47,    24,    45,    44,    70,    51,    46,    66,
      66,    45,    45,    24,    66,    44,    44,    44,    43,    46,
      65,    65,    70,    15,    44,    65,    46
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    52,    53,    54,    55,    55,    56,    57,    57,    57,
      58,    58,    59,    60,    60,    61,    61,    62,    63,    63,
      64,    64,    64,    65,    65,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    67,    67,    67,    67,
      67,    68,    68,    68,    68,    68,    68,    68,    68,    69,
      69,    70,    70,    71,    71
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     2,    14,     2,     0,     6,     2,     2,     0,
       3,     5,     8,     2,     0,     3,     0,     2,     2,     0,
       2,     2,     0,     3,     5,     7,     5,     4,     2,     2,
       3,     2,     7,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     1,     1,
       1,     1,     1,     1,     2,     2,     2,     1,     1,     1,
       1,     2,     5,     1,     2,     1,     6,     3,     3,     3,
       1,     1,     0,     4,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

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
#ifndef YYINITDEPTH
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
static YYSIZE_T
yystrlen (const char *yystr)
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
static char *
yystpcpy (char *yydest, const char *yysrc)
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

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
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
  int yytoken = 0;
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

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
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
      if (yytable_value_is_error (yyn))
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
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
     '$$ = $1'.

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
#line 54 "yaccer.y" /* yacc.c:1646  */
    {
                                      Node* parent = createNode("goal");
                                      addChildToParent(&parent, (yyvsp[-1].nodePointer));
                                      addChildToParent(&parent, (yyvsp[0].nodePointer));
									  printTree(parent);
                                      printf("\n");
                                    }
#line 1444 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 63 "yaccer.y" /* yacc.c:1646  */
    {
                                      Node* parent = createNode("mainclass");
                                      addChildToParent(&parent, createNode("CLASS"));
                                      addChildToParent(&parent, createNode("ID"));
                                      addChildToParent(&parent, createNode("{"));
                                      addChildToParent(&parent, createNode("VOID"));
                                      addChildToParent(&parent, createNode("ID"));
                                      addChildToParent(&parent, createNode("("));
                                      addChildToParent(&parent, createNode("ID"));
                                      addChildToParent(&parent, createNode("ARR"));
                                      addChildToParent(&parent, createNode("ID"));
                                      addChildToParent(&parent, createNode(")"));
                                      addChildToParent(&parent, createNode("{"));
                                      addChildToParent(&parent, (yyvsp[-2].nodePointer));
                                      addChildToParent(&parent, createNode("}"));
                                      addChildToParent(&parent, createNode("}"));
                                      (yyval.nodePointer) = parent;
                                    }
#line 1467 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 83 "yaccer.y" /* yacc.c:1646  */
    {
                                      Node* parent = createNode("classdecs");
                                      addChildToParent(&parent, (yyvsp[-1].nodePointer));
                                      addChildToParent(&parent, (yyvsp[0].nodePointer));
                                      (yyval.nodePointer) = parent;
                                    }
#line 1478 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 89 "yaccer.y" /* yacc.c:1646  */
    {
                                      Node* parent = createNode("classdecs");
                                      addChildToParent(&parent, createNode("EPS"));
                                      (yyval.nodePointer) = parent;
                                    }
#line 1488 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 96 "yaccer.y" /* yacc.c:1646  */
    {
                                      Node* parent = createNode("classdec");
                                      Node* child1 = createNode("CLASS");
                                      Node* child2 = createNode("ID");
                                      Node* child4 = createNode("{");
                                      Node* child6 = createNode("}");

                                      addChildToParent(&parent, child1);
                                      addChildToParent(&parent, child2);
                                      addChildToParent(&parent, (yyvsp[-3].nodePointer));
                                      addChildToParent(&parent, child4);
                                      addChildToParent(&parent, (yyvsp[-1].nodePointer));
                                      addChildToParent(&parent, child6);

                                      (yyval.nodePointer) = parent;
                                    }
#line 1509 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 114 "yaccer.y" /* yacc.c:1646  */
    {
                                      Node* parent = createNode("classmembers");

                                      addChildToParent(&parent, (yyvsp[-1].nodePointer));
                                      addChildToParent(&parent, (yyvsp[0].nodePointer));
                                      (yyval.nodePointer) = parent;
                                    }
#line 1521 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 122 "yaccer.y" /* yacc.c:1646  */
    {
                                      Node* parent = createNode("classmembers");

                                      addChildToParent(&parent, (yyvsp[-1].nodePointer));
                                      addChildToParent(&parent, (yyvsp[0].nodePointer));
                                      (yyval.nodePointer) = parent;
                                    }
#line 1533 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 129 "yaccer.y" /* yacc.c:1646  */
    {
                                      Node* parent = createNode("classmembers");
                                      addChildToParent(&parent, createNode("EPS"));
                                      (yyval.nodePointer) = parent;
                                    }
#line 1543 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 136 "yaccer.y" /* yacc.c:1646  */
    {
                                      Node* parent = createNode("vardec");
                                      Node* child2 = createNode("ID");
                                      Node* child3 = createNode(";");
                                      addChildToParent(&parent, (yyvsp[-2].nodePointer));
                                      addChildToParent(&parent, child2);
                                      addChildToParent(&parent, child3);
                                      (yyval.nodePointer) = parent;
                                    }
#line 1557 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 145 "yaccer.y" /* yacc.c:1646  */
    {
                                      Node* parent = createNode("vardec");
                                      Node* child2 = createNode("ID");
                                      Node* child3 = createNode("=");
                                      Node* child5 = createNode(";");
                                      addChildToParent(&parent, (yyvsp[-4].nodePointer));
                                      addChildToParent(&parent, child2);
                                      addChildToParent(&parent, child3);
                                      addChildToParent(&parent, (yyvsp[-1].nodePointer));
                                      addChildToParent(&parent, child5);
                                      (yyval.nodePointer) = parent;
                                    }
#line 1574 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 160 "yaccer.y" /* yacc.c:1646  */
    {
                                      Node* parent = createNode("methoddec");
                                      Node* child2 = createNode("ID");
                                      Node* child3 = createNode("(");
                                      Node* child5 = createNode(")");
                                      Node* child6 = createNode("{");
                                      Node* child8 = createNode("}");
                                      addChildToParent(&parent, (yyvsp[-7].nodePointer));
                                      addChildToParent(&parent, child2);
                                      addChildToParent(&parent, child3);
                                      addChildToParent(&parent, (yyvsp[-4].nodePointer));
                                      addChildToParent(&parent, child5);
                                      addChildToParent(&parent, child6);
                                      addChildToParent(&parent, (yyvsp[-1].nodePointer));
                                      addChildToParent(&parent, child8);
                                      (yyval.nodePointer) = parent;
                                    }
#line 1596 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 179 "yaccer.y" /* yacc.c:1646  */
    {
                                      Node* parent = createNode("params");
                                      addChildToParent(&parent, (yyvsp[-1].nodePointer));
                                      addChildToParent(&parent, (yyvsp[0].nodePointer));
                                      (yyval.nodePointer) = parent;
                                    }
#line 1607 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 185 "yaccer.y" /* yacc.c:1646  */
    {
                                      Node* parent = createNode("params");
                                      addChildToParent(&parent, createNode("EPS"));
                                      (yyval.nodePointer) = parent;
                                    }
#line 1617 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 192 "yaccer.y" /* yacc.c:1646  */
    {
                                      Node* parent = createNode("paramsrest");
                                      Node* child1 = createNode(",");
                                      addChildToParent(&parent, (yyvsp[-1].nodePointer));
                                      addChildToParent(&parent, (yyvsp[0].nodePointer));
                                      (yyval.nodePointer) = parent;
                                    }
#line 1629 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 199 "yaccer.y" /* yacc.c:1646  */
    {
                                      Node* parent = createNode("paramsrest");
                                      addChildToParent(&parent, createNode("EPS"));
                                      (yyval.nodePointer) = parent;
                                    }
#line 1639 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 206 "yaccer.y" /* yacc.c:1646  */
    {
                                      Node* parent = createNode("param");
                                      Node* child2 = createNode("ID");
                                      addChildToParent(&parent, (yyvsp[-1].nodePointer));
                                      addChildToParent(&parent, child2);
                                      (yyval.nodePointer) = parent;
                                    }
#line 1651 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 215 "yaccer.y" /* yacc.c:1646  */
    {
                                      Node* parent = createNode("extendsopt");
                                      Node* child1 = createNode("EXTENDS");
                                      Node* child2 = createNode("ID");
                                      addChildToParent(&parent, child1);
                                      addChildToParent(&parent, child2);

                                      (yyval.nodePointer) = parent;
                                    }
#line 1665 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 224 "yaccer.y" /* yacc.c:1646  */
    {
                                      Node* parent = createNode("extendsopt");
                                      addChildToParent(&parent, createNode("EPS"));
                                      (yyval.nodePointer) = parent;
                                    }
#line 1675 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 232 "yaccer.y" /* yacc.c:1646  */
    {
                                      Node* parent = createNode("blockstmts");
                                      addChildToParent(&parent, (yyvsp[-1].nodePointer));
                                      addChildToParent(&parent, (yyvsp[0].nodePointer));

                                      (yyval.nodePointer) = parent;
                                    }
#line 1687 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 239 "yaccer.y" /* yacc.c:1646  */
    {
                                      Node* parent = createNode("blockstmts");
                                      addChildToParent(&parent, (yyvsp[-1].nodePointer));
                                      addChildToParent(&parent, (yyvsp[0].nodePointer));

                                      (yyval.nodePointer) = parent;
                                    }
#line 1699 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 246 "yaccer.y" /* yacc.c:1646  */
    {
                                      Node* parent = createNode("blockstmts");
                                      addChildToParent(&parent, createNode("EPS"));
                                      (yyval.nodePointer) = parent;
                                    }
#line 1709 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 253 "yaccer.y" /* yacc.c:1646  */
    {
                                                        Node* parent = createNode("stmt");
                                                        addChildToParent(&parent, createNode("{"));
                                                        addChildToParent(&parent, (yyvsp[-1].nodePointer));
                                                        addChildToParent(&parent, createNode("}"));
                                                        (yyval.nodePointer) = parent;
                                                      }
#line 1721 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 260 "yaccer.y" /* yacc.c:1646  */
    {
                                                        Node* parent = createNode("stmt");
                                                        addChildToParent(&parent, createNode("IF"));
                                                        addChildToParent(&parent, createNode("("));
                                                        addChildToParent(&parent, (yyvsp[-2].nodePointer));
                                                        addChildToParent(&parent, createNode(")"));
                                                        addChildToParent(&parent, (yyvsp[0].nodePointer));
                                                        (yyval.nodePointer) = parent;
                                                      }
#line 1735 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 269 "yaccer.y" /* yacc.c:1646  */
    {
                                                        Node* parent = createNode("stmt");
                                                        addChildToParent(&parent, createNode("IF"));
                                                        addChildToParent(&parent, createNode("("));
                                                        addChildToParent(&parent, (yyvsp[-4].nodePointer));
                                                        addChildToParent(&parent, createNode(")"));
                                                        addChildToParent(&parent, (yyvsp[-2].nodePointer));
                                                        addChildToParent(&parent, createNode("ELSE"));
                                                        addChildToParent(&parent, (yyvsp[0].nodePointer));
                                                        (yyval.nodePointer) = parent;
                                                      }
#line 1751 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 280 "yaccer.y" /* yacc.c:1646  */
    {
                                                        Node* parent = createNode("stmt");
                                                        addChildToParent(&parent, createNode("WHILE"));
                                                        addChildToParent(&parent, createNode("("));
                                                        addChildToParent(&parent, (yyvsp[-2].nodePointer));
                                                        addChildToParent(&parent, createNode(")"));
                                                        addChildToParent(&parent, (yyvsp[0].nodePointer));
                                                        (yyval.nodePointer) = parent;
                                                      }
#line 1765 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 289 "yaccer.y" /* yacc.c:1646  */
    {
                                                        Node* parent = createNode("stmt");
                                                        addChildToParent(&parent, (yyvsp[-3].nodePointer));
                                                        addChildToParent(&parent, createNode("="));
                                                        addChildToParent(&parent, (yyvsp[-1].nodePointer));
                                                        addChildToParent(&parent, createNode(";"));
                                                        (yyval.nodePointer) = parent;
                                                      }
#line 1778 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 297 "yaccer.y" /* yacc.c:1646  */
    {
                                                        Node* parent = createNode("stmt");
                                                        addChildToParent(&parent, createNode("CONTINUE"));
                                                        addChildToParent(&parent, createNode(";"));
                                                        (yyval.nodePointer) = parent;
                                                      }
#line 1789 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 303 "yaccer.y" /* yacc.c:1646  */
    {
                                                        Node* parent = createNode("stmt");
                                                        addChildToParent(&parent, createNode("BREAK"));
                                                        addChildToParent(&parent, createNode(";"));
                                                        (yyval.nodePointer) = parent;
                                                      }
#line 1800 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 309 "yaccer.y" /* yacc.c:1646  */
    {
                                                        Node* parent = createNode("stmt");
                                                        addChildToParent(&parent, createNode("RETURN"));
                                                        addChildToParent(&parent, (yyvsp[-1].nodePointer));
                                                        addChildToParent(&parent, createNode(";"));
                                                        (yyval.nodePointer) = parent;
                                                      }
#line 1812 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 316 "yaccer.y" /* yacc.c:1646  */
    {
                                                        Node* parent = createNode("stmt");
                                                        addChildToParent(&parent, createNode("RETURN"));
                                                        addChildToParent(&parent, createNode(";"));
                                                        (yyval.nodePointer) = parent;
                                                      }
#line 1823 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 322 "yaccer.y" /* yacc.c:1646  */
    {
                                                        Node* parent = createNode("stmt");
                                                        addChildToParent(&parent, (yyvsp[-6].nodePointer));
                                                        addChildToParent(&parent, createNode("."));
                                                        addChildToParent(&parent, createNode("ID"));
                                                        addChildToParent(&parent, createNode("("));
                                                        addChildToParent(&parent, (yyvsp[-2].nodePointer));
                                                        addChildToParent(&parent, createNode(")"));
                                                        addChildToParent(&parent, createNode(";"));
                                                        (yyval.nodePointer) = parent;
                                                      }
#line 1839 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 333 "yaccer.y" /* yacc.c:1646  */
    {
                                                        Node* parent = createNode("stmt");
                                                        addChildToParent(&parent, createNode(";"));
                                                        (yyval.nodePointer) = parent;
                                                      }
#line 1849 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 340 "yaccer.y" /* yacc.c:1646  */
    {
                                Node* parent = createNode("expr");
                                Node* child2 = createNode(">");
                                addChildToParent(&parent, (yyvsp[-2].nodePointer));
                                addChildToParent(&parent, child2);
                                addChildToParent(&parent, (yyvsp[0].nodePointer));
                                (yyval.nodePointer) = parent;
                               }
#line 1862 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 349 "yaccer.y" /* yacc.c:1646  */
    {
                                Node* parent = createNode("expr");
                                Node* child2 = createNode("<");
                                addChildToParent(&parent, (yyvsp[-2].nodePointer));
                                addChildToParent(&parent, child2);
                                addChildToParent(&parent, (yyvsp[0].nodePointer));
                                (yyval.nodePointer) = parent;
                               }
#line 1875 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 358 "yaccer.y" /* yacc.c:1646  */
    {
                                Node* parent = createNode("expr");
                                Node* child2 = createNode(">=");
                                addChildToParent(&parent, (yyvsp[-2].nodePointer));
                                addChildToParent(&parent, child2);
                                addChildToParent(&parent, (yyvsp[0].nodePointer));
                                (yyval.nodePointer) = parent;
                               }
#line 1888 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 367 "yaccer.y" /* yacc.c:1646  */
    {
                                Node* parent = createNode("expr");
                                Node* child2 = createNode("<=");
                                addChildToParent(&parent, (yyvsp[-2].nodePointer));
                                addChildToParent(&parent, child2);
                                addChildToParent(&parent, (yyvsp[0].nodePointer));
                                (yyval.nodePointer) = parent;
                               }
#line 1901 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 376 "yaccer.y" /* yacc.c:1646  */
    {
                                Node* parent = createNode("expr");
                                Node* child2 = createNode("==");
                                addChildToParent(&parent, (yyvsp[-2].nodePointer));
                                addChildToParent(&parent, child2);
                                addChildToParent(&parent, (yyvsp[0].nodePointer));
                                (yyval.nodePointer) = parent;
                               }
#line 1914 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 385 "yaccer.y" /* yacc.c:1646  */
    {
                                Node* parent = createNode("expr");
                                Node* child2 = createNode("!=");
                                addChildToParent(&parent, (yyvsp[-2].nodePointer));
                                addChildToParent(&parent, child2);
                                addChildToParent(&parent, (yyvsp[0].nodePointer));
                                (yyval.nodePointer) = parent;
                               }
#line 1927 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 394 "yaccer.y" /* yacc.c:1646  */
    {
                                Node* parent = createNode("expr");
                                Node* child2 = createNode("||");
                                addChildToParent(&parent, (yyvsp[-2].nodePointer));
                                addChildToParent(&parent, child2);
                                addChildToParent(&parent, (yyvsp[0].nodePointer));
                                (yyval.nodePointer) = parent;
                               }
#line 1940 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 403 "yaccer.y" /* yacc.c:1646  */
    {
                                Node* parent = createNode("expr");
                                Node* child2 = createNode("&&");
                                addChildToParent(&parent, (yyvsp[-2].nodePointer));
                                addChildToParent(&parent, child2);
                                addChildToParent(&parent, (yyvsp[0].nodePointer));
                                (yyval.nodePointer) = parent;
                               }
#line 1953 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 412 "yaccer.y" /* yacc.c:1646  */
    {
                                Node* parent = createNode("expr");
                                Node* child2 = createNode("+");
                                addChildToParent(&parent, (yyvsp[-2].nodePointer));
                                addChildToParent(&parent, child2);
                                addChildToParent(&parent, (yyvsp[0].nodePointer));
                                (yyval.nodePointer) = parent;
                               }
#line 1966 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 421 "yaccer.y" /* yacc.c:1646  */
    {
                                Node* parent = createNode("expr");
                                Node* child2 = createNode("-");
                                addChildToParent(&parent, (yyvsp[-2].nodePointer));
                                addChildToParent(&parent, child2);
                                addChildToParent(&parent, (yyvsp[0].nodePointer));
                                (yyval.nodePointer) = parent;
                               }
#line 1979 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 430 "yaccer.y" /* yacc.c:1646  */
    {
                                Node* parent = createNode("expr");
                                Node* child2 = createNode("/");
                                addChildToParent(&parent, (yyvsp[-2].nodePointer));
                                addChildToParent(&parent, child2);
                                addChildToParent(&parent, (yyvsp[0].nodePointer));
                                (yyval.nodePointer) = parent;
                               }
#line 1992 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 439 "yaccer.y" /* yacc.c:1646  */
    {
                                Node* parent = createNode("expr");
                                Node* child2 = createNode("*");
                                addChildToParent(&parent, (yyvsp[-2].nodePointer));
                                addChildToParent(&parent, child2);
                                addChildToParent(&parent, (yyvsp[0].nodePointer));
                                (yyval.nodePointer) = parent;
                               }
#line 2005 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 448 "yaccer.y" /* yacc.c:1646  */
    {
                                Node* parent = createNode("expr");
                                Node* child2 = createNode("%");
                                addChildToParent(&parent, (yyvsp[-2].nodePointer));
                                addChildToParent(&parent, child2);
                                addChildToParent(&parent, (yyvsp[0].nodePointer));
                                (yyval.nodePointer) = parent;
                               }
#line 2018 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 457 "yaccer.y" /* yacc.c:1646  */
    {
                                Node* parent = createNode("expr");
                                addChildToParent(&parent, (yyvsp[-1].nodePointer));
                                addChildToParent(&parent, (yyvsp[0].nodePointer));
                                (yyval.nodePointer) = parent;
                               }
#line 2029 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 464 "yaccer.y" /* yacc.c:1646  */
    {
                                 Node* parent = createNode("LIT_INT");
                                 (yyval.nodePointer) = parent;
                              }
#line 2038 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 469 "yaccer.y" /* yacc.c:1646  */
    {
                                 Node* parent = createNode("LIT_STR");
                                 (yyval.nodePointer) = parent;
                              }
#line 2047 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 474 "yaccer.y" /* yacc.c:1646  */
    {
                                 Node* parent = createNode("TRUE");
                                 (yyval.nodePointer) = parent;
                              }
#line 2056 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 479 "yaccer.y" /* yacc.c:1646  */
    {
                                 Node* parent = createNode("FALSE");
                                 (yyval.nodePointer) = parent;
                              }
#line 2065 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 484 "yaccer.y" /* yacc.c:1646  */
    {
                                 Node* parent = createNode("NULL");
                                 (yyval.nodePointer) = parent;
                              }
#line 2074 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 489 "yaccer.y" /* yacc.c:1646  */
    {
                                 Node* parent = createNode("expr");
                                 addChildToParent(&parent, (yyvsp[0].nodePointer));
                                 (yyval.nodePointer) = parent;
                              }
#line 2084 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 495 "yaccer.y" /* yacc.c:1646  */
    {
                                        Node* parent = createNode("expr");
                                        Node* child1 = createNode("-");
                                        addChildToParent(&parent, child1);
                                        addChildToParent(&parent, (yyvsp[0].nodePointer));
                                        (yyval.nodePointer) = parent;
                                      }
#line 2096 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 503 "yaccer.y" /* yacc.c:1646  */
    {
                                        Node* parent = createNode("expr");
                                        Node* child1 = createNode("!");
                                        addChildToParent(&parent, child1);
                                        addChildToParent(&parent, (yyvsp[0].nodePointer));
                                        (yyval.nodePointer) = parent;
                                      }
#line 2108 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 512 "yaccer.y" /* yacc.c:1646  */
    {
                  Node* parent = createNode("type");
                  addChildToParent(&parent, (yyvsp[-1].nodePointer));
                  addChildToParent(&parent, createNode("[]"));
                  (yyval.nodePointer) = parent;
                }
#line 2119 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 518 "yaccer.y" /* yacc.c:1646  */
    {
                  Node* parent = createNode("type");
                  addChildToParent(&parent, createNode("BOOLEAN"));
                  (yyval.nodePointer) = parent;
                }
#line 2129 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 523 "yaccer.y" /* yacc.c:1646  */
    {
                  Node* parent = createNode("type");
                  addChildToParent(&parent, createNode("INT"));
                  (yyval.nodePointer) = parent;
                }
#line 2139 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 528 "yaccer.y" /* yacc.c:1646  */
    {
                  Node* parent = createNode("type");
                  addChildToParent(&parent, createNode("VOID"));
                  (yyval.nodePointer) = parent;
                }
#line 2149 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 533 "yaccer.y" /* yacc.c:1646  */
    {
                  Node* parent = createNode("type");
                  addChildToParent(&parent, createNode("ID"));
                  (yyval.nodePointer) = parent;
                }
#line 2159 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 540 "yaccer.y" /* yacc.c:1646  */
    {
                                            Node* parent = createNode("object");
                                            addChildToParent(&parent, createNode("NEW"));
                                            addChildToParent(&parent, (yyvsp[0].nodePointer));
                                            (yyval.nodePointer) = parent;
                                          }
#line 2170 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 546 "yaccer.y" /* yacc.c:1646  */
    {
                                            Node* parent = createNode("object");
                                            addChildToParent(&parent, createNode("NEW"));
                                            addChildToParent(&parent, createNode("ID"));
                                            addChildToParent(&parent, createNode("("));
                                            addChildToParent(&parent, (yyvsp[-1].nodePointer));
                                            addChildToParent(&parent, createNode(")"));
                                            (yyval.nodePointer) = parent;
                                          }
#line 2184 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 555 "yaccer.y" /* yacc.c:1646  */
    {
                                            Node* parent = createNode("object");
                                            addChildToParent(&parent, createNode("ID"));
                                            (yyval.nodePointer) = parent;
                                          }
#line 2194 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 560 "yaccer.y" /* yacc.c:1646  */
    {
                                            Node* parent = createNode("object");
                                            addChildToParent(&parent, createNode("THIS"));
                                            addChildToParent(&parent, createNode("."));
                                            addChildToParent(&parent, createNode("ID"));
                                            (yyval.nodePointer) = parent;
                                          }
#line 2206 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 567 "yaccer.y" /* yacc.c:1646  */
    {
                                            Node* parent = createNode("object");
                                            addChildToParent(&parent, createNode("THIS"));
                                            (yyval.nodePointer) = parent;
                                          }
#line 2216 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 572 "yaccer.y" /* yacc.c:1646  */
    {
                                            Node* parent = createNode("object");
                                            addChildToParent(&parent, (yyvsp[-5].nodePointer));
                                            addChildToParent(&parent, createNode("."));
                                            addChildToParent(&parent, createNode("ID"));
                                            addChildToParent(&parent, createNode("("));
                                            addChildToParent(&parent, (yyvsp[-1].nodePointer));
                                            addChildToParent(&parent, createNode(")"));
                                            (yyval.nodePointer) = parent;
                                          }
#line 2231 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 582 "yaccer.y" /* yacc.c:1646  */
    {
                                            Node* parent = createNode("object");
                                            addChildToParent(&parent, createNode("("));
                                            addChildToParent(&parent, (yyvsp[-1].nodePointer));
                                            addChildToParent(&parent, createNode(")"));
                                            (yyval.nodePointer) = parent;
                                          }
#line 2243 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 589 "yaccer.y" /* yacc.c:1646  */
    {
                                            Node* parent = createNode("object");
                                            addChildToParent(&parent, createNode("'{'"));
                                            addChildToParent(&parent, (yyvsp[-1].nodePointer));
                                            addChildToParent(&parent, createNode("'}'"));
                                            (yyval.nodePointer) = parent;
                                          }
#line 2255 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 598 "yaccer.y" /* yacc.c:1646  */
    {
                                Node* parent = createNode("exprlist");
                                addChildToParent(&parent, (yyvsp[-2].nodePointer));
                                addChildToParent(&parent, createNode(","));
                                addChildToParent(&parent, (yyvsp[0].nodePointer));
                                (yyval.nodePointer) = parent;
                              }
#line 2267 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 605 "yaccer.y" /* yacc.c:1646  */
    {
                                Node* parent = createNode("exprlist");
                                addChildToParent(&parent, (yyvsp[0].nodePointer));
                                (yyval.nodePointer) = parent;
                              }
#line 2277 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 71:
#line 612 "yaccer.y" /* yacc.c:1646  */
    {
                          Node* parent = createNode("exprlistopt");
                          addChildToParent(&parent, (yyvsp[0].nodePointer));
                          (yyval.nodePointer) = parent;
                        }
#line 2287 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 72:
#line 617 "yaccer.y" /* yacc.c:1646  */
    {
                          Node* parent = createNode("exprlistopt");
                          addChildToParent(&parent, createNode("EPS"));
                          (yyval.nodePointer) = parent;
                        }
#line 2297 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 73:
#line 625 "yaccer.y" /* yacc.c:1646  */
    {
                                            Node* parent = createNode("filledbracks");
                                            addChildToParent(&parent, (yyvsp[-3].nodePointer));
                                            addChildToParent(&parent, createNode("["));
                                            addChildToParent(&parent, (yyvsp[-1].nodePointer));
                                            addChildToParent(&parent, createNode("]"));
                                            (yyval.nodePointer) = parent;
                                          }
#line 2310 "yaccer.cpp" /* yacc.c:1646  */
    break;

  case 74:
#line 633 "yaccer.y" /* yacc.c:1646  */
    {
                                            Node* parent = createNode("filledbracks");
                                            addChildToParent(&parent, createNode("["));
                                            addChildToParent(&parent, (yyvsp[-1].nodePointer));
                                            addChildToParent(&parent, createNode("]"));
                                            (yyval.nodePointer) = parent;
                                          }
#line 2322 "yaccer.cpp" /* yacc.c:1646  */
    break;


#line 2326 "yaccer.cpp" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
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
                      yytoken, &yylval);
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

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
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

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


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

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
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
  return yyresult;
}
#line 641 "yaccer.y" /* yacc.c:1906  */


void yyerror(char *s) {
   cout << "Syntax error on line " << yylineno << endl; //TODO: line number
}


Node* createNode(char* content){
  Node* newNode = (Node*) malloc(sizeof(Node));
  newNode->content = content;
//  printf("createNode\n");
  return newNode;
}

void addChildToParent(Node** parent, Node* child){
  for(int i = 0; i < NUMBER_OF_CHILDREN; ++i){
    if( ACCESS(parent).children[i] == NULL  ){
      ACCESS(parent).children[i] = child;
      break;
    }
  }

  //printf("added child\n");
}

void printTree(Node* root){
  if(root->children[0] != NULL) {
    printf(" { ");
    printf(" \"%s\" ", root->content);

    printf(" : [ ");

    for(int i = 0; i < NUMBER_OF_CHILDREN; i++){
      if(root->children[i] == NULL)
        break;

      if(i > 0)
        printf(" , ");

      printTree(root->children[i]);
    }

    printf("]");
    printf(" } ");
  } else {
    printf(" \"%s\" ", root->content);
  }
}

int main(){
  yyparse();
  return 0;
}
