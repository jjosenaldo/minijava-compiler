#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <unordered_map>
#include <string>
#include "type.hpp"

using std::hash;
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

// boolean, int, ID, this, null
class AtomExpression : public Expression{
    private:
        AtomExpValue val;

    public:
        AtomExpression(Type* type);
        AtomExpression(AtomExpValue val, Type* type);
        AtomExpValue getVal();
        void print();
};
#endif