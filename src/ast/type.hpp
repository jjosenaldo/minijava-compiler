#ifndef TYPE_HPP
#define TYPE_HPP

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "operator.hpp"

using std::string;
using std::unordered_map;
using std::unordered_set;
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
        Type(){}
        virtual string toString() = 0;
        virtual Type* copy(Type* other) = 0;
        virtual string getClassName(){return "";}
        virtual string getActualClassName(){return "";}
        virtual void setActualClassName(string actualClassName) {}
        virtual vector<Type*>* getMethodHeader(){return nullptr;};
        virtual Type* getBaseType(){return nullptr;}
};

class ClassType : public Type{
    private:
        string className;
    
    public:
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
        MethodType(Type* other);
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

/**
 * @brief Returns the type of the result of a binary operation
 * 
 * @param t1        The first operand
 * @param t2        The second operand 
 * @param op        The binary operator
 * @return Type*    The type of the result, or nullptr if the given types can't be applied to the given operator
 */
Type* returnTypeBinOp(Type* t1, Type* t2, BinOperator op);

/**
 * @brief Returns the type of the result of an unary operation
 * 
 * @param t1        The first operand
 * @param op        The unary operator
 * @return Type*    The type of the result, or nullptr if the given type can't be applied to the given operator
 */
Type* returnTypeUnOp(Type* t1, UnOperator op);

bool areCompatibleTypes(Type* expected, Type* actual);

/**
 * @brief           Evaluates the type of an array literal.
 *
 *                  Evaluates the type of an array literal based on the types of its elements. Returns nullptr if there is none (for example: {"a",1})                    
 * 
 * @param types     Array of types
 * @param n         Number of types in the array (it should be >=1 )
 * @return Type*    The type of the array
 */
Type* resultingType(Type** types, int n);

bool typeIsString(Type* type);

class DefaultSymbolHandler{
    private:
        unordered_map<string, bool> defaultClasses;
        unordered_map<string, unordered_map<string, MethodType*>> defaultStaticMethodsOfClasses;
        unordered_map<string, unordered_map<string, MethodType*>> defaultNonstaticMethodsOfClasses;
        unordered_map<string, MethodType*> defaultNonstaticMethodsOfArrays;
        void initDefaultClasses();
        void initDefaultMethodsOfClasses();
        void initDefaultMethodsOfArrays();
        void addDefaultNonstaticMethodOfClass(string className, string method, vector<Type*>* args);
        void addDefaultStaticMethodOfClass(string className, string method, vector<Type*>* args);
    
    public:
        DefaultSymbolHandler();
        MethodType* getDefaultStaticMethodHeader(Type* type, string method);
        MethodType* getDefaultStaticMethodHeader(string type, string method);
        MethodType* getDefaultNonstaticMethodHeader(Type* type, string method);
        MethodType* getDefaultNonstaticMethodHeader(string type, string method);
        bool isDefaultClass(string className);
        bool isInstantiatableDefaultType(string className);
};

#endif  