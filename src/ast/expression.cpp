#include <iostream>
#include <string>
#include "error.hpp"
#include "expression.hpp"

using std::cout;
using std::string;
using std::to_string;

bool predefinedId(string id){
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

AtomExpression::AtomExpression(Type* type){
    this->type = type;
}

AtomExpression::AtomExpression(AtomExpValue val, Type* type){
    this->type = type;
    this->val = val;
}

string AtomExpression::toString(){
    if(this->type == nullptr){
        return "???";
    } else switch(this->type->kind){
        case TypeNull:
            return "null";
        case TypeInt:
            return to_string(this->val.intval);
        case TypeVoid:
            return "ERROR: exp of type void";
        case TypeBoolean:
            return to_string(this->val.boolval);
        case TypeClass:
            return string(this->val.strval);
        default:
            return "ERROR: invalid type for an atomic expression";
    }
}

bool AtomExpression::process(Symtable* environment, ClassSymtablePool* pool){
    return true;
}

ArrayDeclExpression::ArrayDeclExpression(Type* type){
    this->type = type;
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
    return id;
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

string FieldAccessExpression::toString(){
    return "this." + id;
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

string ThisExpression::toString(){
    return "this";
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

string MethodCallExpression::toString(){
    string ans = left->toString() + "." + method + "(";
    if(arguments != nullptr) for(auto e : *arguments) ans += e->toString() + ",";
    return ans + ")";
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
        if(expectedArgs != 0){
            diffNumberOfArgsMethodError(method, 0, expectedArgs);
            return false;
        }
        
        type = (*(tc.type->getMethodHeader()))[0];
        return true;
    }

    if(arguments->size() != expectedArgs){
        diffNumberOfArgsMethodError(method, arguments->size(), expectedArgs);
        return false;
    }

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

string ParenExpression::toString(){
    return "(" + first->toString() + ")";
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

string LitArrayExpression::toString(){
    string ans = "{";
    for(auto e : *expressions) ans += e->toString() + ",";
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

NewArrayExpression::NewArrayExpression(ArrayDeclExpression* decl, deque<Expression*>* dimensions){
    this->type = decl->getType();
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
}

string NewArrayExpression::toString(){
    string ans = this->type->toString();

    for(auto dim : *dimensions) ans += "[" + dim->toString() +"]";

    return ans;
}

#include "ast.hpp"