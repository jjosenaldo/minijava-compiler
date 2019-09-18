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
    STRING = 259,
    INT = 260,
    TRUE = 261,
    FALSE = 262,
    BOOLEAN = 263,
    BREAK = 264,
    CLASS = 265,
    CONTINUE = 266,
    PUBLIC = 267,
    STATIC = 268,
    VOID = 269,
    MAIN = 270,
    EXTENDS = 271,
    RETURN = 272,
    IF = 273,
    ELSE = 274,
    WHILE = 275,
    LENGTH = 276,
    THIS = 277,
    NEW = 278,
    TOK_NULL = 279,
    ID = 280,
    ERROR = 281,
    LIT_STR = 282,
    BOOL = 283,
    PREC_UNARY_OP = 284,
    AND = 285,
    OR = 286,
    EQ = 287,
    DIFF = 288,
    LESS_EQ = 289,
    GREAT_EQ = 290,
    PREC_NEW_MATRIX = 291,
    PREC_ELSELESS_IF = 292
  };
#endif
/* Tokens.  */
#define LIT_INT 258
#define STRING 259
#define INT 260
#define TRUE 261
#define FALSE 262
#define BOOLEAN 263
#define BREAK 264
#define CLASS 265
#define CONTINUE 266
#define PUBLIC 267
#define STATIC 268
#define VOID 269
#define MAIN 270
#define EXTENDS 271
#define RETURN 272
#define IF 273
#define ELSE 274
#define WHILE 275
#define LENGTH 276
#define THIS 277
#define NEW 278
#define TOK_NULL 279
#define ID 280
#define ERROR 281
#define LIT_STR 282
#define BOOL 283
#define PREC_UNARY_OP 284
#define AND 285
#define OR 286
#define EQ 287
#define DIFF 288
#define LESS_EQ 289
#define GREAT_EQ 290
#define PREC_NEW_MATRIX 291
#define PREC_ELSELESS_IF 292

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
