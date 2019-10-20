#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "type.hpp"

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
    type->className = className;
    return type;
}

Type* MkTypeArray(Type* baseType){
    Type* type = (Type*) malloc(sizeof(Type));
    type->kind = TypeArray;
    type->baseType = baseType;
    return type;
}

Type* MkTypeMethod(vector<Type*>* methodHeader){
    Type* type = (Type*) malloc(sizeof(Type));
    type->kind = TypeMethod;
    type->methodHeader = methodHeader;
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
            cout << type->className;
            break;
        case TypeArray:
            printType(type->baseType);
            printf("[]");
            break;
        case TypeMethod:{
            cout << "(";
            auto it = type->methodHeader->begin();
            printType(*it++);

            while(it != type->methodHeader->end()) {
                cout << ", ";
                printType(*it++);
            }
            cout << ")";
            break;}
        default:
            printf("ERROR at printType()\n");
    }
}