%{

#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ast.hpp"
#include "node.hpp"
#include "symtable-pool.hpp"

using std::cout;
using std::endl;

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

%code requires{
    #include <deque>
    #include "ast.hpp"
    using std::deque;

    struct ClassMember{
        bool isField;
        union{
            Method* method;
            Field* field;
        };
    };
}

%union{
  struct Node* nodePointer;
  char* _str;
  int _int;
  class ClassDeclaration* _classDecl;
  class Block* _block;
  class Program* _program;
  class VarDec* _varDec;
  class Method* _methodDec;
  struct Type* _type;
  deque<ClassDeclaration*>* _classDecls; 
  deque<ClassMember>* _classMembers; 
  deque<Parameter*>* _params;
  Parameter* _param;
  Expression* _expr;
};

%token INT TRUE FALSE BOOLEAN BREAK CLASS CONTINUE VOID EXTENDS RETURN IF ELSE WHILE THIS TOK_NULL NEW ERROR ARR THIS_DOT
%token <_str> ID LIT_STR
%token <_int> LIT_INT

%type <_str> extendsopt
%type <_block> blockstmts
%type <_classMembers> classmembers
%type <_classDecl> mainclass classdec
%type <_classDecls> classdecs
%type <_expr> expr
%type <_param> param
%type <_params> params paramsrest
%type <_program> goal
%type <_varDec> vardec
%type <_methodDec> methoddec
%type <_type> type
%type <nodePointer>  stmt exprlistopt object filledbracks exprlist

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
    program = new Program($2);
    program->addClassDeclAtFront($1); 
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

classdecs : classdec classdecs {
    if($2 != nullptr){
        $2->push_front($1);
        $$ = $2;
    }
        
    else{
        $$ = new deque<ClassDeclaration*>();
        $$->push_front($1);
    }
}
| {
    $$ = nullptr;
};

classdec : CLASS ID extendsopt '{' classmembers '}' {
    Symtable* newTable = new Symtable();
    if(!tablePool.insert(string($2), newTable)){
        multipleClassError($2);
        return 1;
    }

    ClassDeclaration* decl;

    if($3 != nullptr)
        decl = new ClassDeclaration($2,string($3));
    else
        decl = new ClassDeclaration($2);
    
    if($5 != nullptr){
        for(auto classMember : *$5){
            if(classMember.isField){
                decl->addField(classMember.field);
            } else{
                decl->addMethod(classMember.method);
            }
        }
    }
    
    $$ = decl;

    currentScope = newTable;
} ;

classmembers : vardec classmembers {
    Field* f = new Field($1->getType(), $1->getId(), $1->getExpression());
    ClassMember member;
    member.field = f;
    member.isField = true;
    
    if($2 == nullptr){
        $$ = new deque<ClassMember>();
        $$->push_front(member);
    } else{
        $2->push_front(member);
        $$ = $2;
    }
}
| methoddec classmembers {
    Method* m = new Method($1->getId(), $1->getReturnType(), $1->getParameters(), $1->getStatement());
    ClassMember member;
    member.method = m;
    member.isField = false;
    
    if($2 == nullptr){
        $$ = new deque<ClassMember>();
        $$->push_front(member);
    } else{
        $2->push_front(member);
        $$ = $2;
    }
}
|{
    $$ = nullptr;
};

vardec : type ID ';' {
    $$ = new VarDec($1, $2);
}
| type ID '=' expr ';' {
    $$ = new VarDec($1, $2, $4);
};

methoddec : type ID '(' params ')' '{' blockstmts '}' {
    Method* m = new Method($2, $1, $4, $7);
    $$ = m;
} ;

params : param paramsrest {
    if($2 == nullptr){
        deque<Parameter*>* params = new deque<Parameter*>();
        params->push_front($1);
        $$ = params;
    } else{
        $2->push_front($1);
        $$ = $2;
    }
}
| {
    $$ = nullptr;
} ;

paramsrest : ',' param paramsrest {
    if($3 == nullptr){
        deque<Parameter*>* params = new deque<Parameter*>();
        params->push_front($2);
        $$ = params;
    } else{
        $3->push_front($2);
        $$ = $3;
    }
} 
| {
    $$ = nullptr;
};

param : type ID {
    $$ = new Parameter($1, $2);
};

extendsopt : EXTENDS ID {
    $$ = $2;
}
| {
    $$ = nullptr;
};


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
    // TODO
    $$ = nullptr;
}
| {
    $$ = nullptr;
};

stmt : '{' blockstmts '}' {
    // TODO
    $$ = nullptr;
}
     | IF '(' expr ')' stmt %prec PREC_ELSELESS_IF    {
                                                      }
     | IF '(' expr ')' stmt ELSE stmt                 {
                                                       
                                                      }
     | WHILE '(' expr ')' stmt                        {
                                                        
                                                      }
     | expr '=' expr ';'                              {
                                                        
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
                                                        
                                                      }
     | RETURN ';'                                     {
                                                        Node* parent = createNode("stmt");
                                                        addChildToParent(&parent, createNode("RETURN"));
                                                        addChildToParent(&parent, createNode(";"));
                                                        $$ = parent;
                                                      }
     | expr '.' ID '(' exprlistopt ')'  ';'           {
                                                        
                                                      }
     | ';'                                            {
                                                        Node* parent = createNode("stmt");
                                                        addChildToParent(&parent, createNode(";"));
                                                        $$ = parent;
                                                      }
     ;

expr : expr '>' expr {

}

| expr '<' expr {
    
}

| expr GREAT_EQ expr {

}

| expr LESS_EQ expr {

}

| expr EQ expr {
    
}

| expr DIFF expr {
    
}

| expr OR expr {

}

| expr AND expr {

}

| expr '+' expr {

}

| expr '-' expr {
    
}

| expr '/' expr {
    
}

| expr '*' expr {
    
}

| expr '%' expr {
    
}

| object filledbracks {
    
}

| LIT_INT {
    AtomExpValue val;
    val.intval = $1;
    AtomExpression* exp = new AtomExpression(val, MkTypeInt());
    $$ = exp;
}

| LIT_STR {
    AtomExpValue val;
    val.strval = $1;
    AtomExpression* exp = new AtomExpression(val, MkTypeClass("String"));
}

| TRUE {
    AtomExpValue val;
    val.boolval = true;
    AtomExpression* exp = new AtomExpression(val, MkTypeBoolean());
}

| FALSE {
    AtomExpValue val;
    val.boolval = false;
    AtomExpression* exp = new AtomExpression(val, MkTypeBoolean());
}

| TOK_NULL {
    AtomExpression* exp = new AtomExpression(MkTypeNull());
}

| object {

}

| '-' expr %prec PREC_UNARY_OP {

}

| '!' expr %prec PREC_UNARY_OP {

} ;

type : type ARR {
    $$ = MkTypeArray($1);
}
| BOOLEAN  {
    $$ = MkTypeBoolean();
}
| INT {
    $$ = MkTypeInt();
}
| VOID {
    $$ = MkTypeVoid();
}
| ID {
    $$ = MkTypeClass($1);
};

object : NEW type {

}
       | NEW ID '(' exprlistopt ')'       {
                                            
                                          }
       | ID                               {
                                            
                                          }
       | THIS_DOT ID                      {
                                            
                                          }
       | THIS                             {
                                            
                                          }
       | expr '.' ID '(' exprlistopt ')'  {
                                            
                                          }
       | '(' expr ')'                     {
                                            
                                          }
       | '{' exprlist '}'                 {
                                            
                                          }
       ;

exprlist : expr ',' exprlist  {
                                
                              }
         | expr               {
                                
                              }
         ;

exprlistopt : exprlist  {
                          
                        }
            |           {
                          
                        }
            ;


filledbracks : filledbracks '[' expr ']'  {
                                            
                                          }
             | '[' expr ']'               {
                                            
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
