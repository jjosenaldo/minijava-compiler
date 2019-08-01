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

{C_START}({C_NOT_WORRYING}*{C_WORRYING}+{C_NOT_WOR_NOR_FINAL})*{C_NOT_WORRYING}*{C_WORRYING}+{C_FINAL} { /* multiline comment */ }
{S_START}({S_WORRYING}{S_NOT_WOR_NOR_FINAL}|{S_NOT_WORRYING})*{S_FINAL} { 
    char aux[yyleng];
    int pointer = 1;
    int writing = 0;
    while(pointer < yyleng-2){
        if(yytext[pointer] == '\\'){
            ++pointer;

            if(yytext[pointer] == '\\'){
                aux[writing] = '\\';
            } else if(yytext[pointer] == 'n'){
                aux[writing] = '\n';
            } else if(yytext[pointer] == 't'){
                aux[writing] = '\t';
            } else if(yytext[pointer] == '\"'){
                aux[writing] = '\"';
            } else{
                // we can assume the string is well-formed, so this else won't be reached
            }
        } else{
            aux[writing] = yytext[pointer];
        }

        ++pointer;
        ++writing;
    }

    aux[writing++] = '\0';
    strcpy (yytext,aux);
    yyleng = writing;
    return TOK_STRING; }




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