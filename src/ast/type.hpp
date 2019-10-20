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
    TypeMethod, 
    TypeClass
} TypeKind;

struct Type{
    TypeKind kind;
    union {
        string className;
        struct Type* baseType;
        vector<Type*>* methodHeader;
    };
    Type() {}
};

Type* MkTypeNull();

Type* MkTypeInt();

Type* MkTypeVoid();

Type* MkTypeBoolean();

Type* MkTypeClass(string className);

Type* MkTypeArray(Type* baseType);

Type* MkTypeMethod(vector<Type*>* methodHeader);

void printType(Type* type);

#endif  