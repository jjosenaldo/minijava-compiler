%option noyywrap
%option yylineno

%{
#include "token.h"

struct token tokRead;
int current_column = 1;
int prev_column;

// Adapted from: https://stackoverflow.com/questions/26854374/how-do-i-use-yy-bs-lineno-and-yy-bs-column-in-flex
/* It's executed before entering each action */
#define YY_USER_ACTION                                                                     \
  start_line = prev_yylineno; start_column = current_column; prev_column = current_column; \
  if (yylineno == prev_yylineno) current_column += yyleng;                                 \
  else {                                                                                   \
    for (current_column = 1; yytext[yyleng - current_column] != '\n'; ++current_column) {} \
    prev_yylineno = yylineno;                                                              \
  }
%}

digit        [0-9]
letter       [a-zA-Z]

%%
 int start_line, start_column;
 int prev_yylineno = yylineno;

\/\/(.*)\n        { /* single line comment */ }
\/\*(\n|.)*\*\/   { /* multiline comment */ }
[ \n\t\r]+        { /* spaces, tabs and newlines */ }

{digit}+        { return TOK_LIT_INT; }
\+              { return '+'; }
\-              { return '-'; }
\*              { return '*'; }
\=              { return '='; }
\&\&            { return TOK_AND; }
\<              { return '<'; }
String          { return TOK_STRING; }
int             { return TOK_INT; }
true            { return TOK_TRUE; }
false           { return TOK_FALSE; }

class           { return TOK_CLASS; }
public          { return TOK_PUBLIC; }
static          { return TOK_STATIC; }
void            { return TOK_VOID; }
main            { return TOK_MAIN; }
extends         { return TOK_EXTENDS; }
return          { return TOK_RETURN; }
if              { return TOK_IF; }
else            { return TOK_ELSE; }
while           { return TOK_WHILE; }
length          { return TOK_LENGTH; }
this            { return TOK_THIS; }
new             { return TOK_NEW; }
\{              { return '{'; }
\}              { return '}'; }
\(              { return '('; }
\)              { return ')'; }
\[              { return '['; }
\]              { return ']'; }
\;              { return ';'; }
\,              { return ','; }
\.              { return '.'; }
\!              { return '!'; }

{letter}({digit}|{letter}|"_")*    { return TOK_ID; }
<<EOF>>         { return TOK_EOF; }
.               { return TOK_ERROR; }

%%

struct token getNextToken(){
    tokRead.id = yylex();
    tokRead.lexem = yytext;
    tokRead.lexemLen = yyleng;
    tokRead.row = yylineno;
    tokRead.col = prev_column;

    return tokRead;
}