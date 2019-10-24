#include <iostream>
#include "error.hpp"
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

bool VarDec::process(Symtable* parent, ClassSymtablePool* pool, Program* program){
    if(type->kind == TypeClass && pool->get(type->getClassName()) == nullptr){
        classNotDefinedError(type->getClassName());
        return false;
    }

    if(predefinedId(id) || pool->get(id) != nullptr){
        classAsVariableNameError(id);
        return false;
    }

    if(parent->get(id).tag != TCNOCONTENT){
        multipleVariableError(id);
        return false;
    }
    
    if(this->value != nullptr){
        if(!this->value->process(parent, pool, program))
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

bool Block::process(Symtable* parent, ClassSymtablePool* pool, Program* program){
    Symtable* table = new Symtable(parent->getClassName());

    if(statements != nullptr)
        for(auto stmt : *statements){
            if(!stmt->process(table, pool, program))
                return false;
        }
            

    table->setParent(parent);
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

bool ElselessIf::process(Symtable* parent, ClassSymtablePool* pool, Program* program){
    return statement->process(parent, pool, program);
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

bool IfElse::process(Symtable* parent, ClassSymtablePool* pool, Program* program){
    return statementIf->process(parent, pool, program) && statementElse->process(parent, pool, program);
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

bool While::process(Symtable* parent, ClassSymtablePool* pool, Program* program){
    return statement->process(parent, pool, program);
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