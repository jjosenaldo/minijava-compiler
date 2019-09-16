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
    TOK_LIT_INT = 258,
    TOK_EQ = 259,
    TOK_DIFF = 260,
    TOK_LESS_EQ = 261,
    TOK_GREAT_EQ = 262,
    TOK_AND = 263,
    TOK_OR = 264,
    TOK_STRING = 265,
    TOK_INT = 266,
    TOK_TRUE = 267,
    TOK_FALSE = 268,
    TOK_BOOLEAN = 269,
    TOK_BREAK = 270,
    TOK_CLASS = 271,
    TOK_CONTINUE = 272,
    TOK_PUBLIC = 273,
    TOK_STATIC = 274,
    TOK_VOID = 275,
    TOK_MAIN = 276,
    TOK_EXTENDS = 277,
    TOK_RETURN = 278,
    TOK_IF = 279,
    TOK_ELSE = 280,
    TOK_WHILE = 281,
    TOK_LENGTH = 282,
    TOK_THIS = 283,
    TOK_NEW = 284,
    TOK_NULL = 285,
    TOK_ID = 286,
    TOK_EOF = 287,
    TOK_ERROR = 288,
    TOK_LIT_STR = 289,
    TOK_BOOL = 290,
    UMINUS = 291
  };
#endif
/* Tokens.  */
#define TOK_LIT_INT 258
#define TOK_EQ 259
#define TOK_DIFF 260
#define TOK_LESS_EQ 261
#define TOK_GREAT_EQ 262
#define TOK_AND 263
#define TOK_OR 264
#define TOK_STRING 265
#define TOK_INT 266
#define TOK_TRUE 267
#define TOK_FALSE 268
#define TOK_BOOLEAN 269
#define TOK_BREAK 270
#define TOK_CLASS 271
#define TOK_CONTINUE 272
#define TOK_PUBLIC 273
#define TOK_STATIC 274
#define TOK_VOID 275
#define TOK_MAIN 276
#define TOK_EXTENDS 277
#define TOK_RETURN 278
#define TOK_IF 279
#define TOK_ELSE 280
#define TOK_WHILE 281
#define TOK_LENGTH 282
#define TOK_THIS 283
#define TOK_NEW 284
#define TOK_NULL 285
#define TOK_ID 286
#define TOK_EOF 287
#define TOK_ERROR 288
#define TOK_LIT_STR 289
#define TOK_BOOL 290
#define UMINUS 291

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
