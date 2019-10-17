#include "type.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using std::cout;

Type* MkTypeNull(){
    Type* type = (Type*) malloc(sizeof(Type));
    type->kind = TypeNull;
    return type;
}

Type* MkTypeInt(){
    Type* type = (Type*) malloc(sizeof(Type));
    type->kind = TypeInt;
    return type;
}

Type* MkTypeVoid(){
    Type* type = (Type*) malloc(sizeof(Type));
    type->kind = TypeVoid;
    return type;
}

Type* MkTypeBoolean(){
    Type* type = (Type*) malloc(sizeof(Type));
    type->kind = TypeBoolean;
    return type;
}

Type* MkTypeClass(string className){
    Type* type = (Type*) malloc(sizeof(Type));
    type->kind = TypeClass;
    type->content.className = className;
    return type;
}

Type* MkTypeArray(Type* baseType){
    Type* type = (Type*) malloc(sizeof(Type));
    type->kind = TypeArray;
    type->content.baseType = baseType;
    return type;
}

Type* MkTypeMethod(vector<Type*>* methodHeader){
    Type* type = (Type*) malloc(sizeof(Type));
    type->kind = TypeMethod;
    type->content.methodHeader = methodHeader;
    return type;
}

void printType(Type* type){
    switch(type->kind){
        case TypeInt:
            printf("int");
            break;
        case TypeVoid:
            printf("void");
            break;
        case TypeNull:
            printf("null");
            break;
        case TypeBoolean:
            printf("boolean");
            break;
        case TypeClass:
            cout << type->content.className;
            break;
        default:
            printf("ERROR\n");
    }
}