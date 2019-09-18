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

%nonassoc PREC_5
%nonassoc PREC_4
%left PREC_3
%left PREC_2
%nonassoc PREC_1
%nonassoc PREC_0

%%

init : expr 
     ;

expr : expr '>' expr                     %prec PREC_5
     | expr '<' expr                     %prec PREC_5 
     | expr TOK_GREAT_EQ expr            %prec PREC_5
     | expr TOK_LESS_EQ expr             %prec PREC_5
     | expr TOK_EQ expr                  %prec PREC_5
     | expr TOK_DIFF expr                %prec PREC_5
     | expr TOK_OR expr                  %prec PREC_4
     | expr TOK_AND expr                 %prec PREC_4
     | expr '+' expr                     %prec PREC_3
     | expr '-' expr                     %prec PREC_3
     | expr '/' expr                     %prec PREC_2
     | expr '*' expr                     %prec PREC_2
     | expr '%' expr                     %prec PREC_2
     | expr '[' expr ']'                 %prec PREC_0
     | '{' expr_list '}'                 %prec PREC_0
     | expr '.' TOK_ID '(' expr_list ')' %prec PREC_0
     | TOK_LIT_INT                       %prec PREC_0
     | TOK_LIT_STR                       %prec PREC_0
     | TOK_TRUE                          %prec PREC_0
     | TOK_FALSE                         %prec PREC_0
     | TOK_THIS '.' TOK_ID               %prec PREC_0
     | TOK_THIS                          %prec PREC_0
     | TOK_ID                            %prec PREC_0
     | TOK_NULL                          %prec PREC_0
     | TOK_NEW type filledbracks         %prec PREC_0
     | TOK_NEW type '(' expr_list ')'    %prec PREC_0
     | '-' expr                          %prec PREC_1
     | '!' expr                          %prec PREC_1
     | '(' expr ')'                      %prec PREC_0
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
