#include <iostream>
#include <string>
#include "ast.hpp"
#include "global.hpp"
#include "error.hpp"
#include "expression.hpp"

using std::cout;
using std::endl;
using std::string;
using std::to_string;

bool predefinedId(string id){
    return string(id) == "String";
}

Expression::Expression(Type* type){
    this->type = type;
}

Type* Expression::getType(){
    return this->type;
}

bool Expression::isObject(){
    return this->type->kind == TypeClass;
}

BinExpression::BinExpression(Expression* first, Expression* second, BinOperator op){
    this->first = first;
    this->second = second;
    this->op = op;
}

string BinExpression::toString(){
    return this->first->toString() + " " + binOpSymbol(op) + " " + second->toString();
}

bool BinExpression::process(Symtable* environment, ClassSymtablePool* pool){
    bool retFirst = first->process(environment, pool);
    bool retSecond = second->process(environment, pool);

    if(!retFirst || !retSecond)
        return false;

    Type* newType = returnTypeBinOp(first->getType(), second->getType(), op);

    if(newType == nullptr){
        typeErrorBinOp(first->getType()->toString(), second->getType()->toString(), binOpSymbol(op));
        return false;
    }

    type = newType;
    return true;
}

Expression* BinOperator::getFirst() {
    return first;
}

Expression* BinOperator::getSecond() {
    return second;
}

BinOperator BinOperator::getOp() {
    return op;
}

UnExpression::UnExpression(Expression* first, UnOperator op){
    this->first = first;
    this->op = op;
}

string UnExpression::toString(){
    return unOpSymbol(op) + first->toString();
}

bool UnExpression::process(Symtable* environment, ClassSymtablePool* pool){
    bool retFirst = first->process(environment, pool);

    if(!retFirst)
        return false;

    Type* newType = returnTypeUnOp(first->getType(), op);

    if(newType == nullptr){
        typeErrorUnOp(first->getType()->toString(), unOpSymbol(op));
        return false;
    }

    type = newType;
    return true;
}

Expression* UnOperator::getFirst() {
    return first;
}

BinOperator UnOperator::getOp() {
    return op;
}

AtomExpression::AtomExpression(Type* type){
    this->type = type;
}

AtomExpression::AtomExpression(AtomExpValue val, Type* type){
    this->type = type;
    this->val = val;
}

string AtomExpression::toString(){
    if(this->type != nullptr) {
        if(this->type->kind == TypeNull)
            return "null";
        if(this->type->kind == TypeInt)
            return to_string(this->val.intval);;
        if(this->type->kind == TypeBoolean)
            return this->val.boolval ? "true" : "false";
        if(this->type->kind == TypeClass and this->type->getClassName() == "String")
            return "\"" + string(this->val.strval) + "\"";
    }
    return "ERROR: invalid type for an atomic expression";
}

bool AtomExpression::process(Symtable* environment, ClassSymtablePool* pool){
    return true;
}

string ArrayDeclExpression::toString(){
    return "new " + type->toString();
}

bool ArrayDeclExpression::process(Symtable* environment, ClassSymtablePool* pool){
    switch(type->kind){
        case TypeNull:
            arrayOfInvalidTypeError(type->toString());
            return false;
        case TypeMethod:
            arrayOfInvalidTypeError(type->toString());
            return false;
        case TypeVoid:
            arrayOfInvalidTypeError(type->toString());
            return false;
        case TypeClass:
            if(pool->get(type->getClassName()) == nullptr){
                classNotDefinedError(type->getClassName());
                return false;
            }
    }

    return true;
}

NewObjExpression::NewObjExpression(string id){
    this->id = id;
}

string NewObjExpression::toString(){
    return  "new " + id + "( )";
}

bool NewObjExpression::process(Symtable* environment, ClassSymtablePool* pool){
    if(pool->get(id) == nullptr){
        classNotDefinedError(id);
        return false;
    }

    type = MkTypeClass(id);
    return true;
}

IdExpression::IdExpression(string id){
    this->id = id;
}

string IdExpression::toString(){
    return getId();
}

string IdExpression::getId(){
    return id;
}

bool IdExpression::process(Symtable* environment, ClassSymtablePool* pool){
    if(predefinedId(id) || pool->get(id) != nullptr){
        classAsExpressionError(id);
        return false;
    }

    TableContent tc = environment->lookup(id);

    if(tc.tag != TCTYPE){
        variableNotDefinedError(id);
        return false;
    }

    type = tc.type;
    return true;
}

bool IdExpression::isLvalue(){
    return true;
}

bool FieldAccessExpression::isLvalue(){
    return true;
}

FieldAccessExpression::FieldAccessExpression(string id){
    this->id = id;
}

string FieldAccessExpression::toString(){
    return "this." + id;
}

bool FieldAccessExpression::process(Symtable* environment, ClassSymtablePool* pool){
    TableContent tc;
    string currentClass = environment->getClassName();

    while(currentClass != ""){
        tc = pool->get(currentClass)->get(id);

        // The class doesn't contain the field
        if(tc.tag == TCNOCONTENT || (tc.tag == TCTYPE && tc.type->kind == TypeMethod))

            // Looks in its parent
            currentClass = g_classParentMap[currentClass];

        else{
            type = tc.type;
            return true;
        }
    }

    fieldNotFoundError(id, environment->getClassName());
    return false;
}

string ThisExpression::toString(){
    return "this";
}

bool ThisExpression::process(Symtable* environment, ClassSymtablePool* pool){
    type = MkTypeClass(environment->getClassName());
    return true;
}

ParenExpression::ParenExpression(Expression* fst){
    this->first = fst;
}

string ParenExpression::toString(){
    return "(" + first->toString() + ")";
}

bool ParenExpression::isLvalue(){
    return first->isLvalue();
}

bool ParenExpression::process(Symtable* environment, ClassSymtablePool* pool){
    bool retFirst = first->process(environment, pool);

    if(!retFirst)
        return false;

    type = first->getType();
    return true;
}

Expression* ParenExpression::getFirst() {
    return first;
}

LitArrayExpression::LitArrayExpression(deque<Expression*>* exprs){
    this->expressions = exprs;
}

string LitArrayExpression::toString(){
    string ans = "{";
    int i = 0;
    for(auto e : *expressions) 
        if(++i < expression->size())
            ans += e->toString() + ",";
        else
            ans += e->toString();
    return ans + "}";
}

bool LitArrayExpression::process(Symtable* environment, ClassSymtablePool* pool){
    Type** types = new Type*[expressions->size()];
    bool retExp;

    int i = 0;
    for(auto exp : *expressions){
        retExp = exp->process(environment, pool);

        if(!retExp){
            delete[] types;
            return false;
        }

        types[i++] = exp->getType();
    }

    Type* resType = resultingType(types, expressions->size());
    delete[] types;

    if(resType == nullptr)
        return false;

    type = resType;
    return true;
}

ArrayAccessExpression::ArrayAccessExpression(ObjExpression* left, deque<Expression*>* dimensions){
    this->left = left;
    this->dimensions = dimensions;
}

string ArrayAccessExpression::toString(){
    string ans = left->toString();
    for(auto d : *dimensions) ans += "[" + d->toString() + "]";
    return ans;
}

bool ArrayAccessExpression::process(Symtable* environment, ClassSymtablePool* pool){
    bool retLeft = left->process(environment, pool);

    if(!retLeft)
        return false;

    Type* currentType = left->getType();

    for(auto dim : *dimensions){
        if(currentType->kind != TypeArray){
            nonArrayExpressionError(left->toString());
            return false;
        }

        bool ret = dim->process(environment, pool);

        if(!ret)
            return false;

        if(dim->getType()->kind != TypeInt){
            nonIntArrayDimensionError(dim->toString());
            return false;
        }

        currentType = currentType->getBaseType();
    }

    type = currentType;
    return true;
}

bool ArrayAccessExpression::isLvalue(){
    return true;
}

NewArrayExpression::NewArrayExpression(ArrayDeclExpression* decl, deque<Expression*>* dimensions){
    Type* newType = decl->getType();

    for(auto dim : *dimensions)
        newType = MkTypeArray(newType);

    this->type = newType;
    this->dimensions = dimensions;
}

bool NewArrayExpression::process(Symtable* environment, ClassSymtablePool* pool){
    for(auto dim : *dimensions)
        if(!dim->process(environment, pool))
            return false;

    if(type->kind == TypeMethod || type->kind == TypeNull || type->kind == TypeVoid){
        arrayOfInvalidTypeError(type->toString());
        return false;
    }

    if(type->kind == TypeClass){
        if(predefinedId(type->getClassName()))
            return true;

        if(pool->get(type->getClassName()) != nullptr)
            return true;

        classNotDefinedError(type->getClassName());
        return false;
    }

    return true;
}

string NewArrayExpression::toString(){
    string ans = this->type->toString();

    for(auto dim : *dimensions) ans += "[" + dim->toString() +"]";

    return ans;
}

#include "ast.hpp"