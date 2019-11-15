#ifndef STATEMENT_HPP
#define STATEMENT_HPP

#include <deque>
#include "expression.hpp"
#include "symtable.hpp"

using std::deque;

class Program;

class GenStatement{
    public:
        // Will be defined in a derived class
        virtual void print() = 0;
        virtual bool accept(StaticVisitor& visitor) = 0;
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
        bool accept(StaticVisitor& visitor);
        void print();

        friend class StaticVisitor;
};

class Block : public Statement{
    private:
        deque<GenStatement*>* statements;

    public:
        Block();
        void addStatement(GenStatement* stmt);
        void addStatementAtFront(GenStatement* stmt);
        deque<GenStatement*>* getStatements();
        bool accept(StaticVisitor& visitor);
        void print();

        friend class StaticVisitor;
};

class ElselessIf : public Statement {
    private:
        Expression* guard;
        Statement* statement;

    public:
        ElselessIf(Expression* guard, Statement* statement);
        bool accept(StaticVisitor& visitor);
        Statement* getStatement();
        void print();

        friend class StaticVisitor;

};

class IfElse : public Statement{
    private:
        Expression* guard;
        Statement* statementIf;
        Statement* statementElse;
    public:
        IfElse(Expression* guard, Statement* statementIf, Statement* statementElse);
        bool accept(StaticVisitor& visitor);

        Statement* getStatementIf();
        Statement* getStatementElse();
        void print();

        friend class StaticVisitor;
};

class While : public Statement{
    private:
        Expression* guard;
        Statement* statement;
    public:
        While(Expression* guard, Statement* statement);
        bool accept(StaticVisitor& visitor);
        Statement* getStatement();
        void print();

        friend class StaticVisitor;
};

class Assignment : public Statement{
    private:
        Expression* lvalue;
        Expression* rvalue;
    public:
        Assignment(Expression* lvalue, Expression* rvalue);
        bool accept(StaticVisitor& visitor);
        void print();

        friend class StaticVisitor;
};

class Continue : public Statement{
    public:
        void print();
        bool accept(StaticVisitor& visitor);

        friend class StaticVisitor;

};

class Break : public Statement{
    public:
        void print();
        bool accept(StaticVisitor& visitor);

        friend class StaticVisitor;

};

class Return : public Statement{
    private:
        Expression* optExp;
    public:
        Return();
        Return(Expression* optExp);
        bool accept(StaticVisitor& visitor);
        void print();

        friend class StaticVisitor;

};

class Skip : public Statement {
    public:
        void print();
        bool accept(StaticVisitor& visitor);
        friend class StaticVisitor;
};

class StaticMethodCallExpression : public Statement, public ObjExpression{
    private:
        string className;
        string method;
        deque<Expression*>* arguments;

    public:
        StaticMethodCallExpression(string className, string method, deque<Expression*>* arguments);
        string toString();
        bool accept(StaticVisitor&);
        void print();

        friend class StaticVisitor;

};

// Its type is not known when the tree is being built
class MethodCallExpression : public Statement,  public ObjExpression{
    private:
        Expression* left;
        string method;
        deque<Expression*>* arguments;

    public:
        MethodCallExpression(Expression* left, string method, deque<Expression*>* args);
        string toString();
        bool accept(StaticVisitor&);
        void print();

        friend class StaticVisitor;
};

#endif