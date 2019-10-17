#ifndef AST_HPP
#define AST_HPP

#include <string>
#include <vector>
#include "expression.hpp"
#include "statement.hpp"
#include "type.hpp"

using std::string;
using std::vector;

class Program{
    private:
        vector<ClassDeclaration*> declarations;
};

class ClassDeclaration{
    private:
        string name;
        string parent;
        vector<Method*>* methods;
        vector<Field*>* fields;        
};

class Method{
    private: 
        Type* returnType;
        vector<Parameter*>* parameters;
        Block* statements;
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
};

#endif