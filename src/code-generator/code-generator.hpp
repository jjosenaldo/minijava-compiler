#ifndef CODE_GENERATOR_HPP
#define CODE_GENERATOR_HPP  

#include "ast.hpp"

class CodeGenerator{
    public:
        void generateCode(Program* program);
        void generatePreamble();
        void generateMainMethod(Program* program);
};


#endif