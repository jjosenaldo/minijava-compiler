%{
#include <ctype.h>
#include <stdio.h>

#define YYSTYPE Node*
#define NUMBER_OF_CHILDREN 20
#define ACCESS(x) (*(*x))

int yylex();
void yyerror(char* s);

typedef struct Node{
  struct Node* children[NUMBER_OF_CHILDREN];
  char* content;
} Node;



Node* createNode(char* name);
void addChildToParent(Node** parent, Node* child);
void printTree(Node* root);



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

goal : mainclass classdecs          { printf("\n");}
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

stmt : '{' blockstmts '}'                             {
                                                        Node* parent = createNode("stmt");
                                                        addChildToParent(&parent, createNode("{"));
                                                        addChildToParent(&parent, $2);
                                                        addChildToParent(&parent, createNode("}"));
                                                        $$ = parent;
                                                      }
     | IF '(' expr ')' stmt %prec PREC_ELSELESS_IF    {
                                                        Node* parent = createNode("stmt");
                                                        addChildToParent(&parent, createNode("IF"));
                                                        addChildToParent(&parent, createNode("("));
                                                        addChildToParent(&parent, $3);
                                                        addChildToParent(&parent, createNode(")"));
                                                        addChildToParent(&parent, $5);
                                                        $$ = parent;
                                                      }
     | IF '(' expr ')' stmt ELSE stmt                 {
                                                        Node* parent = createNode("stmt");
                                                        addChildToParent(&parent, createNode("IF"));
                                                        addChildToParent(&parent, createNode("("));
                                                        addChildToParent(&parent, $3);
                                                        addChildToParent(&parent, createNode(")"));
                                                        addChildToParent(&parent, $5);
                                                        addChildToParent(&parent, createNode("ELSE"));
                                                        addChildToParent(&parent, $7);
                                                        $$ = parent;
                                                      }
     | WHILE '(' expr ')' stmt                        {
                                                        Node* parent = createNode("stmt");
                                                        addChildToParent(&parent, createNode("WHILE"));
                                                        addChildToParent(&parent, createNode("("));
                                                        addChildToParent(&parent, $3);
                                                        addChildToParent(&parent, createNode(")"));
                                                        addChildToParent(&parent, $5);
                                                        $$ = parent;
                                                      }
     | expr '=' expr ';'                              {
                                                        Node* parent = createNode("stmt");
                                                        addChildToParent(&parent, $1);
                                                        addChildToParent(&parent, createNode("="));
                                                        addChildToParent(&parent, $3);
                                                        addChildToParent(&parent, createNode(";"));
                                                        $$ = parent;
                                                      }
     | CONTINUE ';'                                   {
                                                        Node* parent = createNode("stmt");
                                                        addChildToParent(&parent, createNode("CONTINUE"));
                                                        addChildToParent(&parent, createNode(";"));
                                                        $$ = parent;
                                                      }
     | BREAK ';'                                      {
                                                        Node* parent = createNode("stmt");
                                                        addChildToParent(&parent, createNode("BREAK"));
                                                        addChildToParent(&parent, createNode(";"));
                                                        $$ = parent;
                                                      }
     | RETURN expr ';'                                {
                                                        Node* parent = createNode("stmt");
                                                        addChildToParent(&parent, createNode("RETURN"));
                                                        addChildToParent(&parent, $2);
                                                        addChildToParent(&parent, createNode(";"));
                                                        $$ = parent;
                                                      }
     | RETURN ';'                                     {
                                                        Node* parent = createNode("stmt");
                                                        addChildToParent(&parent, createNode("RETURN"));
                                                        addChildToParent(&parent, createNode(";"));
                                                        $$ = parent;
                                                      }
     | expr '.' ID '(' exprlistopt ')'  ';'           {
                                                        Node* parent = createNode("stmt");
                                                        addChildToParent(&parent, $1);
                                                        addChildToParent(&parent, createNode("."));
                                                        addChildToParent(&parent, createNode("ID"));
                                                        addChildToParent(&parent, createNode("("));
                                                        addChildToParent(&parent, $5);
                                                        addChildToParent(&parent, createNode(")"));
                                                        addChildToParent(&parent, createNode(";"));
                                                        $$ = parent;
                                                      }
     ;

expr : expr '>' expr          {
                                Node* parent = createNode("expr");
                                Node* child2 = createNode(">"); 
                                addChildToParent(&parent, $1);
                                addChildToParent(&parent, child2);
                                addChildToParent(&parent, $3);
                                $$ = parent;
                               }                   
     
     | expr '<' expr           {
                                Node* parent = createNode("expr");
                                Node* child2 = createNode("<"); 
                                addChildToParent(&parent, $1);
                                addChildToParent(&parent, child2);
                                addChildToParent(&parent, $3);
                                $$ = parent;
                               }   

     | expr GREAT_EQ expr      {
                                Node* parent = createNode("expr");
                                Node* child2 = createNode(">="); 
                                addChildToParent(&parent, $1);
                                addChildToParent(&parent, child2);
                                addChildToParent(&parent, $3);
                                $$ = parent;
                               } 

     | expr LESS_EQ expr       {
                                Node* parent = createNode("expr");
                                Node* child2 = createNode("<="); 
                                addChildToParent(&parent, $1);
                                addChildToParent(&parent, child2);
                                addChildToParent(&parent, $3);
                                $$ = parent;
                               } 

     | expr EQ expr            {
                                Node* parent = createNode("expr");
                                Node* child2 = createNode("=="); 
                                addChildToParent(&parent, $1);
                                addChildToParent(&parent, child2);
                                addChildToParent(&parent, $3);
                                $$ = parent;
                               }  

     | expr DIFF expr          {
                                Node* parent = createNode("expr");
                                Node* child2 = createNode("!="); 
                                addChildToParent(&parent, $1);
                                addChildToParent(&parent, child2);
                                addChildToParent(&parent, $3);
                                $$ = parent;
                               }  

     | expr OR expr            {
                                Node* parent = createNode("expr");
                                Node* child2 = createNode("||"); 
                                addChildToParent(&parent, $1);
                                addChildToParent(&parent, child2);
                                addChildToParent(&parent, $3);
                                $$ = parent;
                               } 

     | expr AND expr           {
                                Node* parent = createNode("expr");
                                Node* child2 = createNode("&&"); 
                                addChildToParent(&parent, $1);
                                addChildToParent(&parent, child2);
                                addChildToParent(&parent, $3);
                                $$ = parent;
                               }      

     | expr '+' expr           {
                                Node* parent = createNode("expr");
                                Node* child2 = createNode("+"); 
                                addChildToParent(&parent, $1);
                                addChildToParent(&parent, child2);
                                addChildToParent(&parent, $3);
                                $$ = parent;
                               }

     | expr '-' expr           {
                                Node* parent = createNode("expr");
                                Node* child2 = createNode("-"); 
                                addChildToParent(&parent, $1);
                                addChildToParent(&parent, child2);
                                addChildToParent(&parent, $3);
                                $$ = parent;
                               }

     | expr '/' expr           {
                                Node* parent = createNode("expr");
                                Node* child2 = createNode("/"); 
                                addChildToParent(&parent, $1);
                                addChildToParent(&parent, child2);
                                addChildToParent(&parent, $3);
                                $$ = parent;
                               } 

     | expr '*' expr           {
                                Node* parent = createNode("expr");
                                Node* child2 = createNode("*"); 
                                addChildToParent(&parent, $1);
                                addChildToParent(&parent, child2);
                                addChildToParent(&parent, $3);
                                $$ = parent;
                               }      

     | expr '%' expr           {
                                Node* parent = createNode("expr");
                                Node* child2 = createNode("%"); 
                                addChildToParent(&parent, $1);
                                addChildToParent(&parent, child2);
                                addChildToParent(&parent, $3);
                                $$ = parent;
                               }   

     | object filledbracks     {
                                Node* parent = createNode("expr");
                                addChildToParent(&parent, $1);
                                addChildToParent(&parent, $2);
                                $$ = parent;
                               } 

     | LIT_INT                {
                                 Node* parent = createNode("LIT_INT");
                                 $$ = parent;
                              }

     | LIT_STR                {
                                 Node* parent = createNode("LIT_STR");
                                 $$ = parent;
                              }

     | TRUE                   {
                                 Node* parent = createNode("TRUE");
                                 $$ = parent;
                              }      

     | FALSE                  {
                                 Node* parent = createNode("FALSE");
                                 $$ = parent;
                              }      

     | TOK_NULL               {
                                 Node* parent = createNode("NULL");
                                 $$ = parent;
                              }

     | object                 {
                                 Node* parent = createNode("expr");
                                 addChildToParent(&parent, $1);
                                 $$ = parent;
                              }

     | '-' expr %prec PREC_UNARY_OP   {
                                        Node* parent = createNode("expr");
                                        Node* child1 = createNode("-");
                                        addChildToParent(&parent, child1);
                                        addChildToParent(&parent, $2);
                                        $$ = parent;
                                      }

     | '!' expr %prec PREC_UNARY_OP   {
                                        Node* parent = createNode("expr");
                                        Node* child1 = createNode("!");
                                        addChildToParent(&parent, child1);
                                        addChildToParent(&parent, $2);
                                        $$ = parent;
                                      }                                           
     ; 

type : type ARR {
                  Node* parent = createNode("type");
                  addChildToParent(&parent, $1);
                  addChildToParent(&parent, createNode("[]"));
                  $$ = parent;
                }
     | BOOLEAN  {
                  Node* parent = createNode("type");
                  addChildToParent(&parent, createNode("BOOLEAN"));
                  $$ = parent;
                }
     | INT      {
                  Node* parent = createNode("type");
                  addChildToParent(&parent, createNode("INT"));
                  $$ = parent;
                }
     | VOID     {
                  Node* parent = createNode("type");
                  addChildToParent(&parent, createNode("VOID"));
                  $$ = parent;
                }
     | ID       {
                  Node* parent = createNode("type");
                  addChildToParent(&parent, createNode("ID"));
                  $$ = parent;
                }
     ;

object : NEW type                         {
                                            Node* parent = createNode("object");
                                            addChildToParent(&parent, createNode("NEW"));
                                            addChildToParent(&parent, $2);
                                            $$ = parent;
                                          }
       | NEW ID '(' exprlistopt ')'       {
                                            Node* parent = createNode("object");
                                            addChildToParent(&parent, createNode("NEW"));
                                            addChildToParent(&parent, createNode("ID"));
                                            addChildToParent(&parent, createNode("("));
                                            addChildToParent(&parent, $4);
                                            addChildToParent(&parent, createNode(")"));
                                            $$ = parent;
                                          }
       | ID                               {
                                            Node* parent = createNode("object");
                                            addChildToParent(&parent, createNode("ID"));
                                            $$ = parent;
                                          }
       | THIS_DOT ID                      {
                                            Node* parent = createNode("object");
                                            addChildToParent(&parent, createNode("THIS"));
                                            addChildToParent(&parent, createNode("."));
                                            addChildToParent(&parent, createNode("ID"));
                                            $$ = parent;
                                          }
       | THIS                             {
                                            Node* parent = createNode("object");
                                            addChildToParent(&parent, createNode("THIS"));
                                            $$ = parent;
                                          }
       | expr '.' ID '(' exprlistopt ')'  {
                                            Node* parent = createNode("object");
                                            addChildToParent(&parent, $1);
                                            addChildToParent(&parent, createNode("."));
                                            addChildToParent(&parent, createNode("ID"));
                                            addChildToParent(&parent, createNode("("));
                                            addChildToParent(&parent, $5);
                                            addChildToParent(&parent, createNode(")"));
                                            $$ = parent;
                                          }
       | '(' expr ')'                     {
                                            Node* parent = createNode("object");
                                            addChildToParent(&parent, createNode("("));
                                            addChildToParent(&parent, $2);
                                            addChildToParent(&parent, createNode(")"));
                                            $$ = parent;
                                          }
       | '{' exprlist '}'                 {
                                            Node* parent = createNode("object");
                                            addChildToParent(&parent, createNode("'{'"));
                                            addChildToParent(&parent, $2);
                                            addChildToParent(&parent, createNode("'}'"));
                                            $$ = parent;
                                          }
       ;

exprlist : expr ',' exprlist  {
                                Node* parent = createNode("exprlist");
                                addChildToParent(&parent, $1);
                                addChildToParent(&parent, createNode(","));
                                addChildToParent(&parent, $3);
                                $$ = parent;
                              }
         | expr               {
                                Node* parent = createNode("exprlist");
                                addChildToParent(&parent, $1);
                                $$ = parent;
                              }
         ;

exprlistopt : exprlist  {
                          Node* parent = createNode("exprlistopt");
                          addChildToParent(&parent, $1);
                          $$ = parent;
                        }
            |           {
                          Node* parent = createNode("exprlistopt");
                          addChildToParent(&parent, createNode("EPS"));
                          $$ = parent;
                        }
            ;


filledbracks : filledbracks '[' expr ']'  {
                                            Node* parent = createNode("filledbracks");
                                            addChildToParent(&parent, $1);
                                            addChildToParent(&parent, createNode("["));
                                            addChildToParent(&parent, $3);
                                            addChildToParent(&parent, createNode("]"));
                                            $$ = parent;
                                          }
             | '[' expr ']'               {
                                            Node* parent = createNode("filledbracks");
                                            addChildToParent(&parent, createNode("["));
                                            addChildToParent(&parent, $2);
                                            addChildToParent(&parent, createNode("]"));
                                            $$ = parent;
                                          }
             ; 

%%

#include "lex.yy.c"

void yyerror(char* s){
  fprintf(stderr, "line: %d: %s\n", yylineno, s);
}

Node* createNode(char* content){
  Node* newNode = (Node*) malloc(sizeof(Node));
  newNode->content = content;
//  printf("createNode\n");
  return newNode;
}

void addChildToParent(Node** parent, Node* child){
  for(int i = 0; i < NUMBER_OF_CHILDREN; ++i){
    if( ACCESS(parent).children[i] == NULL  ){
      ACCESS(parent).children[i] = child;
      break;
    }
  }

  //printf("added child\n");
}

void printTree(Node* root){
  printf("%s", root->content);

  if(root->children[0] != NULL) {
    printf(" { ");

    for(int i = 0; i < NUMBER_OF_CHILDREN; i++){
      if(root->children[i] == NULL)
        break;

      printTree(root->children[i]);
    }


    printf("}");
  }

  printf(" ");

}