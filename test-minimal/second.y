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
                                      Node* child1 = createNode("CLASS");
                                      Node* child2 = createNode("ID");
                                      Node* child3 = createNode("{");
                                      Node* child4 = createNode("VOID");
                                      Node* child5 = createNode("ID");
                                      Node* child6 = createNode("(");
                                      Node* child7 = createNode("ID");
                                      Node* child8 = createNode("ARR");
                                      Node* child9 = createNode("ID");
                                      Node* child10 = createNode(")");
                                      Node* child11 = createNode("{");

                                      Node* child13 = createNode("}");
                                      Node* child14 = createNode("}");

                                      addChildToParent(&parent, child1);
                                      addChildToParent(&parent, child2);
                                      addChildToParent(&parent, child3);
                                      addChildToParent(&parent, child4);
                                      addChildToParent(&parent, child5);
                                      addChildToParent(&parent, child6);
                                      addChildToParent(&parent, child7);
                                      addChildToParent(&parent, child8);
                                      addChildToParent(&parent, child9);
                                      addChildToParent(&parent, child10);
                                      addChildToParent(&parent, child11);
                                      addChildToParent(&parent, $12);
                                      addChildToParent(&parent, child13);
                                      addChildToParent(&parent, child14);

                                      $$ = parent;
                                      printTree(parent);
                                    }
          ;

classdecs : classdec classdecs      {
                                      Node* parent = createNode("classdecs");
                                      addChildToParent(&parent, $1);
                                      addChildToParent(&parent, $2);
                                      printTree(parent);
                                    }
          |                         {
                                      Node* parent = createNode("EPS");
                                      printTree(parent);
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

                                      printTree(parent);
                                      printf("\n");
                                    }
         ;

classmembers : vardec classmembers {
                                      Node* parent = createNode("classmembers");

                                      addChildToParent(&parent, $1);
                                      addChildToParent(&parent, $2);
                                      printTree(parent);
                                    }
             | methoddec classmembers
                                    {
                                      Node* parent = createNode("classmembers");

                                      addChildToParent(&parent, $1);
                                      addChildToParent(&parent, $2);
                                      printTree(parent);
                                    }
             |                      {
                                      Node* parent = createNode("EPS");
                                      printTree(parent);
                                    }
             ;

vardec : type ID ';'                {
                                      Node* parent = createNode("vardec");
                                      Node* child2 = createNode("ID");
                                      Node* child3 = createNode(";");
                                      addChildToParent(&parent, $1);
                                      addChildToParent(&parent, child2);
                                      addChildToParent(&parent, child3);
                                      printTree(parent);
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
                                      printTree(parent);
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
                                      printTree(parent);
                                    }
          ;

params : param paramsrest           {
                                      Node* parent = createNode("params");
                                      addChildToParent(&parent, $1);
                                      addChildToParent(&parent, $2);
                                      printTree(parent);
                                    }
       |                            {
                                      Node* parent = createNode("EPS");
                                      printTree(parent);
                                    }
       ;

paramsrest : ';' param paramsrest   {
                                      Node* parent = createNode("paramsrest");
                                      Node* child1 = createNode(";");
                                      addChildToParent(&parent, child1);
                                      addChildToParent(&parent, $2);
                                      addChildToParent(&parent, $3);
                                      printTree(parent);
                                    }
           |                        {
                                      Node* parent = createNode("EPS");
                                      printTree(parent);
                                    }
           ;

param : type ID                     {
                                      Node* parent = createNode("param");
                                      Node* child2 = createNode("ID");
                                      addChildToParent(&parent, $1);
                                      addChildToParent(&parent, child2);
                                      printTree(parent);
                                    }
      ;

extendsopt : EXTENDS ID             {
                                      Node* parent = createNode("extendsopt");
                                      Node* child1 = createNode("EXTENDS");
                                      Node* child2 = createNode("ID");
                                      addChildToParent(&parent, child1);
                                      addChildToParent(&parent, child2);

                                      printTree(parent);
                                    }
           |                        {
                                      Node* parent = createNode("EPS");
                                      printTree(parent);
                                    }
           ;


blockstmts : vardec blockstmts      {
                                      Node* parent = createNode("blockstmts");
                                      addChildToParent(&parent, $1);
                                      addChildToParent(&parent, $2);

                                      printTree(parent);
                                    }
           | stmt blockstmts        {
                                      Node* parent = createNode("blockstmts");
                                      addChildToParent(&parent, $1);
                                      addChildToParent(&parent, $2);

                                      printTree(parent);
                                    }
           |                        {
                                      Node* parent = createNode("EPS");
                                      printTree(parent);
                                    }
           ;

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

expr : expr '>' expr          {
                                Node* parent = createNode("expr");
                                Node* child2 = createNode(">");
                                addChildToParent(&parent, $1);
                                addChildToParent(&parent, child2);
                                addChildToParent(&parent, $3);
                                $$ = parent;
                                printTree(parent);
                               }
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
     | LIT_INT               {
                                Node* parent = createNode("LIT_INT");
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

<<<<<<< HEAD
                              }
     | LIT_STR
     | TRUE
     | FALSE
     | TOK_NULL
     | object
     | '-' expr %prec PREC_UNARY_OP
     | '!' expr %prec PREC_UNARY_OP
     ;
=======
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
>>>>>>> 228e2d49a238e208d894dd16e01046c62b7f25d6

type : type ARR
     | BOOLEAN
     | INT
     | VOID
     | ID
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