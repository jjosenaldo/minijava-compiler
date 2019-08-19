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
#define FR_Xp_3(x) x == TOK_ID

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

// then rbracket ) comma id lbrace while system continue break return semicolon if boolean int void rbrace
#define FF_Ep(x) x == TOK_THEN || x == ']' || x == ')' || x == TOK_ID || x == '{' || x == TOK_WHILE || \
        x == TOK_SYSTEM || x == TOK_CONTINUE || x == TOK_BREAK || x == TOK_RETURN || x == ';' || \
        x == TOK_IF || x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID || x == '}'

// less lesseq greatereq greater isequal isdiff then rbracket ) comma id lbrace while system continue break return semicolon if boolean int void rbrace
#define FF_E1(x) x == '<' || x == TOK_LESS_EQ || X == TOK_GREAT_EQ || X  == '>' || X == TOK_EQ || X == TOK_DIFF || \
        X == TOK_THEN || X == ']' || X == ')' || X == ',' || X == TOK_ID || X == '{' || X == TOK_WHILE || \
        X == TOK_SYSTEM || X == TOK_CONTINUE || X == TOK_BREAK || X == TOK_RETURN || X == ';' || X == TOK_IF || \
        X == TOK_BOOLEAN || X == TOK_INT || X == TOK_VOID || X == '}'

// less lesseq greatereq greater isequal isdiff then rbracket ) comma id lbrace while system continue break return semicolon if boolean int void rbrace
#define FF_E1p(x) FF_E1(x)

// and or less lesseq greatereq greater isequal isdiff then rbracket ) comma id lbrace while system continue break return semicolon if boolean int void rbrace
#define FF_E2(x) x == TOK_AND || X == TOK_OR || X == '<' || X == TOK_LESS_EQ || X == TOK_GREAT_EQ || X  == '>' || X == TOK_EQ || X == TOK_DIFF || \
        X == TOK_THEN || X == ']' || X == ')' || X == ',' || X == TOK_ID || X == '}' || X == TOK_WHILE || X == TOK_SYSTEM || X == TOK_CONTINUE || \
        X == TOK_BREAK || X == TOK_RETURN || X == ';' || X == TOK_IF || X == TOK_BOOLEAN || X == TOK_INT || X == TOK_VOID || X == '}'

// and or less lesseq greatereq greater isequal isdiff then rbracket ) comma id lbrace while system continue break return semicolon if boolean int void rbrace
#define FF_E2p(x) x == TOK_AND || x == TOK_OR || x == '<' || x == TOK_LESS_EQ || x == TOK_GREATER_EQ || x == '>' || x == TOK_EQ || x == TOK_DIFF || \
        x == TOK_THEN || x == ']' || x == ')' || x == ',' || x == TOK_ID || x == '{' || x == TOK_WHILE || x == TOK_SYSTEM || x == TOK_CONTINUE || \
        x == TOK_BREAK || x == TOK_RETURN || x == ';' || x == TOK_IF || x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID || x == '}'

// plus minus and or less lesseq greatereq greater isequal isdiff then rbracket ) comma id lbrace while system continue break return semicolon if boolean int void rbrace
#define FF_E3(x) x == '+' || x == '-' || x == TOK_AND || x == TOK_OR || x == '<' || x == TOK_LESS_EQ || x == TOK_GREATER_EQ || x == '>' || \
        x == TOK_EQ || x == TOK_DIFF || x == TOK_THEN || x == ']' || x == ')' || x == ',' || x == TOK_ID || x == '{' || x == TOK_WHILE || \
        x == TOK_SYSTEM || x == TOK_CONTINUE || x == TOK_BREAK || x == TOK_RETURN || x == ';' || x == TOK_IF || x == TOK_BOOLEAN || x == TOK_INT || \
        x == TOK_VOID || x == '}'

// plus minus and or less lesseq greatereq greater isequal isdiff then rbracket ) comma id lbrace while system continue break return semicolon if boolean int void rbrace
#define FF_E3p(x) x == '+' || x == '-' || x == TOK_AND || x == TOK_OR || x == '<' || x == TOK_LESS_EQ || x == TOK_GREATER_EQ || x == '>' || \
        x == TOK_EQ || x == TOK_DIFF || x == TOK_THEN || x == ']' || x == ')' || x == ',' || x == TOK_ID || x == '{' || x == TOK_WHILE || \
        x == TOK_SYSTEM || x == TOK_CONTINUE || x == TOK_BREAK || x == TOK_RETURN || x == ';' || x == TOK_IF || x == TOK_BOOLEAN || x == TOK_INT || \
        x == TOK_VOID || x == '}'

// times div mod plus minus and or less lesseq greatereq greater isequal isdiff then rbracket ) comma id lbrace while system continue break return semicolon if boolean int void rbrace
#define FF_T(x) x == '*' || x == '/' || x == '%' || x == '+' || x == '-' || x == TOK_AND || x == TOK_OR || x == '<' || x == TOK_LESS_EQ || \
        x == TOK_GREATER_EQ || x == '>' || x == TOK_EQ || x == TOK_DIFF || x == TOK_THEN || x == ']' || x == ')' || x == ',' || x == TOK_ID || \
        x == '{' || x == TOK_WHILE || x == TOK_SYSTEM || x == TOK_CONTINUE || x == TOK_BREAK || x == TOK_RETURN || x == ';' || x == TOK_IF || \
        x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID || x == '}'

// times div mod plus minus and or less lesseq greatereq greater isequal isdiff then rbracket ) comma id lbrace while system continue break return semicolon if boolean int void rbrace
#define FF_Tp(x) x == '*' || x == '/' || x == '%' || x == '+' || x == '-' || x == TOK_AND || x == TOK_OR || x == '<' || x == TOK_LESS_EQ || \
        x == TOK_GREATER_EQ || x == '>' || x == TOK_EQ || x == TOK_DIFF || x == TOK_THEN || x == ']' || x == ')' || x == ',' || x == TOK_ID || \
        x == '{' || x == TOK_WHILE || x == TOK_SYSTEM || x == TOK_CONTINUE || x == TOK_BREAK || x == TOK_RETURN || x == ';' || x == TOK_IF || \
        x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID || x == '}'

// )
#define FF_T4(x) x == ')'

// dot lbracket times div mod plus minus and or less lesseq greatereq greater isequal isdiff then rbracket ) comma id lbrace while system continue break return semicolon if boolean int void rbrace
#define FF_X(x) x == '.' || x == '[' || x == '*' || x == '/' || x == '%' || x == '+' || x == '-' || x == TOK_AND || x == TOK_OR || x == '<' || \
        x == TOK_LESS_EQ || x == TOK_GREATER_EQ || x == '>' || x == TOK_EQ || x == TOK_DIFF || x == TOK_THEN || x == ']' || x == ')' || x == ',' || \
        x == TOK_ID || x == '{' || x == TOK_WHILE || x == TOK_SYSTEM || x == TOK_CONTINUE || x == TOK_BREAK || x == TOK_RETURN || x == ';' || \
        x == TOK_IF || x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID || x == '}'

// dot lbracket times div mod plus minus and or less lesseq greatereq greater isequal isdiff then rbracket ) comma id lbrace while system continue break return semicolon if boolean int void rbrace
#define FF_Xp(x) x == '.' || x == '[' || x == '*' || x == '/' || x == '%' || x == '+' || x == '-' || x == TOK_AND || x == TOK_OR || x == '<' || \
        x == TOK_LESS_EQ || x == TOK_GREATER_EQ || x == '>' || x == TOK_EQ || x == TOK_DIFF || x == TOK_THEN || x == ']' || x == ')' || x == ',' || \
        x == TOK_ID || x == '{' || x == TOK_WHILE || x == TOK_SYSTEM || x == TOK_CONTINUE || x == TOK_BREAK || x == TOK_RETURN || x == ';' || \
        x == TOK_IF || x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID || x == '}'

// )
#define FF_T2(x) x == ')'

// )
#define FF_T3(x) x == ')'

// dot lbracket times div mod plus minus and or less lesseq greatereq greater isequal isdiff then rbracket ) comma id lbrace while system continue break return semicolon if boolean int void rbrace
#define FF_P(x) x == '.' || x == '[' || x == '*' || x == '/' || x == '%' || x == '+' || x == '-' || x == TOK_AND || x == TOK_OR || x == '<' || \
        x == TOK_LESS_EQ || x == TOK_GREATER_EQ || x == '>' || x == TOK_EQ || x == TOK_DIFF || x == TOK_THEN || x == ']' || x == ')' || x == ',' || \
                x == TOK_ID || x == '{' || x == TOK_WHILE || x == TOK_SYSTEM || x == TOK_CONTINUE || x == TOK_BREAK || x == TOK_RETURN || x == ';' || \
                x == TOK_IF || x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID || x == '}'

// dot lbracket times div mod plus minus and or less lesseq greatereq greater isequal isdiff then rbracket ) comma id lbrace while system continue break return semicolon if boolean int void rbrace
#define FF_F(x) x == '.' || x == '[' || x == '*' || x == '/' || x == '%' || x == '+' || x == '-' || x == TOK_AND || x == TOK_OR || x == '<' || \
        x == TOK_LESS_EQ || x == TOK_GREATER_EQ || x == '>' || x == TOK_EQ || x == TOK_DIFF || x == TOK_THEN || x == ']' || x == ')' || x == ',' || \
        x == TOK_ID || x == '{' || x == TOK_WHILE || x == TOK_SYSTEM || x == TOK_CONTINUE || x == TOK_BREAK || x == TOK_RETURN || x == ';' || \
        x == TOK_IF || x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID || x == '}'

// dot lbracket times div mod plus minus and or less lesseq greatereq greater isequal isdiff then rbracket ) comma id lbrace while system continue break return semicolon if boolean int void rbrace
#define FF_TT(x) x == '.' || x == '[' || x == '*' || x == '/' || x == '%' || x == '+' || x == '-' || x == TOK_AND || x == TOK_OR || x == '<' || \
        x == TOK_LESS_EQ || x == TOK_GREATER_EQ || x == '>' || x == TOK_EQ || x == TOK_DIFF || x == TOK_THEN || x == ']' || x == ')' || x == ',' || \
        x == TOK_ID || x == '{' || x == TOK_WHILE || x == TOK_SYSTEM || x == TOK_CONTINUE || x == TOK_BREAK || x == TOK_RETURN || x == ';' || \
        x == TOK_IF || x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID || x == '}'

// dot lbracket times div mod plus minus and or less lesseq greatereq greater isequal isdiff then rbracket ) comma id lbrace while system continue break return semicolon if boolean int void rbrace
#define FF_R(x) x == '.' || x == '[' || x == '*' || x == '/' || x == '%' || x == '+' || x == '-' || x == TOK_AND || x == TOK_OR || x == '<' || \
        x == TOK_LESS_EQ || x == TOK_GREATER_EQ || x == '>' || x == TOK_EQ || x == TOK_DIFF || x == TOK_THEN || x == ']' || x == ')' || x == ',' || \
        x == TOK_ID || x == '{' || x == TOK_WHILE || x == TOK_SYSTEM || x == TOK_CONTINUE || x == TOK_BREAK || x == TOK_RETURN || x == ';' || \
        x == TOK_IF || x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID || x == '}'

// }
#define FF_El(x) x == '}'

// then rbracket ) comma id lbrace while system continue break return semicolon if boolean int void rbrace
#define FF_E(x) x == TOK_THEN || x == ']' || x == ')' || x == ',' || x == TOK_ID || x == '{' || x == TOK_WHILE || x == TOK_SYSTEM || x == TOK_CONTINUE || \
        x == TOK_BREAK || x == TOK_RETURN || x == ';' || x == TOK_IF || x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID || x == '}'

// }
#define FF_Elp(x) x == '}'

// minus excl litint true false id litstr this null lbrace (
#define FF_Relop(x) x == '-' || x == '!' || x == TOK_LIT_INT || x == TOK_TRUE || x == TOK_FALSE || x == TOK_ID || x == TOK_LIT_STR || x == TOK_THIS || \
        x == TOK_NULL || x == '{' || x == '('

// minus excl litint true false id litstr this null lbrace (
#define FF_Boolop(x) x == '-' || x == '!' || x == TOK_LIT_INT || x == TOK_TRUE || x == TOK_FALSE || x == TOK_ID || x == TOK_LIT_STR || x == TOK_THIS || \
        x == TOK_NULL || x == '{' || x == '('

// minus excl litint true false id litstr this null lbrace (
#define FF_Addop(x) x == '-' || x == '!' || x == TOK_LIT_INT || x == TOK_TRUE || x == TOK_FALSE || x == TOK_ID || x == TOK_LIT_STR || x == TOK_THIS || \
        x == TOK_NULL || x == '{' || x == '('

// minus excl litint true false id litstr this null lbrace (
#define FF_Multop(x) x == '-' || x == '!' || x == TOK_LIT_INT || x == TOK_TRUE || x == TOK_FALSE || x == TOK_ID || x == TOK_LIT_STR || x == TOK_THIS || \
        x == TOK_NULL || x == '{' || x == '('

// minus excl litint true false id litstr this null lbrace (
#define FF_Unop(x) x == '-' || x == '!' || x == TOK_LIT_INT || x == TOK_TRUE || x == TOK_FALSE || x == TOK_ID || x == TOK_LIT_STR || x == TOK_THIS || \
        x == TOK_NULL || x == '{' || x == '('

#define F_STMT(x) x == '{' || x == TOK_WHILE || x == TOK_PRINT || x == TOK_ID || x == TOK_CONTINUE || \
                  x == TOK_BREAK || x == TOK_RETURN || x == ';' || x == TOK_IF

#define F_ARR_ASSGMT(x) x == TOK_ID

#define F_AFT_ID(x) x == '[' || x == '=' || x == TOK_ID

#define F_RMNG_ARR_ASSGMT(x) x == '{' || x == '='

#define F_BLK_STMTS(x) x == TOK_BOOLEAN || x == TOK_INT || x == TOK_ID || x == TOK_VOID || \
                      x == '{' || x == TOK_WHILE || x == TOK_PRINT || x == TOK_ID || x == TOK_CONTINUE || \
                      x == TOK_BREAK || x == TOK_RETURN || x == ';' || x == TOK_IF || x == EPS

#define F_BLK_STMT(x) x == TOK_BOOLEAN || x == TOK_INT || x == TOK_ID || x == TOK_VOID || \
                      x == '{' || x == TOK_WHILE || x == TOK_PRINT || x == TOK_ID || x == TOK_CONTINUE || \
                      x == TOK_BREAK || x == TOK_RETURN || x == ';' || x == TOK_IF

#define F_TYPE(x) x == TOK_BOOLEAN || x == TOK_INT || x == TOK_ID || x == TOK_VOID

#define F_TYPE1(x) x == '['

#define F_NON_CLASS_TYPE(x) x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID

#define F_ID_TYPE(x) x == TOK_ID

#define F_GOAL(x) x == TOK_CLASS || x == EPS

#define F_MAIN(x) x == TOK_CLASS || x == EPS

#define F_CLASS_DCRLTS(x) x == TOK_CLASS || x == EPS

#define F_CLASS_DCRLT(x) x == TOK_CLASS  || x == EPS

#define F_EXTNDS(x) x == TOK_EXTENDS || x == EPS

#define F_CLASS_BODY(x) x == '{'

#define F_CLASS_CONTENT(x) x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID || x == TOK_ID || x == EPS

#define F_CLASS_COMPONENT(x) x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID || x == TOK_ID

#define F_REST_DEC(x) x == ';' || x == '('

#define F_VAR_DEC(x) x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID || x == TOK_ID

#define F_NONCLASS_VAR_DEC(x) x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID

#define F_VAR_OBJ_DEC(x) x == TOK_ID

#define F_PARAMS_OPT(x) x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID || x == TOK_ID

#define F_PARAMS_REST(x) x == ','

#define F_PARAMS(x) x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID || x == TOK_ID

#define F_PARAM(x) x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID || x == TOK_ID

#define F_OPT_ELSE(x) x == TOK_ELSE || x == EPS

// Goal -> MainClass ClassDeclarations .
#define FR_GOAL(x) F_MAIN(x) || F_CLASS_DCRLTS(x) || x == EPS

// MainClass -> class id lbrace void main ( string lbracket rbracket id ) lbrace Blockstatements rbrace rbrace .
#define FR_MAIN(x) x == TOK_CLASS

// Blockstatements -> BlockStatement Blockstatements .
#define FR_BLK_STMTS(x) F_BLK_STMT(x)

// Blockstatements -> .
#define FR_BLK_STMTS2(x) x == EPS

// BlockStatement -> NonclassVarDec .
#define FR_BLK_STMT(x) F_NONCLASS_VAR_DEC(x)
// BlockStatement -> Statement .
#define FR_BLK_STMT1(x) F_STMT(x)

// BlockStatement -> id AfterId .
#define FR_BLK_STMT2(x) x == TOK_ID

// ClassDeclarations -> ClassDeclaration ClassDeclarations .
#define FR_CLASS_DCRLTS(x) F_CLASS_DCRLT(x)

// ClassDeclarations -> .
#define FR_CLASS_DCRLTS2(x) x == EPS

// ClassDeclaration -> class id Extends ClassBody .
#define FR_CLASS_DCRLT(x) x == TOK_CLASS

// Extends -> extends id .
#define FR_EXTNDS(x) x == TOK_EXTENDS

// Extends -> .
#define FR_EXTNDS2(x) x == EPS

// ClassBody -> lbrace ClassContent rbrace .
#define FR_CLASS_BODY(x) x == '{'

// ClassContent -> ClassComponent ClassContent .
#define FR_CLASS_CONTENT(x) F_CLASS_COMPONENT(x)

// ClassContent -> .
#define FR_CLASS_CONTENT1(x) x == EPS

// ClassComponent -> Type id RestDec .
#define FR_CLASS_COMPONENT(x) F_TYPE(x)

// RestDec -> semicolon .
#define FR_REST_DEC(x) x == ';'

// RestDec -> ( ParamsOpt ) lbrace Blockstatements rbrace .
#define FR_REST_DEC1(x) x == '('

// VarDec -> NonclassVarDec .
#define FR_VAR_DEC(x) F_NONCLASS_VAR_DEC(x)

// VarDec ->  VarObjDec .
#define FR_VAR_DEC1(x) F_VAR_OBJ_DEC(x)

// NonclassVarDec -> NonclassType id semicolon .
#define FR_NONCLASS_VAR_DEC(x) F_NON_CLASS_TYPE(x)

// VarObjDec -> id id semicolon .
#define FR_VAR_OBJ_DEC(x) x == TOK_ID

// ParamsOpt -> Params .
#define FR_PARAMS_OPT(x) F_PARAMS(x)

// ParamsOpt1 -> .
#define FR_PARAMS_OPT1(x) x == EPS

// Params -> Param ParamsRest .
#define FR_PARAMS(x) F_PARAM(x)

// ParamsRest -> comma Params .
#define FR_PARAMS_REST(x) x == ','

// ParamsRest -> .
#define FR_PARAMS_REST1(x) x == EPS

// Param -> Type id .
#define FR_PARAM(x) F_TYPE(x)

// Type1 -> lbracket rbracket Type1 .
#define FR_TYPE1(x) x == '{'

// Type1 -> .
#define FR_TYPE1_1(x) x == EPS

// NonclassType -> boolean Type1 .
#define FR_NON_CLASS_TYPE(x) x == TOK_BOOLEAN

// NonclassType -> int Type1 .
#define FR_NON_CLASS_TYPE1(x) x == TOK_INT

// NonclassType -> void .
#define FR_NON_CLASS_TYPE2(x) x == TOK_VOID

// IdType -> id Type1 .
#define FR_ID_TYPE(x) x == TOK_ID

// Type -> NonclassType .
#define FR_TYPE(x) F_NON_CLASS_TYPE(x)

// Type -> IdType .
#define FR_TYPE_1(x) F_ID_TYPE(x)

// Statement ->  lbrace Blockstatements rbrace .
#define FR_STMT(x) x == '{'

// Statement ->  while ( E ) Statement .
#define FR_STMT1(x) x == TOK_WHILE

// Statement ->  system dot out dot println ( E ) semicolon .
#define FR_STMT2(x) x == TOK_PRINT

// Statement ->  continue semicolon .
#define FR_STMT3(x) x == TOK_CONTINUE

// Statement ->  break semicolon .
#define FR_STMT4(x) x == TOK_BREAK

// Statement ->  return E semicolon .
#define FR_STMT5(x) x == TOK_RETURN

// Statement ->  semicolon .
#define FR_STMT6(x) x == ';'

// Statement ->  if E then Statement OptElse .
#define FR_STMT7(x) x == TOK_IF

// OptElse -> else Statement .
#define FR_OPT_ELSE(x) x == TOK_ELSE

// OptElse ->  .
#define FR_OPT_ELSE1(x) x == EPS

// ArrAssignment -> id  RemainingArrAssignment .
#define FR_ARR_ASSGMT(x) x == TOK_ID

// RemainingArrAssignment -> lbracket E rbracket equal E .
#define FR_RMNG_ARR_ASSGMT(x) == '{'

// RemainingArrAssignment -> equal E .
#define FR_RMNG_ARR_ASSGMT1(x) == TOK_EQ

// AfterId -> RemainingArrAssignment .
#define FR_AFTER_ID(x) F_RMNG_ARR_ASSGMT(x)

// AfterId -> id semicolon .
#define FR_AFTER_ID1(x) F_RMNG_ARR_ASSGMT(x)

// AfterId -> id semicolon .
#define FR_Relop(x) F_Relop(x)

// ∅
#define FF_GOAL(x) 0

// class
#define FF_MAIN_CLASS(x) x == TOK_CLASS

// id lbrace while system continue break return semicolon if boolean int void rbrace
#define FF_BLK_STMT(x) x == TOK_ID || x == '{' || x == TOK_WHILE || x == TOK_SYSTEM || x == TOK_CONTINUE || x == TOK_BREAK || \
        x == TOK_RETURN || x == ';' || x == TOK_IF || x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID || x == '}'

// ∅
#define FF_CLASS_DECLARATIONS(x) 0

// class
#define FF_CLASS_DECLARATION (x) x == TOK_CLASS

// lbrace
#define FF_EXTENDS(x) X == '{'

// class
#define FF_CLASS_BODY(x) X == TOK_CLASS

// rbrace
#define FF_CLASS_CONTENT(x) X == '}'

// boolean int void id rbrace
#define FF_CLASS_COMPONENT(x) x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID || x == TOK_ID || x == '}'

// boolean int void id rbrace
#define FF_REST_DEC(x) x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID || x == TOK_ID || x == '}'

// ∅
#define FF_VAR_DEC(x) 0

// id lbrace while system continue break return semicolon if boolean int void rbrace
#define FF_NONCLASS_VAR_DEC(x) x == TOK_ID || x == '{' || x == TOK_WHILE || x == TOK_SYSTEM || x == TOK_CONTINUE || \
        x == TOK_BREAK || x == TOK_RETURN || x == ';' || x == TOK_IF || x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID || x == '}'

// ∅
#define FF_VAR_OBJ_DEC(x) 0

// )
#define FF_PARAMS_OPT(x) x == ')'

// )
#define FF_PARAMS_REST(x) x == ')'

// )
#define FF_PARAMS(x) x == ')'

// comma )
#define FF_PARAM(x) x == ',' || x == ')'

// id
#define FF_TYPE1(x) x == TOK_ID

// id
#define FF_TYPE(x) x == TOK_ID

// id
#define FF_NONCLASS_TYPE(x) x == TOK_ID

// id
#define FF_ID_TYPE(x) x == TOK_ID

// rbrace
#define FF_BLK_STMTS(x) x == '}'

// else id lbrace while system continue break return semicolon if boolean int void rbrace
#define FF_OPT_ELSE(x) x == TOK_ELSE || x == TOK_ID || x == '{' || x == TOK_WHILE || x == TOK_SYSTEM || x == TOK_CONTINUE || \
        x == TOK_BREAK || x == TOK_RETURN || x == ';' || x == TOK_IF || x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID || x == '}'

// else id lbrace while system continue break return semicolon if boolean int void rbrace
#define FF_STMT(x) x == TOK_ELSE || x == TOK_ID || x == '{' || x == TOK_WHILE || x == TOK_SYSTEM || \
        x == TOK_CONTINUE || x == TOK_BREAK || x == TOK_RETURN || x == ';' || x == TOK_IF || x == TOK_BOOLEAN || x == TOK_INT || \
        x == TOK_VOID || x == '}'

// ∅
#define FF_ARR_ASSIGNMENT(x) 0

// id lbrace while system continue break return semicolon if boolean int void rbrace
#define FF_AFTER_ID(x) x == TOK_ID || x == '{' || x == TOK_WHILE || x == TOK_SYSTEM || x == TOK_CONTINUE || x == TOK_BREAK || \
        x == TOK_RETURN || x == ';' || x == TOK_IF || x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID || x == '}'

// id lbrace while system continue break return semicolon if boolean int void rbrace
#define FF_REMAINING_ARR_ASSIGNMENT(x) x == TOK_ID || x == '{' || x == TOK_WHILE || x == TOK_SYSTEM || x == TOK_CONTINUE || \
        x == TOK_BREAK || x == TOK_RETURN || x == ';' || x == TOK_IF || x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID || x == '}'
#endif