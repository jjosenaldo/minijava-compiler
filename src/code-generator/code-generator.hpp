#ifndef CODE_GENERATOR_HPP
#define CODE_GENERATOR_HPP  

#include "ast.hpp"
#include "code-visitor.hpp"
#include <iostream>

using std::ostream;
using std::cout;

class CodeGenerator{
    private:
        CodeVisitor codeVisitor;
        Program* program;
        void generateClassDecls();
        void generatePreamble();
        void generateMainMethod();
    public:
        CodeGenerator(Program* program, ostream& out = cout);
        void generateCode();
};


#endif