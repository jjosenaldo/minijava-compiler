#ifndef PRED_SETS_H
#define PRED_SETS_H

#include "token.h"

// unop litint true false id litstr this null lbrace (
#define F_E(x) F_Unop(x) || x == TOK_LIT_INT || x == TOK_TRUE || x == TOK_FALSE || x == TOK_ID ||\
        x == TOK_LIT_STR || x == TOK_THIS || x == TOK_NULL || x == '{' || \
        x == '(' 

// relop
#define F_Ep(x) F_Relop(x) || x == EPS

// unop litint true false id litstr this null lbrace (
#define F_E1(x) F_E(x)

// boolop
#define F_E1p(x) F_Boolop(x) || x == EPS

// unop litint true false id litstr this null lbrace (
#define F_E2(x) F_E(x)

// addop
#define F_E2p(x) F_Addop(x) || x == EPS

// unop litint true false id litstr this null lbrace (
#define F_E3(x) F_E(x)

// multop
#define F_E3p(x) F_Multop(x) || x == EPS

// unop litint true false id litstr this null lbrace (
#define F_T(x) F_E(x)

// dot lbracket
#define F_Tp(x) x == '.' || x == '[' || x == EPS

// comma
#define F_T2(x) x == ',' || x == EPS

// unop litint true false id litstr this null lbrace (
#define F_T3(x) F_E(x) || x == EPS

// comma
#define F_T4(x) x == ',' || x == EPS

// dot lbracket
#define F_X(x) x == '.' || x == '['

// length substring id
#define F_Xp(x) x == TOK_LENGTH || x == TOK_SUBSTRING || x == TOK_ID

// ()
#define F_P(x) x == '(' || x == EPS

// 	litint true false id litstr this null lbrace (
#define F_F(x) x == TOK_LIT_INT || x == TOK_TRUE || x == TOK_FALSE || x == TOK_ID || x == TOK_LIT_STR || \
        x == TOK_THIS || x == TOK_NULL || x == '{' || x == '('

// litint true false id litstr this null
#define F_TT(x) x == LIT_INT || x == TOK_TRUE || x == TOK_FALSE || x == TOK_ID || x == TOK_LIT_STR || \
        x == TOK_THIS || x == TOK_NULL

// lbrace (    
#define F_R(x) x == '{' || x == '('

// unop litint true false id litstr this null lbrace (
#define F_El(x) F_E(x) || x == EPS

// comma
#define F_Elp(x) x == ',' || x == EPS
 
#define F_Unop(x) x == '-' || x == '!'
#define F_Relop(x) x == '<' || x == TOK_LESS_EQ || x == '>' || x == TOK_GREAT_EQ || x == TOK_EQ || \
        x == TOK_DIFF
#define F_Multop(x) x == '/' || x == '*' || x == '%'
#define F_Boolop(x) x == TOK_AND || x == TOK_OR
#define F_Addop(x) x == '+' || x == '-'

// E -> E1 Ep .
#define FR_E(x) F_E1(x)

// Ep -> relop E1 .
#define FR_Ep_1(x) F_Relop(x)

// Ep -> .
#define FR_Ep_2(x) x == EPS

// E1 -> E2 E1p .
#define FR_E1(x) F_E2(x)

// E1p -> boolop E2 E1p .
#define FR_E1p_1(x) F_Boolop(x)

// E1p -> .
#define FR_E1p_2(x) x == EPS

// E2 -> E3 E2p .
#define FR_E2(x) F_E3(x)

// E2p -> addop E3 E2p .
#define FR_E2p_1(x) F_Addop(x)

// E2p -> .
#define FR_E2p_2(x) x == EPS

// E3 -> T E3p .
#define FR_E3(x) F_T(x)

// E3p -> multop T E3p .
#define FR_E3p_1(x) F_Multop(x)

// E3p -> .
#define FR_E3p_2(x) x == EPS

// T -> F Tp  .
#define FR_T_1(x) F_F(x)

// T -> unop T .
#define FR_T_2(x) F_Unop(x)

// Tp -> X Tp .
#define FR_Tp_1(x) F_X(x)

// Tp -> .
#define FR_Tp_2(x) x == EPS

// T2 -> comma E .                   
#define FR_T2_1(x) x == ','

// T2 -> .
#define FR_T2_2(x) x == EPS

// T3 -> E T4 .
#define FR_T3_1(x) F_E(x)

// T3 -> .
#define FR_T3_2(x) x == EPS

// T4 -> comma E T4 .
#define FR_T4_1(x) x == ','

// T4 -> .
#define FR_T4_2(x) x == EPS

// X -> dot Xp .
#define FR_X_1(x) x == '.'

// X -> lbracket E rbracket .
#define FR_X_2(x) x == '['

// Xp -> length P .
#define FR_Xp_1(x) x == TOK_LENGTH

// Xp -> substring ( E T2 ) .
#define FR_Xp_2(x) x == TOK_SUBSTRING

// Xp -> id ( T3 ) .
#define FR_Xp_1(x) x == TOK_ID

// P -> ( ) .
#define FR_P_1(x) x == '('

// P -> .
#define FR_P_2(x) x == EPS

// F -> TT .
#define FR_F_1(x) F_TT(x)

// F -> R .
#define FR_F_2(x) F_R(x)

// TT -> litint .
#define FR_TT_1(x) x == TOK_LIT_INT

// TT -> true .
#define FR_TT_2(x) x == TOK_TRUE

// TT -> false .
#define FR_TT_3(x) x == TOK_FALSE

// TT -> id .
#define FR_TT_4(x) x == TOK_ID

// TT -> litstr .
#define FR_TT_5(x) x == TOK_LIT_STR

// TT -> this .
#define FR_TT_6(x) x == TOK_THIS

// TT -> null .
#define FR_TT_7(x) x == TOK_NULL

// R -> lbrace El rbrace .
#define FR_R_1(x) x == '{'

// R -> ( E ) .
#define FR_R_2(x) x == '('

// El -> E Elp .
#define FR_El_1(x) F_E(x)

// El -> .
#define FR_El_2(x) x == EPS

// Elp -> comma E Elp .
#define FR_Elp_1(x) x == ','

// Elp -> .
#define FR_Elp_2(x) x == EPS



/*
Goal -> MainClass ClassDeclarations .
MainClass -> class id lbrace void main ( string lbracket rbracket id ) lbrace Blockstatements rbrace rbrace .
Blockstatements -> BlockStatement Blockstatements | .
BlockStatement -> NonclassVarDec | Statement | id AfterId .

ClassDeclarations -> ClassDeclaration ClassDeclarations  | .
ClassDeclaration -> class id Extends ClassBody .
Extends -> extends id | .
ClassBody -> lbrace ClassContent rbrace .
ClassContent -> ClassComponent ClassContent | .

ClassComponent -> Type id RestDec .

RestDec -> semicolon | ( ParamsOpt ) lbrace Blockstatements rbrace .
VarDec -> NonclassVarDec |  VarObjDec .
NonclassVarDec -> NonclassType id semicolon .
VarObjDec -> id id semicolon .

ParamsOpt -> Params | .
Params -> Param ParamsRest .
ParamsRest -> comma Params | .
Param -> Type id .

Type1 -> lbracket rbracket Type1 | .
NonclassType -> boolean Type1 | int Type1 | void .
IdType -> id Type1 .
Type -> NonclassType | IdType .

Statement ->  lbrace Blockstatements rbrace |  while ( E ) Statement | system dot out dot println ( E ) semicolon  | continue semicolon | break semicolon | return E semicolon | semicolon | if E then Statement OptEelse .

OptElse -> else Statement | .

ArrAssignment -> id  RemainingArrAssignment .
RemainingArrAssignment -> lbracket E rbracket equal E | equal E .
AfterId -> RemainingArrAssignment | id semicolon .
*/

#define F_STMT(x) x == '{' || x == TOK_WHILE || x == TOK_PRINT || x == TOK_ID || x == TOK_CONTINUE || \
                  x == TOK_BREAK || x == TOK_RETURN || x == ';' || x == TOK_IF

#define F_AFT_ID(x) x == '[' || x == '='

#define F_BLK_STMT(x) x == TOK_BOOLEAN || x == TOK_INT || x == TOK_ID || x == TOK_VOID || \
                      x == '{' || x == TOK_WHILE || x == TOK_PRINT || x == TOK_ID || x == TOK_CONTINUE || \
                      x == TOK_BREAK || x == TOK_RETURN || x == ';' || x == TOK_IF || x == EPS

#define F_TYPE(x) x == TOK_BOOLEAN || x == TOK_INT || x == TOK_ID || x == TOK_VOID

#define F_TYPE1(x) x == '[' || x == EPS

#endif