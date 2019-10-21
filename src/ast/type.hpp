#ifndef TYPE_HPP
#define TYPE_HPP

#include <string>
#include <vector>
#include "operator.hpp"

using std::string;
using std::vector;

enum BinOperator;
enum UnOperator;

typedef enum TypeKind{
    TypeNull, 
    TypeInt, 
    TypeVoid, 
    TypeBoolean,
    TypeArray, 
    TypeMethod, 
    TypeClass
} TypeKind;

class Type{
    public:
        TypeKind kind;

        Type(TypeKind kind);
        virtual string toString() = 0;
        virtual Type* copy(Type* other) = 0;
        virtual string getClassName(){return "";}
        virtual vector<Type*>* getMethodHeader(){return nullptr;};
        virtual Type* getBaseType(){return nullptr;}
};

class ClassType : public Type{
    public:
        string className;
        ClassType(string className);
        string toString();
        virtual Type* copy(Type* other);
        string getClassName();
};

class BasicType : public Type{
    public:
        BasicType(TypeKind tk);
        string toString();
        virtual Type* copy(Type* other);
};

class ArrayType : public Type{
    public:
        Type* baseType;

        ArrayType(Type* baseType);
        string toString();
        virtual Type* copy(Type* other);
        Type* getBaseType();
};

class MethodType : public Type{
    public: 
        vector<Type*>* methodHeader;
        MethodType();
        MethodType(vector<Type*>* methodHeader);
        string toString();
        virtual Type* copy(Type* other);
        vector<Type*>* getMethodHeader();
};

ClassType* ToClassType(Type* type);

ArrayType* ToArrayType(Type* type);

BasicType* MkTypeNull();

BasicType* MkTypeInt();

BasicType* MkTypeVoid();

BasicType* MkTypeBoolean();

ClassType* MkTypeClass(string className);

ArrayType* MkTypeArray(Type* baseType);

MethodType* MkTypeMethod(vector<Type*>* methodHeader);

void printType(Type* type);

Type* returnTypeBinOp(Type* t1, Type* t2, BinOperator op);

Type* returnTypeUnOp(Type* t1, UnOperator op);

bool areCompatibleTypes(Type* expected, Type* actual);

Type* resultingType(Type** types, int n);

#endif  