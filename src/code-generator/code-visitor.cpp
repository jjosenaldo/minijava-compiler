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
#define INSERTVAR(x,y) string("insertVar(\"" + x + "\"," + y + ")")
#define CREATERECORD string(RS_TOP + "createRecord();")
#define POPRECORD string(RS_TOP + "pop();")
#define GOTO(label) "goto " + string(label)
#define IFNOT_GOTO(guard, label) string("if(!" + guard + ")" + GOTO(label))

// AST base

// TODO: 
string CodeVisitor::visit(Program *program) {
    for(auto &e : *(program->declarations))
        e->accept(*this);
    return "";
}

string CodeVisitor::visit(Method *method) {
    method->statement->accept(*this);
    return "";
}

string CodeVisitor::visit(ClassDeclaration *classdec) {
    for(auto &e : *(classdec->methods))
        e->accept(*this);
    return "";
}

// Statements
string CodeVisitor::visit(VarDec *vardec){
    cout << "{\n";
    string tmp_var = vardec->value->accept(*this);
    cout << RS_TOP + INSERTVAR(vardec->id, tmp_var) + ";\n";
    cout << "}\n";

    return ""; // Dumb value?
}

string CodeVisitor::visit(Block *block) {
    cout << CREATERECORD << "\n";
    //cout << "{\n";
    for(auto &e : *(block->statements))
        e->accept(*this);
    //cout << "}\n";
    cout << POPRECORD << "\n";

    return ""; // Dumb value?
}

// TODO: Solve unique label problem
// Sugestion: each line has a unique name (l<line_number>)
// For example, line 3 has a label named l3
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

    // Solve guard
    string tmp_guard = elselessIf->guard->accept(*this);

    // Test guard
    cout << IFNOT_GOTO(tmp_guard, "<lab>") << ";\n"; // TODO: Change label here

    // Visit statement
    elselessIf->statement->accept(*this);

    // End if
    cout << "<lab>:\n"; // TODO: Change label here

    return ""; // Dumb value?
}

// TODO: Solve unique label problem
// Sugestion: each line has a unique name (l<line_number>)
// For example, line 3 has a label named l3
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

    // Solve guard
    string tmp_guard = ifElse->guard->accept(*this);

    // Test guard
    cout << IFNOT_GOTO(tmp_guard, "<lab1>") << ";\n"; // TODO: Change label here

    // Visit first statement
    ifElse->statementIf->accept(*this);

    // Goto second label
    cout << GOTO("<lab2>") << ";\n"; // TODO: Change label here

    // Begin else
    cout << "<lab1>:\n"; // TODO: Change label here

    // Visit second statement
    ifElse->statementElse->accept(*this);

    cout << "<lab2>:\n"; // TODO: Change label here

    return ""; // Dumb value?
}


// TODO: Solve unique label problem. See visit(ElselessIf&);
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

    cout << "{\n";
    cout << "<lab1>" << ":\n"; // TODO: Change label here
    
    // Solve guard
    string tmp_guard = whilestmt->guard->accept(*this);

    // Test guard
    cout << IFNOT_GOTO(tmp_guard, "<lab2>") << ";\n"; // TODO: Change label here

    // Visit statement
    whilestmt->statement->accept(*this);

    // Goto begin while
    cout << GOTO("<lab1>") << ";\n"; // TODO: Change label here

    cout << "<lab2>" << ":\n"; // TODO: Change label here

    cout << "}\n"; 

    return ""; // Dumb value?
}

// TODO: Implement after
string CodeVisitor::visit(Assignment *stmt) {
    /* Code generaton example:
    
        MiniJava Code:
            a = <exp>;
        
        Generated C++ code:
            Value *tmp = <expr>;
            rs->top()->update("a", tmp);
    */

    return ""; // Dumb value?
}

string CodeVisitor::visit(Continue *stmt) { return ""; }   // TODO: Implement after
string CodeVisitor::visit(Break *stmt) { return ""; }      // TODO: Implement after
string CodeVisitor::visit(Return *stmt) { return ""; }     // TODO: Implement after
string CodeVisitor::visit(Skip *stmt) { return ""; }       // TODO: Implement after

string CodeVisitor::visit(StaticMethodCallExpression *exp) { return ""; } // TODO: Implement after
string CodeVisitor::visit(MethodCallExpression *exp) { return ""; }       // TODO: Implement after

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
//  return "";
// }

// // TODO: Declarar memória dinâmica no registro de ativação
// string CodeVisitor::visit(NewObjExpression *exp) {
//  return "";
// }

string CodeVisitor::visit(IdExpression *exp) {
    cout << TYPE << " _" << exp->getId() << " = " << RS_LOOKUP("\"" + exp->getId() + "\"")<< ";\n";
    return "_"+exp->getId();
}

// // TODO: Pegar referência para a classe em que o código está sendo executado (caso não seja um método estático)
// string CodeVisitor::visit(FieldAccessExpression *exp) {
//  return "";//RS_TOP + "getInstance()->query(\""+exp.getId()+"\")";
// }

// // TODO: Pegar referência para a classe em que o código está sendo executado (caso não seja um método estático)
// string CodeVisitor::visit(ThisExpression *exp) {
//  return ""; //"r.getInstance()->";
// }

string CodeVisitor::visit(ParenExpression *exp) {
    return exp->first->accept(*this);
}

// // TODO: Permitir adiocionar um array literal no registro de ativação
// string CodeVisitor::visit(LitArrayExpression *exp) {
//  return "";
// }

// // TODO: Decidir como acessar posições de um vetor
// string CodeVisitor::visit(ArrayAccessExpression *exp) {
//  return "";
// }

// // TODO: Decidir como declarar dinâmicamente um array
// string CodeVisitor::visit(NewArrayExpression *exp) {
//  return "";
// }