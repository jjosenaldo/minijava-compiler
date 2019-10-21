#include <iostream>
#include "statement.hpp"

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

void VarDec::buildSymtable(Symtable* parent){
    // TODO: checks if the variable is already there
    parent->insert(id, tableContentFromType(type));
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

void Block::buildSymtable(Symtable* parent){
    Symtable* table = new Symtable;

    if(statements != nullptr)
        for(auto stmt : *statements)
            stmt->buildSymtable(table);

    table->setParent(parent);
    parent->insert(table);
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

void ElselessIf::buildSymtable(Symtable* parent){
    statement->buildSymtable(parent);
}

void ElselessIf::print(){
    cout << "if(";
    guard->print();
    cout << ")";
    statement->print();
}

IfElse::IfElse(Expression* guard, Statement* statementIf, Statement* statementElse){
    this->guard = guard;
    this->statementIf = statementIf;
    this->statementElse = statementElse;
}

void IfElse::buildSymtable(Symtable* parent){
    statementIf->buildSymtable(parent);
    statementElse->buildSymtable(parent);
}

void IfElse::print(){
    cout << "if(";
    guard->print();
    cout << ")";
    statementIf->print();
    cout << "else ";
    statementElse->print();
}

While::While(Expression* guard, Statement* statement){
    this->guard = guard;
    this->statement = statement;
}

void While::buildSymtable(Symtable* parent){
    statement->buildSymtable(parent);
}

void While::print(){
    cout << "while(";
    guard->print();
    cout << ") ";
    statement->print();
}

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

void Continue::print(){
    cout << "continue;";
}

void Break::print(){
    cout << "break;";
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

MethodCall::MethodCall(Expression* lvalue, string methodName, deque<Expression*>* arguments){
    this->lvalue = lvalue;
    this->methodName = methodName;
    this->arguments = arguments;
}

void MethodCall::print(){
    lvalue->print();
    cout << "." << methodName << "(";
    
    if(arguments != nullptr){
        for(auto arg : *arguments) {arg->print();cout << ",";}
    }

    cout << ");";
}   

void Skip::print(){
    cout << ";";
}