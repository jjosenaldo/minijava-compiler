#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <vector>
#include "expression.hpp"
#include "statement.hpp"
#include "type.hpp"

using std::string;
using std::vector;

class ClassDeclaration;
class Field;
class Parameter;

class Program{
    private:
        vector<ClassDeclaration*> declarations;
    
    public:
        void addClassDecl(ClassDeclaration* decl);

        void print();
};

class Method{
    private: 
        string id;
        Type* returnType;
        vector<Parameter*> parameters;
        Block* statement;

    public:
        Method(string id, Type* returnType, Block* stmt);

        void addParam(Parameter* param);

        void print();
};

class ClassDeclaration{
    private:
        string name;
        string parent;
        vector<Method*> methods;
        vector<Field*>* fields;  
    public:
        ClassDeclaration(string name);

        void addMethod(Method* method);

        void print();
};

class Field{
    private:
        Type* type;
        string name;
        Expression* initValue;
};

class Parameter{
    private:
        Type* type;
        string name;
    
    public:
        Parameter(Type* type, string name);

        void print();
};

#endif