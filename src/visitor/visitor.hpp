#ifndef VISITOR_HPP
#define VISITOR_HPP
#include "expression.hpp"

class Visitor {
private:

public:
	void visit(IdExpression exp);
	void visit(FieldAccessExpression exp);
	void visit(ThisExpression exp);
	void visit(ParenExpression exp);
	void visit(LitArrayExpression exp);
	void visit(ArrayAccessExpression exp);
	void visit(NewArrayExpression exp);
}

#endif