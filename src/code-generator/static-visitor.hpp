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

class StaticVisitor{
private:
    Symtable* environment;
    ClassSymtablePool* pool;

public:
    StaticVisitor(Symtable*, ClassSymtablePool*);
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
};

#endif
