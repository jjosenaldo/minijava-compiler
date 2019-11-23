#ifndef CODE_VISITOR_HPP
#define CODE_VISITOR_HPP

#include "ast.hpp"
#include "error.hpp"
#include "expression.hpp"
#include "symtable.hpp"
#include "statement.hpp"

#include <vector>
#include <string>
#include <unordered_map>

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

	// TODO: Solve problem described in Trello (Polimorphism)
	vector<string> getRealParams(string className, string methodName) {
		return methodsInfo->at(className).at(methodName).second;

		// for(auto &classDec : *program->declarations) {
		// 	if(classDec->name == className) {
		// 		for(auto &method : *classDec->methods) {
		// 			if(method->id == methodName) {
		// 				for(auto &params : *method->parameters) {
		// 					ans.add(params->name);
		// 				}
		// 			}
		// 		}	
		// 	}
		// }
		//return ans;
	}
	
	// TODO: Solve problem described in Trello (Polimorphism)
	string getMethodLabel(string className, string methodName) {
		return methodsInfo->at(className).at(methodName).first;
	}

	void initMethodsInfo(Program* program) {
		methodsInfo = new unordered_map<string, unordered_map<string, pair<string,vector<string>>>>();
		for(auto &classDec : *program->declarations) {
			unordered_map< string, pair<string, vector<string>> > methods;
			for(auto &method : *classDec->methods) {
				vector<string> vec;
				for(auto &params : *method->parameters)
					vec.push_back(params->name);
				methods.insert( make_pair(method->id, make_pair(getNewLabel(), vec)) );
			}
			methodsInfo->insert(make_pair(classDec->name, methods));
		}
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