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

class ElselessIf : public Statement{
    private:
        Expression* guard;
        Statement* statement;

    public:
        ElselessIf(Expression* guard, Statement* statement);
        void print();
};

class IfElse : public Statement{
    private: 
        Expression* guard;
        Statement* statementIf;
        Statement* statementElse;
    public:
        IfElse(Expression* guard, Statement* statementIf, Statement* statementElse);
        void print();
};

class While : public Statement{
    private:
        Expression* guard;
        Statement* statement;
    public:
        While(Expression* guard, Statement* statement);
        void print();
};

class Assignment : public Statement{
    private:
        Expression* lvalue;
        Expression* rvalue;
    public:
        Assignment(Expression* lvalue, Expression* rvalue);
        void print();
};

class Continue : public Statement{
    public:
        void print();
};

class Break : public Statement{
    public:
        void print();
};

class Return : public Statement{
    private:
        Expression* optExp;
    public:
        Return();
        Return(Expression* optExp);
        void print();
};

class MethodCall : public Statement{
    private:
        Expression* lvalue;
        string methodName;
        deque<Expression*>* arguments;
    public:
        MethodCall(Expression* lvalue, string methodName, deque<Expression*>* arguments);
        void print();
};

class Skip : public Statement {
    public:
        void print();
};


#endif