#include "expression.hpp"
#include "code-visitor.hpp"
#include "global.hpp"
#include "yaccer.hpp"

int main(){
    
    // if(yyparse() != 1){
    //     // program->print();
    //     auto pool = buildClassSymtablePool(program);

    //     if(pool != nullptr)
    //         //pool->print();
    //         std::cout << "1\n";
    //     else 
    //         std::cout << "0\n";
    // }

    IdExpression* ida = new IdExpression("a");
    IdExpression* idb = new IdExpression("b");
    BinExpression* binop = new BinExpression(ida, idb, OP_PLUS);
    CodeVisitor visitor;
    visitor.visit(binop);
    return 0;
}
