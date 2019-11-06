#include "visitor.hpp"
#define RS_TOP "rs->top()->"

string Visitor::visit(IdExpression *exp) {
	return RS_TOP + "getVarVal(\"" + exp->getId() + "\")";
}

// TODO
string Visitor::visit(FieldAccessExpression *exp) {
	return "";//RS_TOP + "getInstance()->query(\""+exp.getId()+"\")";
}

string Visitor::visit(AtomExpression *exp) {
	return exp->toString();
}

string Visitor::visit(BinExpression *exp) {
	return visit(exp->first) + binOpSymbol(exp->) +
}

// TODO: all

string Visitor::visit(ThisExpression *exp) {
	return "r.getInstance()->";
}

string Visitor::visit(ParenExpression *exp) {
	return "("+exp.first->toString()+")";
}
string Visitor::visit(LitArrayExpression *exp);
string Visitor::visit(ArrayAccessExpression *exp);
string Visitor::visit(NewArrayExpression *exp);