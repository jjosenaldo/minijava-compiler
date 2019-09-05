#ifndef PRED_SETS_H
#define PRED_SETS_H

#include "token.h"

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