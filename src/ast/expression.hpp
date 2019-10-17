#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

enum BinOperator{
    '>',
    '<',
    OP_GREAT_EQ,
    OP_LESS_EQ,
    OP_IS_EQ,
    OP_DIFF,
    OP_OR,
    OP_AND,
    '+',
    '-',
    '*',
    '/',
    '*',
    '%'
};

enum UnOperator{
    '-',
    '!'
}

class Expression{
    protected:
        Type* type;
};

class BinExpression : Expression{
    private:
        Expression* first;
        Expression* second;
        BinOperator operator;
};

class UnExpression : Expression{
    private:
        Expression* first;
        UnOperator operator;
};

#endif