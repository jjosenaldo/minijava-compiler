#include <iostream>
#include "ast.hpp"

using std::cout;
using std::endl;

void Program::print(){
    for(auto decl : this->declarations){   
        decl->print();
        cout << endl;
    }
}

void Program::addClassDecl(ClassDeclaration* decl){
    this->declarations.push_back(decl);
}

Parameter::Parameter(Type* type, string name){
    this->type = type;
    this->name = name;
}

void Parameter::print(){
    printType(this->type);
    cout << " " << name;
}

Method::Method(string id, Type* returnType, Block* stmt){
    this->id = id;
    this->returnType = returnType;
    this->statement = stmt;
}

void Method::print(){
    printType(this->returnType);
    cout << " " << id << "(";

    for(auto param : this->parameters){
        param->print();
        cout << ", ";
    }
    cout << ") ";
    this->statement->print();
}

void Method::addParam(Parameter* param){
    this->parameters.push_back(param);
}

ClassDeclaration::ClassDeclaration(string name){
    this->name = name;
}

void ClassDeclaration::print(){
    cout << "class " << this->name << " {" << endl;
    for(auto method : this->methods){
        method->print();
        cout << endl;
    }
    cout << "}";
}

void ClassDeclaration::addMethod(Method* method){
    this->methods.push_back(method);
}
