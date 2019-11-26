#ifndef CODE_VISITOR_HPP
#define CODE_VISITOR_HPP

#include "ast.hpp"
#include "error.hpp"
#include "expression.hpp"
#include "symtable.hpp"
#include "statement.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using std::ostream;
using std::string;
using std::vector;
using std::unordered_map;
using std::pair;
using std::make_pair;


#include <cstdlib>
class Method;

class CodeVisitor {
private:
	unsigned long int countTmpVars = 0u;
	unsigned long int countLabels = 0u;

	ostream &out;

	void resetCountTmpVars();
	string getNewTmpVar();
	string getNewLabel();

	unordered_map<
		string, // className
		unordered_map<
			string, // methodName
			pair<
				string, // label
				vector<string> // parameters' names
			>
		>
	> *methodsInfo;

	unordered_map<string, string> inheritanceInfo;

	vector<string> getRealParams(string className, string methodName);
	string getMethodLabel(string className, string methodName);
	void initMethodsInfo(Program* program);

public:
	CodeVisitor(ostream &out) : out(out) {}

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

	// Statements and Expressions
	string visit(StaticMethodCallExpression*);
	string visit(MethodCallExpression*);

	// Expressions
	string visit(BinExpression*);
	string visit(UnExpression*);
	string visit(AtomExpression*);
	string visit(NewObjExpression*);
	string visit(IdExpression*);
	string visit(FieldAccessExpression*);
	string visit(ThisExpression*);
	string visit(ParenExpression*);
	string visit(LitArrayExpression*);
	string visit(ArrayAccessExpression*);
	string visit(NewArrayExpression*);
};

string typeToValueString(Type* t);

#endif