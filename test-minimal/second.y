%{
#include <ctype.h>
#include <stdio.h>
%}

%token TOK_LIT_INT TOK_EQ TOK_DIFF TOK_LESS_EQ TOK_GREAT_EQ TOK_AND TOK_OR TOK_STRING TOK_INT TOK_TRUE TOK_FALSE TOK_BOOLEAN TOK_BREAK TOK_CLASS TOK_CONTINUE TOK_PUBLIC TOK_STATIC TOK_VOID TOK_MAIN TOK_EXTENDS TOK_RETURN TOK_IF TOK_ELSE TOK_WHILE TOK_LENGTH TOK_THIS TOK_NEW TOK_NULL TOK_ID TOK_EOF TOK_ERROR TOK_LIT_STR

%left '+' '-'
%left '*' '/'
%right UMINUS

%%

lines : lines expr '\n'	{printf("%d\n", $2); }
	  | lines '\n'
	  | /* empty */
	  ;

expr  : expr '+' expr	{$$ = $1 + $3; }
	  |	expr '-' expr	{$$ = $1 - $3; } 
	  |	expr '*' expr	{$$ = $1 * $3; } 
	  |	expr '/' expr	{$$ = $1 / $3; } 
	  | '(' expr ')'    {$$ = $2; }
	  | '-' expr %prec UMINUS { $$ = - $2; }
	  | TOK_LIT_INT {  }
	  ;

%%

#include "lex.yy.c"