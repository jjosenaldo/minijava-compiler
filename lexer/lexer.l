%option noyywrap

%{
#include "token.h"
#include "stdio.h"

struct token tokRead;
%}

digit        [0-9]

%%

[ \n\t\r]+      ;
     
{digit}+        return TOK_LIT_INT;

\+              return '+';
\-              return '-';
\*              return '*';

<<EOF>>         return TOK_EOF;

%%

struct token getNextToken(){
    tokRead.id = yylex();
    tokRead.lexem = yytext;
    tokRead.lexemLen = yyleng;

    return tokRead;
}