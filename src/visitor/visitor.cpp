#include "visitor.hpp"// Statements
#include "operator.hpp"

#define RS "rs->"
#define RS_TOP "rs->top()->"

// Statements
string visit(VarDec *stmt){
	return RS_TOP + "insertVar("+ exp->getId() + "," + visit(expr->getExpression()) +");\n";
}

string visit(Block *stmt) {
	string res = RS + "createRecord();\n";
	for(auto &e : stmt->getStatements())
		res += visit(e);
	return res + RS + "pop();\n";
}

// TODO
string visit(ElselessIf *stmt) {
	// string label = this->getLabelIf();
	// // Avaliar a expressão

	// temp =
	// // Testar
	// string res = "if(!" + visit(stmt->guard) ") goto " + label + ";\n";
	// res += "blá"; // Execute o statement
	// res += label + ":\n";
}

string visit(IfElse *stmt);
string visit(While *stmt);
string visit(Assignment *stmt);
string visit(Continue *stmt);
string visit(Break *stmt);
string visit(Return *stmt);
string visit(Skip *stmt);

// Expressions
string Visitor::visit(BinExpression *exp) {
	return visit(exp->first) + binOpSymbol(exp->getOp()) + visit(exp->second);
}

string Visitor::visit(UnExpression *exp) {
	return unOpSymbol(exp->getOp()) + visit(exp->getFirst());
}

string Visitor::visit(AtomExpression *exp) {
	return exp->toString();
}

// TODO: Declarar memória dinâmica no registro de ativação
string Visitor::visit(ArrayDeclExpression *exp) {
	return "";
}

// TODO: Declarar memória dinâmica no registro de ativação
string Visitor::visit(NewObjExpression *exp) {
	return "";
}

string Visitor::visit(IdExpression *exp) {
	return RS_TOP + "getVarVal(\"" + exp->getId() + "\")";
}

// TODO: Pegar referência para a classe em que o código está sendo executado (caso não seja um método estático)
string Visitor::visit(FieldAccessExpression *exp) {
	return "";//RS_TOP + "getInstance()->query(\""+exp.getId()+"\")";
}

// TODO: Pegar referência para a classe em que o código está sendo executado (caso não seja um método estático)
string Visitor::visit(ThisExpression *exp) {
	return ""; //"r.getInstance()->";
}

string Visitor::visit(ParenExpression *exp) {
	return "(" + visit(exp->getFirst()) + ")";
}

// TODO: Permitir adiocionar um array literal no registro de ativação
string Visitor::visit(LitArrayExpression *exp) {
	return "";
}

// TODO: Decidir como acessar posições de um vetor
string Visitor::visit(ArrayAccessExpression *exp) {
	return "";
}

// TODO: Decidir como declarar dinâmicamente um array
string Visitor::visit(NewArrayExpression *exp) {
	return "";
}