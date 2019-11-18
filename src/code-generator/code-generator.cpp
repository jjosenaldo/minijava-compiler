#include <iostream>
#include <string>
#include "code-generator.hpp"
#include "code-visitor.hpp"

using std::cout;
using std::endl;
using std::string;

#define TAB string("    ")

void CodeGenerator::generateCode(Program* program){
    generatePreamble();
    generateMainMethod(program);
}

void CodeGenerator::generatePreamble(){
    // #includes
    cout << "#include \"src/code-generator/activation-record.hpp\"" << endl;
    cout << "#include \"src/code-generator/value.hpp\"" << endl;

    // usings 
    cout << "using std::cout;" << endl;
    cout << "using std::endl;" << endl;
}

void CodeGenerator::generateMainMethod(Program* program){
    cout << "int main(){" << endl;

    // Declares the activation record stack
    cout << "RecordStack* rs = new RecordStack();" << endl;
    
    CodeVisitor visitor = CodeVisitor();
    visitor.visit(program);

    cout << "return 0;" << endl;
    cout << "}" << endl;
}