#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <deque>
#include <unordered_map>
#include <string>
#include "type.hpp"

using std::deque;
using std::unordered_map;
using std::string;

enum BinOperator{
    OP_GREAT,
    OP_LESS,   
    OP_GREAT_EQ,
    OP_LESS_EQ,
    OP_IS_EQ,
    OP_DIFF,
    OP_OR,
    OP_AND,
    OP_PLUS,
    OP_BIN_MINUS,
    OP_TIMES,
    OP_DIV,
    OP_MOD
};

enum UnOperator{
    OP_UN_MINUS,
    OP_NOT
};

union AtomExpValue{
    bool boolval;   
    int intval;
    char* strval;
};

string binOpSymbol(BinOperator op);

string unOpSymbol(UnOperator op);

class Expression{
    protected:
        Type* type;

    public:
        virtual ~Expression() {}
        Type* getType();
        virtual void print() = 0;
};

class BinExpression : public Expression{
    private:
        Expression* first;
        Expression* second;
        BinOperator op;
    
    public:
        BinExpression(Expression* first, Expression* second, BinOperator op);

        void print();
};

class UnExpression : public Expression{
    private:
        Expression* first;
        UnOperator op;

    public:
        UnExpression(Expression* first, UnOperator op);

        void print();
};

// boolean, int, ID (String), null
class AtomExpression : public Expression{
    private:
        AtomExpValue val;

    public:
        AtomExpression(Type* type);
        AtomExpression(AtomExpValue val, Type* type);
        AtomExpValue getVal();
        void print();
};

class ObjExpression : public Expression{
    
};

class ArrayDeclExpression : public ObjExpression{
    private:
        Type* type;
    public:
        ArrayDeclExpression(Type* type);
        void print();
};

class NewObjExpression : public ObjExpression{
    private:
        string id;
        deque<Expression*>* arguments;
    
    public:
        NewObjExpression(string id, deque<Expression*>* args);
        void print();
};

class IdExpression : public ObjExpression{
    private:
        string id;
    
    public:
        IdExpression(string id);
        void print();
};

class FieldAccessExpression : public ObjExpression{
    private:
        string id;
    
    public:
        FieldAccessExpression(string id);
        void print();
};

class ThisExpression : public ObjExpression{
    public:
        void print();
};

class MethodCallExpression : public ObjExpression{
    private:
        Expression* left;
        string method;
        deque<Expression*>* arguments;

    public:
        MethodCallExpression(Expression* left, string method, deque<Expression*>* args);
        void print();
};

class ParenExpression : public ObjExpression{
    private:
        Expression* first;

    public:
        ParenExpression(Expression* first);
        void print();
};

class LitArrayExpression : public ObjExpression{
    private:
        deque<Expression*>* expressions;
    public:
        LitArrayExpression(deque<Expression*>* exprs);
        void print();
};

class ArrayAccessExpression : public Expression{
    private:
        ObjExpression* left;
        deque<Expression*>* dimensions;

    public:
        ArrayAccessExpression(ObjExpression* left, deque<Expression*>* dimensions);
        void print();
};

#endif