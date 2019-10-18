%{

#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ast.hpp"
#include "node.hpp"
#include "symtable-pool.hpp"

using namespace std;

extern int yylex();
extern int yylineno;
void yyerror(const char* s);

void errorMsgPrefix();
void multipleClassError(char* id);
void beginScope();
void endScope();

SymtablePool tablePool;
Symtable* currentScope;

Program* program;
%}

%union{
  struct Node* nodePointer;
  char* str;
  class ClassDeclaration* _classDecl;
  class Block* _block;
  class Program* _program;
  class VarDec* _varDec;
  struct Type* _type;
};

%token LIT_INT INT TRUE FALSE BOOLEAN BREAK CLASS CONTINUE VOID EXTENDS RETURN IF ELSE WHILE THIS TOK_NULL NEW ERROR LIT_STR ARR THIS_DOT
%token <str> ID

%type <_block> blockstmts
%type <_classDecl> mainclass;
%type <_program> goal
%type <_varDec> vardec
%type <_type> type
%type <nodePointer> classdecs classdec extendsopt classmembers  methoddec params expr paramsrest param stmt exprlistopt object filledbracks exprlist

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
goal : mainclass classdecs {
    program = new Program();
    program->addClassDecl($1);                        
} ;

mainclass : CLASS ID '{' VOID ID '(' ID ARR ID ')' '{' blockstmts '}' '}' {
    Symtable* newTable = new Symtable();
    tablePool.insert(string($2), newTable);
    currentScope = newTable;

    // Parameter
    Type* paramType = MkTypeArray(MkTypeClass($7));
    string paramName = string($9);
    Parameter* param = new Parameter(paramType, paramName);

    // Method
    Block* statements = $12;
    Type* returnType = MkTypeVoid();
    Method* mainMethod = new Method(string($5), returnType, statements);
    mainMethod->addParam(param);

    // Class
    ClassDeclaration* decl = new ClassDeclaration($2);
    decl->addMethod(mainMethod);
    $$ = decl;
};

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
                                      Symtable* newTable = new Symtable();
                                      if(!tablePool.insert(string($2), newTable)){
                                        multipleClassError($2);
                                        return 1;
                                      }
                                      currentScope = newTable;

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
                                      addChildToParent(&parent, createNode("EPS"));
                                      $$ = parent;
                                    }
             ;

vardec : type ID ';' {
    VarDec* decl = new VarDec($1, $2);
    $$ = decl;
}
| type ID '=' expr ';' {
};

methoddec : type ID '(' params ')' '{' blockstmts '}' {
    $$ = nullptr;
} ;

params : param paramsrest           {
                                      Node* parent = createNode("params");
                                      addChildToParent(&parent, $1);
                                      addChildToParent(&parent, $2);
                                      $$ = parent;
                                    }
       |                            {
                                      Node* parent = createNode("params");
                                      addChildToParent(&parent, createNode("EPS"));
                                      $$ = parent;
                                    }
       ;

paramsrest : ',' param paramsrest   {
                                      Node* parent = createNode("paramsrest");
                                      Node* child1 = createNode(",");
                                      addChildToParent(&parent, $2);
                                      addChildToParent(&parent, $3);
                                      $$ = parent;
                                    }
           |                        {
                                      Node* parent = createNode("paramsrest");
                                      addChildToParent(&parent, createNode("EPS"));
                                      $$ = parent;
                                    }
           ;

param : type ID {
};

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
                                      addChildToParent(&parent, createNode("EPS"));
                                      $$ = parent;
                                    }
           ;


blockstmts : vardec blockstmts{
    if($2 != nullptr){
        $2->addStatementAtFront($1);
        $$ = $2;
    }
        
    else{
        Block* block = new Block;
        block->addStatement($1);
        $$ = block;
    }
}
| stmt blockstmts   {
    $$ = nullptr;
}
| {
    $$ = nullptr;
};

stmt : '{' blockstmts '}' {
    $$ = nullptr;
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
     | ';'                                            {
                                                        Node* parent = createNode("stmt");
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

}
| BOOLEAN  {
    
}
| INT {
    $$ = MkTypeInt();
}
| VOID {

}
| ID {

};

object : NEW type {

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

void yyerror(const char *s) {
    fprintf(stderr, "line: %d: %s\n", yylineno, s);
}

void errorMsgPrefix(){
    cout << "ERROR at l." << yylineno << ": ";
}

void multipleClassError(char* id){
    errorMsgPrefix();
    cout << "the class " << id << " was multiply defined!" << endl;
}

void beginScope(){
    Symtable* table = new Symtable(currentScope);
    currentScope = table;
}

void endScope(){
    currentScope = currentScope->getParent();
}

int main(){
    tablePool = SymtablePool();
    if(yyparse() != 1){
        // tablePool.print();
        program->print();
    }
    return 0;
}
