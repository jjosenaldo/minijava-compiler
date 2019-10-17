#ifndef TYPE_HPP
#define TYPE_HPP

#include <string>
#include <vector>

using std::string;
using std::vector;

typedef enum TypeKind{
    TypeNull, 
    TypeInt, 
    TypeVoid, 
    TypeBoolean,
    TypeArray, 
    TypeFunction, 
    TypeClass
} TypeKind;

struct Type{
    TypeKind kind;
    union {
        string className;
        struct Type* baseType;
        vector<Type*>* functionHeader;
    } content;
};

Type* MkTypeNull();

Type* MkTypeInt();

Type* MkTypeVoid();

Type* MkTypeBoolean();

Type* MkTypeClass(string className);

Type* MkTypeArray(Type* baseType);

Type* MkTypeFunction(vector<Type*>* functionHeader);

void printType(Type* type);

#endif  