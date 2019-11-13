#include "visitor.hpp"// Statements
#include "operator.hpp"
#include <algorithm>

#include <iostream>

using std::to_string;
using std::cout;


#define RS string("rs->")
#define RS_TOP string("rs->top()->")
#define RS_LOOKUP(x) string(RS+"lookupVarVal(" + x + ")")
#define TYPE string("Value*")

// Statements
// string visit(VarDec *stmt){
// 	return RS_TOP + "insertVar("+ exp->getId() + "," + visit(expr->getExpression()) +");\n";
// }

// string visit(Block *stmt) {
// 	string res = RS + "createRecord();\n";
// 	for(auto &e : stmt->getStatements())
// 		res += visit(e);
// 	return res + RS + "pop();\n";
// }

// // TODO
// string visit(ElselessIf *stmt) {
// 	// string label = this->getLabelIf();
// 	// // Avaliar a expressão

// 	// temp =
// 	// // Testar
// 	// string res = "if(!" + visit(stmt->guard) ") goto " + label + ";\n";
// 	// res += "blá"; // Execute o statement
// 	// res += label + ":\n";
// }

// string visit(IfElse *stmt);
// string visit(While *stmt);
// string visit(Assignment *stmt);
// string visit(Continue *stmt);
// string visit(Break *stmt);
// string visit(Return *stmt);
// string visit(Skip *stmt);

// Expressions
string Visitor::visit(BinExpression *exp) {
	string tmp1 = visit(exp->first);
	string tmp2 = visit(exp->second);
	cout << TYPE << " _tmp" << this->contTmpVars << " = *" << tmp1 << " " << binOpSymbol(exp->getOp()) << " " << tmp2 << ";\n";
	return "_tmp" + to_string(this->contTmpVars++);
}

string Visitor::visit(Expression *exp) {
	BinExpression* bin = dynamic_cast<BinExpression*> (exp);

	if(bin != nullptr){
		return visit(bin);
	}

	IdExpression* idExp = dynamic_cast<IdExpression*> (exp);

	if(idExp != nullptr){
		return visit(idExp);
	}

	return "";
}

// string Visitor::visit(UnExpression *exp) {
// 	return unOpSymbol(exp->getOp()) + visit(exp->getFirst());
// }

// string Visitor::visit(AtomExpression *exp) {
// 	return exp->toString();
// }

// // TODO: Declarar memória dinâmica no registro de ativação
// string Visitor::visit(ArrayDeclExpression *exp) {
// 	return "";
// }

// // TODO: Declarar memória dinâmica no registro de ativação
// string Visitor::visit(NewObjExpression *exp) {
// 	return "";
// }

string Visitor::visit(IdExpression *exp) {
	cout << TYPE << " _" << exp->getId() << " = " << RS_LOOKUP("\"" + exp->getId() + "\"")<< ";\n";
	return "_"+exp->getId();
}

// // TODO: Pegar referência para a classe em que o código está sendo executado (caso não seja um método estático)
// string Visitor::visit(FieldAccessExpression *exp) {
// 	return "";//RS_TOP + "getInstance()->query(\""+exp.getId()+"\")";
// }

// // TODO: Pegar referência para a classe em que o código está sendo executado (caso não seja um método estático)
// string Visitor::visit(ThisExpression *exp) {
// 	return ""; //"r.getInstance()->";
// }

// string Visitor::visit(ParenExpression *exp) {
// 	return "(" + visit(exp->getFirst()) + ")";
// }

// // TODO: Permitir adiocionar um array literal no registro de ativação
// string Visitor::visit(LitArrayExpression *exp) {
// 	return "";
// }

// // TODO: Decidir como acessar posições de um vetor
// string Visitor::visit(ArrayAccessExpression *exp) {
// 	return "";
// }

// // TODO: Decidir como declarar dinâmicamente um array
// string Visitor::visit(NewArrayExpression *exp) {
// 	return "";
// }