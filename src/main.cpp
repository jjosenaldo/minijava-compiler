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
    IdExpression* idc = new IdExpression("c");
    IdExpression* idd = new IdExpression("d");
    BinExpression* binopAB = new BinExpression(ida, idb, OP_PLUS);
    BinExpression* binopABC = new BinExpression(binopAB, idc, OP_PLUS);
    BinExpression* binopABCD = new BinExpression(binopABC, idd, OP_PLUS);
    UnExpression* binopABCDminus = new UnExpression(binopABCD, OP_UN_MINUS);
    ParenExpression* paren = new ParenExpression(binopABCDminus);
    AtomExpValue aev;
    aev.intval = 42;
    AtomExpression* fortytwo = new AtomExpression(aev, MkTypeInt());
    BinExpression* fortytwoPlusParen = new BinExpression(fortytwo, paren, OP_PLUS);

    CodeVisitor visitor;
    std::cout << visitor.visit(fortytwoPlusParen) << "\n";
    return 0;
}
