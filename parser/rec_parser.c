#include "rec_parser.h"
#include "pred_sets.h"
#include "firsts_of_rules.h"
#include <stdio.h>
#include <stdlib.h> // exit()

void match(char tok_id){
	if (lookahead.id == tok_id){
		printf("%s", lookahead.lexem);
		lookahead = getNextToken();
	} else{
		if(lookahead.id == TOK_EOF)
		printf("\n\nSYNTAX ERROR: the token %c couldn't be matched with the end of file!\n", tok_id);
		else
			printf("\n\nSYNTAX ERROR: the token %c couldn't be matched with the input symbol %s!\n", tok_id, lookahead.lexem);
		exit(EXIT_FAILURE);
	}
}

void error(char* nonterminal) {
	printf("\n\nSYNTAX ERROR: the non-terminal %s couldn't be matched with the input symbol %s!\n", nonterminal, lookahead.lexem);
	exit(EXIT_FAILURE);
}

void parse(){
	lookahead = getNextToken();
    E();
    printf("\n");
}

// Goal -> MainClass ClassDeclarations .
void Goal() {
	printf("Goal { ");
	MainClass();
	printf(", ");
	ClassDeclarations();
	printf(" }");
}

// MainClass -> class id lbrace void main ( string lbracket rbracket id ) lbrace Blockstatements rbrace rbrace .
void MainClass() {
	printf("MainClass { ");
	match(TOK_CLASS);
	printf(", ");
	match(TOK_ID);
	printf(", ");
	match('{');
	printf(", ");
	match(TOK_VOID);
	printf(", ");
	match(TOK_MAIN);
	printf(", ");
	match('(');
	printf(", ");
	match(TOK_STRING);
	printf(", ");
	match('[');
	printf(", ");
	match(']');
	printf(", ");
	match(TOK_ID);
	printf(", ");
	match(')');
	printf(", ");
	match('{');
	printf(", ");
	BlockStmts();
	printf(", ");
	match('}');
	printf(", ");
	match('}');
	printf(" }");
}

// Blockstatements -> BlockStatement Blockstatements | .
void BlockStmts(){
	printf("BlockStmts { ");
	if(FR_BLK_STMT_1(lookahead.id)){
		BlockStmt();
		printf(", ");
		BlockStmts();
	}
	else printf("\u03B5") /* Epsilon */;
	printf(" }");
}

// BlockStatement -> id AfterId semicolon | NonclassVarDec semicolon | StmtWithoutId .
void BlockStmt(){
	printf("BlockStmt { ");
	if(FR_BLK_STMT_1(lookahead.id)){
		match(TOK_ID);
		AfterId();
		match(';');
	} else if (FR_BLK_STMT_2(lookahead.id)) {
		NonClassVarDec();
		match(';');
	} else if (FR_BLK_STMT_3(lookahead.id)) {
		StmtWithoutId();
	} else error("BlockStmt");
	printf(" }");
}

// AfterId -> id Eq | AfterIdExceptId . 
void AfterId(){
	printf("AfterId {");
	if(FR_AFTER_ID_1(lookahead.id)){
		match(TOK_ID);
		match('=');
	} else if(FR_AFTER_ID_2(lookahead.id)){
		AfterIdExceptId();
	} else error("AfterId");
	printf("}");
}

// Eq -> eq E | .
void Eq(){
	printf("Eq {");
	if(FR_Eq_1(lookahead.id)){
		match('=');
		E();
	} else printf("\u03B5") /* Epsilon */;
	printf("}");
}

// NonclassVarDec -> NonclassType id Eq .
void NonClassVarDec(){
	if(FR_NONCLASS_VAR_DEC(lookahead.id)){
		NonClassType();
		match(TOK_ID);
		Eq();
	} else error("NonClassVarDec");
}

// Type1 -> lbracket rbracket Type1 | .
void Type1(){
	printf("Type1 { ");
	if(FR_TYPE1_1(lookahead.id)) {
		match('[');
		printf(", ");
		match(']');
		printf(", ");
		Type1();
	}
	else printf("\u03B5") /* Epsilon */;
	printf(" }");
}

// NonclassType -> boolean Type1 | int Type1 | void .
void NonClassType(){
	printf("NonClassType { ");
	if(FR_NON_CLASS_TYPE_1(lookahead.id)) {
		match(TOK_BOOLEAN);
		printf(", ");
		Type1();
	} else if(FR_NON_CLASS_TYPE_2(lookahead.id)) {
		match(TOK_INT);
		printf(", ");
		Type1();
	} else if(FR_NON_CLASS_TYPE_3(lookahead.id)) {
		match(TOK_VOID);
		printf(", ");
		Type1();
	} else printf("\u03B5") /* Epsilon */;
	printf(" }");
}

// Type -> NonclassType | id Type1 .
void Type() {
	printf("Type { ");
	if(FR_TYPE_1(lookahead.id)) {
		NonClassType();
	} else if (FR_TYPE_2(lookahead.id)) {
		match(TOK_ID);
	}
	else printf("\u03B5") /* Epsilon */;
	printf(" }");
}

// Stmt -> id AfterIdExceptId semicolon | StmtWithoutId .
void Stmt() {
	printf("Stmt { ");
	if(FR_Stmt_1(lookahead.id)){
		match(TOK_ID);
		AfterIdExceptId();
		match(';');
	} else if(FR_Stmt_2(lookahead.id)){
		StmtWithoutId();
	} else error("Stmt");
	printf(" }");
}

// StmtWithoutId -> lbrace Blockstatements rbrace |  while ( E ) Stmt | system dot out dot println ( E ) semicolon  | continue semicolon | break semicolon | return E semicolon | if ( E ) Stmt OptElse | semicolon .
void StmtWithoutId(){
	printf("StmtWithoutId {");
	if(FR_StmtWithoutId_1(lookahead.id)){
		match('{');
		BlockStmts();
		match('}');
	} else if(FR_StmtWithoutId_2(lookahead.id)){
		match(TOK_WHILE);
		match('(');
		E();
		match(')');
		Stmt();
	} else if(FR_StmtWithoutId_3(lookahead.id)){
		match(TOK_SYSOUT);
		match('(');
		E();
		match(')');
		match(';');
	} else if(FR_StmtWithoutId_4(lookahead.id)){
		match(TOK_CONTINUE);
		match(';');
	} else if(FR_StmtWithoutId_5(lookahead.id)){
		match(TOK_BREAK);
		match(';');
	} else if(FR_StmtWithoutId_6(lookahead.id)){
		match(TOK_RETURN);
		E();
		match(';');
	} else if(FR_StmtWithoutId_7(lookahead.id)){
		match(';');
	} else error("StmtWithoutId");
	printf("}");
}

// OptElse -> else Stmt | .
void OptElse(){
	// TODO
}

// AfterIdExceptId -> Dot Eq | Bracket Eq .
void AfterIdExceptId(){
	printf("AfterIdExceptId {");
	if(FR_AfterIdExceptId_1(lookahead.id)){
		Dot();
		Eq();
	} else if (FR_AfterIdExceptId_2(lookahead.id)){
		Bracket();
		Eq();
	} else error("AfterIdExceptId");
	printf("}");
}

// Dot -> dot id ( ParamsOpt ) DotR .
void Dot(){
	printf("Dot {");
	if(FR_Dot(lookahead.id)){
		match('.');
		match(TOK_ID);
		match('(');
		ParamsOpt();
		match(')');
		DotR();
	} else error("Dot");
	printf("}");
}

// DotR -> dot id ( ParamsOpt ) DotR | lbracket E rbracket DotR | .
void DotR(){
	printf("DotR {");
	if(FR_DotR_1(lookahead.id)){
		match('.');
		match(TOK_ID);
		match('(');
		ParamsOpt();
		match(')');
		DotR();
	} else if(FR_DotR_2(lookahead.id)){
		match('[');
		E();
		match(']');
		DotR();
	} else printf("\u03B5") /* Epsilon */;
	printf("}");
}

// Bracket -> lbracket BracketR .
void Bracket(){
	printf("Bracket {");
	if(FR_Dot(lookahead.id)){
		match('[');
		BracketR();
	} else error("Bracket");
	printf("}");
}

// BracketR -> E rbracket DotR | rbracket BracketEmpty id .
void BracketR(){
	printf("BracketR {");
	if(FR_BracketR_1(lookahead.id)){
		E();
		match(']');
		DotR();
	} else if(FR_BracketR_2(lookahead.id)){
		E();
		match(']');
		BracketEmpty();
		match(TOK_ID);
	} else error("BracketR");
	printf("}");
}

// BracketEmpty -> lbracket rbracket BracketEmpty | .
void BracketEmpty(){
	printf("BracketEmpty {");
	if(FR_BracketEmpty_1(lookahead.id)){
		match('[');
		match(']');
		BracketEmpty();
	} else printf("\u03B5") /* Epsilon */;
	printf("}");
}

// ClassDeclarations -> ClassDeclaration ClassDeclarations  | .
void ClassDeclarations() {
	printf("ClassDeclarations { ");
	if(FR_CLASS_DCRLTS_1(lookahead.id)) {
		ClassDeclaration();
		printf(", ");
		ClassDeclarations();
	}
	else printf("\u03B5") /* Epsilon */;
	printf(" }");
}

// ClassDeclaration -> class id Extends ClassBody .
void ClassDeclaration() {
	printf("ClassDeclaration { ");
	match(TOK_CLASS);
	printf(", ");
	match(TOK_ID);
	printf(", ");
	Extends();
	printf(", ");
	ClassBody();
	printf(" }");
}

// Extends -> extends id | .
void Extends() {
	printf("Extends { ");
	if(FR_EXTNDS_1(lookahead.id)) {
		match(TOK_EXTENDS);
		printf(", ");
		match(TOK_ID);
	}
	else printf("\u03B5") /* Epsilon */;
	printf(" }");
}

// ClassBody -> lbrace ClassContent rbrace .
void ClassBody(){
	printf("ClassBody { ");
	match('{');
	printf(", ");
	ClassContent();
	printf(", ");
	match('}');
	printf(" }");
}

// ClassContent -> ClassComponent ClassContent | .
void ClassContent(){
	printf("ClassContent { ");
	if(FR_CLASS_CONTENT_1(lookahead.id)){
		ClassComponent();
		printf(", ");
		ClassContent();
	}
	else printf("\u03B5") /* Epsilon */;
	printf(" }");
}

// ClassComponent -> Type id RestDec .
void ClassComponent(){
	printf("ClassComponent { ");
	Type();
	printf(", ");
	match(TOK_ID);
	printf(", ");
	RestDec();
	printf(" }");
}

// RestDec -> Eq semicolon | ( ParamsOpt ) lbrace Blockstatements rbrace .
void RestDec() {
	printf("RestDec { ");
	if(FR_REST_DEC_1(lookahead.id)) {
		match('=');
		match(';');
	} else if (FR_REST_DEC_2(lookahead.id)) {
		match('(');
		printf(", ");
		ParamsOpt();
		printf(", ");
		match(')');
		printf(", ");
		match('{');
		printf(", ");
		BlockStmts();
		printf(", ");
		match('}');
	} else error("RestDec");
	printf(" }");
}

// ParamsOpt -> Params | .
void ParamsOpt(){
	printf("ParamsOpt { ");
	if(FR_PARAMS_OPT_1(lookahead.id)) {
		Params();
	}
	else printf("\u03B5") /* Epsilon */;
	printf(" }");
}

// Params -> Param ParamsRest .
void Params(){
	printf("Params { ");
	Param();
	printf(", ");
	ParamsRest();
	printf(" }");
}

// ParamsRest -> comma Params | .
void ParamsRest(){
	printf("ParamsRest { ");
	if(FR_PARAMS_REST_1(lookahead.id)) {
		match(',');
		printf(", ");
		Params();
	}
	else printf("\u03B5") /* Epsilon */;
	printf(" }");
}

// Param -> Type id .
void Param() {
	printf("Param { ");
	Type();
	printf(", ");
	match(TOK_ID);
	printf(" }");
}

// E -> E1 Ep .
void E() {
	printf("E {");
	E1();
	printf(", ");
	Ep();
	printf(" }");
}

// Ep -> Relop E1 | .
void Ep() {
	printf("Ep { ");
	if(FR_Ep_1(lookahead.id)) {
		Relop();
		printf(", ");
		E1();
	}
	else printf("\u03B5") /* Epsilon */;
	printf(" }");
}

// E1 -> E2 E1p .
void E1() {
	printf("E1 { ");
	E2();
	printf(", ");
	E1p();
	printf(" }");
}

// E1p -> Boolop E2 E1p | .
void E1p() {
	printf("E1p { ");
	if(FR_E1p_1(lookahead.id)) {
		Boolop();
		printf(", ");
		E2();
		printf(", ");
		E1p();
	}
	else printf("\u03B5") /* Epsilon */;
	printf(" }");
}

// E2 -> E3 E2p .
void E2() {
	printf("E2 { ");
	E3();
	printf(", ");
	E2p();
	printf(" }");
}

// E2p -> Addop E3 E2p | .
void E2p() {
	printf("E2p { ");
	if(FR_E2p_1(lookahead.id)) {
		Addop();
		printf(", ");
		E3();
		printf(", ");
		E2p();
	}
	else printf("\u03B5") /* Epsilon */;
	printf(" }");
}

// E3 -> T E3p .
void E3() {
	printf("E3 { ");
	T();
	printf(", ");
	E3p();
	printf(" }");
}

// E3p -> Multop T E3p | .
void E3p() {
	printf("E3p { ");
	if(FR_E3p_1(lookahead.id)) {
		Multop();
		printf(", ");
		T();
		printf(", ");
		E3p();
	}
	else printf("\u03B5") /* Epsilon */;
	printf(" }");
}

// T -> F Tp | Unop T .
void T() {
	printf("T { ");
	if(FR_T_1(lookahead.id)) {
		F();
		printf(", ");
		Tp();
	}
	else if(FR_T_2(lookahead.id)) {
		Unop();
		printf(", ");
		T();
	}
	else error("T");
	printf(" }");
}

// Tp -> X Tp | .
void Tp() {
	printf("Tp { ");
	if(FR_Tp_1(lookahead.id)) {
		X();
		printf(", ");
		Tp();
	}
	else printf("\u03B5") /* Epsilon */;
	printf(" }");
}

// T2 -> comma E | .
void T2() {
	printf("T2 { ");
	if(FR_T2_1(lookahead.id)) {
		match(',');
		printf(", ");
		E();
	}
	else printf("\u03B5") /* Epsilon */;
	printf(" }");
}

// T3 -> E T4 | .
void T3() {
	printf("T3 { ");
	if(FR_T3_1(lookahead.id)) {
		E();
		printf(", ");
		T4();
	}
	else printf("\u03B5") /* Epsilon */;
	printf(" }");
}

void T4() {
	printf("T4 { ");
	if(FR_T4_1(lookahead.id)) {
		match(',');
		printf(", ");
		E();
		printf(", ");
		T4();
	}
	else printf("\u03B5") /* Epsilon */;
	printf(" }");
}

void X() {
	printf("X { ");
	if(FR_X_1(lookahead.id)) {
		match('.');
		printf(", ");
		Xp();
	}
	else if(FR_X_2(lookahead.id)) {
		match('[');
		printf(", ");
		E();
		printf(", ");
		match(']');
	}
	else error("X");
	printf(" }");
}

void Xp() {
	printf("Xp { ");
	if(FR_Xp_1(lookahead.id)) {
		match(TOK_LENGTH);
		printf(", ");
		P();
	}
	else if(FR_Xp_2(lookahead.id)) {
		match(TOK_SUBSTRING);
		printf(", ");
		match('(');
		printf(", ");
		E();
		printf(", ");
		T2();
		printf(", ");
		match(')');
	}
	else if(FR_Xp_3(lookahead.id)) {
		match(TOK_ID);
		printf(", ");
		match('(');
		printf(", ");
		T3();
		printf(", ");
		match(')');
	}
	else error("Xp");
	printf(" }");
}

void P() {
	printf("P { ");
	if(FR_P_1(lookahead.id)) {
		match('(');
		printf(", ");
		match(')');
	}
	else printf("\u03B5") /* Epsilon */;
	printf(" }");
}

void F() {
	printf("F { ");
	if(FR_F_1(lookahead.id)) {
		TT();
	}
	else if(FR_F_2(lookahead.id)) {
		R();
	}
	else error("F");
	printf(" }");
}

void TT() {
	printf("TT { ");
	if(FR_TT_1(lookahead.id))
		match(TOK_LIT_INT);
	else if(FR_TT_2(lookahead.id))
		match(TOK_TRUE);
	else if(FR_TT_3(lookahead.id))
		match(TOK_FALSE);
	else if(FR_TT_4(lookahead.id))
		match(TOK_ID);
	else if(FR_TT_5(lookahead.id))
		match(TOK_LIT_STR);
	else if(FR_TT_6(lookahead.id))
		match(TOK_THIS);
	else if(FR_TT_7(lookahead.id))
		match(TOK_NULL);
	else if(FR_TT_8(lookahead.id)){
		match(TOK_NEW);
		AfterNew();
	}
	else error("TT");
	printf(" }");
}

void AfterNew(){
	
}

void R() {
	printf("R { ");
	if(FR_R_1(lookahead.id)) {
		match('{');
		printf(", ");
		El();
		printf(", ");
		match('}');
	}
	else if(FR_R_2(lookahead.id)) {
		match('(');
		printf(", ");
		E();
		printf(", ");
		match(')');
	}
	else error("R");
	printf(" }");
}

void El() {
	printf("El { ");
	if(FR_El_1(lookahead.id)) {
		E();
		printf(", ");
		Elp();
	}
	else printf("\u03B5") /* Epsilon */;
	printf(" }");
}

void Elp() {
	printf("Elp { ");
	if(FR_Elp_1(lookahead.id)) {
		match(',');
		printf(", ");
		E();
		printf(", ");
		Elp();
	}
	else error("Elp");
	printf(" }");
}



void VarObjDec(){
	if(FR_VAR_OBJ_DEC(lookahead.id)){
		match(TOK_ID);
		match(TOK_ID);
		match(';');
	} else error("VarObjDec");
}

void RemainingArrAssignment(){
	if(FR_RMNG_ARR_ASSGMT(lookahead.id)){
		match('[');
		E();
		match(']');
		match('=');
		E();
	} else if(FR_RMNG_ARR_ASSGMT1(lookahead.id)){
		match('=');
		E();
	}
}

void Relop() {
	if(FR_Relop_1(lookahead.id))
		match('<');
	else if(FR_Relop_2(lookahead.id))
		match(TOK_LESS_EQ);
	else if(FR_Relop_3(lookahead.id))
		match(TOK_GREAT_EQ);
	else if(FR_Relop_4(lookahead.id))
		match('>');
	else if(FR_Relop_5(lookahead.id))
		match(TOK_EQ);
	else if(FR_Relop_6(lookahead.id))
		match(TOK_DIFF);
	else
		error("Relop");
}

void Boolop() {
	if(FR_Boolop_1(lookahead.id))
		match(TOK_AND);
	else if(FR_Boolop_2(lookahead.id))
		match(TOK_OR);
	else
		error("Boolop");
}

void Addop() {
	if(FR_Addop_1(lookahead.id))
		match('+');
	else if(FR_Addop_2(lookahead.id))
		match('-');
	else
		error("Addop");
}

void Multop() {
	if(FR_Multop_1(lookahead.id))
		match('*');
	else if(FR_Multop_2(lookahead.id))
		match('/');
	else if(FR_Multop_3(lookahead.id))
		match('%');
	else
		error("Multop");
}

void Unop() {
	if(FR_Unop_1(lookahead.id))
		match('-');
	else if(FR_Unop_2(lookahead.id))
		match('!');
	else
		error("Unop");
}

// ---------- ^^^^^^^ Gilney ^^^^^^^ ---------- //