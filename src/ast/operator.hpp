#ifndef OPERATOR_HPP
#define OPERATOR_HPP

#include <string>
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

string binOpSymbol(BinOperator op);

string unOpSymbol(UnOperator op);

#endif