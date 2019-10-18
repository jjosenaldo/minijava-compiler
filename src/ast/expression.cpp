#include <iostream>
#include <string>
#include "expression.hpp"

using std::cout;
using std::string;

string binOpSymbol(BinOperator op){
    if(op == OP_MOD) return "%";
    if(op == OP_GREAT) return ">";
    if(op == OP_LESS   ) return "<";
    if(op == OP_GREAT_EQ) return ">=";
    if(op == OP_LESS_EQ) return "<=";
    if(op == OP_IS_EQ) return "==";
    if(op == OP_DIFF) return "!=";
    if(op == OP_OR) return "||";
    if(op == OP_AND) return "&&";
    if(op == OP_PLUS) return "+";
    if(op == OP_BIN_MINUS) return "-";
    if(op == OP_TIMES) return "*";
    if(op == OP_DIV) return "/";
    return "";
}

string unOpSymbol(UnOperator op){
    if(op == OP_UN_MINUS) return "-";
    if(op == OP_NOT) return "!";
    return "";
}

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

BinExpression::BinExpression(Expression* first, Expression* second, BinOperator op){
    this->first = first;
    this->second = second;
    this->op = op;
}

void BinExpression::print(){
    this->first->print();
    cout << " " << binOpSymbol(op) << " ";
    this->second->print();
}

UnExpression::UnExpression(Expression* first, UnOperator op){
    this->first = first;
    this->op = op;
}

void UnExpression::print(){
    cout << unOpSymbol(op);
    first->print();
}