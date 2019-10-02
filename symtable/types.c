#include "types.h"
#include "stdio.h"

Type MkTypeNull(){
    Type type;
    type.kind = TypeNull;
    return type;
}

Type MkTypeInt(){
    Type type;
    type.kind = TypeInt;
    return type;
}

Type MkTypeVoid(){
    Type type;
    type.kind = TypeVoid;
    return type;
}

Type MkTypeBoolean(){
    Type type;
    type.kind = TypeBoolean;
    return type;
}

Type MkTypeClass(char* className){
    Type type;
    type.kind = TypeClass;
    type.content.className = className;
    return type;
}

Type MkTypeArray(Type* baseType){
    Type type;
    type.kind = TypeArray;
    type.content.baseType = baseType;
    return type;
}

Type MkTypeFunction(TypeNode* typeNode){
    Type type;
    type.kind = TypeFunction;
    type.content.functionHeader = typeNode;
    return type;
}

TypeNode MkTypeNode(Type* type){
    TypeNode node;
    node.type = type;
    node.next = NULL;
    return node;
}

TypeList MkTypeList(){
    TypeList list;
    list.head = NULL;
    return list;
}

void addTypeToList(TypeList* list, Type* type){
    TypeNode newNode = MkTypeNode(type);

    if(list->head == NULL){
        list->head = &newNode;
    }

    else{
        // TypeNode* curr = list->head;
        // while(curr->next !=  NULL){
        //     curr = curr->next;
        // }
        // curr->next = &newNode;
    }
}

void printTypeList(TypeList* list){
    TypeNode* curr = list->head;
    while(curr != NULL){
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
    }
}