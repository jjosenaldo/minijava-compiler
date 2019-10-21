#include <iostream>
#include "ast.hpp"

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

// TODO: the class declarations should be in a hash map
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

Type* Method::getType(){
    Type* type = new Type;
    type->kind = TypeMethod;
    auto header = new vector<Type*>;
    header->push_back(returnType);

    if(parameters != nullptr) for(auto param : *parameters) header->push_back(param->getType());

    type->methodHeader = header;
    return type;
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

vector<Method*>* ClassDeclaration::getMethods(){
    return methods;
}

vector<Field*>* ClassDeclaration::getFields(){
    return fields;
}

// TODO: the methods should be in a hashtable
Method* ClassDeclaration::getMethod(string methodName){
    for(Method* method : *methods) if(method->getId() == methodName) return method;
    return nullptr;
}

ClassSymtablePool* buildClassSymtablePool(Program* program){
    ClassSymtablePool* pool = new ClassSymtablePool;

    // Processes the method headers and fields of each class
    for(auto classDecl : *program->getDecls()){
        string className = classDecl->getName();

        if(pool->get(className) != nullptr) {
            delete pool;
            multipleClassError(className);
            return nullptr;
        }

        ClassSymtable* root = new ClassSymtable;

        auto fields = classDecl->getFields();

        // TODO: check fields with the same name
        if(fields != nullptr) 
            for(auto field : *fields){ 
                TableContent tc;
                tc.tag = TCTYPE;
                tc.type = field->getType();
                root->insert(field->getName(), tc);
            }

        auto methods = classDecl->getMethods();
        
        if(methods != nullptr){
            // First, adds the method headers in the symbol table
            for(auto method : *methods){
                string methodName = method->getId();

                if(root->get(methodName).tag != TCNOCONTENT){
                    multipleMethodError(className, methodName);
                    delete root;
                    delete pool;
                    return nullptr;
                }

                // Adds the method name
                TableContent tcMethodType;
                tcMethodType.tag = TCTYPE;
                tcMethodType.type = method->getType();
                root->insert(methodName, tcMethodType);

                Symtable* methodTable = new Symtable;

                // TODO: check method parameters with the same name
                // Adds the method params
                auto params = method->getParameters();
                if(params != nullptr)
                    for(auto param : *params)
                        methodTable->insert(param->getName(), tableContentFromType(param->getType()));

                root->insertMethodTable(methodName, methodTable);
            }
        }

        pool->insert(className, root);
    }

    // Processes each method body
    unordered_map<string, ClassSymtable*>* tablePool = pool->getPool();
    for(auto tablePoolEntry : *tablePool){
        string className = tablePoolEntry.first;
        ClassSymtable* classSymtable = tablePoolEntry.second;

        for(auto methodTablePair : *classSymtable->getMethodTables()){
            string methodName = methodTablePair.first;
            Symtable* methodTable = methodTablePair.second;
            auto classDecl = program->getClassDecl(className);
            auto method = classDecl->getMethod(methodName);
            auto blockStmt = method->getStatement();

            if(blockStmt != nullptr)
                blockStmt->buildSymtable(methodTable);
        }
    }

    return pool;
}

void multipleClassError(string id){
    errorMsgPrefix();
    cout << "the class " << id << " was multiply defined!" << endl;
}

void multipleMethodError(string className, string methodName){
    errorMsgPrefix();
    cout << "the method " << methodName << " in the class " << className << " is already defined!" << endl;
}

void multipleVariableError(string id){
    errorMsgPrefix();
    cout << "the variable " << id << " is already defined in this scope" << endl;
}

void errorMsgPrefix(){
    cout << "ERROR: ";
}