#include "visitor.hpp"
#include "operator.hpp"
#include "expression.hpp"

int main(){
    IdExpression* ida = new IdExpression("a");
    IdExpression* idb = new IdExpression("b");
    BinExpression* binop = new BinExpression(ida, idb, OP_PLUS);
    Visitor* visitor = new Visitor;
    visitor->visit(binop);


    return 0;
}