#include <algorithm>
#include <deque>
#include <iostream>

#include "code-visitor.hpp"
#include "global.hpp"
#include "operator.hpp"
#include "value.hpp"

using std::cout;
using std::endl;
using std::to_string;

#define RS string("rs->")
#define RS_TOP string("rs->top()->")
#define LOOKUP_DYN(x) string(RS_TOP + "lookupDynamic(" + x + ")")
#define LOOKUP_STATIC(x) string(RS_TOP + "lookupStatic(" + x + ")")
#define LOOKUP_STATIC_REFERENCE(x) string(RS_TOP + "lookupStaticReference(" + x + ")")
#define TYPE string("Value*")
#define CREATERECORD(b_label, e_label, returnLabel, currentObject, returnVal) \
    string(RS + "createRecord(" + b_label + "," + e_label + "," + returnLabel + "," + currentObject + "," + returnVal ");")
#define CREATERECORD_CAST_OBJ(b_label, e_label, returnLabel, currentObject, returnVal) \
    string(RS + "createRecord(" + b_label + "," + e_label + "," + returnLabel + ",dynamic_cast<ClassValue*>(" + currentObject + ")," + returnVal + ");")
#define POPRECORD string(RS + "pop();")
#define GOTO(label) "goto " + string(label)
#define IFNOT_GOTO(guard, label) string("if(!" + guard + "->getBool()) " + GOTO(label))
#define UPDATE_STATIC(lvalue, rvalue) string(RS_TOP + "updateStatic(\"" + lvalue + "\"," + rvalue + ");")
#define INSERTVAR(x, y) string("insertVar(\"" + x + "\"," + y + ");")
#define CURRENT_OBJ string(RS_TOP + "getCurrentObject()")
#define UPDATE_CURRENT_OBJ_FIELD(field, rvalue) \
    string(CURRENT_OBJ + "->set(" + field + ", " + rvalue + ");")

void CodeVisitor::resetCountTmpVars()
{
    this->countTmpVars = 0;
}

string CodeVisitor::getNewTmpVar()
{
    return "tmp" + to_string(this->countTmpVars++);
}

string CodeVisitor::getNewLabel()
{
    return "l" + to_string(this->countLabels++);
}

string CodeVisitor::visit(Program *program)
{
    // initMethodInfo
    initMethodsInfo(program);

    // Create a new record to main method
    string end_label = getNewLabel();
    cout << CREATERECORD("nullptr", "nullptr", "&&" + end_label, "nullptr", "nullptr") << endl;

    for (auto classdec : *program->declarations)
        classdec->accept(*this);

    cout << end_label << ":" << endl;

    // auto main_class = program->declarations->begin();
    // (**main_class).accept(*this);

    // for(auto it = ++(program->declarations->begin()); it != program->declarations->end(); it++)
    //     (**it).accept(*this);

    return "";
}

string CodeVisitor::visit(Method *method)
{
    cout << "{\n";
    // Generate block code
    method->statement->accept(*this);

    // Get a temp var containing the label to last method call point
    string tmpReturn = getNewTmpVar();
    cout << "void* " << tmpReturn << " = " << RS_TOP << "getMethodCallPosLabel();\n";

    // Goto last method call point
    cout << GOTO("*" + tmpReturn) << ";\n";
    cout << "}\n";
    resetCountTmpVars();
    return "";
}

string CodeVisitor::visit(ClassDeclaration *classdec)
{
    for (auto &method : *(classdec->methods))
    {
        cout << this->getMethodLabel(classdec->name, method->id) << ": ";
        method->accept(*this);
    }
    return "";
}

string CodeVisitor::visitClassDeclarationsFields(Program *program)
{
    for (auto decl : *(program->declarations))
        visitClassDeclarationFields(decl);
    return "";
}

// TODO: implement inheritance
// TODO: do not create methods for the Main class at all
string CodeVisitor::visitClassDeclarationFields(ClassDeclaration *classDec)
{
    cout << "struct " << classDec->name << " : ClassValue ";
    cout << "{\n";

    // Generate constructor
    cout << classDec->name << "() : ClassValue( \"" << classDec->name << "\"){\ninitFields();\n}\n";

    // Generate initFields method
    cout << "void initFields(){\n";
    for (auto field : *(classDec->fields))
    {
        if (field->initValue != nullptr)
        {
            auto initVal = field->initValue->accept(*this);
            cout << "fields->emplace(\"" << field->name << "\"," << initVal << ");\n";
        }
        else
            cout << "fields->emplace(\"" << field->name << "\", new " << typeToValueString(field->type) << ");\n";
    }
    cout << "\n}\n";

    // Generate newObj method
    cout << "static Value* new" << classDec->name << "(){\n";
    cout << classDec->name << "* c = new " << classDec->name << "();\n";
    cout << "c->initFields();\nreturn c;\n}\n";

    cout << "};\n";

    return "";
}

// Statements
string CodeVisitor::visit(VarDec *vardec)
{
    cout << "{\n";
    string tmp;

    if (vardec->value != nullptr)
    {
        tmp = vardec->value->accept(*this);
    }
    else
        tmp = "new " + typeToValueString(vardec->type);

    cout << RS_TOP + INSERTVAR(vardec->id, tmp) + "\n";
    cout << "}\n";
    resetCountTmpVars();

    return "";
}

string CodeVisitor::visit(Block *block)
{
    cout << CREATERECORD("nullptr", "nullptr", "nullptr", CURRENT_OBJ, "nullptr") << "\n";
    for (auto &e : *(block->statements))
        e->accept(*this);
    cout << POPRECORD << "\n";

    return "";
}

string CodeVisitor::visit(ElselessIf *elselessIf)
{
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
    cout << "{ \n";
    elselessIf->statement->accept(*this);
    cout << "} \n";
    cout << "} \n";

    // End if
    cout << lab << ":;\n";

    return "";
}

string CodeVisitor::visit(IfElse *ifElse)
{
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
    cout << "{ \n";
    ifElse->statementIf->accept(*this);
    cout << "} \n";

    // Goto second label
    cout << GOTO(lab2) << ";\n";

    // Begin else
    cout << "{ \n";
    cout << lab1 + ":\n";

    // Visit second statement
    ifElse->statementElse->accept(*this);

    cout << "} \n";
    cout << "} \n";
    cout << lab2 + ":;\n";

    return "";
}

string CodeVisitor::visit(While *whilestmt)
{
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

    cout << CREATERECORD("&&" + lab1, "&&" + lab2, "nullptr", CURRENT_OBJ, "nullptr") << "\n";

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

    cout << "}\n";

    cout << lab2 << ":;\n";

    cout << POPRECORD << "\n";

    return "";
}

// Assignments allowed:
//     a = <exp>
//     a[i_1]...[i_n] = <exp>
//     this.a = <exp>
string CodeVisitor::visit(Assignment *assign)
{
    // a = <exp>
    cout << "{\n";
    string tmp_rvalue = assign->rvalue->accept(*this);

    IdExpression *ie = dynamic_cast<IdExpression *>(assign->lvalue);
    if (ie != nullptr)
        cout << UPDATE_STATIC(ie->id, tmp_rvalue) << "\n";
    else
    {
        FieldAccessExpression *fae = dynamic_cast<FieldAccessExpression *>(assign->lvalue);
        if (fae != nullptr)
            cout << UPDATE_CURRENT_OBJ_FIELD("\"" + fae->id + "\"", tmp_rvalue) << "\n";
        else
        {
            ArrayAccessExpression *aae = dynamic_cast<ArrayAccessExpression *>(assign->lvalue);
            auto tmpDimsVar = getNewTmpVar();
            cout << "int* " << tmpDimsVar << " = new int[" << aae->dimensions->size() << "];\n";

            for (int i = 0; i < aae->dimensions->size(); ++i)
            {
                auto tmpDimVar = ((*(aae->dimensions))[i])->accept(*this);
                cout << tmpDimsVar << "[" << i << "] = " << tmpDimVar << "->getInt();\n";
            }

            auto tmpArr = getNewTmpVar();
            auto tmpLvalue = aae->left->accept(*this);
            cout << "ArrayValue* " << tmpArr << " = dynamic_cast<ArrayValue*>(" << tmpLvalue << ");\n";
            cout << tmpArr << "->setAt(" << tmpDimsVar << "," << aae->dimensions->size() << "," << tmp_rvalue << ");\n";
        }
    }

    cout << "}\n";
    return "";
}

string CodeVisitor::visit(Continue *stmt)
{
    string tmp = getNewTmpVar();
    cout << "void* " + tmp + " = rs->searchContinue(); \n";
    cout << GOTO("*" + tmp) << ";\n";
    return "";
}

string CodeVisitor::visit(Break *stmt)
{
    string tmp = getNewTmpVar();
    cout << "void* " + tmp + " = rs->searchBreak(); \n";
    cout << GOTO("*" + tmp) << ";\n";
    return "";
}

string CodeVisitor::visit(Return *stmt)
{
    string methodCallLabel = getNewTmpVar();
    string varValueAdress = getNewTmpVar();
    string tmp_exp;

    //solve exp
    if (stmt->optExp != nullptr)
    {
        tmp_exp = stmt->optExp->accept(*this);
        cout << "void* " + methodCallLabel + " = rs->searchMethodCallLabel(); \n";
        cout << "rs->top()->setReturnValue(" + tmp_exp + "); \n";
    }
    else
        cout << "void* " + methodCallLabel + " = rs->searchMethodCallLabel(); \n";

    cout << GOTO("*" + methodCallLabel) << ";\n";
    return "";
}

string CodeVisitor::visit(Skip *stmt)
{
    return "";
}

string CodeVisitor::visit(StaticMethodCallExpression *exp)
{
    if (exp->className == "System")
    {
        if (exp->method == "print")
        {
            cout << "{\n";
            string argFirstVar = exp->arguments->at(0)->accept(*this);
            cout << "cout << " << argFirstVar << "->toString();\n";
            cout << "}\n";
            resetCountTmpVars();
        }
    }
    else if (exp->className == "String")
    {
        string argFirstVar = exp->arguments->at(0)->accept(*this);
        string tmp = getNewTmpVar();

        if (exp->method == "intToString" || exp->method == "booleanToString")
        {
            cout << TYPE << " " << tmp << " = new StringValue( " << argFirstVar << "->toString()"
                 << ");\n";
            return tmp;
        }
    }
    return "";
}

// TODO: implement the predefined nonstatic methods (such as <array>.length() and <string>.substring())
string CodeVisitor::visit(MethodCallExpression *call)
{
    cout << "{\n";
    // Get formal parameters' names

    // TODO: If you pass the subclass name here, it can solve the polimorphism problem
    string className = call->left->getType()->getClassName();
    vector<string> formal_params = this->getRealParams(className, call->method);

    // Get return label
    string end_label = getNewLabel();

    // Processes the "lvalue"
    string tmpLvalueVarName = call->left->accept(*this);

    // Checks if the lvalue is a null thing
    cout << "if(dynamic_cast<NullValue*>(" << tmpLvalueVarName << ") != nullptr){\n";
    cout << "std::cerr << \"ERROR: you cannot call a method on a null object!\\n\";\nexit(0);";
    cout << "\n}\n";

    // Process the parameters
    string paramListVarName = getNewLabel();
    cout << "Value** " << paramListVarName << " = new Value*[" << formal_params.size()  << "];\n";

    auto it = call->arguments->begin();
    int cont = 0;
    for (auto &e : formal_params){
        string tmpVar = (**(it++)).accept(*this);
        cout << paramListVarName << "[" << (cont++) << "] = " << tmpVar << ";\n"; 
    }

    // Creates a new record
    cout << "{\n" << CREATERECORD_CAST_OBJ("nullptr", "nullptr", "&&" + end_label, tmpLvalueVarName, "nullptr") << "\n";

    // Inserts the params in the record
    for(int i = 0; i < formal_params.size(); ++i)
        cout << RS_TOP << "insertVar(\"" << formal_params[i] << "\"," << paramListVarName << "[" << i << "]);\n";

    string tmp_label = this->getMethodLabel(className, call->method);
    cout << GOTO(tmp_label) << ";\n";
    cout << "}\n";

    cout << "}\n";
    cout << end_label << ":\n";
    string tmpReturn = getNewTmpVar();
    cout << TYPE << " " << tmpReturn << " = rs->top()->getReturnValue();\n";
    // Pop the record
    cout << POPRECORD << "\n";

    return tmpReturn;
}

string CodeVisitor::visit(BinExpression *exp)
{
    string tmp1 = exp->first->accept(*this);
    string tmp2 = exp->second->accept(*this);

    string tmp = getNewTmpVar();
    cout << TYPE << " " << tmp << " = *" << tmp1 << " " << binOpSymbol(exp->getOp()) << " *" << tmp2 << ";\n";
    return tmp;
}

string CodeVisitor::visit(UnExpression *exp)
{
    string tmp1 = exp->first->accept(*this);

    string tmp = getNewTmpVar();
    cout << TYPE << " " << tmp << " = " << unOpSymbol(exp->op) << " *" << tmp1 << ";\n";
    return tmp;
}

// TODO: implement TypeNull
string CodeVisitor::visit(AtomExpression *exp)
{
    string tmp = getNewTmpVar();

    if (exp->type->kind == TypeInt)
        cout << TYPE << " " << tmp << " = new IntValue(" << exp->val.intval << ");\n";
    else if (exp->type->kind == TypeBoolean)
        cout << TYPE << " " << tmp << " = new BoolValue(" << (exp->val.boolval ? "true" : "false") << ");\n";
    else
    {
        string toBePrinted = "\"";
        int it = 0;
        while (exp->val.strval[it] != '\0')
        {
            if (exp->val.strval[it] == '\\')
                toBePrinted += "\\\\";
            else if (exp->val.strval[it] == '\n')
                toBePrinted += "\\n";
            else if (exp->val.strval[it] == '\t')
                toBePrinted += "\\t";
            else if (exp->val.strval[it] == '\"')
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

string CodeVisitor::visit(NewObjExpression *exp)
{
    string tmp = getNewTmpVar();
    cout << TYPE << " " << tmp << " = new " << exp->getType()->toString() << "();\n";
    return tmp;
}

string CodeVisitor::visit(IdExpression *exp)
{
    auto tmpVar = getNewTmpVar();
    // cout << TYPE << " _" << exp->getId() << " = " << LOOKUP_STATIC("\"" + exp->getId() + "\"")<< ";\n";
    cout << TYPE << " " << tmpVar << " = " << LOOKUP_STATIC("\"" + exp->getId() + "\"") << ";\n";
    return tmpVar;
}

string CodeVisitor::visit(FieldAccessExpression *exp)
{
    auto tmp = getNewTmpVar();
    cout << TYPE << " " << tmp << " = " << CURRENT_OBJ << "->get(\"" << exp->id << "\");\n";
    return tmp;
}

// TODO: Pegar referência para a classe em que o código está sendo executado (caso não seja um método estático)
string CodeVisitor::visit(ThisExpression *exp)
{
    auto tmpVar = getNewTmpVar();
    cout << TYPE << " " << tmpVar << " = " << CURRENT_OBJ << ";\n";
    return tmpVar;
}

string CodeVisitor::visit(ParenExpression *exp)
{
    return exp->first->accept(*this);
}

// TODO: literal multidimensional arrays
string CodeVisitor::visit(LitArrayExpression *exp)
{
    string litArrTempVar = getNewTmpVar();
    string arrValTempVar = getNewTmpVar();
    int n = exp->expressions->size();

    cout << TYPE << "* " << litArrTempVar << " = new " << TYPE << "[" << n << "];\n";

    for (int i = 0; i != n; ++i)
    {
        string tmpExpVar = exp->expressions->at(i)->accept(*this);
        cout << litArrTempVar << "[" << i << "] = " << tmpExpVar << ";\n";
    }

    cout << TYPE << " " << arrValTempVar << " = new ArrayValue(" << litArrTempVar << "," << n << ");\n";
    return arrValTempVar;
}

string CodeVisitor::visit(ArrayAccessExpression *exp)
{
    string dimAccesses = exp->left->accept(*this);

    for (auto dim : *(exp->dimensions))
    {
        auto tmpVarDim = dim->accept(*this);
        dimAccesses = "(*" + dimAccesses + ")" + "[" + tmpVarDim + "->getInt()" + "]";
    }

    auto returnTmpVar = getNewTmpVar();
    cout << TYPE << " " << returnTmpVar << " = " << dimAccesses << ";\n";
    return returnTmpVar;
}

string CodeVisitor::visit(NewArrayExpression *exp)
{
    auto n = exp->dimensions->size();
    auto varDimsName = getNewTmpVar();
    cout << "int* " << varDimsName << " = new int[" << n << "];\n";

    for (int i = 0; i < n; ++i)
    {
        auto dimVarName = exp->dimensions->at(i)->accept(*this);
        cout << varDimsName << "[" << i << "] = " << dimVarName << "->getInt();\n";
    }

    string arrVarName = getNewTmpVar();

    cout << TYPE << " " << arrVarName << " = new ArrayValue(" << varDimsName << "," << n << ",";
    switch (exp->baseType->kind)
    {
    case TypeInt:
        cout << "IntValue::newInt";
        break;
    case TypeBoolean:
        cout << "BoolValue::newBool";
        break;
    case TypeClass:
        if (exp->baseType->toString() == "String")
            cout << "StringValue::newString";
        else
            cout << exp->baseType->toString() << "::new" << exp->baseType->toString();
        break;
    }

    cout << ");\n";
    return arrVarName;
}

string typeToValueString(Type *t)
{
    BasicType *bt = dynamic_cast<BasicType *>(t);
    if (bt != nullptr)
    {
        switch (bt->kind)
        {
        case TypeInt:
            return "IntValue";
        case TypeBoolean:
            return "BoolValue";
        case TypeNull:
            return "NullValue";
            return "";
        }
    }

    ClassType *ct = dynamic_cast<ClassType *>(t);
    if (ct != nullptr)
    {
        if (ct->getClassName() == "String")
            return "StringValue";
        else
            return "NullValue";
    }

    ArrayType *at = dynamic_cast<ArrayType *>(t);
    if (at != nullptr)
        return "NullValue";

    return "";
}