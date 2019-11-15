#include <iostream>
#include "error.hpp"
#include "global.hpp"
#include "statement.hpp"
#include "static-visitor.hpp"

using std::cout;
using std::endl;

VarDec::VarDec(Type* type, string id, Expression* value) {
    this->type = type;
    this->id = id;
    this->value = value;
}

VarDec::VarDec(Type* type, string id) : VarDec(type, id, nullptr){}

void VarDec::print(){
    printType(this->type);
    cout << " " << this->id;

    if(this->value != nullptr){
        cout << " = ";
        this->value->print();
    }
    cout << ";";
}

bool VarDec::process(Symtable* parent, ClassSymtablePool* pool){
    if(type->kind == TypeClass && !g_defaultSymbolHandler.isDefaultClass(type->getClassName())){
        if(pool->get(type->getClassName()) == nullptr){
            classNotDefinedError(type->getClassName());
            return false;
        }

        if(g_mainClassName == type->getClassName()){
            instanceOfMainClassError();
            return false;
        }
    }
    
    if(!canBeInstantiated(type, pool))
        return false;

    if(g_defaultSymbolHandler.isDefaultClass(id) || pool->get(id) != nullptr){
        classAsVariableNameError(id);
        return false;
    }

    if(parent->get(id).tag != TCNOCONTENT){
        multipleVariableError(id);
        return false;
    }

    if(this->value != nullptr){
        auto visitor = StaticVisitor(parent, pool);
        std::cout << id << std::endl;
        if(!this->value->accept(visitor))
            return false;

        if(!areCompatibleTypes(type, this->value->getType())){
            varDeclarationTypeError(id, type->toString(), this->value->getType()->toString());
            return false;
        }

        if(this->value->getType()->kind == TypeClass)
            type->setActualClassName(this->value->getType()->getClassName());
    }

    parent->insert(id, tableContentFromType(type));

    return true;
}

Type* VarDec::getType(){
    return this->type;
}

string VarDec::getId(){
    return this->id;
}

Expression* VarDec::getExpression(){
    return this->value;
}

Block:: Block(){
    this->statements = new deque<GenStatement*>;
}

void Block::addStatement(GenStatement* stmt){
    this->statements->push_back(stmt);
}

void Block::addStatementAtFront(GenStatement* stmt){
    this->statements->push_front(stmt);
}

deque<GenStatement*>* Block::getStatements(){
    return statements;
}

bool Block::process(Symtable* parent, ClassSymtablePool* pool){
    Symtable* table = new Symtable(parent->getClassName(), parent->getMethodName());
    table->setParent(parent);

    if(statements != nullptr)
        for(auto stmt : *statements){
            if(!stmt->process(table, pool))
                return false;
        }

    parent->insert(table);
    return true;
}

void Block::print(){
    cout << "{ ";
    for(auto stmt : *this->statements){
        stmt->print();
    }
    cout << " }";
}

ElselessIf::ElselessIf(Expression* guard, Statement* statement){
    this->guard = guard;
    this->statement = statement;
}

bool ElselessIf::process(Symtable* parent, ClassSymtablePool* pool){
    return statement->process(parent, pool);
}

void ElselessIf::print(){
    cout << "if(";
    guard->print();
    cout << ")";
    statement->print();
}

Statement* ElselessIf::getStatement() { return statement; }

IfElse::IfElse(Expression* guard, Statement* statementIf, Statement* statementElse){
    this->guard = guard;
    this->statementIf = statementIf;
    this->statementElse = statementElse;
}

bool IfElse::process(Symtable* parent, ClassSymtablePool* pool){
    return statementIf->process(parent, pool) && statementElse->process(parent, pool);
}

void IfElse::print(){
    cout << "if(";
    guard->print();
    cout << ")";
    statementIf->print();
    cout << "else ";
    statementElse->print();
}

Statement* IfElse::getStatementIf() { return statementElse; }
Statement* IfElse::getStatementElse() { return statementIf; }

While::While(Expression* guard, Statement* statement){
    this->guard = guard;
    this->statement = statement;
}

bool While::process(Symtable* parent, ClassSymtablePool* pool){
    pool->setIsLoopBlock(true);
    bool r = statement->process(parent, pool);
    pool->setIsLoopBlock(false);
    return r;
}

void While::print(){
    cout << "while(";
    guard->print();
    cout << ") ";
    statement->print();
}

Statement* While::getStatement() { return statement; }

Assignment::Assignment(Expression* lvalue, Expression* rvalue){
    this->lvalue = lvalue;
    this->rvalue = rvalue;
}

void Assignment::print(){
    lvalue->print();
    cout << " = ";
    rvalue->print();
    cout << ";";
}

bool Assignment::process(Symtable* parent, ClassSymtablePool* pool){
    lvalue->print();
    std::cout << " = ";
    rvalue->print();
    std::cout << "\n";
    pool->print();
    std::cout << "\n";
    auto visitor = StaticVisitor(parent, pool);

    if(!lvalue->accept(visitor))
        return false;

    std::cout << "Type attributed: " << "\n";
    std::cout << lvalue->getType()->toString() << std::endl;

    if(!lvalue->isLvalue()){
        notAnLvalueError(lvalue->toString());
        return false;
    }

    if(!rvalue->accept(visitor))
        return false;

    if(!areCompatibleTypes(lvalue->getType(), rvalue->getType())){
        typeError(lvalue->getType()->toString(), rvalue->getType()->toString());
        return false;
    }

    return true;
}

void Continue::print(){
    cout << "continue;";
}

bool Continue::process(Symtable* parent, ClassSymtablePool* pool){
    if(!pool->isLoopBlock()){
        breakOutsideLoop();
        return false;
    } else {
        return true;
    }
}

void Break::print(){
    cout << "break;";
}

bool Break::process(Symtable* parent, ClassSymtablePool* pool){
    if(!pool->isLoopBlock()){
        breakOutsideLoop();
        return false;
    } else {
        return true;
    }
}


Return::Return() : Return(nullptr) {}

Return::Return(Expression* optExp){
    this->optExp = optExp;
}

void Return::print(){
    cout << "return";
    if(optExp != nullptr) {cout << " "; optExp->print();}
    cout << ";";
}

bool Return::process(Symtable* parent, ClassSymtablePool* pool){
    Type* optExpType = MkTypeVoid();
    if(optExp != nullptr){
        auto visitor = StaticVisitor(parent, pool);
        bool res = optExp->accept(visitor);

        if(!res)
            return false;
        
        optExpType = optExp->getType();
    }

    ClassSymtable* classTable = pool->get(parent->getClassName());
    TableContent tc = classTable->get(parent->getMethodName());
    Type* methodReturnType = tc.type->getMethodHeader()->at(0);
    if(!areCompatibleTypes(optExpType, methodReturnType)){
        methodReturnTypeError(optExpType->toString(), methodReturnType->toString(), parent->getMethodName());
        return false;
    }

   return true;
}


MethodCallExpression::MethodCallExpression(Expression* left, string method, deque<Expression*>* args){
    this->left = left;
    this->method = method;
    this->arguments = args;
}

string MethodCallExpression::toString(){
    string ans = left->toString() + "." + method + "(";
    if(arguments != nullptr) for(auto e : *arguments) ans += e->toString() + ",";
    return ans + ")";
}

bool MethodCallExpression::process(Symtable* environment, ClassSymtablePool* pool){
    auto visitor = StaticVisitor(environment,pool); 
    return accept(visitor);
}

bool MethodCallExpression::accept(StaticVisitor& visitor){
    return visitor.visit(this);
}

void MethodCallExpression::print(){
    left->print();
    cout << "." << method << "(";

    if(arguments != nullptr){
        for(auto arg : *arguments) {arg->print();cout << ",";}
    }

    cout << ");";
}

StaticMethodCallExpression::StaticMethodCallExpression(string className, string method, deque<Expression*>* arguments){
    this->className = className;
    this->method = method;
    this->arguments = arguments;
}

bool StaticMethodCallExpression::accept(StaticVisitor& visitor){
    return visitor.visit(this);
}

bool StaticMethodCallExpression::process(Symtable* environment, ClassSymtablePool* pool){
    auto visitor = StaticVisitor(environment,pool); 
    return accept(visitor);
}

string StaticMethodCallExpression::toString(){
    // TODO
    return "";
}

void StaticMethodCallExpression::print(){
    // TODO
}

void Skip::print(){
    cout << ";";
}