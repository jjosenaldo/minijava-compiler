#include <iostream>
#include <string>
#include "expression.hpp"

using std::cout;
using std::string;

Type* Expression::getType(){
    return this->type;
}

AtomExpression::AtomExpression(Type* type){
    this->type = type;
}

AtomExpression::AtomExpression(AtomExpValue val, Type* type){
    this->type = type;
    this->val = val;
}

void AtomExpression::print(){
    if(this->type == nullptr){
        cout << "???";
    } else switch(this->type->kind){
        case TypeNull:
            cout << "null";break;
        case TypeInt:
            cout << this->val.intval;break;
        case TypeVoid:
            cout << "ERROR: exp of type void";break;
        case TypeBoolean:
            cout << this->val.boolval;break;
        case TypeClass:
            cout << string(this->val.strval);break;
        default:
            cout << "ERROR: invalid type for an atomic expression";
    }
}