/* A Bison parser, made by GNU Bison 3.4.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.4.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "./src/parser/yaccer.y"


#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ast.hpp"
#include "error.hpp"
#include "global.hpp"
#include "statement.hpp"

using std::cout;
using std::endl;

extern int yylex();
extern int yylineno;
void yyerror(const char* s);

void errorMsgPrefix();

Program* program;

#line 94 "./src/parser/yaccer.cpp"

# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_SRC_PARSER_YACCER_HPP_INCLUDED
# define YY_YY_SRC_PARSER_YACCER_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 25 "./src/parser/yaccer.y"

    #include <deque>
    #include "ast.hpp"
    #include "statement.hpp"
    using std::deque;

    struct ClassMember{
        bool isField;
        union{
            Method* method;
            Field* field;
        };
    };

#line 143 "./src/parser/yaccer.cpp"

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT = 258,
    TRUE = 259,
    FALSE = 260,
    BOOLEAN = 261,
    BREAK = 262,
    CLASS = 263,
    CONTINUE = 264,
    VOID = 265,
    EXTENDS = 266,
    RETURN = 267,
    IF = 268,
    ELSE = 269,
    WHILE = 270,
    THIS = 271,
    TOK_NULL = 272,
    NEW = 273,
    ERROR = 274,
    ARR = 275,
    THIS_DOT = 276,
    ID = 277,
    LIT_STR = 278,
    LIT_INT = 279,
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
#line 40 "./src/parser/yaccer.y"

  struct Node* nodePointer;
  char* _str;
  int _int;
  class ClassDeclaration* _classDecl;
  class Block* _block;
  class Program* _program;
  class VarDec* _varDec;
  class Method* _methodDec;
  struct Type* _type;
  deque<ClassDeclaration*>* _classDecls; 
  deque<ClassMember>* _classMembers; 
  deque<Parameter*>* _params;
  Parameter* _param;
  Expression* _expr;
  ObjExpression* _objExpr;
  deque<Expression*>* _exprList;
  Statement* _statement;

#line 208 "./src/parser/yaccer.cpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_SRC_PARSER_YACCER_HPP_INCLUDED  */



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
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
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
#  define YYSIZE_T unsigned
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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
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


#define YY_ASSERT(E) ((void) (0 && (E)))

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
#define YYLAST   457

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  20
/* YYNRULES -- Number of rules.  */
#define YYNRULES  74
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  166

#define YYUNDEFTOK  2
#define YYMAXUTOK   288

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
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
       0,    92,    92,    97,   121,   132,   136,   157,   171,   185,
     189,   192,   196,   201,   211,   215,   225,   229,   233,   236,
     241,   253,   265,   269,   272,   275,   278,   281,   284,   287,
     290,   293,   296,   309,   313,   317,   321,   325,   329,   333,
     337,   341,   345,   349,   353,   357,   361,   365,   374,   381,
     388,   395,   402,   407,   418,   422,   426,   429,   432,   435,
     438,   442,   445,   447,   449,   451,   453,   465,   467,   471,
     480,   486,   488,   492,   496
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT", "TRUE", "FALSE", "BOOLEAN",
  "BREAK", "CLASS", "CONTINUE", "VOID", "EXTENDS", "RETURN", "IF", "ELSE",
  "WHILE", "THIS", "TOK_NULL", "NEW", "ERROR", "ARR", "THIS_DOT", "ID",
  "LIT_STR", "LIT_INT", "'.'", "'<'", "'>'", "EQ", "DIFF", "LESS_EQ",
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

#define YYPACT_NINF -133

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-133)))

#define YYTABLE_NINF -61

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-61)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
       5,    -4,    28,    24,    15,  -133,    38,  -133,    24,    67,
      69,  -133,    65,    79,    61,    63,  -133,    -1,    87,  -133,
    -133,  -133,  -133,    75,    -1,    -1,    51,   104,  -133,  -133,
    -133,  -133,   -39,   103,    -1,  -133,   144,    85,    91,    88,
      54,  -133,  -133,  -133,  -133,     0,   117,  -133,  -133,  -133,
     144,   144,   144,   144,   294,    90,   100,   101,    -1,  -133,
    -133,   107,   126,  -133,  -133,   247,   106,   360,  -133,   135,
     144,   144,   144,   144,   144,   144,   144,   144,   144,   144,
     144,   144,   144,  -133,   144,   108,    46,    46,    88,   119,
     144,  -133,  -133,   127,   419,   419,   419,   419,   419,   419,
      48,    48,   -11,   -11,  -133,  -133,  -133,   169,   144,   123,
     125,   110,   129,   131,    71,    46,  -133,    46,   128,    46,
     271,    74,   132,  -133,  -133,  -133,   144,  -133,   196,  -133,
    -133,  -133,   316,   144,   144,   133,   223,  -133,   136,  -133,
     154,   144,    19,  -133,  -133,   138,  -133,  -133,   380,   400,
    -133,  -133,   137,   338,  -133,    95,    95,   144,  -133,   170,
    -133,   139,    95,   143,  -133,  -133
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
       0,    50,    51,    65,    52,     0,     0,    63,    49,    48,
       0,     0,     0,     0,     0,    53,     0,     0,     0,    13,
      17,    60,    61,    64,    54,    70,     0,     0,    55,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    11,     0,    47,    22,    22,    16,     0,
       0,    68,    67,     0,    35,    34,    38,    39,    37,    36,
      41,    40,    42,    43,    45,    44,    46,     0,     0,     0,
       0,     0,     0,     0,    63,    22,    33,    22,     0,    22,
       0,     0,     0,    15,    62,    69,    72,    74,     0,    29,
      28,    31,     0,     0,     0,     0,    70,    20,     0,    21,
       0,     0,     0,    12,    71,     0,    73,    30,     0,     0,
      23,     3,     0,     0,    66,     0,     0,    72,    27,    24,
      26,     0,     0,    66,    25,    32
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -133,  -133,  -133,   177,  -133,    98,    -5,  -133,  -133,   102,
     134,  -133,   -86,  -132,   -36,   130,  -133,   -79,    34,  -133
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     7,     8,    23,   117,    25,    38,    59,
      39,    14,   118,   119,   120,   121,    55,    66,   145,    85
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      54,   122,    19,    19,    34,    20,    20,    35,    36,    21,
      21,   125,    24,     1,    64,    65,    67,    68,     4,    24,
      24,    22,    61,   159,   160,    80,    81,    82,     5,   135,
     164,   137,     6,   139,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,   106,   144,   107,    19,
      41,    42,    20,   109,    65,   110,    21,     9,   111,   112,
      10,   113,    43,    44,    45,    35,    36,    46,   114,    48,
      49,    31,   128,    32,    31,   132,    60,    12,   144,   136,
      13,    50,    78,    79,    80,    81,    82,    15,   115,    52,
      65,   -60,   116,   -60,    31,    53,   142,   148,   149,    41,
      42,    16,   109,    17,   110,   153,    18,   111,   112,    27,
     113,    43,    44,    45,    41,    42,    46,    47,    48,    49,
      28,    65,    29,    30,    33,    37,    43,    44,    45,    56,
      50,    46,    47,    48,    49,    57,    58,   115,    52,    63,
      84,   116,    86,    87,    53,    50,    31,    26,    41,    42,
      89,    91,    51,    52,    26,    26,   131,    93,   108,    53,
      43,    44,    45,   124,    40,    46,    47,    48,    49,   129,
     126,   130,   133,   138,   134,    62,   152,   143,   150,    50,
     157,   151,   154,   163,   162,    11,    51,    52,    40,   165,
     123,   161,    88,    53,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     127,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   146,   140,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,     0,     0,     0,     0,     0,     0,     0,     0,
     141,    90,    69,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    90,   140,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
       0,     0,     0,     0,     0,     0,     0,     0,   141,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,     0,     0,     0,     0,     0,     0,     0,
      83,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,     0,     0,     0,     0,     0,
       0,     0,   147,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,     0,     0,     0,
       0,     0,     0,     0,   158,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,     0,
       0,     0,     0,     0,    92,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,     0,
       0,     0,     0,     0,   155,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,     0,
       0,     0,     0,     0,   156,   -61,   -61,   -61,   -61,   -61,
     -61,    76,    77,    78,    79,    80,    81,    82
};

static const yytype_int16 yycheck[] =
{
      36,    87,     3,     3,    43,     6,     6,    46,    47,    10,
      10,    90,    17,     8,    50,    51,    52,    53,    22,    24,
      25,    22,    22,   155,   156,    36,    37,    38,     0,   115,
     162,   117,     8,   119,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,   126,    84,     3,
       4,     5,     6,     7,    90,     9,    10,    42,    12,    13,
      22,    15,    16,    17,    18,    46,    47,    21,    22,    23,
      24,    20,   108,    22,    20,   111,    22,    10,   157,   115,
      11,    35,    34,    35,    36,    37,    38,    22,    42,    43,
     126,    20,    46,    22,    20,    49,    22,   133,   134,     4,
       5,    22,     7,    42,     9,   141,    43,    12,    13,    22,
      15,    16,    17,    18,     4,     5,    21,    22,    23,    24,
      45,   157,    24,    25,    20,    22,    16,    17,    18,    44,
      35,    21,    22,    23,    24,    44,    48,    42,    43,    22,
      50,    46,    42,    42,    49,    35,    20,    17,     4,     5,
      43,    45,    42,    43,    24,    25,    46,    22,    50,    49,
      16,    17,    18,    44,    34,    21,    22,    23,    24,    46,
      43,    46,    43,    45,    43,    45,    22,    45,    45,    35,
      43,    45,    44,    44,    14,     8,    42,    43,    58,    46,
      88,   157,    58,    49,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      51,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      47,    48,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    47,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      46,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    46,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    46,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    -1,
      -1,    -1,    -1,    -1,    44,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    -1,
      -1,    -1,    -1,    -1,    44,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    -1,
      -1,    -1,    -1,    -1,    44,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     8,    53,    54,    22,     0,     8,    55,    56,    42,
      22,    55,    10,    11,    63,    22,    22,    42,    43,     3,
       6,    10,    22,    57,    58,    59,    67,    22,    45,    57,
      57,    20,    22,    20,    43,    46,    47,    22,    60,    62,
      67,     4,     5,    16,    17,    18,    21,    22,    23,    24,
      35,    42,    43,    49,    66,    68,    44,    44,    48,    61,
      22,    22,    67,    22,    66,    66,    69,    66,    66,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    46,    50,    71,    42,    42,    62,    43,
      48,    45,    44,    22,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    66,    50,     7,
       9,    12,    13,    15,    22,    42,    46,    58,    64,    65,
      66,    67,    64,    61,    44,    69,    43,    51,    66,    46,
      46,    46,    66,    43,    43,    64,    66,    64,    45,    64,
      25,    47,    22,    45,    69,    70,    51,    46,    66,    66,
      45,    45,    22,    66,    44,    44,    44,    43,    46,    65,
      65,    70,    14,    44,    65,    46
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
       1,     2,     4,     1,     2,     1,     6,     3,     3,     3,
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

#define YYBACKUP(Token, Value)                                    \
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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
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
  unsigned long yylno = yyrline[yyrule];
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
                       &yyvsp[(yyi + 1) - (yynrhs)]
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
            else
              goto append;

          append:
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

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
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
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
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
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yynewstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

# if defined yyoverflow
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
# else /* defined YYSTACK_RELOCATE */
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
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
| yyreduce -- do a reduction.  |
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
#line 92 "./src/parser/yaccer.y"
    {
    program = new Program((yyvsp[0]._classDecls));
    program->addClassDeclAtFront((yyvsp[-1]._classDecl)); 
}
#line 1472 "./src/parser/yaccer.cpp"
    break;

  case 3:
#line 97 "./src/parser/yaccer.y"
    {
    if((yyvsp[-9]._str) != MAIN_METHOD_NAME){
        mainMethodNameError(MAIN_METHOD_NAME, (yyvsp[-9]._str));
        return 1;
    }

    // Parameter
    Type* paramType = MkTypeArray(MkTypeClass((yyvsp[-7]._str)));
    string paramName = string((yyvsp[-5]._str));
    Parameter* param = new Parameter(paramType, paramName);

    // Method
    Block* statements = (yyvsp[-2]._block);
    Type* returnType = MkTypeVoid();
    Method* mainMethod = new Method(string((yyvsp[-9]._str)), returnType, statements);
    mainMethod->addParam(param);

    // Class
    g_mainClassName = (yyvsp[-12]._str);
    ClassDeclaration* decl = new ClassDeclaration((yyvsp[-12]._str));
    decl->addMethod(mainMethod);
    (yyval._classDecl) = decl;
}
#line 1500 "./src/parser/yaccer.cpp"
    break;

  case 4:
#line 121 "./src/parser/yaccer.y"
    {
    if((yyvsp[0]._classDecls) != nullptr){
        (yyvsp[0]._classDecls)->push_front((yyvsp[-1]._classDecl));
        (yyval._classDecls) = (yyvsp[0]._classDecls);
    }
        
    else{
        (yyval._classDecls) = new deque<ClassDeclaration*>();
        (yyval._classDecls)->push_front((yyvsp[-1]._classDecl));
    }
}
#line 1516 "./src/parser/yaccer.cpp"
    break;

  case 5:
#line 132 "./src/parser/yaccer.y"
    {
    (yyval._classDecls) = nullptr;
}
#line 1524 "./src/parser/yaccer.cpp"
    break;

  case 6:
#line 136 "./src/parser/yaccer.y"
    {
    ClassDeclaration* decl;

    if((yyvsp[-3]._str) != nullptr)
        decl = new ClassDeclaration((yyvsp[-4]._str),string((yyvsp[-3]._str)));
    else
        decl = new ClassDeclaration((yyvsp[-4]._str));
    
    if((yyvsp[-1]._classMembers) != nullptr){
        for(auto classMember : *(yyvsp[-1]._classMembers)){
            if(classMember.isField){
                decl->addField(classMember.field);
            } else{
                decl->addMethod(classMember.method);
            }
        }
    }
    
    (yyval._classDecl) = decl;
}
#line 1549 "./src/parser/yaccer.cpp"
    break;

  case 7:
#line 157 "./src/parser/yaccer.y"
    {
    Field* f = new Field((yyvsp[-1]._varDec)->getType(), (yyvsp[-1]._varDec)->getId(), (yyvsp[-1]._varDec)->getExpression());
    ClassMember member;
    member.field = f;
    member.isField = true;
    
    if((yyvsp[0]._classMembers) == nullptr){
        (yyval._classMembers) = new deque<ClassMember>();
        (yyval._classMembers)->push_front(member);
    } else{
        (yyvsp[0]._classMembers)->push_front(member);
        (yyval._classMembers) = (yyvsp[0]._classMembers);
    }
}
#line 1568 "./src/parser/yaccer.cpp"
    break;

  case 8:
#line 171 "./src/parser/yaccer.y"
    {
    Method* m = new Method((yyvsp[-1]._methodDec)->getId(), (yyvsp[-1]._methodDec)->getReturnType(), (yyvsp[-1]._methodDec)->getParameters(), (yyvsp[-1]._methodDec)->getStatement());
    ClassMember member;
    member.method = m;
    member.isField = false;
    
    if((yyvsp[0]._classMembers) == nullptr){
        (yyval._classMembers) = new deque<ClassMember>();
        (yyval._classMembers)->push_front(member);
    } else{
        (yyvsp[0]._classMembers)->push_front(member);
        (yyval._classMembers) = (yyvsp[0]._classMembers);
    }
}
#line 1587 "./src/parser/yaccer.cpp"
    break;

  case 9:
#line 185 "./src/parser/yaccer.y"
    {
    (yyval._classMembers) = nullptr;
}
#line 1595 "./src/parser/yaccer.cpp"
    break;

  case 10:
#line 189 "./src/parser/yaccer.y"
    {
    (yyval._varDec) = new VarDec((yyvsp[-2]._type), (yyvsp[-1]._str));
}
#line 1603 "./src/parser/yaccer.cpp"
    break;

  case 11:
#line 192 "./src/parser/yaccer.y"
    {
    (yyval._varDec) = new VarDec((yyvsp[-4]._type), (yyvsp[-3]._str), (yyvsp[-1]._expr));
}
#line 1611 "./src/parser/yaccer.cpp"
    break;

  case 12:
#line 196 "./src/parser/yaccer.y"
    {
    Method* m = new Method((yyvsp[-6]._str), (yyvsp[-7]._type), (yyvsp[-4]._params), (yyvsp[-1]._block));
    (yyval._methodDec) = m;
}
#line 1620 "./src/parser/yaccer.cpp"
    break;

  case 13:
#line 201 "./src/parser/yaccer.y"
    {
    if((yyvsp[0]._params) == nullptr){
        deque<Parameter*>* params = new deque<Parameter*>();
        params->push_front((yyvsp[-1]._param));
        (yyval._params) = params;
    } else{
        (yyvsp[0]._params)->push_front((yyvsp[-1]._param));
        (yyval._params) = (yyvsp[0]._params);
    }
}
#line 1635 "./src/parser/yaccer.cpp"
    break;

  case 14:
#line 211 "./src/parser/yaccer.y"
    {
    (yyval._params) = nullptr;
}
#line 1643 "./src/parser/yaccer.cpp"
    break;

  case 15:
#line 215 "./src/parser/yaccer.y"
    {
    if((yyvsp[0]._params) == nullptr){
        deque<Parameter*>* params = new deque<Parameter*>();
        params->push_front((yyvsp[-1]._param));
        (yyval._params) = params;
    } else{
        (yyvsp[0]._params)->push_front((yyvsp[-1]._param));
        (yyval._params) = (yyvsp[0]._params);
    }
}
#line 1658 "./src/parser/yaccer.cpp"
    break;

  case 16:
#line 225 "./src/parser/yaccer.y"
    {
    (yyval._params) = nullptr;
}
#line 1666 "./src/parser/yaccer.cpp"
    break;

  case 17:
#line 229 "./src/parser/yaccer.y"
    {
    (yyval._param) = new Parameter((yyvsp[-1]._type), (yyvsp[0]._str));
}
#line 1674 "./src/parser/yaccer.cpp"
    break;

  case 18:
#line 233 "./src/parser/yaccer.y"
    {
    (yyval._str) = (yyvsp[0]._str);
}
#line 1682 "./src/parser/yaccer.cpp"
    break;

  case 19:
#line 236 "./src/parser/yaccer.y"
    {
    (yyval._str) = nullptr;
}
#line 1690 "./src/parser/yaccer.cpp"
    break;

  case 20:
#line 241 "./src/parser/yaccer.y"
    {
    if((yyvsp[0]._block) != nullptr){
        (yyvsp[0]._block)->addStatementAtFront((yyvsp[-1]._varDec));
        (yyval._block) = (yyvsp[0]._block);
    }
        
    else{
        Block* block = new Block;
        block->addStatement((yyvsp[-1]._varDec));
        (yyval._block) = block;
    }
}
#line 1707 "./src/parser/yaccer.cpp"
    break;

  case 21:
#line 253 "./src/parser/yaccer.y"
    {
     if((yyvsp[0]._block) != nullptr){
        (yyvsp[0]._block)->addStatementAtFront((yyvsp[-1]._statement));
        (yyval._block) = (yyvsp[0]._block);
    }
        
    else{
        Block* block = new Block;
        block->addStatement((yyvsp[-1]._statement));
        (yyval._block) = block;
    }
}
#line 1724 "./src/parser/yaccer.cpp"
    break;

  case 22:
#line 265 "./src/parser/yaccer.y"
    {
    (yyval._block) = new Block;
}
#line 1732 "./src/parser/yaccer.cpp"
    break;

  case 23:
#line 269 "./src/parser/yaccer.y"
    {
    (yyval._statement) = (yyvsp[-1]._block);
}
#line 1740 "./src/parser/yaccer.cpp"
    break;

  case 24:
#line 272 "./src/parser/yaccer.y"
    {
    (yyval._statement) = new ElselessIf((yyvsp[-2]._expr), (yyvsp[0]._statement));
}
#line 1748 "./src/parser/yaccer.cpp"
    break;

  case 25:
#line 275 "./src/parser/yaccer.y"
    {
    (yyval._statement) = new IfElse((yyvsp[-4]._expr), (yyvsp[-2]._statement), (yyvsp[0]._statement));
}
#line 1756 "./src/parser/yaccer.cpp"
    break;

  case 26:
#line 278 "./src/parser/yaccer.y"
    {
    (yyval._statement) = new While((yyvsp[-2]._expr), (yyvsp[0]._statement));
}
#line 1764 "./src/parser/yaccer.cpp"
    break;

  case 27:
#line 281 "./src/parser/yaccer.y"
    {
    (yyval._statement) = new Assignment((yyvsp[-3]._expr), (yyvsp[-1]._expr));
}
#line 1772 "./src/parser/yaccer.cpp"
    break;

  case 28:
#line 284 "./src/parser/yaccer.y"
    {
    (yyval._statement) = new Continue;
}
#line 1780 "./src/parser/yaccer.cpp"
    break;

  case 29:
#line 287 "./src/parser/yaccer.y"
    {
    (yyval._statement) = new Break;
}
#line 1788 "./src/parser/yaccer.cpp"
    break;

  case 30:
#line 290 "./src/parser/yaccer.y"
    {
    (yyval._statement) = new Return((yyvsp[-1]._expr));
}
#line 1796 "./src/parser/yaccer.cpp"
    break;

  case 31:
#line 293 "./src/parser/yaccer.y"
    {
    (yyval._statement) = new Return;
}
#line 1804 "./src/parser/yaccer.cpp"
    break;

  case 32:
#line 296 "./src/parser/yaccer.y"
    {
    IdExpression* idExpr = dynamic_cast<IdExpression*>((yyvsp[-6]._expr));

    if(idExpr != nullptr){
        if(!g_defaultSymbolHandler.isDefaultClass(idExpr->getId())){
            (yyval._statement) = new MethodCallExpression((yyvsp[-6]._expr), (yyvsp[-4]._str), (yyvsp[-2]._exprList));
        } else{
            (yyval._statement) = new StaticMethodCallExpression(idExpr->getId(), (yyvsp[-4]._str), (yyvsp[-2]._exprList));
        }
    } else{
        (yyval._statement) = new MethodCallExpression((yyvsp[-6]._expr), (yyvsp[-4]._str), (yyvsp[-2]._exprList));
    }
}
#line 1822 "./src/parser/yaccer.cpp"
    break;

  case 33:
#line 309 "./src/parser/yaccer.y"
    {
    (yyval._statement) = new Skip;
}
#line 1830 "./src/parser/yaccer.cpp"
    break;

  case 34:
#line 313 "./src/parser/yaccer.y"
    {
    (yyval._expr) = new BinExpression((yyvsp[-2]._expr), (yyvsp[0]._expr), OP_GREAT);
}
#line 1838 "./src/parser/yaccer.cpp"
    break;

  case 35:
#line 317 "./src/parser/yaccer.y"
    {
    (yyval._expr) = new BinExpression((yyvsp[-2]._expr), (yyvsp[0]._expr), OP_LESS);
}
#line 1846 "./src/parser/yaccer.cpp"
    break;

  case 36:
#line 321 "./src/parser/yaccer.y"
    {
    (yyval._expr) = new BinExpression((yyvsp[-2]._expr), (yyvsp[0]._expr), OP_GREAT_EQ);
}
#line 1854 "./src/parser/yaccer.cpp"
    break;

  case 37:
#line 325 "./src/parser/yaccer.y"
    {
    (yyval._expr) = new BinExpression((yyvsp[-2]._expr), (yyvsp[0]._expr), OP_LESS_EQ);
}
#line 1862 "./src/parser/yaccer.cpp"
    break;

  case 38:
#line 329 "./src/parser/yaccer.y"
    {
    (yyval._expr) = new BinExpression((yyvsp[-2]._expr), (yyvsp[0]._expr), OP_IS_EQ);
}
#line 1870 "./src/parser/yaccer.cpp"
    break;

  case 39:
#line 333 "./src/parser/yaccer.y"
    {
    (yyval._expr) = new BinExpression((yyvsp[-2]._expr), (yyvsp[0]._expr), OP_DIFF);
}
#line 1878 "./src/parser/yaccer.cpp"
    break;

  case 40:
#line 337 "./src/parser/yaccer.y"
    {
    (yyval._expr) = new BinExpression((yyvsp[-2]._expr), (yyvsp[0]._expr), OP_OR);
}
#line 1886 "./src/parser/yaccer.cpp"
    break;

  case 41:
#line 341 "./src/parser/yaccer.y"
    {
    (yyval._expr) = new BinExpression((yyvsp[-2]._expr), (yyvsp[0]._expr), OP_AND);
}
#line 1894 "./src/parser/yaccer.cpp"
    break;

  case 42:
#line 345 "./src/parser/yaccer.y"
    {
    (yyval._expr) = new BinExpression((yyvsp[-2]._expr), (yyvsp[0]._expr), OP_PLUS);   
}
#line 1902 "./src/parser/yaccer.cpp"
    break;

  case 43:
#line 349 "./src/parser/yaccer.y"
    {
    (yyval._expr) = new BinExpression((yyvsp[-2]._expr), (yyvsp[0]._expr), OP_BIN_MINUS);   
}
#line 1910 "./src/parser/yaccer.cpp"
    break;

  case 44:
#line 353 "./src/parser/yaccer.y"
    {
    (yyval._expr) = new BinExpression((yyvsp[-2]._expr), (yyvsp[0]._expr), OP_DIV);   
}
#line 1918 "./src/parser/yaccer.cpp"
    break;

  case 45:
#line 357 "./src/parser/yaccer.y"
    {
    (yyval._expr) = new BinExpression((yyvsp[-2]._expr), (yyvsp[0]._expr), OP_TIMES);   
}
#line 1926 "./src/parser/yaccer.cpp"
    break;

  case 46:
#line 361 "./src/parser/yaccer.y"
    {
    (yyval._expr) = new BinExpression((yyvsp[-2]._expr), (yyvsp[0]._expr), OP_MOD);   
}
#line 1934 "./src/parser/yaccer.cpp"
    break;

  case 47:
#line 365 "./src/parser/yaccer.y"
    {
    auto arrayDecl = dynamic_cast<ArrayDeclExpression*>((yyvsp[-1]._objExpr));
    if(arrayDecl != nullptr ){
        (yyval._expr) = new NewArrayExpression(arrayDecl, (yyvsp[0]._exprList));
    } else{
        (yyval._expr) = new ArrayAccessExpression((yyvsp[-1]._objExpr), (yyvsp[0]._exprList));
    }
}
#line 1947 "./src/parser/yaccer.cpp"
    break;

  case 48:
#line 374 "./src/parser/yaccer.y"
    {
    AtomExpValue val;
    val.intval = (yyvsp[0]._int);
    AtomExpression* exp = new AtomExpression(val, MkTypeInt());
    (yyval._expr) = exp;
}
#line 1958 "./src/parser/yaccer.cpp"
    break;

  case 49:
#line 381 "./src/parser/yaccer.y"
    {
    AtomExpValue val;
    val.strval = (yyvsp[0]._str);
    AtomExpression* exp = new AtomExpression(val, MkTypeClass("String"));
    (yyval._expr) = exp;
}
#line 1969 "./src/parser/yaccer.cpp"
    break;

  case 50:
#line 388 "./src/parser/yaccer.y"
    {
    AtomExpValue val;
    val.boolval = true;
    AtomExpression* exp = new AtomExpression(val, MkTypeBoolean());
    (yyval._expr) = exp;
}
#line 1980 "./src/parser/yaccer.cpp"
    break;

  case 51:
#line 395 "./src/parser/yaccer.y"
    {
    AtomExpValue val;
    val.boolval = false;
    AtomExpression* exp = new AtomExpression(val, MkTypeBoolean());
    (yyval._expr) = exp;
}
#line 1991 "./src/parser/yaccer.cpp"
    break;

  case 52:
#line 402 "./src/parser/yaccer.y"
    {
    AtomExpression* exp = new AtomExpression(MkTypeNull());
    (yyval._expr) = exp;
}
#line 2000 "./src/parser/yaccer.cpp"
    break;

  case 53:
#line 407 "./src/parser/yaccer.y"
    {
    // Prevents things like "new int" from being considered expressions
    auto decl = dynamic_cast<ArrayDeclExpression*>((yyvsp[0]._objExpr));
    if(decl != nullptr){
        newTypeIsNotAnExpression(decl->getType()->toString());
        return 1;
    }

    (yyval._expr) = (yyvsp[0]._objExpr);
}
#line 2015 "./src/parser/yaccer.cpp"
    break;

  case 54:
#line 418 "./src/parser/yaccer.y"
    {
    (yyval._expr) = new UnExpression((yyvsp[0]._expr), OP_UN_MINUS);
}
#line 2023 "./src/parser/yaccer.cpp"
    break;

  case 55:
#line 422 "./src/parser/yaccer.y"
    {
    (yyval._expr) = new UnExpression((yyvsp[0]._expr), OP_NOT);
}
#line 2031 "./src/parser/yaccer.cpp"
    break;

  case 56:
#line 426 "./src/parser/yaccer.y"
    {
    (yyval._type) = MkTypeArray((yyvsp[-1]._type));
}
#line 2039 "./src/parser/yaccer.cpp"
    break;

  case 57:
#line 429 "./src/parser/yaccer.y"
    {
    (yyval._type) = MkTypeBoolean();
}
#line 2047 "./src/parser/yaccer.cpp"
    break;

  case 58:
#line 432 "./src/parser/yaccer.y"
    {
    (yyval._type) = MkTypeInt();
}
#line 2055 "./src/parser/yaccer.cpp"
    break;

  case 59:
#line 435 "./src/parser/yaccer.y"
    {
    (yyval._type) = MkTypeVoid();
}
#line 2063 "./src/parser/yaccer.cpp"
    break;

  case 60:
#line 438 "./src/parser/yaccer.y"
    {
    (yyval._type) = MkTypeClass((yyvsp[0]._str));
}
#line 2071 "./src/parser/yaccer.cpp"
    break;

  case 61:
#line 442 "./src/parser/yaccer.y"
    {
    (yyval._objExpr) = new ArrayDeclExpression((yyvsp[0]._type));
}
#line 2079 "./src/parser/yaccer.cpp"
    break;

  case 62:
#line 445 "./src/parser/yaccer.y"
    {
    (yyval._objExpr) = new NewObjExpression((yyvsp[-2]._str));
}
#line 2087 "./src/parser/yaccer.cpp"
    break;

  case 63:
#line 447 "./src/parser/yaccer.y"
    {
    (yyval._objExpr) = new IdExpression((yyvsp[0]._str));
}
#line 2095 "./src/parser/yaccer.cpp"
    break;

  case 64:
#line 449 "./src/parser/yaccer.y"
    {
    (yyval._objExpr) = new FieldAccessExpression((yyvsp[0]._str));
}
#line 2103 "./src/parser/yaccer.cpp"
    break;

  case 65:
#line 451 "./src/parser/yaccer.y"
    {
    (yyval._objExpr) = new ThisExpression;
}
#line 2111 "./src/parser/yaccer.cpp"
    break;

  case 66:
#line 453 "./src/parser/yaccer.y"
    {
    IdExpression* idExpr = dynamic_cast<IdExpression*>((yyvsp[-5]._expr));

    if(idExpr != nullptr){
        if(!g_defaultSymbolHandler.isDefaultClass(idExpr->getId())){
            (yyval._objExpr) = new MethodCallExpression((yyvsp[-5]._expr), (yyvsp[-3]._str), (yyvsp[-1]._exprList));
        } else{
            (yyval._objExpr) = new StaticMethodCallExpression(idExpr->getId(), (yyvsp[-3]._str), (yyvsp[-1]._exprList));
        }
    } else{
        (yyval._objExpr) = new MethodCallExpression((yyvsp[-5]._expr), (yyvsp[-3]._str), (yyvsp[-1]._exprList));
    }
}
#line 2129 "./src/parser/yaccer.cpp"
    break;

  case 67:
#line 465 "./src/parser/yaccer.y"
    {
    (yyval._objExpr) = new ParenExpression((yyvsp[-1]._expr));
}
#line 2137 "./src/parser/yaccer.cpp"
    break;

  case 68:
#line 467 "./src/parser/yaccer.y"
    {
    (yyval._objExpr) = new LitArrayExpression((yyvsp[-1]._exprList));
}
#line 2145 "./src/parser/yaccer.cpp"
    break;

  case 69:
#line 471 "./src/parser/yaccer.y"
    {
    deque<Expression*>* newExprList;
    if((yyvsp[0]._exprList) == nullptr)
        newExprList = new deque<Expression*>();
    else
        newExprList = (yyvsp[0]._exprList);

    newExprList->push_front((yyvsp[-2]._expr));
    (yyval._exprList) = newExprList;
}
#line 2160 "./src/parser/yaccer.cpp"
    break;

  case 70:
#line 480 "./src/parser/yaccer.y"
    {
    deque<Expression*>* newExprList = new deque<Expression*>();
    newExprList->push_front((yyvsp[0]._expr));
    (yyval._exprList) = newExprList;
}
#line 2170 "./src/parser/yaccer.cpp"
    break;

  case 71:
#line 486 "./src/parser/yaccer.y"
    {
    (yyval._exprList) = (yyvsp[0]._exprList);
}
#line 2178 "./src/parser/yaccer.cpp"
    break;

  case 72:
#line 488 "./src/parser/yaccer.y"
    {
    (yyval._exprList) = nullptr;
}
#line 2186 "./src/parser/yaccer.cpp"
    break;

  case 73:
#line 492 "./src/parser/yaccer.y"
    {
    deque<Expression*>* newExprList = (yyvsp[-3]._exprList);
    newExprList->push_front((yyvsp[-1]._expr));
    (yyval._exprList) = newExprList;
}
#line 2196 "./src/parser/yaccer.cpp"
    break;

  case 74:
#line 496 "./src/parser/yaccer.y"
    {
    deque<Expression*>* newExprList = new deque<Expression*>();
    newExprList->push_front((yyvsp[-1]._expr));
    (yyval._exprList) = newExprList;
}
#line 2206 "./src/parser/yaccer.cpp"
    break;


#line 2210 "./src/parser/yaccer.cpp"

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
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
#line 501 "./src/parser/yaccer.y"


void yyerror(const char *s) {
    fprintf(stderr, "line: %d: %s\n", yylineno, s);
}
