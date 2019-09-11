%{
	#include "../lexer/token.h"
	#include <stdio.h>
%}

%left '+'
%token TOK_LIT_INT TOK_EOF TOK_ERROR

%%

line : expr '\n'	 { printf("%d\n", $1); }
expr : expr '+' expr { $$ = $1 + $3; }
	 | TOK_LIT_INT

%%

void yyerror (char const *s) {
  fprintf (stderr, "%s\n", s);
}