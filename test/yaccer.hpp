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
#line 26 "yaccer.y" /* yacc.c:1909  */

  struct Node* nodePointer;
  char* string;

#line 93 "yaccer.hpp" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_YACCER_HPP_INCLUDED  */
