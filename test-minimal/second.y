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

goal : mainclass classdecs          {
                                      Node* parent = createNode("goal");
                                      addChildToParent(&parent, $1);
                                      addChildToParent(&parent, $2);
                                      printTree(parent);
                                      printf("\n");
                                    }
     ;

mainclass : CLASS ID '{' VOID ID '(' ID ARR ID ')' '{' blockstmts '}' '}' {
                                      Node* parent = createNode("mainclass");
                                      addChildToParent(&parent, createNode("CLASS"));
                                      addChildToParent(&parent, createNode("ID"));
                                      addChildToParent(&parent, createNode("{"));
                                      addChildToParent(&parent, createNode("VOID"));
                                      addChildToParent(&parent, createNode("ID"));
                                      addChildToParent(&parent, createNode("("));
                                      addChildToParent(&parent, ccreateNode("ID"));
                                      addChildToParent(&parent, createNode("ARR"));
                                      addChildToParent(&parent, createNode("ID"));
                                      addChildToParent(&parent, createNode(")"));
                                      addChildToParent(&parent, createNode("{"));
                                      addChildToParent(&parent, $12);
                                      addChildToParent(&parent, createNode("}"));
                                      addChildToParent(&parent, createNode("}"));
                                      $$ = parent;
                                    }
          ;

classdecs : classdec classdecs      {
                                      Node* parent = createNode("classdecs");
                                      addChildToParent(&parent, $1);
                                      addChildToParent(&parent, $2);
                                      $$ = parent;
                                    }
          |                         {
                                      Node* parent = createNode("classdecs");
                                      addChildToParent(&parent, createNode("EPS"));
                                      $$ = parent;
                                    }
          ;

classdec : CLASS ID extendsopt '{' classmembers '}' {
                                      Node* parent = createNode("classdec");
                                      Node* child1 = createNode("CLASS");
                                      Node* child2 = createNode("ID");
                                      Node* child4 = createNode("{");
                                      Node* child6 = createNode("}");

                                      addChildToParent(&parent, child1);
                                      addChildToParent(&parent, child2);
                                      addChildToParent(&parent, $3);
                                      addChildToParent(&parent, child4);
                                      addChildToParent(&parent, $5);
                                      addChildToParent(&parent, child6);

                                      $$ = parent;
                                    }
         ;

classmembers : vardec classmembers {
                                      Node* parent = createNode("classmembers");

                                      addChildToParent(&parent, $1);
                                      addChildToParent(&parent, $2);
                                      $$ = parent;
                                    }
             | methoddec classmembers
                                    {
                                      Node* parent = createNode("classmembers");

                                      addChildToParent(&parent, $1);
                                      addChildToParent(&parent, $2);
                                      $$ = parent;
                                    }
             |                      {
                                      Node* parent = createNode("classmembers");
                                      addChildToParent(&parent, createNode("EPS"))
                                      $$ = parent;
                                    }
             ;

vardec : type ID ';'                {
                                      Node* parent = createNode("vardec");
                                      Node* child2 = createNode("ID");
                                      Node* child3 = createNode(";");
                                      addChildToParent(&parent, $1);
                                      addChildToParent(&parent, child2);
                                      addChildToParent(&parent, child3);
                                      $$ = parent;
                                    }
       | type ID '=' expr ';'       {
                                      Node* parent = createNode("vardec");
                                      Node* child2 = createNode("ID");
                                      Node* child3 = createNode("=");
                                      Node* child5 = createNode(";");
                                      addChildToParent(&parent, $1);
                                      addChildToParent(&parent, child2);
                                      addChildToParent(&parent, child3);
                                      addChildToParent(&parent, $4);
                                      addChildToParent(&parent, child5);
                                      $$ = parent;
                                    }
       ;

methoddec : type ID '(' params ')' '{' blockstmts '}'
                                    {
                                      Node* parent = createNode("methoddec");
                                      Node* child2 = createNode("ID");
                                      Node* child3 = createNode("(");
                                      Node* child5 = createNode(")");
                                      Node* child6 = createNode("{");
                                      Node* child8 = createNode("}");
                                      addChildToParent(&parent, $1);
                                      addChildToParent(&parent, child2);
                                      addChildToParent(&parent, child3);
                                      addChildToParent(&parent, $4);
                                      addChildToParent(&parent, child5);
                                      addChildToParent(&parent, child6);
                                      addChildToParent(&parent, $7);
                                      addChildToParent(&parent, child8);
                                      $$ = parent;
                                    }
          ;

params : param paramsrest           {
                                      Node* parent = createNode("params");
                                      addChildToParent(&parent, $1);
                                      addChildToParent(&parent, $2);
                                      $$ = parent;
                                    }
       |                            {
                                      Node* parent = createNode("params");
                                      addChildToParent(&parent, createNode("EPS"))
                                      $$ = parent;
                                    }
       ;

paramsrest : ';' param paramsrest   {
                                      Node* parent = createNode("paramsrest");
                                      Node* child1 = createNode(";");
                                      addChildToParent(&parent, $2);
                                      addChildToParent(&parent, $3);
                                      $$ = parent;
                                    }
           |                        {
                                      Node* parent = createNode("paramsrest");
                                      addChildToParent(&parent, createNode("EPS"))
                                      $$ = parent;
                                    }
           ;

param : type ID                     {
                                      Node* parent = createNode("param");
                                      Node* child2 = createNode("ID");
                                      addChildToParent(&parent, $1);
                                      addChildToParent(&parent, child2);
                                      $$ = parent;
                                    }
      ;

extendsopt : EXTENDS ID             {
                                      Node* parent = createNode("extendsopt");
                                      Node* child1 = createNode("EXTENDS");
                                      Node* child2 = createNode("ID");
                                      addChildToParent(&parent, child1);
                                      addChildToParent(&parent, child2);

                                      $$ = parent;
                                    }
           |                        {
                                      Node* parent = createNode("extendsopt");
                                      addChildToParent(&parent, createNode("EPS"))
                                      $$ = parent;
                                    }
           ;


blockstmts : vardec blockstmts      {
                                      Node* parent = createNode("blockstmts");
                                      addChildToParent(&parent, $1);
                                      addChildToParent(&parent, $2);

                                      $$ = parent;
                                    }
           | stmt blockstmts        {
                                      Node* parent = createNode("blockstmts");
                                      addChildToParent(&parent, $1);
                                      addChildToParent(&parent, $2);

                                      $$ = parent;
                                    }
           |                        {
                                      Node* parent = createNode("blockstmts");
                                      addChildToParent(&parent, createNode("EPS"))
                                      $$ = parent;
                                    }
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