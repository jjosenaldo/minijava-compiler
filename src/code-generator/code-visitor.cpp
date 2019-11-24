#include <algorithm>
#include <deque>
#include <iostream>
#include "code-visitor.hpp"

#include "global.hpp"
#include "operator.hpp"

using std::to_string;
using std::cout;
using std::endl;


#define RS string("rs->")
#define RS_TOP string("rs->top()->")
#define RS_LOOKUP(x) string(RS_TOP+"lookupVarVal(" + x + ")")
#define TYPE string("Value*")
#define CREATERECORD(b_label, e_label, returnLabel) string(RS + "createRecord(" + b_label + "," + e_label + "," + returnLabel + ");")
#define POPRECORD string(RS + "pop();")
#define GOTO(label) "goto " + string(label)
#define IFNOT_GOTO(guard, label) string("if(!" + guard + "->getBool()) " + GOTO(label))
#define UPDATEVAR(lvalue, rvalue) string(RS_TOP + "update(\"" + lvalue + "\"," + rvalue + ")")
#define INSERTVAR(x,y) string("insertVar(\"" + x + "\"," + y + ");")

void CodeVisitor::resetCountTmpVars() {
    this->countTmpVars = 0;
}

string CodeVisitor::getNewTmpVar() {
    return "tmp" + to_string(this->countTmpVars++);
}

string CodeVisitor::getNewLabel() {
    return "l" + to_string(this->countLabels++);
}

string CodeVisitor::visit(Program *program) {
    // initMethodInfo
    initMethodsInfo(program);
    
    // Create a new record to main method
    string end_label = getNewLabel();
    cout << CREATERECORD("nullptr", "nullptr", "&&" + end_label) << endl;

    for(auto classdec : *program->declarations)
        classdec->accept(*this);

    cout << end_label << ":" << endl;

    // auto main_class = program->declarations->begin();
    // (**main_class).accept(*this);

    // for(auto it = ++(program->declarations->begin()); it != program->declarations->end(); it++)
    //     (**it).accept(*this);
    
    return "";
}

string CodeVisitor::visit(Method *method) {
    cout << "{\n";
    // Generate block code
    method->statement->accept(*this);

    // Get a temp var containing the label to last method call point
    string tmpReturn = getNewTmpVar();
    cout << "void* " << tmpReturn << " = " << RS_TOP << "getReturnLabel();\n";

    // Pop the record
    cout << POPRECORD << "\n";

    // Goto last method call point
    cout << GOTO("*" + tmpReturn) << ";\n";
    cout << "}\n";
    resetCountTmpVars();
    return "";
}

// TODO
string CodeVisitor::visit(ClassDeclaration *classdec) {
    for(auto &method : *(classdec->methods)) {
        cout << this->getMethodLabel(classdec->name, method->id) << ": ";
        method->accept(*this);
    }
    return "";
}

string CodeVisitor::visitClassDeclarationsFields(Program* program){
    for(auto decl : *(program->declarations))
        visitClassDeclarationFields(decl);
    return "";
}

string CodeVisitor::visitClassDeclarationFields(ClassDeclaration* classDec){
    cout << "struct " << classDec->name << " : ClassValue ";
    if(classDec->parent != "") cout << " , " << classDec->parent;
    cout << "{\n";

    // Generate constructor
    cout << classDec->name << "() : ClassValue( \"" << classDec->name << "\"){}\n";

    // Generate fields
    for(auto field : *(classDec->fields)){
        cout << typeToValueString(field->type) << "* " << field->name;

        // TODO: deal with fields that have initial value
        // if(field->initValue != nullptr) doSomething

        cout << ";\n";
    }
    cout << "};\n";

    return "";
}

// Statements
string CodeVisitor::visit(VarDec *vardec){
    cout << "{\n";
    string tmp = vardec->value->accept(*this);
    cout << RS_TOP + INSERTVAR(vardec->id, tmp) + "\n";
    cout << "}\n";
    resetCountTmpVars();
    return "";
}

string CodeVisitor::visit(Block *block) {
    cout << CREATERECORD("nullptr", "nullptr","nullptr") << "\n";
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
    cout << lab << ":;\n";
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

    cout << CREATERECORD("&&"+ lab1,"&&"+lab2,"nullptr") << "\n";

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
    cout << "cout << \"\\n TODO: Solve lvalue problem\\n\"\n";
    cout << "}\n";
    return "";
}

string CodeVisitor::visit(Continue *stmt) {
    string tmp = getNewTmpVar();
    cout << "void* " + tmp + " = rs->searchContinue(); \n";
    cout << GOTO("*" + tmp) << ";\n";
    return "";
}

string CodeVisitor::visit(Break *stmt) { return ""; }      // TODO: Implement after
string CodeVisitor::visit(Return *stmt) { return ""; }     // TODO: Implement after
string CodeVisitor::visit(Skip *stmt) { return ""; }       // TODO: Implement after

string CodeVisitor::visit(StaticMethodCallExpression *exp) {
    if(exp->className == "System"){
        if(exp->method == "print"){
            std::cout << "{\n";
            string argFirstVar =  exp->arguments->at(0)->accept(*this);
            std::cout << "cout << " << argFirstVar << "->toString() << endl;\n";
            std::cout << "}\n";
            resetCountTmpVars();
        }
    } else if(exp->className == "String"){
        string argFirstVar =  exp->arguments->at(0)->accept(*this);
        string tmp = getNewTmpVar();

        if(exp->method == "intToString" || exp->method == "booleanToString"){
            std::cout << TYPE << " " << tmp << " = new StringValue( " << argFirstVar << "->toString()" <<  ");\n";
            return tmp;
        }
    }
    return "";
}

string CodeVisitor::visit(MethodCallExpression *call) {
    // Get formal parameters' names

    // TODO: If you pass the subclass name here, it can solve the polimorphism problem
    string className = call->left->getType()->getClassName();
    vector<string> formal_params = this->getRealParams(className, call->method);
    
    // Get return label
    string end_label = getNewLabel();

    // Create a new record
    cout << "{\n" << CREATERECORD("nullptr","nullptr","&&" + end_label) << "\n";

    // Assign real parameters to formal parameters inserting then in the new record
    auto it = call->arguments->begin();
    for (auto &e : formal_params) {
        string tmpVar = (**(it++)).accept(*this);
        cout << RS_TOP << INSERTVAR(e, tmpVar) << endl;
    }

    string tmp_label = this->getMethodLabel(className, call->method);
    cout << GOTO(tmp_label) << ";\n";
    cout << "}\n";

    cout << end_label << ":\n";
    return "";
}

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

// TODO: implement the remaining atomic expressions (TypeNull is missing)
string CodeVisitor::visit(AtomExpression *exp) {
    string tmp = getNewTmpVar();

    if(exp->type->kind == TypeInt)
        cout << TYPE << " " << tmp << " = new IntValue(" << exp->val.intval << ");\n";
    else if(exp->type->kind == TypeBoolean)
        cout << TYPE << " " << tmp << " = new BoolValue(" << (exp->val.boolval ? "true" :  "false") << ");\n";
    else {
        string toBePrinted = "\"";
        int it = 0;
        while(exp->val.strval[it] != '\0'){
            if(exp->val.strval[it] == '\\')
                toBePrinted += "\\\\";
            else if(exp->val.strval[it] == '\n')
                toBePrinted += "\\n";
            else if(exp->val.strval[it] == '\t')
                toBePrinted += "\\t";
            else if(exp->val.strval[it] == '\"')
                toBePrinted += "\\\"";
            else
                toBePrinted += exp->val.strval[it];
            ++it;
        }

        toBePrinted += "\"";
        cout << TYPE << " " << tmp << " = new StringValue(" << toBePrinted << ");\n";
    }
    
    return tmp;
}

string CodeVisitor::visit(NewObjExpression *exp) {
    string tmp = getNewTmpVar();
    cout << TYPE << " " << tmp << " = new " << exp->getType()->toString() << "();\n";
    return tmp;
}

string CodeVisitor::visit(IdExpression *exp) {
    cout << TYPE << " _" << exp->getId() << " = " << RS_LOOKUP("\"" + exp->getId() + "\"")<< ";\n";
    return "_"+exp->getId();
}

// TODO: Pegar referência para a classe em que o código está sendo executado (caso não seja um método estático)
string CodeVisitor::visit(FieldAccessExpression *exp) {
    cout << "// FieldAccessExpression\n";
 return "";//RS_TOP + "getInstance()->query(\""+exp.getId()+"\")";
}

// TODO: Pegar referência para a classe em que o código está sendo executado (caso não seja um método estático)
string CodeVisitor::visit(ThisExpression *exp) {
    cout << "// ThisExpression\n";
 return ""; //"r.getInstance()->";
}

string CodeVisitor::visit(ParenExpression *exp) {
    return exp->first->accept(*this);
}


// TODO: literal multidimensional arrays
string CodeVisitor::visit(LitArrayExpression *exp) {
    string litArrTempVar = getNewTmpVar();
    string arrValTempVar = getNewTmpVar();
    int n = exp->expressions->size();

    cout << TYPE << "* " << litArrTempVar << " = new " << TYPE << "[" << n  << "];\n";

    for(int i = 0; i != n; ++i){
        string tmpExpVar = exp->expressions->at(i)->accept(*this);
        cout << litArrTempVar << "[" << i << "] = " << tmpExpVar << ";\n";
    }

    cout << TYPE << " " << arrValTempVar << " = new ArrayValue(" << litArrTempVar << "," << n << ");\n";
    return arrValTempVar;
}

// TODO: Decidir como acessar posições de um vetor
string CodeVisitor::visit(ArrayAccessExpression *exp) {
    auto lvalue = exp->left->accept(*this);
    string dimAccesses =  "";

    for(auto dim : *(exp->dimensions)){
        auto tmpVarDim = dim->accept(*this);
        dimAccesses += "[" + tmpVarDim + "->getInt()" + "]";
    }

    auto returnTmpVar = getNewTmpVar();
    cout << TYPE << " " << returnTmpVar << " = " << "(*" << lvalue << ")" << dimAccesses << ";\n";
    return returnTmpVar;
}

string CodeVisitor::visit(NewArrayExpression *exp) {
    auto n = exp->dimensions->size();
    auto varDimsName = getNewTmpVar();
    cout << "int* " << varDimsName << " = new int[" << n << "];\n";

    for(int i = 0; i < n; ++i){
        auto dimVarName = exp->dimensions->at(i)->accept(*this);
        cout << varDimsName << "[" << i << "] = " << dimVarName << "->getInt();\n";
    }

    string arrVarName = getNewTmpVar();

    cout << TYPE << " " << arrVarName << " = new ArrayValue(" << varDimsName << ","<<n << ",";
    switch(exp->baseType->kind){
        case TypeInt: cout << "EV_IntValue";break;
        case TypeBoolean: cout << "EV_BoolValue";break;
        case TypeClass:
            if(exp->baseType->toString() == "String") cout << "EV_StringValue";
            else /* TODO */;
            break;
    }

    cout << ");\n";
    return arrVarName;
}

// TODO: arrays
string typeToValueString(Type* t){
    BasicType* bt = dynamic_cast<BasicType*>(t);
    if(bt != nullptr){
        switch(bt->kind){
            case TypeInt: return "IntValue";
            case TypeBoolean: return "BoolValue";
            return "";
        }
    }

    ClassType* ct = dynamic_cast<ClassType*>(ct);
    if(ct != nullptr)
        return ct->getClassName();

    return "";
}