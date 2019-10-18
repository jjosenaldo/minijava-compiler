#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include "type.hpp"

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
    OP_MULT,
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

class Expression{
    protected:
        Type* type;

    public:
        virtual ~Expression() {}
        Type* getType();
        virtual void print() = 0;
};

class BinExpression : Expression{
    private:
        Expression* first;
        Expression* second;
        BinOperator op;
};

class UnExpression : Expression{
    private:
        Expression* first;
        UnOperator op;
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