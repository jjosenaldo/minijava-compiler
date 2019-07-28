%option noyywrap

%{
#include "token.h"

struct token tokRead;
%}

digit        [0-9]

%%

[ \n\t\r]+      ;
{digit}+        return TOK_LIT_INT;
\+              return TOK_PLUS;
\-              return TOK_MINUS;
\*              return TOK_TIMES;
<<EOF>>         return TOK_EOF;
.               return TOK_ERROR;  

%%

struct token getNextToken(){
    tokRead.id = yylex();
    tokRead.lexem = yytext;
    tokRead.lexemLen = yyleng;

    return tokRead;
}