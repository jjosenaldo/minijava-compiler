#ifndef EXPRESSION_HPP
#define EXPRESSION_HPP

#include <deque>
#include <iostream>
#include <unordered_map>
#include <string>
#include "operator.hpp"
#include "symtable.hpp"

using std::cout;
using std::deque;
using std::unordered_map;
using std::string;

class StaticVisitor;
class CodeVisitor;

union AtomExpValue{
    bool boolval;   
    int intval;
    char* strval;
};

bool predefinedId(string id);

#include "type.hpp"


class Program;

class Expression{
    protected:
        Type* type;

    public:
        Expression(){}
        Expression(Type* type);
        virtual void setType(Type* other);
        Type* getType();
        virtual ~Expression() {}
        void print(){cout << toString();}
        bool isObject();
        virtual bool isLvalue();
        virtual bool accept(StaticVisitor&);
        virtual string accept(CodeVisitor&) {return "ERROR";}; // TODO: implement this for all subclasses
        virtual string toString() = 0;
};

// Example: 1+1
class BinExpression : public Expression{
    private:
        Expression* first;
        Expression* second;
        BinOperator op;
    
    public:
        BinExpression(Expression* first, Expression* second, BinOperator op);
        string toString();
        Expression* getFirst();
        Expression* getSecond();
        BinOperator getOp();

        bool accept(StaticVisitor&);
        string accept(CodeVisitor&);
        friend class StaticVisitor;
        friend class CodeVisitor;
};

// Example: false
//,         52
//          "oi"
//          null
// The type is set when the parse tree is built
class AtomExpression : public Expression{
    private:
        AtomExpValue val;

    public:
        AtomExpression(Type* type);
        AtomExpression(AtomExpValue val, Type* type);
        AtomExpValue getVal();
        string toString();

        bool accept(StaticVisitor&);
        string accept(CodeVisitor&);
        friend class StaticVisitor;
        friend class CodeVisitor;
};

// Example: !a
class UnExpression : public Expression{
    private:
        Expression* first;
        UnOperator op;

    public:
        UnExpression(Expression* first, UnOperator op);
        
        string toString();
        Expression* getFirst();
        UnOperator getOp();

        bool accept(StaticVisitor&);
        string accept(CodeVisitor&);
        friend class StaticVisitor;
        friend class CodeVisitor;
};

class ObjExpression : public Expression{
    public:
        ObjExpression(){}
        ObjExpression(Type* type) : Expression(type){}

        virtual bool accept(StaticVisitor&) = 0;
        virtual string accept(CodeVisitor&) {return "";} // TODO: implement in subclasses
};

// Example: new int
// The type is set when the parse tree is built
class ArrayDeclExpression : public ObjExpression{
    public:
        ArrayDeclExpression(Type* type) : ObjExpression(type) {}
        string toString();

        bool accept(StaticVisitor&);
        friend class StaticVisitor;
        friend class CodeVisitor;
};

// Its type is not known when the tree is being built
class IdExpression : public ObjExpression{
    private:
        string id;
    
    public:
        IdExpression(string id);
        string getId();
        string toString();
        bool isLvalue();
        bool accept(StaticVisitor&);
        string accept(CodeVisitor&);
        friend class StaticVisitor;
        friend class CodeVisitor;
};

// Its type is not known when the tree is being built
class FieldAccessExpression : public ObjExpression{
    private:
        string id;
    
    public:
        FieldAccessExpression(string id);
        string toString();
        bool isLvalue();
        bool accept(StaticVisitor&);
        friend class StaticVisitor;
        friend class CodeVisitor;
};

// Its type is not known when the tree is being built
class ThisExpression : public ObjExpression{
    public:
        string toString();
        bool accept(StaticVisitor&);
        friend class StaticVisitor;
        friend class CodeVisitor;
};

// Example: (a)
class ParenExpression : public ObjExpression{
    private:
        Expression* first;

    public:
        ParenExpression(Expression* first);
        string toString();
        bool isLvalue();
        Expression* getFirst();
        bool accept(StaticVisitor&);
        string accept(CodeVisitor&);
        friend class StaticVisitor;
        friend class CodeVisitor;
};

class LitArrayExpression : public ObjExpression{
    private:
        deque<Expression*>* expressions;
    public:
        LitArrayExpression(deque<Expression*>* exprs);
        string toString();
        bool accept(StaticVisitor&);
        string accept(CodeVisitor&);
        friend class StaticVisitor;
        friend class CodeVisitor;
};

class ArrayAccessExpression : public Expression{
    private:
        ObjExpression* left;
        deque<Expression*>* dimensions;

    public:
        ArrayAccessExpression(ObjExpression* left, deque<Expression*>* dimensions);
        string toString();
        bool isLvalue();
        bool accept(StaticVisitor&);
        string accept(CodeVisitor&);
        friend class StaticVisitor;
        friend class CodeVisitor;
};

class NewArrayExpression : public Expression{
    private:
        Type* baseType;
        deque<Expression*>* dimensions;
    
    public:
        NewArrayExpression(ArrayDeclExpression* decl, deque<Expression*>* dimensions);
        string toString();
        bool accept(StaticVisitor&);
        string accept(CodeVisitor&);
        friend class StaticVisitor;
        friend class CodeVisitor;
};

// Example: new Cat()
class NewObjExpression : public ObjExpression{
    private:
        string id;
    
    public:
        NewObjExpression(string id);
        string toString();

        bool accept(StaticVisitor&);
        string accept(CodeVisitor&);

        friend class StaticVisitor;
        friend class CodeVisitor;
};

#endif