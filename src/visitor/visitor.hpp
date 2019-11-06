#ifndef VISITOR_HPP
#define VISITOR_HPP
#include "expression.hpp"

class Visitor {
private:

public:
	string visit(IdExpression *exp);
	string visit(FieldAccessExpression *exp);
	string visit(AtomExpression *exp);
	string visit(BinExpression *exp);

	string visit(ThisExpression *exp);
	string visit(ParenExpression *exp);
	string visit(LitArrayExpression *exp);
	string visit(ArrayAccessExpression *exp);
	string visit(NewArrayExpression *exp);
}

#endif