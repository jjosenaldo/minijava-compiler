#ifndef CODE_VISITOR_HPP
#define CODE_VISITOR_HPP

#include "ast.hpp"
#include "error.hpp"
#include "expression.hpp"
#include "symtable.hpp"
#include "statement.hpp"

#include <vector>
#include <string>

using std::string;
using std::vector;

class Method;

class CodeVisitor {
private:
	unsigned long int countTmpVars = 0u;
	unsigned long int countLabels = 0u;

	void resetCountTmpVars();
	string getNewTmpVar();
	string getNewLabel();

	// TODO: return formal params
	vector<string> getRealParams(string className, string methodName) {
		return vector<string>();
	}
	
	// TODO: return label to method
	string getMethodLabel(string className, string methodName) {
		return "";
	}

public:
	// AST base
	string visit(Program*);
	string visit(Method*);
	string visit(ClassDeclaration*);
	string visitClassDeclarationFields(ClassDeclaration *classDec);
	string visitClassDeclarationsFields(Program* program);

	// Statements
	string visit(VarDec*);
	string visit(Block*);
	string visit(ElselessIf*);
	string visit(IfElse*);
	string visit(While*);
	string visit(Assignment*);
	string visit(Continue*);
	string visit(Break*);
	string visit(Return*);
	string visit(Skip*);

	// Estas classes são statements e expressions?
	string visit(StaticMethodCallExpression*);
	string visit(MethodCallExpression*);

	// Expressions
	string visit(BinExpression*);
	string visit(UnExpression*);
	string visit(AtomExpression*);
	string visit(ArrayDeclExpression*);
	string visit(NewObjExpression*);
	string visit(IdExpression*);
	string visit(FieldAccessExpression*);
	string visit(ThisExpression*);
	string visit(ParenExpression*);
	string visit(LitArrayExpression*);
	string visit(ArrayAccessExpression*);
	string visit(NewArrayExpression*);
};

#endif