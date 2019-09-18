/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    NEW = 273,
    TOK_NULL = 274,
    ID = 275,
    ERROR = 276,
    LIT_STR = 277,
    ARR = 278,
    PREC_UNARY_OP = 279,
    AND = 280,
    OR = 281,
    EQ = 282,
    DIFF = 283,
    LESS_EQ = 284,
    GREAT_EQ = 285,
    PREC_NEW_MATRIX = 286,
    PREC_THIS_WITHOUT_DOT = 287,
    PREC_THIS_WITH_DOT = 288,
    PREC_ELSELESS_IF = 289
  };
#endif
/* Tokens.  */
#define LIT_INT 258
#define INT 259
#define TRUE 260
#define FALSE 261
#define BOOLEAN 262
#define BREAK 263
#define CLASS 264
#define CONTINUE 265
#define VOID 266
#define EXTENDS 267
#define RETURN 268
#define IF 269
#define ELSE 270
#define WHILE 271
#define THIS 272
#define NEW 273
#define TOK_NULL 274
#define ID 275
#define ERROR 276
#define LIT_STR 277
#define ARR 278
#define PREC_UNARY_OP 279
#define AND 280
#define OR 281
#define EQ 282
#define DIFF 283
#define LESS_EQ 284
#define GREAT_EQ 285
#define PREC_NEW_MATRIX 286
#define PREC_THIS_WITHOUT_DOT 287
#define PREC_THIS_WITH_DOT 288
#define PREC_ELSELESS_IF 289

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
