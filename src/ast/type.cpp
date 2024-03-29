#include <stdlib.h>
#include <stdio.h>
#include <stdexcept>
#include <iostream>
#include "type.hpp"
#include "symtable.hpp"

using std::cout;
using std::out_of_range;

Type::Type(TypeKind kind){
    this->kind = kind;
}

ClassType::ClassType(string className) : Type(TypeClass) {
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

MethodType::MethodType(Type* other){
    MethodType* otherMT = dynamic_cast<MethodType*>(other);
    methodHeader = new vector<Type*>;
    
    for(auto t : *otherMT->methodHeader)
        methodHeader->push_back(  t->copy(t)  );
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

// TODO: Operation between class and subclasses
Type* returnTypeBinOp(Type* t1, Type* t2, BinOperator op){
    // TypeInt: 
    //     - * / %
    // TypeBoolean:
    //     && ||
    // TypeInt and TypeClass[String]:
    //     + < <= >= >
    // All expect TypeVoid and TypeMethod:
    //     == !=

    if(op == OP_BIN_MINUS or
       op == OP_TIMES or
       op == OP_DIV or
       op == OP_MOD)
    {       
        if(t1->kind == TypeInt and t2->kind == TypeInt)
            return MkTypeInt();
    }
    else if(op == OP_OR or
            op == OP_AND)
    {
        if(t1->kind == TypeBoolean and t2->kind == TypeBoolean)
            return MkTypeBoolean();
    }
    if(op == OP_PLUS) {
        if(t1->kind == TypeInt and t2->kind == TypeInt)
            return MkTypeInt();
        else if(typeIsString(t1) and typeIsString(t2))
            return MkTypeClass("String");
    }
    else if(op == OP_LESS or
            op == OP_LESS_EQ or
            op == OP_GREAT_EQ or
            op == OP_GREAT)
    {
        if((t1->kind == TypeInt and t2->kind == TypeInt) or
           (typeIsString(t1) and typeIsString(t2))) 
            return MkTypeBoolean();
    }
    else if(op == OP_IS_EQ or
            op == OP_DIFF)
    {
        if(t1->kind == TypeVoid or
           t2->kind == TypeVoid or
           t1->kind == TypeMethod or
           t2->kind == TypeMethod)              // Void and Method types can't be compared
            return nullptr;
        else if(areCompatibleTypes(t1,t2) or areCompatibleTypes(t2,t1))
            return MkTypeBoolean();
    }
    return nullptr;
}

Type* returnTypeUnOp(Type* t1, UnOperator op){
    if(op == OP_NOT and t1->kind == TypeBoolean)
        return MkTypeBoolean();
    else if(op == OP_UN_MINUS and t1->kind == TypeInt)
        return MkTypeInt();
    return nullptr;
}

bool areCompatibleTypes(Type* expected, Type* actual){
    if(expected->kind == TypeInt)
        return actual->kind == TypeInt;
    if(expected->kind == TypeVoid)
        return actual->kind == TypeVoid;
    if(expected->kind == TypeNull)
        return actual->kind == TypeNull;
    if(expected->kind == TypeBoolean)
        return actual->kind == TypeBoolean;
    if(expected->kind == TypeClass)
        return actual->kind == TypeNull or (actual->kind == TypeClass and isSubclassOf(actual->getClassName(), expected->getClassName()));
    if(expected->kind == TypeArray)
        return actual->kind == TypeNull or (actual->kind == TypeArray and areCompatibleTypes(expected->getBaseType(), actual->getBaseType())); 
    // It returns false for method headers
    return false;
}

Type* resultingType(Type** types, int n){
    if(n <= 0)
        return nullptr;

    Type* type = *types;
    if(type->kind == TypeMethod or type->kind == TypeVoid)
            return nullptr;

    for(int i = 1; i < n; i++) {
        Type *t = *(types+i);

        if(t->kind == TypeMethod or t->kind == TypeVoid)
            return nullptr;

        if(areCompatibleTypes(t,type))
            type = t;
        else if(!areCompatibleTypes(type,t))
            return nullptr;
    }
    return MkTypeArray(type);
}

bool typeIsString(Type* type) {
    return type->kind == TypeClass and
           type->getClassName() == "String";
}

DefaultSymbolHandler::DefaultSymbolHandler(){
    initDefaultClasses();
    initDefaultMethodsOfClasses();
    initDefaultMethodsOfArrays();
}

void DefaultSymbolHandler::addDefaultNonstaticMethodOfClass(string className, string method, vector<Type*>* args){
    MethodType* methodType = new MethodType(args);
    auto it = defaultNonstaticMethodsOfClasses.find(className);

    if(it == defaultNonstaticMethodsOfClasses.end()){
        unordered_map<string, MethodType*> newMap;
        newMap.emplace(method, methodType);
        defaultNonstaticMethodsOfClasses.emplace(className, newMap);
    } else{
        it->second.emplace(method, methodType);
    }
}

void DefaultSymbolHandler::addDefaultStaticMethodOfClass(string className, string method, vector<Type*>* args){
    MethodType* methodType = new MethodType(args);
    auto it = defaultStaticMethodsOfClasses.find(className);

    if(it == defaultStaticMethodsOfClasses.end()){
        unordered_map<string, MethodType*> newMap;
        newMap.emplace(method, methodType);
        defaultStaticMethodsOfClasses.emplace(className, newMap);
    } else{
        it->second.emplace(method, methodType);
    }
}

void DefaultSymbolHandler::initDefaultMethodsOfClasses(){
    vector<Type*>* lengthHeaderString = new vector<Type*>;
    lengthHeaderString->push_back(new BasicType(TypeInt));
    addDefaultNonstaticMethodOfClass("String", "length", lengthHeaderString);

    vector<Type*>* substrHeaderString = new vector<Type*>;
    substrHeaderString->push_back(new ClassType("String"));
    substrHeaderString->push_back(new BasicType(TypeInt));
    substrHeaderString->push_back(new BasicType(TypeInt));
    addDefaultNonstaticMethodOfClass("String", "substring", substrHeaderString);

    vector<Type*>* intToStrHeaderString = new vector<Type*>;
    intToStrHeaderString->push_back(new ClassType("String"));
    intToStrHeaderString->push_back(new BasicType(TypeInt));
    addDefaultStaticMethodOfClass("String", "intToString", intToStrHeaderString);

    vector<Type*>* booleanToStrHeaderString = new vector<Type*>;
    booleanToStrHeaderString->push_back(new ClassType("String"));
    booleanToStrHeaderString->push_back(new BasicType(TypeBoolean));
    addDefaultStaticMethodOfClass("String", "booleanToString", booleanToStrHeaderString);
    
    vector<Type*>* printHeaderSystem = new vector<Type*>;
    printHeaderSystem->push_back(new BasicType(TypeVoid));
    printHeaderSystem->push_back(new ClassType("String"));
    addDefaultStaticMethodOfClass("System", "print", printHeaderSystem);
}

void DefaultSymbolHandler::initDefaultMethodsOfArrays(){
    vector<Type*>* lengthTypeHeader = new vector<Type*>;
    lengthTypeHeader->push_back(new BasicType(TypeInt));
    MethodType* lengthType = new MethodType(lengthTypeHeader);
    defaultNonstaticMethodsOfArrays.emplace("length",lengthType);
}

MethodType* DefaultSymbolHandler::getDefaultStaticMethodHeader(string type, string method){
    ClassType* ct = new ClassType(type);
    MethodType* returnType = this->getDefaultStaticMethodHeader(ct, method);
    delete ct;
    return returnType;
}

MethodType* DefaultSymbolHandler::getDefaultNonstaticMethodHeader(string type, string method){
    ClassType* ct = new ClassType(type);
    MethodType* returnType = this->getDefaultNonstaticMethodHeader(ct, method);
    delete ct;
    return returnType;
}

bool DefaultSymbolHandler::isInstantiatableDefaultType(string className){
    return defaultClasses.at(className);
}

MethodType* DefaultSymbolHandler::getDefaultStaticMethodHeader(Type* type, string method){
    if(type->kind == TypeClass){
        try {return defaultStaticMethodsOfClasses.at(type->getClassName()).at(method);}
        catch(out_of_range oor) {return nullptr;}
    } else if(type->kind == TypeArray){
       return nullptr;
    } else return nullptr;
}

MethodType* DefaultSymbolHandler::getDefaultNonstaticMethodHeader(Type* type, string method){
    if(type->kind == TypeClass){
        try {return defaultNonstaticMethodsOfClasses.at(type->getClassName()).at(method);}
        catch(out_of_range oor) {return nullptr;}
    } else if(type->kind == TypeArray){
        try {return defaultNonstaticMethodsOfArrays.at(method);}
        catch(out_of_range oor) {return nullptr;}
    } else return nullptr;
}

void DefaultSymbolHandler::initDefaultClasses(){
    defaultClasses.emplace("String", true);
    defaultClasses.emplace("System", false);
}

bool DefaultSymbolHandler::isDefaultClass(string className){
    return defaultClasses.find(className) != defaultClasses.end();
}