%{
#include <ctype.h>
#include <stdio.h>
int yylex();
int yyerror();

/*

| Operator         | Precedence | Associativity
| PAR_OP           |     0      | ?
| ARRAY_OP         |     0      | ?
| LIST_OP          |     0      | ?
| CALL_OP          |     0      | ?
| ATT_ACCESS_OP    |     0      | ?
| NEW_ARRAY_OP     |     0      | ?
| NEW_OBJ_OP       |     0      | ?
| -(unary)         |     1      | ?
| !(unary)         |     1      | ?
| *                |     2      | left
| /                |     2      | left
| %                |     2      | left
| +                |     3      | left
| -                |     3      | left
| &&               |     4      | left
| ||               |     4      | left
| <=               |     5      | left
| <                |     5      | left
| >=               |     5      | left
| >                |     5      | left
| ==               |     5      | left
| !=               |     5      | left
*/

%}

%token TOK_LIT_INT TOK_EQ TOK_DIFF TOK_LESS_EQ TOK_GREAT_EQ TOK_AND TOK_OR TOK_STRING TOK_INT TOK_TRUE TOK_FALSE TOK_BOOLEAN TOK_BREAK TOK_CLASS TOK_CONTINUE TOK_PUBLIC TOK_STATIC TOK_VOID TOK_MAIN TOK_EXTENDS TOK_RETURN TOK_IF TOK_ELSE TOK_WHILE TOK_LENGTH TOK_THIS TOK_NEW TOK_NULL TOK_ID TOK_EOF TOK_ERROR TOK_LIT_STR TOK_BOOL

%left '+' '-' '*' '/' '%'
%right UMINUS

%%

init : expr  
     ;

expr : expr '>' expr
     | expr '<' expr
     | expr TOK_GREAT_EQ expr
     | expr TOK_LESS_EQ expr
     | expr TOK_EQ expr
     | expr TOK_DIFF expr
     | expr TOK_OR expr
     | expr TOK_AND expr
     | expr '-' expr
     | expr '+' expr
     | expr '/' expr
     | expr '*' expr
     | expr '%' expr
     | expr '[' expr ']'
     | '{' expr_list '}'
     | expr '.' TOK_ID '(' expr_list ')'
     | TOK_LIT_INT
     | TOK_LIT_STR
     | TOK_TRUE
     | TOK_FALSE
     | TOK_THIS '.' TOK_ID
     | TOK_THIS
     | TOK_ID
     | TOK_NULL
     | TOK_NEW type filledbracks
     | TOK_NEW type '(' expr_list ')'
     | '-' expr
     | '!' expr
     | '(' expr ')'
     ; 

expr_list : expr ',' expr_list
         | 
         ;

filledbracks : '[' expr ']' filledbracks
             | 
             ; 

type : type '[' ']'
     | TOK_BOOL
     | TOK_INT
     | TOK_VOID
     | TOK_ID
     ;

%%

#include "lex.yy.c"
