%{
	#include "token.h"
	#include <stdio.h>
%}

%left '+'
%token TOK_LIT_INT TOK_EOF TOK_ERROR

%%

line : expr '\n'	 { printf("%d\n", $1); }
expr : expr '+' expr { $$ = $1 + $3; }
	 | TOK_LIT_INT	 { printf("lex read a digit\n");}

%%

#include "../obj/lex_for_yacc.yy.c"

int yyerror (char const *s) {
  fprintf (stderr, "%s\n", s);
  return 0;
}