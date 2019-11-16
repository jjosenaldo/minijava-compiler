#include "code-visitor.hpp"// Statements
#include "operator.hpp"
#include <algorithm>

#include <iostream>

using std::to_string;
using std::cout;


#define RS string("rs->")
#define RS_TOP string("rs->top()->")
#define RS_LOOKUP(x) string(RS_TOP+"lookupVarVal(" + x + ")")
#define TYPE string("Value*")
#define INSERTVAR(x,y) string("insertVar(\"" + x + "\"," + y + ")")

// Statements
void CodeVisitor::visit(VarDec *vardec){
	cout << "{\n";
	string tmp_var = vardec->value->accept(*this);
	cout << RS_TOP + INSERTVAR(vardec->id, tmp_var) + ";\n";
	cout << "}\n";
}

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
string CodeVisitor::visit(BinExpression *exp) {
	string tmp1 = exp->first->accept(*this);
	string tmp2 = exp->second->accept(*this);
	cout << TYPE << " _tmp" << this->contTmpVars << " = *" << tmp1 << " " << binOpSymbol(exp->getOp()) << " *" << tmp2 << ";\n";
	return "_tmp" + to_string(this->contTmpVars++);
}

string CodeVisitor::visit(UnExpression *exp) {
	string tmp1 = exp->first->accept(*this);
	cout << TYPE << " _tmp" << this->contTmpVars << " = " << unOpSymbol(exp->op) << " *" << tmp1 << ";\n";
	return "_tmp" + to_string(this->contTmpVars++) ;
}

// TODO: implement the remaining atomic expressions
string CodeVisitor::visit(AtomExpression *exp) {
	if(exp->type->kind == TypeInt)
		cout << TYPE << " _tmp" << this->contTmpVars << " = new IntValue(" << exp->val.intval << ")\n";

	return "_tmp" + to_string(this->contTmpVars++);
}

// // TODO: Declarar memória dinâmica no registro de ativação
// string CodeVisitor::visit(ArrayDeclExpression *exp) {
// 	return "";
// }

// // TODO: Declarar memória dinâmica no registro de ativação
// string CodeVisitor::visit(NewObjExpression *exp) {
// 	return "";
// }

string CodeVisitor::visit(IdExpression *exp) {
	cout << TYPE << " _" << exp->getId() << " = " << RS_LOOKUP("\"" + exp->getId() + "\"")<< ";\n";
	return "_"+exp->getId();
}

// // TODO: Pegar referência para a classe em que o código está sendo executado (caso não seja um método estático)
// string CodeVisitor::visit(FieldAccessExpression *exp) {
// 	return "";//RS_TOP + "getInstance()->query(\""+exp.getId()+"\")";
// }

// // TODO: Pegar referência para a classe em que o código está sendo executado (caso não seja um método estático)
// string CodeVisitor::visit(ThisExpression *exp) {
// 	return ""; //"r.getInstance()->";
// }

string CodeVisitor::visit(ParenExpression *exp) {
	return exp->first->accept(*this);
}

// // TODO: Permitir adiocionar um array literal no registro de ativação
// string CodeVisitor::visit(LitArrayExpression *exp) {
// 	return "";
// }

// // TODO: Decidir como acessar posições de um vetor
// string CodeVisitor::visit(ArrayAccessExpression *exp) {
// 	return "";
// }

// // TODO: Decidir como declarar dinâmicamente um array
// string CodeVisitor::visit(NewArrayExpression *exp) {
// 	return "";
// }