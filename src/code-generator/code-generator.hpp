#ifndef CODE_GENERATOR_HPP
#define CODE_GENERATOR_HPP  

#include "ast.hpp"
#include "code-visitor.hpp"

class CodeGenerator{
    private:
        CodeVisitor codeVisitor;
        Program* program;
        void generateClassDecls();

    public:
        CodeGenerator(Program* program);
        void generateCode();
        void generatePreamble();
        void generateMainMethod();
};


#endif