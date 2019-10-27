#include <iostream>
#include "ast.hpp"
#include "error.hpp"
#include "global.hpp"

using std::cout;
using std::endl;

Program::Program(deque<ClassDeclaration*>* decls){
    if(decls != nullptr)
        this->declarations = decls;
    else
        this->declarations = new deque<ClassDeclaration*>;
}

void Program::print(){
    for(auto decl : *this->declarations){
        decl->print();
        cout << endl;
    }
}

void Program::addClassDecl(ClassDeclaration* decl){
    this->declarations->push_back(decl);
}

void Program::addClassDeclAtFront(ClassDeclaration* decl){
    this->declarations->push_front(decl);
}

deque<ClassDeclaration*>* Program::getDecls(){
    return declarations;
}

ClassDeclaration* Program::getClassDecl(string className){
    for(auto decl : *declarations)
        if(decl->getName() == className)
            return decl;
    return nullptr;
}

Parameter::Parameter(Type* type, string name){
    this->type = type;
    this->name = name;
}

void Parameter::print(){
    printType(this->type);
    cout << " " << name;
}

Type* Parameter::getType(){
    return type;
}

bool Parameter::process(Symtable* parent, ClassSymtablePool* pool) {
    if(!canBeInstantiated(type, pool))
        return false;

    if(predefinedId(name) || pool->get(name) != nullptr){
        classAsVariableNameError(name);
        return false;
    }

    if(parent->get(name).tag != TCNOCONTENT) {
        multipleVariableError(name);
        return false;
    }

    parent->insert(name, tableContentFromType(type));

    return true;
}

string Parameter::getName(){
    return name;
}

Method::Method(string id, Type* returnType, Block* stmt) : Method(id, returnType, new deque<Parameter*>(), stmt){}

Method::Method(string id, Type* returnType, deque<Parameter*>* parameters, Block* stmt){
    this->id = id;
    this->returnType = returnType;
    this->statement = stmt;
    this->parameters = parameters;
}

string Method::getId(){
    return this->id;
}

Type* Method::getReturnType(){
    return this->returnType;
}

MethodType* Method::getType(){
    auto header = new vector<Type*>;
    header->push_back(returnType);

    if(parameters != nullptr) for(auto param : *parameters) header->push_back(param->getType());

    return new MethodType(header);
}

deque<Parameter*>* Method::getParameters(){
    return this->parameters;
}

Block* Method::getStatement(){
    return this->statement;
}

void Method::print(){
    printType(this->returnType);
    cout << " " << id << "(";

    if(this->parameters != nullptr){
        for(auto param : *this->parameters){
            param->print();
            cout << ", ";
        }
    }

    cout << ") ";

    if(this->statement != nullptr)
        this->statement->print();
    else
        cout << "{ }";
}

void Method::addParam(Parameter* param){
    this->parameters->push_back(param);
}

bool Method::processHeader(string className, ClassSymtable* root, ClassSymtablePool* pool){
    string methodName = id;

    if(pool->get(methodName) != nullptr || g_defaultSymbolHandler.isDefaultClass(methodName)){
        classAsMethodNameError(methodName);
        return false;
    }

    if(root->get(methodName).tag != TCNOCONTENT){
        multipleMethodError(className, methodName);
        return false;
    }

    if(returnType->kind == TypeClass & pool->get(returnType->getClassName()) == nullptr){
        classNotDefinedError(returnType->getClassName());
        return false;
    }

    // Adds the method name
    TableContent tcMethodType;
    tcMethodType.tag = TCTYPE;
    tcMethodType.type = this->getType();
    root->insert(methodName, tcMethodType);

    Symtable* methodTable = new Symtable(className, root);

    // Adds the method params
    auto params = parameters;
    if(params != nullptr)
        for(auto param : *params){
            if(methodTable->get(param->getName()).tag != TCNOCONTENT){
                multiplyDefinedParamError(param->getName(), methodName, className);
                delete methodTable;
                return false;
            }

            if(!param->process(methodTable, pool))
                return false;
        }

    root->insertMethodTable(methodName, methodTable);
    return true;
}

Field::Field(Type* type, string name, Expression* initValue){
    this->type = type;
    this->name = name;
    this->initValue = initValue;
}

string Field::getName(){
    return name;
}

Type* Field::getType(){
    return type;
}

void Field::print(){
    printType(this->type);
    cout << " " << this->name;

    if(this->initValue != nullptr){
        cout << " = ";
        this->initValue->print();
    }

    cout << ";";
}

bool Field::process(string className, ClassSymtable* root, ClassSymtablePool* pool){
    if(root->get(name).tag != TCNOCONTENT){
        multiplyDefinedFieldError(name, className);
        return false;
    }

    if(pool->get(name) != nullptr || g_defaultSymbolHandler.isDefaultClass(name)){
        classAsFieldNameError(name);
        return false;
    }

    if(this->initValue != nullptr){
        if(!this->initValue->process(root, pool))
            return false;

            if(!areCompatibleTypes(type, this->initValue->getType())){
                attributeInitValueTypeError(name, type->toString(), this->initValue->getType()->toString());
                return false;
            }
    }
    
    TableContent tc;
    tc.tag = TCTYPE;
    tc.type = type;
    root->insert(name, tc);

    return true;
}

ClassDeclaration::ClassDeclaration(string name) : ClassDeclaration(name, "") {}

ClassDeclaration::ClassDeclaration(string name, string parent){
    this->name = name;
    this->parent = parent;
    this->methods = new vector<Method*>;
    this->fields = new vector<Field*>;
}

void ClassDeclaration::print(){
    cout << "class " << this->name << " {" << endl;

    for(auto field : *this->fields){
        field->print();
        cout << endl;
    }
    for(auto method : *this->methods){
        method->print();
        cout << endl;
    }
    cout << "}";
}

void ClassDeclaration::addMethod(Method* method){
    this->methods->push_back(method);
}

void ClassDeclaration::addField(Field* field){
    this->fields->push_back(field);
}

string ClassDeclaration::getName(){
    return name;
}

string ClassDeclaration::getParent(){
    return parent;
}

vector<Method*>* ClassDeclaration::getMethods(){
    return methods;
}

vector<Field*>* ClassDeclaration::getFields(){
    return fields;
}

Method* ClassDeclaration::getMethod(string methodName){
    for(Method* method : *methods) if(method->getId() == methodName) return method;
    return nullptr;
}