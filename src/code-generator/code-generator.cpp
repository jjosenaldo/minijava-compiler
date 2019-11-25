#include <iostream>
#include <string>
#include "code-generator.hpp"
#include "code-visitor.hpp"

using std::endl;
using std::string;
using std::ostream;

#define TAB string("    ")

CodeGenerator::CodeGenerator(Program* program, ostream& out) 
    : codeVisitor(out)
    , program(program)
    , out(out) {}

void CodeGenerator::generateCode(){
    generatePreamble();
    generateMainMethod();
}

void CodeGenerator::generatePreamble(){
    // #includes
    out << "#include \"activation-record.hpp\"" << endl;
    out << "#include \"value.hpp\"" << endl;

    // usings
    out << "using std::cout;" << endl;
    out << "using std::endl;" << endl;

    // class declarations
    generateClassDecls();
}

void CodeGenerator::generateMainMethod(){
    out << "int main(){" << endl;

    // Declares the activation record stack
    out << "RecordStack* rs = new RecordStack();" << endl;

    codeVisitor.visit(program);

    out << "return 0;" << endl;
    out << "}" << endl;
}

void CodeGenerator::generateClassDecls(){
    codeVisitor.visitClassDeclarationsFields(program);
}