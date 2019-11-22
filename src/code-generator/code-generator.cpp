#include <iostream>
#include <string>
#include "code-generator.hpp"
#include "code-visitor.hpp"

using std::cout;
using std::endl;
using std::string;

#define TAB string("    ")

CodeGenerator::CodeGenerator(Program* program){
    codeVisitor = CodeVisitor();
    this->program = program;
}

void CodeGenerator::generateCode(){
    generatePreamble();
    generateMainMethod();
}

void CodeGenerator::generatePreamble(){
    // #includes
    cout << "#include \"src/code-generator/activation-record.hpp\"" << endl;
    cout << "#include \"src/code-generator/value.hpp\"" << endl;

    // usings 
    cout << "using std::cout;" << endl;
    cout << "using std::endl;" << endl;

    // class declarations
    generateClassDecls();
}

void CodeGenerator::generateMainMethod(){
    cout << "int main(){" << endl;

    // Declares the activation record stack
    cout << "RecordStack* rs = new RecordStack();" << endl;
    
    CodeVisitor visitor = CodeVisitor();
    visitor.visit(program);

    cout << "return 0;" << endl;
    cout << "}" << endl;
}

void CodeGenerator::generateClassDecls(){
    codeVisitor.visitClassDeclarationsFields(program);
}