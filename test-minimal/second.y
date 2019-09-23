%{
#include <ctype.h>
#include <stdio.h>
int yylex();
void yyerror(char* s);

/*

| Operator         | Precedence | Associativity
| PAR_OP           |     0      | ?
| ARRAY_OP         |     0      | ?
| LIST_OP          |     0      | ?
| CALL_OP          |     0      | ?
| ATT_ACCESS_OP    |     0      | ?
| NEW_ARRAY_OP     |     0      | ?
| NEW_OBJ_OP       |     0      | ?
| -(unary)         |     1      | ?
| !(unary)         |     1      | ?
| *                |     2      | left
| /                |     2      | left
| %                |     2      | left
| +                |     3      | left
| -                |     3      | left
| &&               |     4      | left
| ||               |     4      | left
| <=               |     5      | left
| <                |     5      | left
| >=               |     5      | left
| >                |     5      | left
| ==               |     5      | left
| !=               |     5      | left
*/

%}

%token LIT_INT INT TRUE FALSE BOOLEAN BREAK CLASS CONTINUE VOID EXTENDS RETURN IF ELSE WHILE THIS TOK_NULL NEW ID ERROR LIT_STR ARR THIS_DOT

%left '.'


%nonassoc '<' '>' EQ DIFF LESS_EQ GREAT_EQ
%left AND OR
%left '+' '-'
%left '*' '/' '%'
%nonassoc PREC_UNARY_OP

%right FILLED_BRACK


%nonassoc PREC_ELSELESS_IF
%nonassoc ELSE



%%

goal : mainclass classdecs
     ;

mainclass : CLASS ID '{' VOID ID '(' ID ARR ID ')' '{' blockstmts '}' '}'
          ;

classdecs : classdec classdecs
          |
          ;

classdec : CLASS ID extendsopt '{' classmembers '}'
         ;

classmembers : vardec classmembers
             | methoddec classmembers
             |
             ;

vardec : type ID ';'
       | type ID '=' expr ';'
       ;

methoddec : type ID '(' params ')' '{' blockstmts '}'
          ;

params : param paramsrest
       |
       ;

paramsrest : ';' param paramsrest
           |
           ;

param : type ID
      ;

extendsopt : EXTENDS ID
           |
           ;


blockstmts : vardec blockstmts
           | stmt blockstmts
           | 
           ;

type : type ARR
     | BOOLEAN
     | INT
     | VOID
     | ID

stmt : '{' blockstmts '}'
     | IF '(' expr ')' stmt %prec PREC_ELSELESS_IF
     | IF '(' expr ')' stmt ELSE stmt
     | WHILE '(' expr ')' stmt
     | expr '=' expr ';'
     | CONTINUE ';'
     | BREAK ';'
     | RETURN expr ';'
     | RETURN ';'
     | expr '.' ID '(' exprlistopt ')'  ';'
     ;

expr : expr '>' expr                    
     | expr '<' expr                    
     | expr GREAT_EQ expr           
     | expr LESS_EQ expr            
     | expr EQ expr                 
     | expr DIFF expr               
     | expr OR expr                 
     | expr AND expr                
     | expr '+' expr                    
     | expr '-' expr                    
     | expr '/' expr                    
     | expr '*' expr                    
     | expr '%' expr                    
     | object filledbracks 
     | LIT_INT                      
     | LIT_STR                      
     | TRUE                         
     | FALSE                        
     | TOK_NULL                         
     | object
     | '-' expr %prec PREC_UNARY_OP                        
     | '!' expr %prec PREC_UNARY_OP                                              
     ; 

object : NEW type  
       | NEW ID '(' exprlistopt ')'   
       | ID
       | THIS_DOT ID
       | THIS
       | expr '.' ID '(' exprlistopt ')'
       | '(' expr ')'      
       | '{' exprlist '}'                         
       ;

exprlist : expr ',' exprlist
         | expr
         ;

exprlistopt : exprlist 
            | 
            ;


filledbracks : filledbracks '[' expr ']' 
             | '[' expr ']' 
             ; 

%%

#include "lex.yy.c"

void yyerror(char* s){
  fprintf(stderr, "line: %d: %s\n", yylineno, s);
}