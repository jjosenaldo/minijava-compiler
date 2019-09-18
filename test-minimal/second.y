%{
#include <ctype.h>
#include <stdio.h>
int yylex();
int yyerror();

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

%token LIT_INT STRING INT TRUE FALSE BOOLEAN BREAK CLASS CONTINUE PUBLIC STATIC VOID MAIN EXTENDS RETURN IF ELSE WHILE LENGTH THIS NEW TOK_NULL ID ERROR LIT_STR BOOL

%nonassoc PREC_1
%left '+' '-'
%left '*' '/' '%'
%nonassoc AND OR
%nonassoc '<' '>' EQ DIFF LESS_EQ GREAT_EQ

%%

init : expr 
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
     | expr '[' expr ']'                
     | '{' expr_list '}'                
     | expr '.' ID '(' expr_list ')'
     | LIT_INT                      
     | LIT_STR                      
     | TRUE                         
     | FALSE                        
     | THIS '.' ID              
     | THIS                         
     | ID                           
     | TOK_NULL                         
     | NEW type filledbracks        
     | NEW type '(' expr_list ')'   
     | '-' expr %prec PREC_1                        
     | '!' expr %prec PREC_1                         
     | '(' expr ')'                     
     ; 

expr_list : expr ',' expr_list
         | 
         ;

filledbracks : '[' expr ']' filledbracks
             | 
             ; 

type : type '[' ']'
     | BOOL
     | INT
     | VOID
     | ID
     ;

%%

#include "lex.yy.c"
