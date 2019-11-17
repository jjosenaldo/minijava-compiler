#include <iostream>
#include "error.hpp"
#include "global.hpp"
#include "statement.hpp"
#include "static-visitor.hpp"
#include "code-visitor.hpp"

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

bool VarDec::accept(StaticVisitor& visitor){
    return visitor.visit(this);
}

string VarDec::accept(CodeVisitor &visitor) {
    return visitor.visit(this);
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

bool Block::accept(StaticVisitor& visitor){
    return visitor.visit(this);
}

string Block::accept(CodeVisitor &visitor) {
    return visitor.visit(this);
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

bool ElselessIf::accept(StaticVisitor& visitor){
    return visitor.visit(this);
}

string ElselessIf::accept(CodeVisitor &visitor) {
    return visitor.visit(this);
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

bool IfElse::accept(StaticVisitor& visitor){
    return visitor.visit(this);
}

string IfElse::accept(CodeVisitor &visitor) {
    return visitor.visit(this);
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

bool While::accept(StaticVisitor& visitor){
    return visitor.visit(this);
}

string While::accept(CodeVisitor &visitor) {
    visitor.visit(this);
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

bool Assignment::accept(StaticVisitor& visitor){
    return visitor.visit(this);
}

string Assignment::accept(CodeVisitor &visitor) {
    return visitor.visit(this);
}

void Continue::print(){
    cout << "continue;";
}

bool Continue::accept(StaticVisitor& visitor){
    return visitor.visit(this);
}

string Continue::accept(CodeVisitor &visitor) {
    return visitor.visit(this);
}

void Break::print(){
    cout << "break;";
}

bool Break::accept(StaticVisitor& visitor){
    return visitor.visit(this);
}

string Break::accept(CodeVisitor &visitor) {
    return visitor.visit(this);
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

bool Return::accept(StaticVisitor& visitor){
    return visitor.visit(this);
}

string Return::accept(CodeVisitor &visitor) {
    return visitor.visit(this);
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

bool MethodCallExpression::accept(StaticVisitor& visitor){
    return visitor.visit(this);
}

string MethodCallExpression::accept(CodeVisitor &visitor) {
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

string StaticMethodCallExpression::accept(CodeVisitor &visitor) {
    return visitor.visit(this);
}

string StaticMethodCallExpression::toString(){
    // TODO
    return "";
}

void StaticMethodCallExpression::print() {
    // TODO
}

void Skip::print(){
    cout << ";";
}

bool Skip::accept(StaticVisitor& visitor){
    return visitor.visit(this);
}

string Skip::accept(CodeVisitor &visitor) {
    return visitor.visit(this);
}