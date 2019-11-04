#include "visitor.hpp"

string Visitor::visit(IdExpression exp) {
	return "r.query(\""+exp.getId()+"\")";
}

void Visitor::visit(FieldAccessExpression exp) {
	return "r.getInstance()->query(\""+exp.getId()+"\")";
}

// TODO: all

void Visitor::visit(ThisExpression exp) {
	return "r.getInstance()->";
}

string Visitor::visit(ParenExpression exp) {
	return "("+exp.first->toString()+")";
}
void Visitor::visit(LitArrayExpression exp);
void Visitor::visit(ArrayAccessExpression exp);
void Visitor::visit(NewArrayExpression exp);