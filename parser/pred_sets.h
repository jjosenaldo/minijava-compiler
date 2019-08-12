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
#define F_ElP(x) x == ',' || x == EPS
#define F_El(x) F_E1(x) || x == EPS
#define F_R(x) x == '{' || x == '(' || x == '-' || x == '!'
#define F_t(x) x == TOK_LIT_INT || x == TOK_TRUE || x == TOK_FALSE || x == TOK_ID || \
        x == TOK_LIT_STR || x == TOK_THIS ||x == TOK_NULL ||x == '{' ||x == '(' ||x == '-' || \
        x == '!'
#define F_Relop(x) x == '<' || x == TOK_LESS_EQ || x == '>' || x == TOK_GREAT_EQ || x == TOK_EQ || \
        x == TOK_DIFF
#define F_Multop(x) x == '/' || x == '*' || x == '%'
#define F_Boolop(x) x == TOK_AND || x == TOK_OR

// E -> E1 E’
#define FR_E(x) F_E1(x)

// E' -> rel_op E1
#define FR_Ep_1(x) F_Relop(x) 

// E' -> eps
#define FR_Ep_2(x) x == EPS

// E1  -> E2 E1'
#define FR_E1(x) F_E(2)

// E1' -> bool_op E2 E1'
#define FR_E1p_1(x) F_Boolop(x)

// E1' -> eps
#define FR_E1p_2(x) x == EPS

// E2  -> E3 E2'
#define FR_E2(x) F_E3(x)

// E2' -> mult_op E3 E2'
#define FR_E2p_1(x) F_Multop(x)

// E2' -> eps
#define FR_E2p_2(x) x == EPS

// E3  -> T E3'
#define FR_E3(x) F_T(x)

// E3' -> add_op T E3'
#define FR_E3p_1(x) x == '+' || x == '-'

// E3' -> eps
#define FR_E3p_2(x) x == EPS

// T -> F T’ 
#define FR_T(x) F_F(x)

// T’ -> X T’
#define FR_Tp_1(x) 

#endif

/*
E -> E1 E’
E’ -> rel_op E1 | EPSILON
E1 -> E2 E1'
E1' -> bool_op E2 E1' | EPSILON
E2 -> E3 E2'
E2' -> mult_op E3 E2' | EPSILON
E3 -> T E3'
E3' -> add_op T E3' | EPSILON

rel_op    -> < | <= | > | >= | == | !=
bool_op   -> && | ||
mult_op   -> / | * | %
add_op      -> + | -

T -> F T’
T’-> X T’ | EPSILON
T2 -> , E | EPSILON                   
T3 -> E T4 | EPSILON
T4 -> , E T4 | EPSILON
X -> . X’ | [ E ]
X’ -> length P | substring ( E T2 ) | ID ( T3 )
F -> t | R
t -> LIT_INT | TRUE | FALSE | ID | LIT_STR | THIS | NULL

R -> { El } | Un T | ( E )
El -> E El’ | EPSILON
El’-> , E El’ | EPSILON

Un -> - | !

*/