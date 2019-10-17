#ifndef TYPE_HPP
#define TYPE_HPP

typedef enum TypeKind{
    TypeNull, 
    TypeInt, 
    TypeVoid, 
    TypeBoolean,
    TypeArray, 
    TypeFunction, 
    TypeClass
} TypeKind;

typedef struct Type{
    TypeKind kind;
    union {
        char* className;
        struct Type* baseType;
        struct TypeNode* functionHeader;
    } content;
} Type;

typedef struct TypeNode{
    Type* type;
    struct TypeNode* next;
} TypeNode;


typedef struct TypeList{
    TypeNode* head;
} TypeList;

Type* MkTypeNull();

Type* MkTypeInt();

Type* MkTypeVoid();

Type* MkTypeBoolean();

Type* MkTypeClass(char* className);

Type* MkTypeArray(Type* baseType);

Type* MkTypeFunction(TypeNode* TypeNode);

TypeNode* MkTypeNode(Type* type);

TypeList* MkTypeList();

void addTypeToList(TypeList* list, Type* next);

void printTypeList(TypeList* list);

void printType(Type* type);

#endif  