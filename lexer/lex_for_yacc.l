%option noyywrap
%option yylineno

%{
#include "y.tab.h"
#include "stdlib.h" 
#include "stdio.h"
%}

digit                   [0-9]

%%
 
\/\/(.*)\n        { /* single line comment */ }
[ \n\t\r]+        { /* spaces, tabs and newlines */ }


{digit}+        { yylval = atoi(yytext); printf("lex read a digit\n"); return TOK_LIT_INT; }
\+              { return '+'; }
<<EOF>>         { return TOK_EOF; }
.|'\n'          { return TOK_ERROR; }

%%