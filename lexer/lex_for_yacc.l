%option noyywrap
%option yylineno

%{
#include "token.h"
#include "y.tab.h"

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

digit                   [0-9]
letter                  [a-zA-Z]
C_START                   "/*"
C_WORRYING                "*"
C_NOT_WORRYING            [^*]
C_NOT_WOR_NOR_FINAL       [^*/]
C_FINAL                   "/"

S_START                   \"
S_WORRYING                \\
S_NOT_WORRYING            [^\\"]
S_NOT_WOR_NOR_FINAL       [\\tn"]
S_FINAL                   \"

%%
 int start_line, start_column;
 int prev_yylineno = yylineno;

\/\/(.*)\n        { /* single line comment */ }
[ \n\t\r]+        { /* spaces, tabs and newlines */ }


{digit}+        { return TOK_LIT_INT; }
\+              { return '+'; }
<<EOF>>         { return TOK_EOF; }
.               { return TOK_ERROR; }

%%

struct token getNextToken(){
    tokRead.id = yylex();
    if(tokRead.id == TOK_EOF)
        tokRead.lexem = "$";
    else 
        tokRead.lexem = yytext;
    tokRead.lexemLen = yyleng;
    tokRead.row = yylineno;
    tokRead.col = prev_column;

    return tokRead;
}