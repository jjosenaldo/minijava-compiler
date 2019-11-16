#ifndef CODE_VISITOR_HPP
#define CODE_VISITOR_HPP

#include "ast.hpp"
#include "error.hpp"
#include "expression.hpp"
#include "symtable.hpp"

class CodeVisitor {
private:
	int contTmpVars = 0;

public:
	// Statements
	// string visit(VarDec *stmt);
	// string visit(Block *stmt);
	// string visit(ElselessIf *stmt);
	// string visit(IfElse *stmt);
	// string visit(While *stmt);
	// string visit(Assignment *stmt);
	// string visit(Continue *stmt);
	// string visit(Break *stmt);
	// string visit(Return *stmt);
	// string visit(Skip *stmt);

	// Estas classes são statements e expressions?
	// string visit(StaticMethodCallExpression *exp);
	// string visit(MethodCallExpression *exp);

	// Expressions
	string visit(Expression *exp);
	string visit(BinExpression *exp);
	// string visit(UnExpression *exp);
	// string visit(AtomExpression *exp);
	// string visit(ArrayDeclExpression *exp);
	// string visit(NewObjExpression *exp);
	string visit(IdExpression *exp);
	// string visit(FieldAccessExpression *exp);
	// string visit(ThisExpression *exp);
	// string visit(ParenExpression *exp);
	// string visit(LitArrayExpression *exp);
	// string visit(ArrayAccessExpression *exp);
	// string visit(NewArrayExpression *exp);

	
};

#endif