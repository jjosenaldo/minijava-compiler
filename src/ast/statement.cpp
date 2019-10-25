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

bool Assignment::process(Symtable* parent, ClassSymtablePool* pool, Program* program){

    if(!lvalue->process(parent, pool, program))
        return false;
    
    if(!lvalue->isLvalue()){
        notAnLvalueError(lvalue->toString());
        return false;
    }

    if(!rvalue->process(parent, pool, program))
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

bool MethodCallExpression::process(Symtable* environment, ClassSymtablePool* pool, Program* program){
    bool leftResult = left->process(environment, pool, program);

    // The callee expression is not well-formed
    if(!leftResult)
        return false;

    // The callee expression is not an object
    if(!left->isObject()){
        methodCallOnNonobjectError(left->toString());
        return false;
    }

    ClassSymtable* classTable = pool->get(left->getType()->getClassName());
    TableContent tc = classTable->get(method);

    // Search for the method (including the ancestor classes)
    string currentClass = left->getType()->getClassName();
    bool methodFound = false;

    while(currentClass != ""){
        tc = pool->get(currentClass)->get(method);

        // The class doesn't contain the field
        if(tc.tag == TCNOCONTENT || (tc.tag == TCTYPE && tc.type->kind != TypeMethod))

            // Looks in its parent
            currentClass = program->getClassDecl(currentClass)->getParent();
        
        else{
            methodFound = true;
            break;
        }
    }

    // The method doesnt exist
    if(!methodFound){
        methodNotFoundError(method, left->getType()->getClassName());
        return false;
    }

    type = tc.type;

    /*

    This code checks for subclasses, i.e., polymorphism. 

    // Up to this point, the method exists. We have to check if it exists
    // in the child class, so that the child class method is used
    string actualClassName = left->getType()->getActualClassName();

    // The ID was indeed created by a statement like "Animal a = new Cat()"
    if(actualClassName != left->getType()->getClassName()){
        auto methodTypeOnDerivedClass = pool->get(actualClassName)->get(method);

        if(methodTypeOnDerivedClass.tag == TCTYPE)
            type = methodTypeOnDerivedClass.type; 
    }
    */

    int expectedArgs = type->getMethodHeader()->size() - 1;
    
    if(arguments == nullptr) {
        if(expectedArgs != 0){
            diffNumberOfArgsMethodError(method, 0, expectedArgs);
            return false;
        }
        
        type = (*(type->getMethodHeader()))[0];
        return true;
    }

    if(arguments->size() != expectedArgs){
        diffNumberOfArgsMethodError(method, arguments->size(), expectedArgs);
        return false;
    }

    for(int i = 0; i < expectedArgs; ++i){
        if(!  arguments->at(i)->process(environment, pool, program)  )
            return false;

        if(!areCompatibleTypes(tc.type->getMethodHeader()->at(i+1), arguments->at(i)->getType()  )    ){ // +1 because the first element is the return type
            incompatibleTypesMethodCall(method, i+1, tc.type->getMethodHeader()->at(i+1)->toString(), arguments->at(i)->getType()->toString());
            return false;
        }
    }

    type = tc.type->getMethodHeader()->at(0);
    return true;
}

void MethodCallExpression::print(){
    left->print();
    cout << "." << method << "(";
    
    if(arguments != nullptr){
        for(auto arg : *arguments) {arg->print();cout << ",";}
    }

    cout << ");";
}

void Skip::print(){
    cout << ";";
}