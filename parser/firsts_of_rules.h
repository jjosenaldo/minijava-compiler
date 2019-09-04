#ifndef FIRSTS_OF_RULES_H
#define FIRSTS_OF_RULES_H

#include "token.h"
#include "firsts_of_nonterminals.h"

#define FR_Goal(x) F_MainClass(x)
#define FR_Main(x) x == TOK_CLASS
#define FR_BLK_STMTS_1(x) F_BlockStatement(x)
#define FR_BLK_STMT_1(x) x == TOK_ID
#define FR_BLK_STMT_2(x) F_NonclassVarDec(x)
#define FR_BLK_STMT_3(x) F_StmtWithoutId(x)
#define FR_AFTER_ID_1(x) x == TOK_ID 
#define FR_AFTER_ID_2(x) F_AfterIdExceptId(x)
#define FR_Eq_1(x) x == '='
#define FR_NONCLASS_VAR_DEC(x) F_NonclassType(x)
#define FR_TYPE1_1(x) x == '['
#define FR_NON_CLASS_TYPE_1(x) x == TOK_BOOLEAN
#define FR_NON_CLASS_TYPE_2(x) x == TOK_INT
#define FR_NON_CLASS_TYPE_3(x) x == TOK_VOID
#define FR_TYPE_1(x) F_NonclassType(x)
#define FR_TYPE_2(x) x == TOK_ID
#define FR_Stmt_1(x) x == TOK_ID 
#define FR_Stmt_2(x) F_StmtWithoutId(x) 
#define FR_OptElse_1(x) x == TOK_ELSE 
#define FR_OptExp_1(x) F_E(x)
#define FR_StmtWithoutId_1(x) x == '{'
#define FR_StmtWithoutId_2(x) x == TOK_WHILE
#define FR_StmtWithoutId_3(x) x == TOK_SYSOUT
#define FR_StmtWithoutId_4(x) x == TOK_CONTINUE
#define FR_StmtWithoutId_5(x) x == TOK_BREAK
#define FR_StmtWithoutId_6(x) x == TOK_RETURN 
#define FR_StmtWithoutId_7(x) x == TOK_IF 
#define FR_StmtWithoutId_8(x) x == ';'
#define FR_StmtWithoutId_9(x) x == TOK_THIS
#define FR_AfterThisInStmt_1(x) F_AfterIdExceptId(x) 
#define FR_AfterThisInStmt_2(x) x == '('
#define FR_OptAfterIdExceptId_1(x) F_AfterIdExceptId(x)
#define FR_AfterIdExceptId_1(x) F_Dot(x) 
#define FR_AfterIdExceptId_2(x) F_Bracket(x)
#define FR_AfterIdExceptId_3(x) x == '='
#define FR_Dot(x) x == '.'
#define FR_DotR_1(x) x == '.'
#define FR_DotR_2(x) x == '['
#define FR_Bracket(x) x == '['
#define FR_BracketR_1(x) F_E(x)
#define FR_BracketR_2(x) x == ']'
#define FR_BracketEmpty_1(x) x == '['
#define FR_CLASS_DCRLTS_1(x) F_ClassDeclaration(x)
#define FR_CLASS_DCRLT(x) x == TOK_CLASS
#define FR_EXTNDS_1(x) x == TOK_EXTENDS
#define FR_CLASS_BODY(x) x == '{'
#define FR_CLASS_CONTENT_1(x) F_ClassComponent(x)
#define FR_CLASS_COMPONENT(x) F_Type(x)
#define FR_REST_DEC_1(x) F_Eq(x) || x == ';'
#define FR_REST_DEC_2(x) x == '('
#define FR_PARAMS_OPT_1(x) F_Params(x)
#define FR_PARAMS(x) F_Params(x)
#define FR_PARAMS_REST_1(x) x == ','
#define FR_PARAM(x) F_Type(x)
#define FR_E(x) F_E1(x)
#define FR_Ep_1(x) F_Relop(x)
#define FR_E1(x) F_E2(x)
#define FR_E1p_1(x) F_Boolop(x)
#define FR_E2(x) F_E3(x)
#define FR_E2p_1(x) F_Addop(x)
#define FR_E3(x) F_T(x)
#define FR_E3p_1(x) F_Multop(x)
#define FR_T_1(x) F_F(x)
#define FR_T_2(x) F_Unop(x)
#define FR_T_3(x) x == TOK_THIS
#define FR_Tp_1(x) F_X(x)
#define FR_T2_1(x) x == ','
#define FR_T3_1(x) F_E(x)
#define FR_T4_1(x) x == ','
#define FR_X_1(x) x == '.' 
#define FR_X_2(x) x == '['
#define FR_Xp_1(x) x == TOK_LENGTH
#define FR_Xp_2(x) x == TOK_SUBSTRING
#define FR_Xp_3(x) x == TOK_ID
#define FR_P_1(x) x == '('
#define FR_F_1(x) F_TT(x)
#define FR_F_2(x) F_R(x)
#define FR_TT_1(x) x == TOK_LIT_INT
#define FR_TT_2(x) x == TOK_TRUE
#define FR_TT_3(x) x == TOK_FALSE
#define FR_TT_4(x) x == TOK_ID
#define FR_TT_5(x) x == TOK_LIT_STR
#define FR_TT_6(x) x == TOK_NULL
#define FR_TT_7(x) x == TOK_NEW
#define FR_AfterThisInExp_1(x) x == '.'
#define FR_RestThisInExp_1(x) x == '('
#define FR_AfterNew_1(x) x == TOK_INT 
#define FR_AfterNew_2(x) x == TOK_BOOLEAN
#define FR_AfterNew_3(x) x == TOK_ID
#define FR_AfterNewId_1(x) x == '['
#define FR_AfterNewId_2(x) x == '('
#define FR_FilledBrackets_1(x) x == '['
#define FR_R_1(x) x == '{'
#define FR_R_2(x) x == '('
#define FR_El_1(x) F_E(x)
#define FR_Elp_1(x) x == ','
#define FR_Relop_1(x) x == '<'
#define FR_Relop_2(x) x == TOK_LESS_EQ
#define FR_Relop_3(x) x == TOK_GREAT_EQ
#define FR_Relop_4(x) x == '>'
#define FR_Relop_5(x) x == TOK_EQ
#define FR_Relop_6(x) x == TOK_DIFF
#define FR_Boolop_1(x) x == TOK_AND
#define FR_Boolop_2(x) x == TOK_OR
#define FR_Addop_1(x) x == '+'
#define FR_Addop_2(x) x == '-'
#define FR_Multop_1(x) x == '*'
#define FR_Multop_2(x) x == '/'
#define FR_Multop_3(x) x == '%'
#define FR_Unop_1(x) x == '-'
#define FR_Unop_2(x) x == '!'

#endif