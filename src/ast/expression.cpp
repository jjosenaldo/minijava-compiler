#include <iostream>
#include <string>
#include "ast.hpp"
#include "code-visitor.hpp"
#include "error.hpp"
#include "expression.hpp"
#include "global.hpp"
#include "static-visitor.hpp"

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

bool Expression::isLvalue(){
    return false;
}

bool Expression::accept(StaticVisitor& visitor){
    return false;
}

void Expression::setType(Type* other){
    this->type = other;
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

bool BinExpression::accept(StaticVisitor& visitor){
    return visitor.visit(this);
}

string BinExpression::accept(CodeVisitor& visitor){
    return visitor.visit(this);
}

Expression* BinExpression::getFirst() {
    return first;
}

Expression* BinExpression::getSecond() {
    return second;
}

BinOperator BinExpression::getOp() {
    return op;
}

UnExpression::UnExpression(Expression* first, UnOperator op){
    this->first = first;
    this->op = op;
}

string UnExpression::toString(){
    return unOpSymbol(op) + first->toString();
}

string UnExpression::accept(CodeVisitor& visitor){
    return visitor.visit(this);
}

bool UnExpression::accept(StaticVisitor& visitor){
    return visitor.visit(this);
}

Expression* UnExpression::getFirst() {
    return first;
}

UnOperator UnExpression::getOp() {
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

bool AtomExpression::accept(StaticVisitor& visitor){
    return visitor.visit(this);
}

string AtomExpression::accept(CodeVisitor& visitor){
    return visitor.visit(this);
}

string ArrayDeclExpression::toString(){
    return "new " + type->toString();
}

bool ArrayDeclExpression::accept(StaticVisitor& visitor){
    return visitor.visit(this);
}

NewObjExpression::NewObjExpression(string id){
    this->id = id;
}

string NewObjExpression::toString(){
    return  "new " + id + "( )";
}

bool NewObjExpression::accept(StaticVisitor& visitor){
    return visitor.visit(this);
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

bool IdExpression::accept(StaticVisitor& visitor){
    return visitor.visit(this);
}

string IdExpression::accept(CodeVisitor& visitor){
    return visitor.visit(this);
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

bool FieldAccessExpression::accept(StaticVisitor& visitor){
    return visitor.visit(this);
}

string ThisExpression::toString(){
    return "this";
}

bool ThisExpression::accept(StaticVisitor& visitor){
    return visitor.visit(this);
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

bool ParenExpression::accept(StaticVisitor& visitor){
    return visitor.visit(this);
}

string ParenExpression::accept(CodeVisitor& visitor){
    return visitor.visit(this);
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
        if(++i < expressions->size())
            ans += e->toString() + ",";
        else
            ans += e->toString();
    return ans + "}";
}

bool LitArrayExpression::accept(StaticVisitor& visitor){
    return visitor.visit(this);
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

bool ArrayAccessExpression::accept(StaticVisitor& visitor){
    return visitor.visit(this);
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

bool NewArrayExpression::accept(StaticVisitor& visitor){
    return visitor.visit(this);
}

string NewArrayExpression::toString(){
    string ans = this->type->toString();

    for(auto dim : *dimensions) ans += "[" + dim->toString() +"]";

    return ans;
}

#include "ast.hpp"