#include "operator.hpp"

string binOpSymbol(BinOperator op){
    if(op == OP_MOD) return "%"; 
    if(op == OP_GREAT) return ">"; 
    if(op == OP_LESS   ) return "<"; 
    if(op == OP_GREAT_EQ) return ">="; 
    if(op == OP_LESS_EQ) return "<="; 
    if(op == OP_IS_EQ) return "=="; // 
    if(op == OP_DIFF) return "!="; //
    if(op == OP_OR) return "||"; //
    if(op == OP_AND) return "&&"; //
    if(op == OP_PLUS) return "+"; // 
    if(op == OP_BIN_MINUS) return "-"; 
    if(op == OP_TIMES) return "*"; 
    if(op == OP_DIV) return "/"; 
    return "";
}

string unOpSymbol(UnOperator op){
    if(op == OP_UN_MINUS) return "-";
    if(op == OP_NOT) return "!";
    return "";
}
