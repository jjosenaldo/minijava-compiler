#ifndef FIRSTS_OF_NONTERMINALS_H
#define FIRSTS_OF_NONTERMINALS_H

#include "token.h"

// class
#define F_Goal(x) x == TOK_CLASS 

// class
#define F_Main(x) x == TOK_CLASS 

//  id lbrace while systemoutprintln continue break return if semicolon boolean int void
#define F_BLK_STMT(x) x == TOK_ID || x == '{' || x == TOK_WHILE || x == TOK_SYSOUT || x == TOK_CONTINUE || x == TOK_BREAK || x == TOK_RETURN || x == TOK_IF || x == ';' || x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID

// id dot lbracket
#define F_AFTER_ID(x) x == TOK_ID || x == '.' || x == '['

// boolean int void
#define F_NON_CLASS_VAR_DEC(x) x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID

// boolean int void
#define F_NON_CLASS_TYPE(x) x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID

// lbracket
#define F_TYPE1(x) x == '['

// lbrace while systemoutprintln continue break return if semicolon
#define F_StmtWithoutId(x) x == '{' || x == TOK_WHILE || x == TOK_SYSOUT || x == TOK_CONTINUE || x == TOK_BREAK || x == TOK_RETURN || x  == TOK_IF || x == ';'

// else
#define F_OptElse(x) x == TOK_ELSE

// id lbrace while systemoutprintln continue break return if semicolon
#define F_STMT(x) x == TOK_ID || x == '{' || x == TOK_WHILE || x == TOK_SYSOUT || x == TOK_CONTINUE || x == TOK_BREAK || x == TOK_RETURN || x == TOK_IF || x == ';'

// eq dot lbracket
#define F_AfterIdExceptId(x) x == '=' || x == '.' || x == '['

// dot
#define F_Dot(x) x == '.'

// lbracket
#define F_Bracket(x) x == '['

// rbracket minus excl litint true false id litstr this null new lbrace (
#define F_BracketR(x) x == ']' || x == '-' || x == '!' || x == TOK_LIT_INT || x == TOK_TRUE || x == TOK_FALSE || x == TOK_ID || x == TOK_LIT_STR || x == TOK_THIS || x == TOK_NULL || x == TOK_NEW || x == '{' || x == '('

// dot lbracket
#define F_DotR(x) x == '.' || x == '['

// lbracket
#define F_BracketEmpty(x) x == '['

// class
#define F_CLASS_DCRLTS(x) x == TOK_CLASS 

// class
#define F_CLASS_DCRLT(x) x == TOK_CLASS 

// extends
#define F_Extends(x) x == TOK_EXTENDS

// lbrace
#define F_CLASS_BODY(x) x == '{'

// id boolean int void
#define F_CLASS_CONTENT(x) x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID || x == TOK_ID 

// id boolean int void
#define F_CLASS_COMPONENT(x) x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID || x == TOK_ID

// semicolon ( eq
#define F_REST_DEC(x) x == ';' || x == '(' || x == '='

// eq
#define F_Eq(x) x == '='

//  id lbrace while systemoutprintln continue break return if semicolon boolean int void
#define F_BLK_STMTS(x) F_BLK_STMT(x)

// id boolean int void
#define F_PARAMS_OPT(x) x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID || x == TOK_ID

// comma
#define F_PARAMS_REST(x) x == ','

// id boolean int void
#define F_PARAMS(x) x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID || x == TOK_ID

// id boolean int void
#define F_PARAM(x) x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID || x == TOK_ID

// id boolean int void
#define F_TYPE(x) x == TOK_BOOLEAN || x == TOK_INT || x == TOK_ID || x == TOK_VOID

// less lesseq greatereq greater isequal isdiff
#define F_Ep(x) x == '<' || x == TOK_LESS_EQ || x == TOK_GREATER_EQ || x == '>' || x == TOK_EQ || x == TOK_DIFF

// minus excl litint true false id litstr this null new lbrace (
#define F_E1(x) F_E(x)

// and or
#define F_E1p(x) x == TOK_AND || x == TOK_OR

// minus excl litint true false id litstr this null lbrace (
#define F_E2(x) F_E(x)

// plus minus
#define F_E2p(x) x == '+' || x == '-'

// minus excl litint true false id litstr this null lbrace (
#define F_E3(x) F_E(x)

// times div mod
#define F_E3p(x) x == '*' || x == '/' || x == '%'

// minus excl litint true false id litstr this null lbrace (
#define F_T(x) F_E(x)

// dot lbracket
#define F_Tp(x) x == '.' || x == '['

// comma
#define F_T4(x) x == ','

// dot lbracket
#define F_X(x) x == '.' || x == '['

// length substring id
#define F_Xp(x) x == TOK_LENGTH || x == TOK_SUBSTRING || x == TOK_ID

// comma
#define F_T2(x) x == ','

// (
#define F_P(x) x == '('

// 	litint true false id litstr this null new lbrace (
#define F_F(x) x == TOK_LIT_INT || x == TOK_TRUE || x == TOK_FALSE || x == TOK_ID || x == TOK_LIT_STR || \
        x == TOK_THIS || x == TOK_NULL || x == TOK_NEW || x == '{' || x == '('

// litint true false id litstr this null new
#define F_TT(x) x == TOK_LIT_INT || x == TOK_TRUE || x == TOK_FALSE || x == TOK_ID || x == TOK_LIT_STR || \
        x == TOK_THIS || x == TOK_NULL || x == TOK_NEW

// int boolean id
#define F_AfterNew(x) x == TOK_INT || x == TOK_BOOLEAN || x == TOK_ID

// lbracket (
#define F_AfterNewId(x) x == '[' || x == '('

// minus excl litint true false id litstr this null new lbrace (
#define F_T3(x) F_E(x) 

// lbracket
#define F_FilledBrackets(x) x == '['

// lbrace (
#define F_R(x) x == '{' || x == '('

// minus excl litint true false id litstr this null new lbrace (
#define F_El(x) F_E(x)

// minus excl litint true false id litstr this null new lbrace (
#define F_E(x) x == '-' || x == '!' || x == TOK_LIT_INT || x == TOK_TRUE || x == TOK_FALSE || x == TOK_ID || x == TOK_LIT_STR || x == TOK_THIS || x == TOK_NULL || x == TOK_NEW || x == '{' || x == '('

// comma
#define F_Elp(x) x == ','

// less lesseq greatereq greater isequal isdiff
#define F_Relop(x) x == '<' || x == TOK_LESS_EQ || x == '>' || x == TOK_GREAT_EQ || x == TOK_EQ || \
        x == TOK_DIFF

// and or
#define F_Boolop(x) x == TOK_AND || x == TOK_OR

// plus minus
#define F_Addop(x) x == '+' || x == '-'

//  times div mod
#define F_Multop(x) x == '/' || x == '*' || x == '%'

// minus excl
#define F_Unop(x) x == '-' || x == '!'

#endif