#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <deque>
#include <iostream>
#include <unordered_map>
#include <string>
#include "operator.hpp"
#include "symtable.hpp"

using std::cout;
using std::deque;
using std::unordered_map;
using std::string;

union AtomExpValue{
    bool boolval;   
    int intval;
    char* strval;
};

bool predefinedId(string id);

#include "type.hpp"

class Expression{
    protected:
        Type* type;

    public:
        virtual ~Expression() {}
        Type* getType();
        void print(){cout << toString();}

        /**
         * @brief Checks if the expression is correct, and sets its type.
         *        
         *        Checks if the expression doesn't contain errors such as type errors and references to undefined ids. If it's
         *        correct, then its type is set.
         * 
         * @param environment   The current scope
         * @param pool          The pool of class tables (needed for looking for class names)
         * @return true         The expression is correct
         * @return false        The expression is not correct
         */
        virtual bool process(Symtable* environment, ClassSymtablePool* pool) = 0;
        virtual string toString() = 0;
};

// Example: 1+1
class BinExpression : public Expression{
    private:
        Expression* first;
        Expression* second;
        BinOperator op;
    
    public:
        BinExpression(Expression* first, Expression* second, BinOperator op);
        bool process(Symtable* environment, ClassSymtablePool* pool);
        string toString();
};

// Example: !a
class UnExpression : public Expression{
    private:
        Expression* first;
        UnOperator op;

    public:
        UnExpression(Expression* first, UnOperator op);
        bool process(Symtable* environment, ClassSymtablePool* pool);
        string toString();
};

// Example: false
//,         52
//          "oi"
//          null
// The type is set when the parse tree is built
class AtomExpression : public Expression{
    private:
        AtomExpValue val;

    public:
        AtomExpression(Type* type);
        AtomExpression(AtomExpValue val, Type* type);
        AtomExpValue getVal();
        bool process(Symtable* environment, ClassSymtablePool* pool);
        string toString();
};

class ObjExpression : public Expression{};

// Example: new int
// The type is set when the parse tree is built
class ArrayDeclExpression : public ObjExpression{
    public:
        ArrayDeclExpression(Type* type);
        bool process(Symtable* environment, ClassSymtablePool* pool);
        string toString();
};

// Example: new Cat()
class NewObjExpression : public ObjExpression{
    private:
        string id;
    
    public:
        NewObjExpression(string id);
        bool process(Symtable* environment, ClassSymtablePool* pool);
        string toString();
};

// Its type is not known when the tree is being built
class IdExpression : public ObjExpression{
    private:
        string id;
    
    public:
        IdExpression(string id);
        bool process(Symtable* environment, ClassSymtablePool* pool);
        string toString();
};

// Its type is not known when the tree is being built
class FieldAccessExpression : public ObjExpression{
    private:
        string id;
    
    public:
        FieldAccessExpression(string id);
        bool process(Symtable* environment, ClassSymtablePool* pool);
        string toString();
};

// Its type is not known when the tree is being built
class ThisExpression : public ObjExpression{
    public:
        bool process(Symtable* environment, ClassSymtablePool* pool);
        string toString();
};

// Its type is not known when the tree is being built
class MethodCallExpression : public ObjExpression{
    private:
        Expression* left;
        string method;
        deque<Expression*>* arguments;

    public:
        MethodCallExpression(Expression* left, string method, deque<Expression*>* args);
        bool process(Symtable* environment, ClassSymtablePool* pool);
        string toString();
};

// Example: (a)
class ParenExpression : public ObjExpression{
    private:
        Expression* first;

    public:
        ParenExpression(Expression* first);
        bool process(Symtable* environment, ClassSymtablePool* pool);
        string toString();
};

class LitArrayExpression : public ObjExpression{
    private:
        deque<Expression*>* expressions;
    public:
        LitArrayExpression(deque<Expression*>* exprs);
        bool process(Symtable* environment, ClassSymtablePool* pool);
        string toString();
};

class ArrayAccessExpression : public Expression{
    private:
        ObjExpression* left;
        deque<Expression*>* dimensions;

    public:
        ArrayAccessExpression(ObjExpression* left, deque<Expression*>* dimensions);
        bool process(Symtable* environment, ClassSymtablePool* pool);
        string toString();
};

class NewArrayExpression : public Expression{
    private:
        deque<Expression*>* dimensions;
    
    public:
        NewArrayExpression(ArrayDeclExpression* decl, deque<Expression*>* dimensions);
        bool process(Symtable* environment, ClassSymtablePool* pool);
        string toString();
};

#endif