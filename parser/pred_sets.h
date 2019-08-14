#ifndef PRED_SETS_H
#define PRED_SETS_H

#include "token.h"

#define F_E1(x) x == TOK_LIT_INT || x == TOK_TRUE || x == TOK_FALSE || x == TOK_ID ||\
        x == TOK_LIT_STR || x == TOK_THIS || x == TOK_NULL || x == '{' || \
        x == '(' || x == '-' || x == '!'
#define F_E2(x) F_E1(x)
#define F_E3(x) F_E1(x)
#define F_T(x) F_E1(x)
#define F_F(x) F_E1(x)
#define F_Un(x) x == '-' || x == '!'
#define F_Elp(x) x == ',' || x == EPS
#define F_El(x) F_E1(x) || x == EPS
#define F_R(x) x == '{' || x == '(' || x == '-' || x == '!'
#define F_t(x) x == TOK_LIT_INT || x == TOK_TRUE || x == TOK_FALSE || x == TOK_ID || \
        x == TOK_LIT_STR || x == TOK_THIS ||x == TOK_NULL 
#define F_Relop(x) x == '<' || x == TOK_LESS_EQ || x == '>' || x == TOK_GREAT_EQ || x == TOK_EQ || \
        x == TOK_DIFF
#define F_Multop(x) x == '/' || x == '*' || x == '%'
#define F_Boolop(x) x == TOK_AND || x == TOK_OR
#define F_Addop(x) x == '+' || x == '-'
#define F_X(x) x == '.' || x == '['

// E -> E1 E’
#define FR_E(x) F_E1(x)

// E' -> rel_op E1
#define FR_Ep_1(x) F_Relop(x)

// E' -> EPS
#define FR_Ep_2(x) x == EPS

// E1  -> E2 E1'
#define FR_E1(x) F_E2(x)

// E1' -> bool_op E2 E1'
#define FR_E1p_1(x) F_Boolop(x)

// E1' -> EPS
#define FR_E1p_2(x) x == EPS

// E2  -> E3 E2'
#define FR_E2(x) F_E3(x)

// E2' -> mult_op E3 E2'
#define FR_E2p_1(x) F_Multop(x)

// E2' -> EPS
#define FR_E2p_2(x) x == EPS

// E3  -> T E3'
#define FR_E3(x) F_T(x)

// E3' -> add_op T E3'
#define FR_E3p_1(x) F_Addop(x)

// E3' -> EPS
#define FR_E3p_2(x) x == EPS

// T -> F T’
#define FR_T(x) F_F(x)

// T’ -> X T’
#define FR_Tp_1(x) F_X(x)

// T2 -> , E
#define FR_T2_1(x) x == ','

// T2 -> EPS
#define FR_T2_2(x) x == EPS

// T3 -> E T4
#define FR_T3_E1(x) F_E(x)

// T3 -> EPS
#define FR_T3_E2(x)  x == EPS

// T4 -> , E T4
#define FR_T4_1(x) x == ','

// T3 -> EPS
#define FR_T4_E2(x)  x == EPS

// X -> . X’
#define FR_X_1(x) x == ','

// X -> [ E ]
#define FR_X_2(x) x == '['

// X' -> length P
#define FR_Xp_1(x) x == TOK_LENGTH

// X' -> substring ( E T2 )
#define FR_Xp_2(x) x == TOK_SUBSTRING

// X' -> ID ( T3 )
#define FR_Xp_3(x) x == TOK_ID

// F -> t
#define FR_F_1(x) F_t(x)

// F -> R
#define FR_F_2(x) F_R(x)

// R -> { El }
#define FR_R_1(x) x == '{'

// R -> Un T
#define FR_R_2(x) F_Un(x)

// R -> ( E )
#define FR_R_3(x) x == '('

// El -> E El’
#define FR_El_1(x) FR_E(x)

// El -> EPS
#define FR_El_2(x)  x == EPS

// El' -> , E El'
#define FR_Elp_1(x) x == ','

// El' -> EPS
#define FR_Elp_2(x) x == EPS

#define F_STMT(x) x == '{' || x == TOK_WHILE || x == TOK_PRINT || x == TOK_ID || x == TOK_CONTINUE || \
                  x == TOK_BREAK || x == TOK_RETURN || x == ';' || x == TOK_IF

#define F_AFT_ID(x) x == '[' || x == '='

#define F_BLK_STMT(x) x == TOK_BOOLEAN || x == TOK_INT || x == TOK_ID || x == TOK_VOID || \
                      x == '{' || x == TOK_WHILE || x == TOK_PRINT || x == TOK_ID || x == TOK_CONTINUE || \
                      x == TOK_BREAK || x == TOK_RETURN || x == ';' || x == TOK_IF || x == EPS

#define F_TYPE(x) x == TOK_BOOLEAN || x == TOK_INT || x == TOK_ID || x == TOK_VOID

#define F_TYPE1(x) x == '[' || x == EPS

#endif
