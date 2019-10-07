%option noyywrap
%option yylineno

%{
#include "y.tab.h"

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
brackets               \[[\n \t]*\]
letter                  [a-zA-Z]
sp                      [\n \t]*
id                      {letter}({digit}|{letter}|"_")*
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
    return LIT_STR; }




{digit}+        { return LIT_INT; }
\+              { return '+'; }
\-              { return '-'; }
\*              { return '*'; }
"/"             { return '/'; }
"%"             { return '%'; }
\=\=            { return EQ; }
\!\=            { return DIFF; }
\=              { return '='; }
\<\=            { return LESS_EQ; }
\>\=            { return GREAT_EQ; }
\&\&            { return AND; }
\|\|            { return OR; }
\<              { return '<'; }
\>              { return '>'; }
{brackets}      { return ARR; }            
int             { return INT; }
true            { return TRUE; }
false           { return FALSE; }
boolean         { return BOOLEAN; }
break           { return BREAK; }
class           { return CLASS; }
continue        { return CONTINUE; }
void            { return VOID; }
extends         { return EXTENDS; }
return          { return RETURN; }
if              { return IF; }
else            { return ELSE; }
while           { return WHILE; }
this{sp}\.      { return THIS_DOT; }
this/{sp}\.{sp}{id}{sp}\( { return THIS; }
this            {  return THIS; }
new             { return NEW; }
null            { return TOK_NULL; }
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
{id}            { 
                    yylval.string = (char*) malloc(sizeof(char)*yyleng);
                    strcpy(yylval.string ,yytext); 
                    return ID; }
.               { yyerror("invalid character"); }

%%