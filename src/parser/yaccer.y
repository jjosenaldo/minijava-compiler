%{

#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ast.hpp"
#include "error.hpp"

using std::cout;
using std::endl;

extern int yylex();
extern int yylineno;
void yyerror(const char* s);

void errorMsgPrefix();

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
  ObjExpression* _objExpr;
  deque<Expression*>* _exprList;
  Statement* _statement;
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
%type <_objExpr> object
%type <_exprList> exprlistopt filledbracks exprlist
%type <_param> param
%type <_params> params paramsrest
%type <_program> goal
%type <_varDec> vardec
%type <_methodDec> methoddec
%type <_type> type
%type <_statement>  stmt   

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
| {
    $$ = new Block;
};

stmt : '{' blockstmts '}' {
    $$ = $2;
}
| IF '(' expr ')' stmt %prec PREC_ELSELESS_IF {
    $$ = new ElselessIf($3, $5);
}
| IF '(' expr ')' stmt ELSE stmt {
    $$ = new IfElse($3, $5, $7);
}
| WHILE '(' expr ')' stmt {
    $$ = new While($3, $5);
}
| expr '=' expr ';' {
    $$ = new Assignment($1, $3);
}
| CONTINUE ';' {
    $$ = new Continue;
}
| BREAK ';' {
    $$ = new Break;
}
| RETURN expr ';' {
    $$ = new Return($2);
}
| RETURN ';' {
    $$ = new Return;
}
| expr '.' ID '(' exprlistopt ')'  ';'{
    $$ = new MethodCall($1, $3, $5);
}
| ';' {
    $$ = new Skip;
} ;

expr : expr '>' expr {
    $$ = new BinExpression($1, $3, OP_GREAT);
}

| expr '<' expr {
    $$ = new BinExpression($1, $3, OP_LESS);
}

| expr GREAT_EQ expr {
    $$ = new BinExpression($1, $3, OP_GREAT_EQ);
}

| expr LESS_EQ expr {
    $$ = new BinExpression($1, $3, OP_LESS_EQ);
}

| expr EQ expr {
    $$ = new BinExpression($1, $3, OP_IS_EQ);
}

| expr DIFF expr {
    $$ = new BinExpression($1, $3, OP_DIFF);
}

| expr OR expr {
    $$ = new BinExpression($1, $3, OP_OR);
}

| expr AND expr {
    $$ = new BinExpression($1, $3, OP_AND);
}

| expr '+' expr {
    $$ = new BinExpression($1, $3, OP_PLUS);   
}

| expr '-' expr {
    $$ = new BinExpression($1, $3, OP_BIN_MINUS);   
}

| expr '/' expr {
    $$ = new BinExpression($1, $3, OP_DIV);   
}

| expr '*' expr {
    $$ = new BinExpression($1, $3, OP_TIMES);   
}

| expr '%' expr {
    $$ = new BinExpression($1, $3, OP_MOD);   
}

| object filledbracks {
    auto arrayDecl = dynamic_cast<ArrayDeclExpression*>($1);
    if(arrayDecl != nullptr ){
        $$ = new NewArrayExpression(arrayDecl, $2);
    } else{
        $$ = new ArrayAccessExpression($1, $2);
    }
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
    $$ = exp;
}

| TRUE {
    AtomExpValue val;
    val.boolval = true;
    AtomExpression* exp = new AtomExpression(val, MkTypeBoolean());
    $$ = exp;
}

| FALSE {
    AtomExpValue val;
    val.boolval = false;
    AtomExpression* exp = new AtomExpression(val, MkTypeBoolean());
    $$ = exp;
}

| TOK_NULL {
    AtomExpression* exp = new AtomExpression(MkTypeNull());
    $$ = exp;
}

| object {
    // Prevents things like "new int" from being considered expressions
    auto decl = dynamic_cast<ArrayDeclExpression*>($1);
    if(decl != nullptr){
        newTypeIsNotAnExpression(decl->getType()->toString());
        return 1;
    }

    $$ = $1;
}

| '-' expr %prec PREC_UNARY_OP {
    $$ = new UnExpression($2, OP_UN_MINUS);
}

| '!' expr %prec PREC_UNARY_OP {
    $$ = new UnExpression($2, OP_NOT);
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
    $$ = new ArrayDeclExpression($2);
}
| NEW ID '(' ')' {
    $$ = new NewObjExpression($2);
} | ID {
    $$ = new IdExpression($1);
} | THIS_DOT ID {
    $$ = new FieldAccessExpression($2);
} | THIS {
    $$ = new ThisExpression;
} | expr '.' ID '(' exprlistopt ')' {
    $$ = new MethodCallExpression($1, $3, $5);
} | '(' expr ')' {
    $$ = new ParenExpression($2);
} | '{' exprlist '}' {
    $$ = new LitArrayExpression($2);
};

exprlist : expr ',' exprlist  {
    deque<Expression*>* newExprList;
    if($3 == nullptr)
        newExprList = new deque<Expression*>();
    else
        newExprList = $3;

    newExprList->push_front($1);
    $$ = newExprList;
} | expr {
    deque<Expression*>* newExprList = new deque<Expression*>();
    newExprList->push_front($1);
    $$ = newExprList;
} ;

exprlistopt : exprlist  {
    $$ = $1;
} | {
    $$ = nullptr;
} ;

filledbracks : filledbracks '[' expr ']'  {
    deque<Expression*>* newExprList = $1;
    newExprList->push_front($3);
    $$ = newExprList;
} | '[' expr ']' {
    deque<Expression*>* newExprList = new deque<Expression*>();
    newExprList->push_front($2);
    $$ = newExprList;
} ;
%%

void yyerror(const char *s) {
    fprintf(stderr, "line: %d: %s\n", yylineno, s);
}

int main(){
    if(yyparse() != 1){
        // program->print();
        auto pool = buildClassSymtablePool(program);

        if(pool != nullptr)
            pool->print();
    }
    return 0;
}
