#ifndef STATEMENT_HPP
#define STATEMENT_HPP

#include <deque>
#include "expression.hpp"

using std::deque;


class GenStatement{
    public:
        // Will be defined in a derived class
        virtual void print() = 0;
};

class Statement : public GenStatement {};

class VarDec : public GenStatement{
    private:
        Type* type;
        string id;
        Expression* value;
    public:
        VarDec(Type* type, string id);
        VarDec(Type* type, string id, Expression* value);
        Type* getType();
        string getId();
        Expression* getExpression();
        void print();
};

class Block : public Statement{
    private:
        deque<GenStatement*> statements;
    
    public:
        void addStatement(GenStatement* stmt);

        void addStatementAtFront(GenStatement* stmt);

        void print();
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