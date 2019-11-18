#include "code-visitor.hpp"// Statements
#include "operator.hpp"
#include <algorithm>
#include <deque>

#include <iostream>

using std::to_string;
using std::cout;


#define RS string("rs->")
#define RS_TOP string("rs->top()->")
#define RS_LOOKUP(x) string(RS_TOP+"lookupVarVal(" + x + ")")
#define TYPE string("Value*")
#define CREATERECORD(b_label, e_label) string(RS + "createRecord(&&" + b_label + ", &&" + e_label + ");")
#define POPRECORD string(RS + "pop();")
#define GOTO(label) "goto " + string(label)
#define IFNOT_GOTO(guard, label) string("if(!" + guard + ") " + GOTO(label))
#define UPDATEVAR(lvalue, rvalue) string(RS_TOP + "update(\"" + lvalue + "\"," + rvalue + ")")
#define INSERTVAR(x,y) string("insertVar(\"" + x + "\"," + y + ")")

void CodeVisitor::resetCountTmpVars() {
    this->countTmpVars = 0;
}

string CodeVisitor::getNewTmpVar() {
    return "tmp" + to_string(this->countTmpVars++);
}

string CodeVisitor::getNewLabel() {
    return "l" + to_string(this->countLabels++);
}

// AST base
// TODO:
string CodeVisitor::visit(Program *program) {
    for(auto &e : *(program->declarations))
        e->accept(*this);
    return "";
}

// TODO
string CodeVisitor::visit(Method *method) {
    method->statement->accept(*this);
    return "";
}

// TODO
string CodeVisitor::visit(ClassDeclaration *classdec) {
    for(auto &e : *(classdec->methods))
        e->accept(*this);
    return "";
}

// Statements
string CodeVisitor::visit(VarDec *vardec){
    cout << "{\n";
    string tmp = vardec->value->accept(*this);
    cout << RS_TOP + INSERTVAR(vardec->id, tmp) + ";\n";
    cout << "}\n";
    resetCountTmpVars();
    return "";
}

string CodeVisitor::visit(Block *block) {
    cout << CREATERECORD("nullptr", "nullptr") << "\n";
    for(auto &e : *(block->statements))
        e->accept(*this);
    cout << POPRECORD << "\n";

    return "";
}

string CodeVisitor::visit(ElselessIf *elselessIf) {
    /* Code generaton example:

        MiniJava Code:
            if(<guard>)
                <stmt>

        Generated C++ code:
            Value* tmp = <guard>;
            if(!tmp) goto <lab>;
            <stmt>
            <lab>:
    */

    cout << "{\n";
    string lab = getNewLabel();

    // Solve guard
    string tmp_guard = elselessIf->guard->accept(*this);

    // Test guard
    cout << IFNOT_GOTO(tmp_guard, lab) << ";\n";

    // Visit statement
    elselessIf->statement->accept(*this);

    // End if
    cout << lab << ":\n";
    cout << "}\n";

    return "";
}

string CodeVisitor::visit(IfElse *ifElse) {
    /* Code generaton example:

        MiniJava Code:
            if(<guard>)
                <stmt1>
            else
                <stmt2>

        Generated C++ code:
            Value* tmp = <guard>;
            if(!tmp) goto <lab1>;
            <stmt1>
            goto <lab2>;
            <lab1>:
            <stmt2>
            <lab2>

    */

    string lab1 = getNewLabel();
    string lab2 = getNewLabel();

    cout << "{\n";
    // Solve guard
    string tmp_guard = ifElse->guard->accept(*this);

    // Test guard
    cout << IFNOT_GOTO(tmp_guard, lab1) << ";\n";

    // Visit first statement
    ifElse->statementIf->accept(*this);

    // Goto second label
    cout << GOTO(lab2) << ";\n";

    // Begin else
    cout << lab1 + ":\n";

    // Visit second statement
    ifElse->statementElse->accept(*this);

    cout << lab2 + ":\n";
    cout << "}\n";
    return "";
}

string CodeVisitor::visit(While *whilestmt) {
    /* Code generaton example:

        MiniJava Code:
            while(<guard>)
                <stmt>

        Generated C++ code:
            {
                <lab1>:
                Value* tmp = <guard>;
                if(!tmp) goto <lab2>;
                <stmt1>
                goto <lab1>;
                <lab2>:
            }
    */

    string lab1 = getNewLabel();
    string lab2 = getNewLabel();

    cout << CREATERECORD(lab1, lab2) << "\n";

    cout << "{\n";
    cout << lab1 << ":\n";

    // Solve guard
    string tmp_guard = whilestmt->guard->accept(*this);

    // Test guard
    cout << IFNOT_GOTO(tmp_guard, lab2) << ";\n";

    // Visit statement
    whilestmt->statement->accept(*this);

    // Goto begin while
    cout << GOTO(lab1) << ";\n";

    cout << lab2 << ":\n";

    cout << "}\n";

    cout << POPRECORD << "\n";

    return "";
}

// TODO: Implement after
string CodeVisitor::visit(Assignment *assign) {
    /* Code generaton example:

        MiniJava Code:
            a = <exp>;

        Generated C++ code:
            Value *tmp = <expr>;
            rs->top()->update("a", tmp);
    */

    cout << "{\n";
    string tmp_rvalue = assign->rvalue->accept(*this);
    //cout << UPDATEVAR(*(assign->lvalue), tmp_rvalue) << ";\n";
    cout << tmp_rvalue << "\nTODO: Solve lvalue problem\n";
    cout << "}\n";
    return "";
}

string CodeVisitor::visit(Continue *stmt) {
    string tmp = getNewTmpVar();
    cout << "void* " + tmp + " = rs->searchContinue(); \n";
    cout << GOTO("*" + tmp) << ";\n";
}

string CodeVisitor::visit(Break *stmt) { return ""; }      // TODO: Implement after
string CodeVisitor::visit(Return *stmt) { return ""; }     // TODO: Implement after
string CodeVisitor::visit(Skip *stmt) { return ""; }       // TODO: Implement after

string CodeVisitor::visit(StaticMethodCallExpression *exp) { return ""; } // TODO: Implement after
string CodeVisitor::visit(MethodCallExpression *exp) { return ""; }       // TODO: Implement after

// Expressions
string CodeVisitor::visit(BinExpression *exp) {
    string tmp1 = exp->first->accept(*this);
    string tmp2 = exp->second->accept(*this);

    string tmp = getNewTmpVar();
    cout << TYPE << " " << tmp << " = *" << tmp1 << " " << binOpSymbol(exp->getOp()) << " *" << tmp2 << ";\n";
    return tmp;
}

string CodeVisitor::visit(UnExpression *exp) {
    string tmp1 = exp->first->accept(*this);

    string tmp = getNewTmpVar();
    cout << TYPE << " " << tmp << " = " << unOpSymbol(exp->op) << " *" << tmp1 << ";\n";
    return tmp;
}

// TODO: implement the remaining atomic expressions
string CodeVisitor::visit(AtomExpression *exp) {
    string tmp = getNewTmpVar();

    if(exp->type->kind == TypeInt)
        cout << TYPE << " " << tmp << " = new IntValue(" << exp->val.intval << ");\n";
    return tmp;
}

// TODO: Declarar memória dinâmica no registro de ativação
string CodeVisitor::visit(ArrayDeclExpression *exp) {
 return "";
}

// TODO: Declarar memória dinâmica no registro de ativação
string CodeVisitor::visit(NewObjExpression *exp) {
 return "";
}

string CodeVisitor::visit(IdExpression *exp) {
    cout << TYPE << " _" << exp->getId() << " = " << RS_LOOKUP("\"" + exp->getId() + "\"")<< ";\n";
    return "_"+exp->getId();
}

// TODO: Pegar referência para a classe em que o código está sendo executado (caso não seja um método estático)
string CodeVisitor::visit(FieldAccessExpression *exp) {
 return "";//RS_TOP + "getInstance()->query(\""+exp.getId()+"\")";
}

// TODO: Pegar referência para a classe em que o código está sendo executado (caso não seja um método estático)
string CodeVisitor::visit(ThisExpression *exp) {
 return ""; //"r.getInstance()->";
}

string CodeVisitor::visit(ParenExpression *exp) {
    return exp->first->accept(*this);
}

// TODO: Permitir adiocionar um array literal no registro de ativação
string CodeVisitor::visit(LitArrayExpression *exp) {
 return "";
}

// TODO: Decidir como acessar posições de um vetor
string CodeVisitor::visit(ArrayAccessExpression *exp) {
 return "";
}

// TODO: Decidir como declarar dinâmicamente um array
string CodeVisitor::visit(NewArrayExpression *exp) {
 return "";
}