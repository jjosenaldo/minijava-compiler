#include "types.h"
#include <stdio.h>
#include <stdlib.h>

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

Type* MkTypeClass(char* className){
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

Type* MkTypeFunction(TypeNode* typeNode){
    Type* type = (Type*) malloc(sizeof(Type));
    type->kind = TypeFunction;
    type->content.functionHeader = typeNode;
    return type;
}

TypeNode* MkTypeNode(Type* type){
    TypeNode* node = (TypeNode*) malloc(sizeof(TypeNode));
    node->type = type;
    node->next = NULL;
    return node;
}

TypeList* MkTypeList(){
    TypeList* list = (TypeList*) malloc(sizeof(TypeList));
    list->head = NULL;
    return list;
}

void addTypeToList(TypeList* list, Type* type){
    TypeNode* newNode = MkTypeNode(type);

    if(list->head == NULL)
        list->head = newNode;
    else {
        TypeNode* curr = list->head;
        while(curr->next !=  NULL)
            curr = curr->next;
        curr->next = newNode;
    }
}

void printTypeList(TypeList* list) {
    TypeNode* curr = list->head;
    while(curr != NULL) {
        printType(curr->type);
        printf("\n");
        curr = curr->next;
    }
}

void printType(Type* type){
    switch(type->kind){
        case TypeInt:
            printf("TypeInt");
            break;
        case TypeVoid:
            printf("TypeVoid");
            break;
        case TypeNull:
            printf("TypeNull");
            break;
        default:
            printf("ERROR\n");
    }
}