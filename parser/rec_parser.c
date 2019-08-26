#include "rec_parser.h"
#include "pred_sets.h"
#include "stdio.h"
#include <stdlib.h> // exit()

void match(char tok_id){
	if (lookahead.id == tok_id){
		printf("%s", lookahead.lexem);
		lookahead = getNextToken();
	} else{
		printf("\n\nSYNTAX ERROR: the token %c couldn't be matched with the input symbol %s!\n", tok_id, lookahead.lexem);
		exit(EXIT_FAILURE);
	}
}

void parse(){
	lookahead = getNextToken();
    E();
    printf("\n");
}
// ---------- vvvvvvv Giovannni vvvvvvv ---------- //

void Goal() {
	MainClass();
	ClassDeclarations();
}

void MainClass() {
	match(TOK_CLASS);
	match(TOK_ID);
	match('{');
	match(TOK_VOID);
	match(TOK_MAIN);
	match('(');
	match(TOK_STRING);
	match('[');
	match(']');
	match(TOK_ID);
	match(')');
	match('{');
	BlockStmts();
	match('}');
	match('}');
}

void BlockStmts(){
	if(FR_BLK_STMT(lookahead.id)){
		BlockStmt();
		BlockStmts();
	}
}

void BlockStmt(){
	if(FR_NONCLASS_VAR_DEC(lookahead.id)){
		NonClassVarDec();
	} else if (FR_STMT(lookahead.id)) {
		Stmt();
	} else if (lookahead.id == TOK_ID) {
		match(TOK_ID);
		AfterId();
	} else error("BlockStatement");
}

void NonClassVarDec(){

}

void Stmt() {

}

void ClassDeclarations() {
	if(FR_CLASS_DCRLT(lookahead.id)) {
		ClassDeclaration();
		ClassDeclarations();
	}
}

void ClassDeclaration() {
	match(TOK_CLASS);
	match(TOK_ID);
	Extends();
	ClassBody();
}

void Extends() {
	if(FR_EXTNDS(lookahead.id)) {
		match(TOK_EXTENDS);
		match(TOK_ID);
	} else {}
}

void ClassBody(){
	match('{');
	ClassContent();
	match('}');
}

void ClassContent(){
	if(FR_CLASS_COMPONENT(lookahead.id)){
		ClassComponent();
		ClassContent();
	}
}

void ClassComponent(){
	Type();
	match(TOK_ID);
	RestDec();
}

void RestDec() {
	if(FR_REST_DEC(lookahead.id)) {
		match(';');
	} else if (FR_REST_DEC1(lookahead.id)) {
		match('(');
		ParamsOpt();
		match(')');
		match('{');
		BlockStmts();
		match('}');
	} else error("RestDec");
}

void VarDec(){
	if(FR_VAR_DEC(lookahead.id)){
		NonClassVarDec();
		VarObjDec();
	}
}

void ParamsOpt(){
	if(FR_PARAMS_OPT(lookahead.id)) {
		Params();
	}
	//
}

void Params(){
	Param();
	ParamsRest();
}

void ParamsRest(){
	if(FR_PARAMS_REST(lookahead.id)) {
		match(',');
		Params();
	} // eps
}

void Param() {
	Type();
	match(TOK_ID);
}

void Type1(){
	if(FR_TYPE1(lookahead.id)) {
		match('{');
		match('}');
		Type1();
	} // eps
}

void NonClassType(){
	if(FR_NON_CLASS_TYPE(lookahead.id)) {
		match(TOK_BOOLEAN);
		Type1();
	} else if(FR_NON_CLASS_TYPE1(lookahead.id)) {
		match(TOK_INT);
		Type1();
	} else if(FR_NON_CLASS_TYPE2(lookahead.id)) {
		match(TOK_VOID);
		Type1();
	}
}

void IdType(){
	match(TOK_ID);
	Type1();
}

void Type() {
	if(FR_TYPE(lookahead.id)) {
		NonClassType();
	} else if (FR_TYPE_1(lookahead.id)) {
		IdType();
	}
}

// ---------- vvvvvvv Giovanni vvvvvvv ---------- //




// ---------- vvvvvvv Gilney vvvvvvv ---------- //

void error(char* nonterminal) {
	printf("\n\nSYNTAX ERROR: the non-terminal %s couldn't be matched with the input symbol %s!\n", nonterminal, lookahead.lexem);
	exit(EXIT_FAILURE);
}

void E() {
	printf("E {");
	E1();
	printf(", ");
	Ep();
	printf(" }");
}

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

void E1() {
	printf("E1 { ");
	E2();
	printf(", ");
	E1p();
	printf(" }");
}

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

void E2() {
	printf("E2 { ");
	E3();
	printf(", ");
	E2p();
	printf(" }");
}

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

void E3() {
	printf("E3 { ");
	T();
	printf(", ");
	E3p();
	printf(" }");
}

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
	else error("TT");
	printf(" }");
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

void AfterId(){

}

void VarObjDec(){
	
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