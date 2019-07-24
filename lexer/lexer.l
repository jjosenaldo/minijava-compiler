%option noyywrap

%{
#include "token_defs.h"
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
