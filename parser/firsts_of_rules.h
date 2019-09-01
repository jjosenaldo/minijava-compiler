#ifndef FIRSTS_OF_RULES_H
#define FIRSTS_OF_RULES_H

#include "token.h"
#include "firsts_of_nonterminals.h"

// Goal -> MainClass ClassDeclarations .
#define FR_GOAL(x) F_MAIN(x)

// MainClass -> class id lbrace void main ( string lbracket rbracket id ) lbrace Blockstatements rbrace rbrace .
#define FR_MAIN(x) x == TOK_CLASS

// Blockstatements -> BlockStatement Blockstatements .
#define FR_BLK_STMTS_1(x) F_BLK_STMT(x)

// Blockstatements -> .
#define FR_BLK_STMTS_2(x) x == EPS

// BlockStatement -> id AfterId semicolon .
#define FR_BLK_STMT_1(x) x == TOK_ID

// BlockStatement -> NonclassVarDec semicolon .
#define FR_BLK_STMT_2(x) F_NONCLASS_VAR_DEC(x)

// BlockStatement -> StmtWithoutId .
#define FR_BLK_STMT_3(x) F_StmtWithoutId(x)

// AfterId -> id Eq . 
#define FR_AFTER_ID_1(x) x == TOK_ID 

// AfterId -> AfterIdExceptId
#define FR_AFTER_ID_2(x) F_AfterIdExceptId(x)

// Eq -> eq E .
#define FR_Eq_1(x) x == '='

// Eq -> .
#define FR_Eq_2(x) x == EPS

// NonclassVarDec -> NonclassType id Eq .
#define FR_NONCLASS_VAR_DEC(x) F_NON_CLASS_TYPE(x)

// Type1 -> lbracket rbracket Type1 .
#define FR_TYPE1_1(x) x == '['

// Type1 -> .
#define FR_TYPE1_2(x) x == EPS

// NonclassType -> boolean Type1 .
#define FR_NON_CLASS_TYPE_1(x) x == TOK_BOOLEAN

// NonclassType -> int Type1 .
#define FR_NON_CLASS_TYPE_2(x) x == TOK_INT

// NonclassType -> void .
#define FR_NON_CLASS_TYPE_3(x) x == TOK_VOID

// Type -> NonclassType .
#define FR_TYPE_1(x) F_NON_CLASS_TYPE(x)

// Type -> id .
#define FR_TYPE_2(x) x == TOK_ID

// Stmt -> id AfterIdExceptId semicolon .
#define FR_Stmt_1(x) x == TOK_ID 

// Stmt -> StmtWithoutId .
#define FR_Stmt_2(x) F_StmtWithoutId(x) 

// StmtWithoutId -> lbrace Blockstatements rbrace .
#define FR_StmtWithoutId_1(x) x == '{'

// StmtWithoutId -> while ( E ) Stmt .
 #define FR_StmtWithoutId_2(x) x == TOK_WHILE

// StmtWithoutId -> system dot out dot println ( E ) semicolon .
#define FR_StmtWithoutId_3(x) x == TOK_SYSOUT

// StmtWithoutId -> continue semicolon .
#define FR_StmtWithoutId_4(x) x == TOK_CONTINUE

// StmtWithoutId -> break semicolon .
#define FR_StmtWithoutId_5(x) x == TOK_BREAK

// StmtWithoutId -> return E semicolon .
#define FR_StmtWithoutId_6(x) x == TOK_RETURN 

// StmtWithoutId -> if ( E ) Stmt OptElse .
#define FR_StmtWithoutId_7(x) x == TOK_IF 

// StmtWithoutId -> semicolon .
#define FR_StmtWithoutId_8(x) x == ';'

// OptElse -> else Stmt .
#define FR_OptElse_1(x) x == TOK_ELSE 

// OptElse -> .
#define FR_OptElse_2(x) x == EPS 

// AfterIdExceptId -> Dot Eq .
#define FR_AfterIdExceptId_1(x) F_Dot(x) 

// AfterIdExceptId -> Bracket Eq .
#define FR_AfterIdExceptId_2(x) F_Bracket(x)

// Dot -> dot id ( ParamsOpt ) DotR .
#define FR_Dot(x) x == '.'

// DotR -> dot id ( ParamsOpt ) DotR .
#define FR_DotR_1(x) x == '.'

// DotR -> lbracket E rbracket DotR .
#define FR_DotR_2(x) x == '['

// DotR -> .
#define FR_DotR_3(x) x == EPS

// Bracket -> lbracket BracketR .
#define FR_Bracket(x) x == '['

// BracketR -> E rbracket DotR .
#define FR_BracketR_1(x) F_E(x)

// BracketR -> rbracket BracketEmpty id .
#define FR_BracketR_2(x) x == ']'

// ClassDeclarations -> ClassDeclaration ClassDeclarations .
#define FR_CLASS_DCRLTS_1(x) F_CLASS_DCRLT(x)

// ClassDeclarations -> .
#define FR_CLASS_DCRLTS_2(x) x == EPS

// ClassDeclaration -> class id Extends ClassBody .
#define FR_CLASS_DCRLT(x) x == TOK_CLASS

// Extends -> extends id .
#define FR_EXTNDS_1(x) x == TOK_EXTENDS

// Extends -> .
#define FR_EXTNDS_2(x) x == EPS

// ClassBody -> lbrace ClassContent rbrace .
#define FR_CLASS_BODY(x) x == '{'

// ClassContent -> ClassComponent ClassContent .
#define FR_CLASS_CONTENT_1(x) F_CLASS_COMPONENT(x)

// ClassContent -> .
#define FR_CLASS_CONTENT_2(x) x == EPS

// ClassComponent -> Type id RestDec .
#define FR_CLASS_COMPONENT(x) F_TYPE(x)

// RestDec -> Eq semicolon .
#define FR_REST_DEC_1(x) F_Eq(x)

// RestDec -> ( ParamsOpt ) lbrace Blockstatements rbrace .
#define FR_REST_DEC_2(x) x == '('

// ParamsOpt -> Params .
#define FR_PARAMS_OPT_1(x) F_PARAMS(x)

// ParamsOpt1 -> .
#define FR_PARAMS_OPT_2(x) x == EPS

// Params -> Param ParamsRest .
#define FR_PARAMS(x) F_PARAM(x)

// ParamsRest -> comma Params .
#define FR_PARAMS_REST_1(x) x == ','

// ParamsRest -> .
#define FR_PARAMS_REST_2(x) x == EPS

// Param -> Type id .
#define FR_PARAM(x) F_TYPE(x)

// E -> E1 Ep .
#define FR_E(x) F_E1(x)

// Ep -> Relop E1 .
#define FR_Ep_1(x) F_Relop(x)

// Ep -> .
#define FR_Ep_2(x) x == EPS

// E1 -> E2 E1p .
#define FR_E1(x) F_E2(x)

// E1p -> Boolop E2 E1p .
#define FR_E1p_1(x) F_Boolop(x)

// E1p -> .
#define FR_E1p_2(x) x == EPS

// E2 -> E3 E2p .
#define FR_E2(x) F_E3(x)

// E2p -> Addop E3 E2p .
#define FR_E2p_1(x) F_Addop(x)

// E2p -> .
#define FR_E2p_2(x) x == EPS

// E3 -> T E3p .
#define FR_E3(x) F_T(x)

// E3p -> Multop T E3p .
#define FR_E3p_1(x) F_Multop(x)

// E3p -> .
#define FR_E3p_2(x) x == EPS

// T -> F Tp  .
#define FR_T_1(x) F_F(x)

// T -> Unop T .
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

// TT -> new AfterNew .
#define FR_TT_8(x) x == TOK_NEW

// AfterNew -> int FilledBrackets .
#define FR_AfterNew_1(x) x == TOK_INT 

// AfterNew -> boolean FilledBrackets .
#define FR_AfterNew_2(x) x == TOK_BOOLEAN

// AfterNew -> id AfterNewId .
#define FR_AfterNew_3(x) x == TOK_ID

// AfterNewId -> lbracket E rbracket FilledBrackets .
#define FR_AfterNewId_1(x) x == '['

// AfterNewId -> ( T3 ) .
#define FR_AfterNewId_2(x) x == '('

// FilledBrackets -> lbracket E rbracket FilledBrackets .
#define FR_FilledBrackets_1(x) x == '['

// FilledBrackets -> .
#define FR_FilledBrackets_2(x) x == EPS 

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

// Relop -> less  .
#define FR_Relop_1(x) x == '<'

// Relop ->  lesseq  .
#define FR_Relop_2(x) x == TOK_LESS_EQ

// Relop -> greatereq .
#define FR_Relop_3(x) x == TOK_GREAT_EQ

// Relop -> greater .
#define FR_Relop_4(x) x == '>'

// Relop -> isequal .
#define FR_Relop_5(x) x == TOK_EQ

// Relop -> isdiff .
#define FR_Relop_6(x) x == TOK_DIFF

// Boolop -> and .
#define FR_Boolop_1(x) x == TOK_AND

// Boolop -> or .
#define FR_Boolop_2(x) x == TOK_OR

// Addop -> plus .
#define FR_Addop_1(x) x == '+'

// Addop -> minus .
#define FR_Addop_2(x) x == '-'

// Multop -> times .
#define FR_Multop_1(x) x == '*'

// Multop -> div .
#define FR_Multop_2(x) x == '/'

// Multop -> mod .
#define FR_Multop_3(x) x == '%'

// Unop -> minus .
#define FR_Unop_1(x) x == '-'

// Unop -> excl .
#define FR_Unop_2(x) x == '!'













// VarDec -> NonclassVarDec .
#define FR_VAR_DEC(x) F_NONCLASS_VAR_DEC(x)

// VarDec ->  VarObjDec .
#define FR_VAR_DEC1(x) F_VAR_OBJ_DEC(x)





// IdType -> id Type1 .
#define FR_ID_TYPE(x) x == TOK_ID

// BracketEmpty -> lbracket rbracket BracketEmpty .
#define FR_BracketEmpty_1(x) x == '['

// BracketEmpty -> .
#define FR_BracketEmpty_2(x) x == EPS



#endif