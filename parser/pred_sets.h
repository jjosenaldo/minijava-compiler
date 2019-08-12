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

#define F_STMT(x) x == '{' || x == TOK_WHILE || x == TOK_PRINT || x == TOK_ID || x == TOK_CONTINUE || \
                  x == TOK_BREAK || x == TOK_RETURN || x == ';' || x == TOK_IF

#define F_AFT_ID(x) x == '[' || x == '='


#endif