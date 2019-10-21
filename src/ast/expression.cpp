#include <iostream>
#include <string>
#include "error.hpp"
#include "expression.hpp"

using std::cout;
using std::string;

bool predefinedId(char* id){
    return string(id) == "String";
}

Type* Expression::getType(){
    return this->type;
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

UnExpression::UnExpression(Expression* first, UnOperator op){
    this->first = first;
    this->op = op;
}

void UnExpression::print(){
    cout << unOpSymbol(op);
    first->print();
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

bool AtomExpression::process(Symtable* environment, ClassSymtablePool* pool){
    if(type->kind == TypeClass && !predefinedId(val.strval)){
        idNotPredefinedError(string(val.strval));
        return false;
    }
    return true;
}

ArrayDeclExpression::ArrayDeclExpression(Type* type){
    this->type = type;
}

void ArrayDeclExpression::print(){
    cout << "new ";
    printType(type);
}

bool ArrayDeclExpression::process(Symtable* environment, ClassSymtablePool* pool){
    if(type->kind == TypeClass){
        ClassType* ct = ToClassType(type);
        
        if(pool->get(ct->className) == nullptr){
            classNotDefinedError(ct->className);
            return false;
        }
    }

    return true;
}

NewObjExpression::NewObjExpression(string id){
    this->id = id;
}

void NewObjExpression::print(){
    cout << "new " << id << "(" << ")";
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

void IdExpression::print(){
    cout << id;
}

bool IdExpression::process(Symtable* environment, ClassSymtablePool* pool){
    TableContent tc = environment->lookup(id);

    if(tc.tag != TCTYPE){
        variableNotDefinedError(id);
        return false;
    }

    type = tc.type;
    return true;
}

FieldAccessExpression::FieldAccessExpression(string id){
    this->id = id;
}

void FieldAccessExpression::print(){
    cout << "this." << id;
}

bool FieldAccessExpression::process(Symtable* environment, ClassSymtablePool* pool){
    TableContent tc = pool->get(environment->getClassName())->get(id);

    if(tc.tag == TCNOCONTENT || (tc.tag == TCTYPE && tc.type->kind == TypeMethod)){
        fieldNotFoundError(id, environment->getClassName());
        return false;
    }

    type = tc.type;
    return true;
}

void ThisExpression::print(){
    cout << "this";
}

bool ThisExpression::process(Symtable* environment, ClassSymtablePool* pool){
    type = MkTypeClass(environment->getClassName());
    return true;
}

MethodCallExpression::MethodCallExpression(Expression* left, string method, deque<Expression*>* args){
    this->left = left;
    this->method = method;
    this->arguments = args;
}

void MethodCallExpression::print(){
    left->print();
    cout << "." << method << "(";
    if(arguments != nullptr) for(auto e : *arguments){e->print();cout << ",";}
    cout << ")";
}

bool MethodCallExpression::process(Symtable* environment, ClassSymtablePool* pool){
    bool leftResult = left->process(environment, pool);

    if(!leftResult)
        return false;
    

    Type* classType = left->getType();

    if(classType->kind != TypeClass){
        notAnObjectError(left->toString(), method);
        return false;
    }

    ClassSymtable* classTable = pool->get(classType->getClassName());
    TableContent tc = classTable->get(method);

    if(tc.tag == TCNOCONTENT || (tc.tag == TCTYPE && tc.type->kind != TypeMethod)){
        methodNotFoundError(method, classType->getClassName());
        return false;
    } 

    int expectedArgs = tc.type->getMethodHeader()->size() - 1;
    
    if(arguments == nullptr) {
        if(expectedArgs != 0)
            return false;
        
        type = (*(tc.type->getMethodHeader()))[0];
        return true;
    }

    if(arguments->size() != expectedArgs) return false;

    for(int i = 0; i < expectedArgs; ++i){
        if(!  arguments->at(i)->process(environment, pool)  )
            return false;

        if(!areCompatibleTypes(tc.type->getMethodHeader()->at(i+1), arguments->at(i)->getType()  )    ){ // +1 because the first element is the return type
            incompatibleTypesMethodCall(method, i+1, tc.type->getMethodHeader()->at(i+1)->toString(), arguments->at(i)->getType()->toString());
            return false;
        }
    }

    type = tc.type->getMethodHeader()->at(0);
    return true;
}

ParenExpression::ParenExpression(Expression* fst){
    this->first = fst;
}

void ParenExpression::print(){
    cout << "("; first->print(); cout << ")";
}

bool ParenExpression::process(Symtable* environment, ClassSymtablePool* pool){
    bool retFirst = first->process(environment, pool);

    if(!retFirst)
        return false;
    
    type = first->getType();
    return true;
}

LitArrayExpression::LitArrayExpression(deque<Expression*>* exprs){
    this->expressions = exprs;
}

void LitArrayExpression::print(){
    cout << "{";
    for(auto e : *expressions){e->print();cout << ",";}
    cout << "}";
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

void ArrayAccessExpression::print(){
    left->print();
    for(auto d : *dimensions){cout << "[";d->print();cout << "]";}
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

#include "ast.hpp"