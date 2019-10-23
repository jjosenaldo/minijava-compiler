#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "type.hpp"

using std::cout;

Type::Type(TypeKind kind){
    this->kind = kind;
}

ClassType::ClassType(string className) : Type(TypeClass){
    this->className = className;
}

string ClassType::getClassName(){
    return className;
}

ArrayType::ArrayType(Type* baseType) : Type(TypeArray){
    this->baseType = baseType;
}

Type* ArrayType::getBaseType(){
    return baseType;
}

vector<Type*>* MethodType::getMethodHeader(){
    return methodHeader;
}

MethodType::MethodType(vector<Type*>* methodHeader) : Type(TypeMethod){
    this->methodHeader = methodHeader;
}

MethodType::MethodType() : Type(TypeMethod){
    this->methodHeader = new vector<Type*>;
}

BasicType::BasicType(TypeKind tk) : Type(tk){}

string BasicType::toString(){
    switch(kind){
        case TypeInt:
            return "int";
        case TypeVoid:
            return "void";
        case TypeNull:
            return "null";
        case TypeBoolean:
            return "boolean";
        default:
            return "ERROR";
    }
}

string ClassType::toString(){
    return className;
}

string ArrayType::toString(){
    return baseType->toString() + "[]";
}

string MethodType::toString(){
    string ans = "(";
    auto it = methodHeader->begin();
    ans += (*it++)->toString();

    while(it != methodHeader->end()) 
        ans += ", " + (*it++)->toString();
    ans +=  ")";

    return ans;
}

Type* ClassType::copy(Type* other){
    ClassType* otherCT = dynamic_cast<ClassType*>(other);

    if(!otherCT)
        return nullptr;

    return new ClassType(otherCT->className);
}

Type* BasicType::copy(Type* other){
    BasicType* otherBT = dynamic_cast<BasicType*>(other);

    if(!otherBT)
        return nullptr;

    return new BasicType(otherBT->kind);
} 

Type* MethodType::copy(Type* other){
    MethodType* otherMT = dynamic_cast<MethodType*>(other);
    auto header = new vector<Type*>;
    
    for(auto t : *otherMT->methodHeader)
        header->push_back(  t->copy(t)  );

    return new MethodType(header);
}

Type* ArrayType::copy(Type* other){
    ArrayType* otherAT = dynamic_cast<ArrayType*>(other);
    return new ArrayType( otherAT->baseType->copy(otherAT->baseType) );
}

ClassType* ToClassType(Type* type){
    return dynamic_cast<ClassType*>(type);
}

ArrayType* ToArrayType(Type* type){
    return dynamic_cast<ArrayType*>(type);
}

BasicType* MkTypeNull(){
    return new BasicType(TypeNull);
}

BasicType* MkTypeInt(){
    return new BasicType(TypeInt);
}

BasicType* MkTypeVoid(){
    return new BasicType(TypeVoid);
}

BasicType* MkTypeBoolean(){
    return new BasicType(TypeBoolean);
}

ClassType* MkTypeClass(string className){
    return new ClassType(className);
}

ArrayType* MkTypeArray(Type* baseType){
    return new ArrayType(baseType);
}

MethodType* MkTypeMethod(vector<Type*>* methodHeader){
    return new MethodType(methodHeader);
}



void printType(Type* type){
    cout << type->toString();
}

// TODO: many more cases!
Type* returnTypeBinOp(Type* t1, Type* t2, BinOperator op){
    if(op == OP_MOD || op == OP_BIN_MINUS || op == OP_TIMES || op == OP_DIV || op == OP_GREAT || op == OP_LESS || op == OP_GREAT || op == OP_GREAT_EQ){
        if(t1->kind != TypeInt || t2->kind != TypeInt)
            return nullptr;
        else
            return MkTypeInt();
    }

    return nullptr;
}

Type* returnTypeUnOp(Type* t1, UnOperator op){
    if(op == OP_NOT){
        if(t1->kind != TypeBoolean)
            return nullptr;
        else 
            return MkTypeBoolean();
    } else if(op == OP_UN_MINUS){
        if(t1->kind != TypeInt)
            return nullptr;
        else 
            return MkTypeInt();
    }

    return nullptr;
}

// It returns false for method headers
bool areCompatibleTypes(Type* expected, Type* actual){
    if(expected->kind == TypeInt)
        return actual->kind == TypeInt;

    if(expected->kind == TypeVoid)
        return actual->kind == TypeVoid;
    
    if(expected->kind == TypeNull)
        return actual->kind == TypeNull;
    
    if(expected->kind == TypeBoolean)
        return actual->kind == TypeBoolean;
    
    // TODO: it should check subclassing aswell
    if(expected->kind == TypeClass){
        return actual->kind == TypeClass && expected->getClassName() == actual->getClassName();
    }
    
    if(expected->kind == TypeArray){
        return actual->kind == TypeArray && areCompatibleTypes(expected->getBaseType(), actual->getBaseType()); 
    }
    
    return false;
}

// TODO
Type* resultingType(Type** types, int n){
    return nullptr;
}