#ifndef FIRSTS_OF_NONTERMINALS_H
#define FIRSTS_OF_NONTERMINALS_H

#include "token.h"

#define F_Goal(x) x == TOK_CLASS
#define F_MainClass(x) x == TOK_CLASS
#define F_BlockStatement(x) x == TOK_ID || x == '{' || x == TOK_WHILE || x == TOK_SYSOUT || x == TOK_CONTINUE || x == TOK_BREAK || x == TOK_RETURN || x == TOK_IF || x == ';' || x == TOK_THIS || x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID
#define F_AfterId(x) x == TOK_ID || x == '=' || x == '.' || x == '['
#define F_NonclassVarDec(x) x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID
#define F_NonclassType(x) x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID
#define F_Type1(x) x == '['
#define F_StmtWithoutId(x) x == '{' || x == TOK_WHILE || x == TOK_SYSOUT || x == TOK_CONTINUE || x == TOK_BREAK || x == TOK_RETURN || x == TOK_IF || x == ';' || x == TOK_THIS
#define F_OptElse(x) x == TOK_ELSE
#define F_Stmt(x) x == TOK_ID || x == '{' || x == TOK_WHILE || x == TOK_SYSOUT || x == TOK_CONTINUE || x == TOK_BREAK || x == TOK_RETURN || x == TOK_IF || x == ';' || x == TOK_THIS
#define F_OptExp(x) x == TOK_THIS || x == '-' || x == '!' || x == TOK_LIT_INT || x == TOK_TRUE || x == TOK_FALSE || x == TOK_ID || x == TOK_LIT_STR || x == TOK_NULL || x == TOK_NEW || x == '{' || x == '('
#define F_AfterThisInStmt(x) x == '(' || x == '=' || x == '.' || x == '['
#define F_OptAfterIdExceptId(x) x == '=' || x == '.' || x == '['
#define F_AfterIdExceptId(x) x == '=' || x == '.' || x == '['
#define F_Dot(x) x == '.'
#define F_Bracket(x) x == '['
#define F_BracketR(x) x == ']' || x == TOK_THIS || x == '-' || x == '!' || x == TOK_LIT_INT || x == TOK_TRUE || x == TOK_FALSE || x == TOK_ID || x == TOK_LIT_STR || x == TOK_NULL || x == TOK_NEW || x == '{' || x == '('
#define F_DotR(x) x == '.' || x == '['
#define F_BracketEmpty(x) x == '['
#define F_ClassDeclarations(x) x == TOK_CLASS
#define F_ClassDeclaration(x) x == TOK_CLASS
#define F_Extends(x) x == TOK_EXTENDS
#define F_ClassBody(x) x == '{'
#define F_ClassContent(x) x == TOK_ID || x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID
#define F_ClassComponent(x) x == TOK_ID || x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID
#define F_RestDec(x) x == ';' || x == '(' || x == '='
#define F_Eq(x) x == '='
#define F_Blockstatements(x) x == TOK_ID || x == '{' || x == TOK_WHILE || x == TOK_SYSOUT || x == TOK_CONTINUE || x == TOK_BREAK || x == TOK_RETURN || x == TOK_IF || x == ';' || x == TOK_THIS || x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID
#define F_ParamsOpt(x) x == TOK_ID || x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID
#define F_ParamsRest(x) x == ','
#define F_Params(x) x == TOK_ID || x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID
#define F_Param(x) x == TOK_ID || x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID
#define F_Type(x) x == TOK_ID || x == TOK_BOOLEAN || x == TOK_INT || x == TOK_VOID
#define F_Ep(x) x == '<' || x == TOK_LESS_EQ || x == TOK_GREATER_EQ || x == '>' || x == TOK_EQ || x == TOK_DIFF
#define F_E1(x) x == TOK_THIS || x == '-' || x == '!' || x == TOK_LIT_INT || x == TOK_TRUE || x == TOK_FALSE || x == TOK_ID || x == TOK_LIT_STR || x == TOK_NULL || x == TOK_NEW || x == '{' || x == '('
#define F_E1p(x) x == TOK_AND || x == TOK_OR
#define F_E2(x) x == TOK_THIS || x == '-' || x == '!' || x == TOK_LIT_INT || x == TOK_TRUE || x == TOK_FALSE || x == TOK_ID || x == TOK_LIT_STR || x == TOK_NULL || x == TOK_NEW || x == '{' || x == '('
#define F_E2p(x) x == '+' || x == '-'
#define F_E3(x) x == TOK_THIS || x == '-' || x == '!' || x == TOK_LIT_INT || x == TOK_TRUE || x == TOK_FALSE || x == TOK_ID || x == TOK_LIT_STR || x == TOK_NULL || x == TOK_NEW || x == '{' || x == '('
#define F_E3p(x) x == '*' || x == '/' || x == '%'
#define F_T(x) x == TOK_THIS || x == '-' || x == '!' || x == TOK_LIT_INT || x == TOK_TRUE || x == TOK_FALSE || x == TOK_ID || x == TOK_LIT_STR || x == TOK_NULL || x == TOK_NEW || x == '{' || x == '('
#define F_T4(x) x == ','
#define F_X(x) x == '.' || x == '['
#define F_Xp(x) x == TOK_LENGTH || x == TOK_SUBSTRING || x == TOK_ID
#define F_T2(x) x == ','
#define F_P(x) x == '('
#define F_F(x) x == TOK_LIT_INT || x == TOK_TRUE || x == TOK_FALSE || x == TOK_ID || x == TOK_LIT_STR || x == TOK_NULL || x == TOK_NEW || x == '{' || x == '('
#define F_TT(x) x == TOK_LIT_INT || x == TOK_TRUE || x == TOK_FALSE || x == TOK_ID || x == TOK_LIT_STR || x == TOK_NULL || x == TOK_NEW
#define F_AfterThisInExp(x) x == '.'
#define F_RestThisInExp(x) x == '('
#define F_Tp(x) x == '.' || x == '['
#define F_AfterNew(x) x == TOK_INT || x == TOK_BOOLEAN || x == TOK_ID
#define F_AfterNewId(x) x == '[' || x == '('
#define F_T3(x) x == TOK_THIS || x == '-' || x == '!' || x == TOK_LIT_INT || x == TOK_TRUE || x == TOK_FALSE || x == TOK_ID || x == TOK_LIT_STR || x == TOK_NULL || x == TOK_NEW || x == '{' || x == '('
#define F_FilledBrackets(x) x == '['
#define F_R(x) x == '{' || x == '('
#define F_El(x) x == TOK_THIS || x == '-' || x == '!' || x == TOK_LIT_INT || x == TOK_TRUE || x == TOK_FALSE || x == TOK_ID || x == TOK_LIT_STR || x == TOK_NULL || x == TOK_NEW || x == '{' || x == '('
#define F_E(x) x == TOK_THIS || x == '-' || x == '!' || x == TOK_LIT_INT || x == TOK_TRUE || x == TOK_FALSE || x == TOK_ID || x == TOK_LIT_STR || x == TOK_NULL || x == TOK_NEW || x == '{' || x == '('
#define F_Elp(x) x == ','
#define F_Relop(x) x == '<' || x == TOK_LESS_EQ || x == TOK_GREAT_EQ || x == '>' || x == TOK_EQ || x == TOK_DIFF
#define F_Boolop(x) x == TOK_AND || x == TOK_OR
#define F_Addop(x) x == '+' || x == '-'
#define F_Multop(x) x == '*' || x == '/' || x == '%'
#define F_Unop(x) x == '-' || x == '!'


#endif