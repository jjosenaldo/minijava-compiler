#ifndef STATIC_VISITOR_HPP
#define STATIC_VISITOR_HPP

#include "symtable.hpp"

class BinExpression;
class UnExpression;
class AtomExpression;
class ArrayDeclExpression;
class NewObjExpression;
class IdExpression;
class FieldAccessExpression;
class ThisExpression;
class ParenExpression;
class LitArrayExpression;
class ArrayAccessExpression;
class NewArrayExpression;
class MethodCallExpression;
class StaticMethodCallExpression;
class VarDec;
class Block;
class ElselessIf;
class IfElse;
class While;
class Assignment;
class Continue;
class Break;
class Return;
class Skip;
class Method;
class Field;

class StaticVisitor{
private:
    Symtable* environment;
    ClassSymtablePool* pool;

public:
    StaticVisitor(Symtable*, ClassSymtablePool*);

    // Expressions
    bool visit(BinExpression*);
    bool visit(UnExpression*);
    bool visit(AtomExpression*);
    bool visit(ArrayDeclExpression*);
    bool visit(NewObjExpression*);
    bool visit(IdExpression*);
    bool visit(FieldAccessExpression*);
    bool visit(ThisExpression*);
    bool visit(ParenExpression*);
    bool visit(LitArrayExpression*);
    bool visit(ArrayAccessExpression*);
    bool visit(NewArrayExpression*);

    // Statements
    bool visit(VarDec* stmt);
    bool visit(Block* stmt);
    bool visit(ElselessIf* stmt);
    bool visit(IfElse* stmt);
    bool visit(While* stmt);
    bool visit(Assignment* stmt);
    bool visit(Continue* stmt);
    bool visit(Break* stmt);
    bool visit(Return* stmt);
    bool visit(Skip* stmt);

    // Both Expressions and Statements
    bool visit(StaticMethodCallExpression* exp);
    bool visit(MethodCallExpression* exp);

    // Other AST elements
    bool visitMethodHeader(Method* method, ClassSymtable* root, string className);
    bool visit(Field* field, ClassSymtable* root, string className);
};

#endif
