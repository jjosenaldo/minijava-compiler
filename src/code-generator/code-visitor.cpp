#include <algorithm>
#include <deque>
#include <iostream>

#include "code-visitor.hpp"
#include "global.hpp"
#include "operator.hpp"
#include "value.hpp"

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
    out << CREATERECORD("nullptr", "nullptr", "&&" + end_label, "nullptr", "nullptr") << endl;

    for (auto classdec : *program->declarations)
        classdec->accept(*this);

    out << end_label << ":" << endl;

    // auto main_class = program->declarations->begin();
    // (**main_class).accept(*this);

    // for(auto it = ++(program->declarations->begin()); it != program->declarations->end(); it++)
    //     (**it).accept(*this);

    return "";
}

string CodeVisitor::visit(Method *method)
{
    out << "{\n";
    // Generate block code
    method->statement->accept(*this);

    // Get a temp var containing the label to last method call point
    string tmpReturn = getNewTmpVar();
    out << "void* " << tmpReturn << " = " << RS_TOP << "getMethodCallPosLabel();\n";

    // Goto last method call point
    out << GOTO("*" + tmpReturn) << ";\n";
    out << "}\n";
    resetCountTmpVars();
    return "";
}

string CodeVisitor::visit(ClassDeclaration *classdec)
{
    for (auto &method : *(classdec->methods))
    {
        out << this->getMethodLabel(classdec->name, method->id) << ": ";
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
    out << "struct " << classDec->name << " : ClassValue ";
    out << "{\n";

    // Generate constructor
    out << classDec->name << "() : ClassValue( \"" << classDec->name << "\"){\ninitFields();\n}\n";

    // Generate initFields method
    out << "void initFields(){\n";
    for (auto field : *(classDec->fields))
    {
        if (field->initValue != nullptr)
        {
            auto initVal = field->initValue->accept(*this);
            out << "fields->emplace(\"" << field->name << "\"," << initVal << ");\n";
        }
        else
            out << "fields->emplace(\"" << field->name << "\", new " << typeToValueString(field->type) << ");\n";
    }
    out << "\n}\n";

    // Generate newObj method
    out << "static Value* new" << classDec->name << "(){\n";
    out << classDec->name << "* c = new " << classDec->name << "();\n";
    out << "c->initFields();\nreturn c;\n}\n";

    out << "};\n";

    return "";
}

// Statements
string CodeVisitor::visit(VarDec *vardec)
{
    out << "{\n";
    string tmp;

    if (vardec->value != nullptr)
    {
        tmp = vardec->value->accept(*this);
    }
    else
        tmp = "new " + typeToValueString(vardec->type);

    out << RS_TOP + INSERTVAR(vardec->id, tmp) + "\n";
    out << "}\n";
    resetCountTmpVars();

    return "";
}

string CodeVisitor::visit(Block *block)
{
    out << CREATERECORD("nullptr", "nullptr", "nullptr", CURRENT_OBJ, "nullptr") << "\n";
    for (auto &e : *(block->statements))
        e->accept(*this);
    out << POPRECORD << "\n";

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

    out << "{\n";
    string lab = getNewLabel();

    // Solve guard
    string tmp_guard = elselessIf->guard->accept(*this);

    // Test guard
    out << IFNOT_GOTO(tmp_guard, lab) << ";\n";

    // Visit statement
    out << "{ \n";
    elselessIf->statement->accept(*this);
    out << "} \n";
    out << "} \n";

    // End if
    out << lab << ":;\n";

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

    out << "{\n";
    // Solve guard
    string tmp_guard = ifElse->guard->accept(*this);

    // Test guard
    out << IFNOT_GOTO(tmp_guard, lab1) << ";\n";

    // Visit first statement
    out << "{ \n";
    ifElse->statementIf->accept(*this);
    out << "} \n";

    // Goto second label
    out << GOTO(lab2) << ";\n";

    // Begin else
    out << "{ \n";
    out << lab1 + ":\n";

    // Visit second statement
    ifElse->statementElse->accept(*this);

    out << "} \n";
    out << "} \n";
    out << lab2 + ":;\n";

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

    out << CREATERECORD("&&" + lab1, "&&" + lab2, "nullptr", CURRENT_OBJ, "nullptr") << "\n";

    out << "{\n";
    out << lab1 << ":\n";

    // Solve guard
    string tmp_guard = whilestmt->guard->accept(*this);

    // Test guard
    out << IFNOT_GOTO(tmp_guard, lab2) << ";\n";

    // Visit statement
    whilestmt->statement->accept(*this);

    // Goto begin while
    out << GOTO(lab1) << ";\n";

    out << "}\n";

    out << lab2 << ":;\n";

    out << POPRECORD << "\n";

    return "";
}

// Assignments allowed:
//     a = <exp>
//     a[i_1]...[i_n] = <exp>
//     this.a = <exp>
string CodeVisitor::visit(Assignment *assign)
{
    // a = <exp>
    out << "{\n";
    string tmp_rvalue = assign->rvalue->accept(*this);

    IdExpression *ie = dynamic_cast<IdExpression *>(assign->lvalue);
    if (ie != nullptr)
        out << UPDATE_STATIC(ie->id, tmp_rvalue) << "\n";
    else
    {
        FieldAccessExpression *fae = dynamic_cast<FieldAccessExpression *>(assign->lvalue);
        if (fae != nullptr)
            out << UPDATE_CURRENT_OBJ_FIELD("\"" + fae->id + "\"", tmp_rvalue) << "\n";
        else
        {
            ArrayAccessExpression *aae = dynamic_cast<ArrayAccessExpression *>(assign->lvalue);
            auto tmpDimsVar = getNewTmpVar();
            out << "int* " << tmpDimsVar << " = new int[" << aae->dimensions->size() << "];\n";

            for (int i = 0; i < aae->dimensions->size(); ++i)
            {
                auto tmpDimVar = ((*(aae->dimensions))[i])->accept(*this);
                out << tmpDimsVar << "[" << i << "] = " << tmpDimVar << "->getInt();\n";
            }

            auto tmpArr = getNewTmpVar();
            auto tmpLvalue = aae->left->accept(*this);
            out << "ArrayValue* " << tmpArr << " = dynamic_cast<ArrayValue*>(" << tmpLvalue << ");\n";
            out << tmpArr << "->setAt(" << tmpDimsVar << "," << aae->dimensions->size() << "," << tmp_rvalue << ");\n";
        }
    }

    out << "}\n";
    return "";
}

string CodeVisitor::visit(Continue *stmt)
{
    string tmp = getNewTmpVar();
    out << "void* " + tmp + " = rs->searchContinue(); \n";
    out << GOTO("*" + tmp) << ";\n";
    return "";
}

string CodeVisitor::visit(Break *stmt)
{
    string tmp = getNewTmpVar();
    out << "void* " + tmp + " = rs->searchBreak(); \n";
    out << GOTO("*" + tmp) << ";\n";
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
        out << "void* " + methodCallLabel + " = rs->searchMethodCallLabel(); \n";
        out << "rs->top()->setReturnValue(" + tmp_exp + "); \n";
    }
    else
        out << "void* " + methodCallLabel + " = rs->searchMethodCallLabel(); \n";

    out << GOTO("*" + methodCallLabel) << ";\n";
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
            out << "{\n";
            string argFirstVar = exp->arguments->at(0)->accept(*this);
            out << "cout << " << argFirstVar << "->toString();\n";
            out << "}\n";
            resetCountTmpVars();
        }
    }
    else if (exp->className == "String")
    {
        string argFirstVar = exp->arguments->at(0)->accept(*this);
        string tmp = getNewTmpVar();

        if (exp->method == "intToString" || exp->method == "booleanToString")
        {
            out << TYPE << " " << tmp << " = new StringValue( " << argFirstVar << "->toString()"
                 << ");\n";
            return tmp;
        }
    }
    return "";
}

// TODO: implement the predefined nonstatic methods (namely: <array>.length(), <string>.length() and <string>.substring())
string CodeVisitor::visit(MethodCallExpression *call)
{
    // Processes the "lvalue"
    string tmpLvalueVarName = call->left->accept(*this);

    // Return tmp variable
    string tmpReturn = getNewTmpVar();

    // <array>.length()
    if(call->left->getType()->kind == TypeArray && call->method == "length"){
        out << TYPE << " " << tmpReturn << " = new IntValue(dynamic_cast<ArrayValue*>(" <<  tmpLvalueVarName << ")->getN());\n";
        return tmpReturn;
    }

    out << "{\n";
    // Get formal parameters' names

    // TODO: If you pass the subclass name here, it can solve the polimorphism problem
    string className = call->left->getType()->getClassName();
    vector<string> formal_params = this->getRealParams(className, call->method);

    // Get return label
    string end_label = getNewLabel();

    

    // Checks if the lvalue is a null thing
    out << "if(dynamic_cast<NullValue*>(" << tmpLvalueVarName << ") != nullptr){\n";
    out << "std::cerr << \"ERROR: you cannot call a method on a null object!\\n\";\nexit(0);";
    out << "\n}\n";

    // Process the parameters
    string paramListVarName = getNewLabel();
    out << "Value** " << paramListVarName << " = new Value*[" << formal_params.size()  << "];\n";

    auto it = call->arguments->begin();
    int cont = 0;
    for (auto &e : formal_params){
        string tmpVar = (**(it++)).accept(*this);
        out << paramListVarName << "[" << (cont++) << "] = " << tmpVar << ";\n"; 
    }

    // Creates a new record
    out << "{\n" << CREATERECORD_CAST_OBJ("nullptr", "nullptr", "&&" + end_label, tmpLvalueVarName, "nullptr") << "\n";

    // Inserts the params in the record
    for(int i = 0; i < formal_params.size(); ++i)
        out << RS_TOP << "insertVar(\"" << formal_params[i] << "\"," << paramListVarName << "[" << i << "]);\n";

    string tmp_label = this->getMethodLabel(className, call->method);
    out << GOTO(tmp_label) << ";\n";
    out << "}\n";

    out << "}\n";
    out << end_label << ":\n";
    
    out << TYPE << " " << tmpReturn << " = rs->top()->getReturnValue();\n";
    // Pop the record
    out << POPRECORD << "\n";

    return tmpReturn;
}

string CodeVisitor::visit(BinExpression *exp)
{
    string tmp1 = exp->first->accept(*this);
    string tmp2 = exp->second->accept(*this);

    string tmp = getNewTmpVar();
    out << TYPE << " " << tmp << " = *" << tmp1 << " " << binOpSymbol(exp->getOp()) << " *" << tmp2 << ";\n";
    return tmp;
}

string CodeVisitor::visit(UnExpression *exp)
{
    string tmp1 = exp->first->accept(*this);

    string tmp = getNewTmpVar();
    out << TYPE << " " << tmp << " = " << unOpSymbol(exp->op) << " *" << tmp1 << ";\n";
    return tmp;
}

// TODO: implement TypeNull
string CodeVisitor::visit(AtomExpression *exp)
{
    string tmp = getNewTmpVar();

    if (exp->type->kind == TypeInt)
        out << TYPE << " " << tmp << " = new IntValue(" << exp->val.intval << ");\n";
    else if (exp->type->kind == TypeBoolean)
        out << TYPE << " " << tmp << " = new BoolValue(" << (exp->val.boolval ? "true" : "false") << ");\n";
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
        out << TYPE << " " << tmp << " = new StringValue(" << toBePrinted << ");\n";
    }

    return tmp;
}

string CodeVisitor::visit(NewObjExpression *exp)
{
    string tmp = getNewTmpVar();
    out << TYPE << " " << tmp << " = new " << exp->getType()->toString() << "();\n";
    return tmp;
}

string CodeVisitor::visit(IdExpression *exp)
{
    auto tmpVar = getNewTmpVar();
    // out << TYPE << " _" << exp->getId() << " = " << LOOKUP_STATIC("\"" + exp->getId() + "\"")<< ";\n";
    out << TYPE << " " << tmpVar << " = " << LOOKUP_STATIC("\"" + exp->getId() + "\"") << ";\n";
    return tmpVar;
}

string CodeVisitor::visit(FieldAccessExpression *exp)
{
    auto tmp = getNewTmpVar();
    out << TYPE << " " << tmp << " = " << CURRENT_OBJ << "->get(\"" << exp->id << "\");\n";
    return tmp;
}

string CodeVisitor::visit(ThisExpression *exp)
{
    auto tmpVar = getNewTmpVar();
    out << TYPE << " " << tmpVar << " = " << CURRENT_OBJ << ";\n";
    return tmpVar;
}

string CodeVisitor::visit(ParenExpression *exp)
{
    return exp->first->accept(*this);
}

// TODO: literal multidimensional arrays (see file: multidimensional-array.mjv)
string CodeVisitor::visit(LitArrayExpression *exp)
{
    string litArrTempVar = getNewTmpVar();
    string arrValTempVar = getNewTmpVar();
    int n = exp->expressions->size();

    out << TYPE << "* " << litArrTempVar << " = new " << TYPE << "[" << n << "];\n";

    for (int i = 0; i != n; ++i)
    {
        string tmpExpVar = exp->expressions->at(i)->accept(*this);
        out << litArrTempVar << "[" << i << "] = " << tmpExpVar << ";\n";
    }

    out << TYPE << " " << arrValTempVar << " = new ArrayValue(" << litArrTempVar << "," << n << ");\n";
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
    out << TYPE << " " << returnTmpVar << " = " << dimAccesses << ";\n";
    return returnTmpVar;
}

string CodeVisitor::visit(NewArrayExpression *exp)
{
    auto n = exp->dimensions->size();
    auto varDimsName = getNewTmpVar();
    out << "int* " << varDimsName << " = new int[" << n << "];\n";

    for (int i = 0; i < n; ++i)
    {
        auto dimVarName = exp->dimensions->at(i)->accept(*this);
        out << varDimsName << "[" << i << "] = " << dimVarName << "->getInt();\n";
    }

    string arrVarName = getNewTmpVar();

    out << TYPE << " " << arrVarName << " = new ArrayValue(" << varDimsName << "," << n << ",";
    switch (exp->baseType->kind)
    {
    case TypeInt:
        out << "IntValue::newInt";
        break;
    case TypeBoolean:
        out << "BoolValue::newBool";
        break;
    case TypeClass:
        if (exp->baseType->toString() == "String")
            out << "StringValue::newString";
        else
            out << exp->baseType->toString() << "::new" << exp->baseType->toString();
        break;
    }

    out << ");\n";
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