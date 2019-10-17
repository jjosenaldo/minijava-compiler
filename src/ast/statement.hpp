#ifndef STATEMENT_HPP
#define STATEMENT_HPP

#include "expression.hpp"

class GenStatement{};

class Statement : GenStatement {};

class VarDec : GenStatement{
    private:
        Type* type;
        string id;
        Expression* value;
};

class Block : Statement{
    private:
        vector<GenStatement*>* statements;
};

class ElselessIf : Statement{
    private:
        Expression* guard;
        Statement* statement;
};

class IfElse : Statement{
    private: 
        Expression* guard;
        Statement* statementIf;
        Statement* statementElse;
};

class While : Statement{
    private:
        Expression* guard;
        Statement* statement;
};

class Assignment : Statement{
    private:
        Expression* lvalue;
        Expression* rvalue;
};

class Continue : Statement{};

class Break : Statement{};

class Return : Statement{
    private:
        Expression* optExp;
};

class MethodCall : Statement{
    private:
        Expression* lvalue;
        string methodName;
        vector<Expression*>* arguments;
};

class Skip : Statement {};


#endif