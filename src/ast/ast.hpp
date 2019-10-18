#ifndef AST_HPP
#define AST_HPP

#include <deque>
#include <string>
#include <vector>
#include "expression.hpp"
#include "statement.hpp"
#include "type.hpp"

using std::deque;
using std::string;
using std::vector;

class ClassDeclaration;
class Field;
class Parameter;

class Program{
    private:
        deque<ClassDeclaration*> declarations;
    
    public:
        Program(deque<ClassDeclaration*>* decls);

        void addClassDecl(ClassDeclaration* decl);

        void addClassDeclAtFront(ClassDeclaration* decl);

        void print();
};

class Method{
    private: 
        string id;
        Type* returnType;
        deque<Parameter*>* parameters;
        Block* statement;

    public:
        Method(string id, Type* returnType, Block* stmt);
        Method(string id, Type* returnType, deque<Parameter*>* parameters, Block* stmt);
        string getId();
        Type* getReturnType();
        deque<Parameter*>* getParameters();
        Block* getStatement();
        void addParam(Parameter* param);
        void print();
};

class ClassDeclaration{
    private:
        string name;
        string parent;
        vector<Method*> methods;
        vector<Field*> fields;  
    public:
        ClassDeclaration(string name);

        ClassDeclaration(string name, string parent);

        void addMethod(Method* method);

        void addField(Field* field);

        void print();
};

class Field{
    private:
        Type* type;
        string name;
        Expression* initValue;
    
    public:
        Field(Type* type, string name, Expression* initValue);

        void print();
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