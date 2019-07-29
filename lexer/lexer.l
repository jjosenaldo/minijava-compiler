%option noyywrap

%{
#include "token.h"

struct token tokRead;
%}

digit                   [0-9]
letter                  [a-zA-Z]
C_START                   "/*"
C_WORRYING                "*"
C_NOT_WORRYING            [^*]
C_NOT_WOR_NOR_FINAL       [^*/]
C_FINAL                   "/"

%%
\/\/(.*)\n        { /* single line comment */ }
\/\*(\n|.)*\*\/   { /* multiline comment */ }
[ \n\t\r]+        { /* spaces, tabs and newlines */ }

{C_START}({C_NOT_WORRYING}*{C_WORRYING}+{C_NOT_WOR_NOR_FINAL})*
{C_NOT_WORRYING}*{C_WORRYING}+{C_FINAL} { /* multiline comment */ }

{digit}+        { return TOK_LIT_INT; }
\+              { return TOK_PLUS; }
\-              { return TOK_MINUS; }
\*              { return TOK_TIMES; }
\=              { return TOK_EQUAL; }
\&\&            { return TOK_AND; }
\<              { return TOK_LESSTHAN; }
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
System\.out\.println   { return TOK_PRINT; }
length          { return TOK_LENGTH; }
this            { return TOK_THIS; }
new             { return TOK_NEW; }
\{              { return TOK_LBRACE; }
\}              { return TOK_RBRACE; }
\(              { return TOK_LPAREN; }
\)              { return TOK_RPAREN; }
\[              { return TOK_LBRACKET; }
\]              { return TOK_RBRACKET; }
\;              { return TOK_SEMICOLON; }
\,              { return TOK_COMMA; }
\.              { return TOK_DOT; }
\!              { return TOK_EXCLAMATION; }

{letter}({digit}|{letter}|"_")*    { return TOK_ID; }
<<EOF>>         { return TOK_EOF; }
.               { return TOK_ERROR; }

%%

struct token getNextToken(){
    tokRead.id = yylex();
    tokRead.lexem = yytext;
    tokRead.lexemLen = yyleng;

    return tokRead;
}