#include "global.hpp"
#include "yaccer.hpp"

// Included to test:
#include "expression.hpp"
#include "code-generator.hpp"
#include "code-visitor.hpp"
#include "operator.hpp"
#include "statement.hpp"
#include "type.hpp"

void test() {

    {
        cout << "Test 1:\n/* 42+(-(a+b+c-d)) */\n\n";
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
        std::cout << visitor.visit(fortytwoPlusParen) << "\n\n";
    }

    {
        cout << "Test 2:\n/* int c = a+b */\n\n";
        IdExpression a("a");
        IdExpression b("b");
        BinExpression bin(&a,&b,OP_PLUS);
        VarDec c(MkTypeInt(), "c", &bin);
        CodeVisitor vis;
        vis.visit(&c);
    }
}

void testGenerateWholeCode(){
    CodeGenerator cg = CodeGenerator(program);
    cg.generateCode();
}

int main() {
    
    if(yyparse() != 1){
        // program->print();
        auto pool = buildClassSymtablePool(program);

        if(pool != nullptr)
            testGenerateWholeCode();        
    }

    return 0;
}
