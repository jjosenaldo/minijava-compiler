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

class Expression{
    protected:
        Type* type;

    public:
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

#endif