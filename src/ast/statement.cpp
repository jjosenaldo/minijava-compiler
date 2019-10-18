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
        value->print();
    }
}

void Block::addStatement(GenStatement* stmt){
    this->statements.push_back(stmt);
}

void Block::addStatementAtFront(GenStatement* stmt){
    this->statements.push_front(stmt);
}

void Block::print(){
    cout << "{ ";
    for(auto stmt : this->statements){
        stmt->print();
    }
    cout << " }";
}