#include "rec_parser.h"
#include "pred_sets.h"
#include "stdio.h"
#include <stdlib.h> // exit()

void match(struct token tok){
	if (lookahead = tok.id){
		lookahead = getNextToken().id;
	} else{
		printf("Syntax error when reading the token %c\n", tok.id);
		exit(EXIT_FAILURE);
	}
}

void parse(){
	lookahead = getNextToken().id;
    printf("not parsing anything yet...\n");
}

// ---------- vvvvvvv Gilney vvvvvvv ---------- //

void error() {
	printf("\n\nERROR: The input doesn't a valid program! :(\n");
	exit(EXIT_FAILURE);
}

void E() {
	printf("E { ");
	E1();
	printf(", ");
	Ep();
	printf(" }");
}

void Ep() {
	printf("Ep { ");
	if(FR_Ep_1(lookahead)) {
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
	if(FR_E1p_1(lookahead)) {
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
	if(FR_E2p_1(lookahead)) {
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
	if(FR_E3p_1(lookahead)) {
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
	if(FR_T_1(lookahead)) {
		F();
		printf(", ");
		Tp();
	}
	else if(FR_T_2(lookahead)) {
		Unop();
		printf(", ");
		T();
	}
	else error();
	printf(" }");
}

void Tp() {
	printf("Tp { ");
	if(FR_Tp_1(lookahead)) {
		X();
		printf(", ");
		Tp()
	}
	else printf("\u03B5") /* Epsilon */;
	printf(" }");
}

void T2() {
	printf("T2 { ");
	if(FR_T2_1(lookahead)) {
		match(',');
		printf(", ");
		E();
	}
	else printf("\u03B5") /* Epsilon */;
	printf(" }");
}

void T3() {
	printf("T3 { ");
	if(FR_T3_1(lookahead)) {
		E();
		printf(", ");
		T4();
	}
	else printf("\u03B5") /* Epsilon */;
	printf(" }");
}

void T4() {
	printf("T4 { ");
	if(FR_T4_1(lookahead)) {
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
	if(FR_X_1(lookahead)) {
		match('.');
		printf(", ");
		Xp();
	}
	else if(FR_X_2(lookahead)) {
		match('[');
		printf(", ");
		E();
		printf(", ");
		match(']');
	}
	else error();
	printf(" }");
}

void Xp() {
	printf("Xp { ");
	if(FR_Xp_1(lookahead)) {
		match(TOK_LENGTH);
		printf(", ");
		P();
	}
	else if(FR_Xp_2(lookahead)) {
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
	else if(FR_Xp_3(lookahead)) {
		match(TOK_ID);
		printf(", ");
		match('(');
		printf(", ");
		T3();
		printf(", ");
		match(')');
	}
	else error();
	printf(" }");
}

void P() {
	printf("P { ");
	if(FR_P_1(lookahead)) {
		match('(');
		printf(", ");
		match(')');
	}
	else printf("\u03B5") /* Epsilon */;
	printf(" }");
}

void F() {
	printf("F { ");
	if(FR_F_1(lookahead)) {
		TT();
	}
	else if(FR_F_2(lookahead)) {
		R();
	}
	else error();
	printf(" }");
}

void TT() {
	printf("TT { ");
	if(FR_TT_1(lookahead))
		match(TOK_LIT_INT);
	else if(FR_TT_2(lookahead))
		match(TOK_TRUE);
	else if(FR_TT_3(lookahead))
		match(TOK_FALSE);
	else if(FR_TT_4(lookahead))
		match(TOK_ID);
	else if(FR_TT_5(lookahead))
		match(TOK_LIT_STR);
	else if(FR_TT_6(lookahead))
		match(TOK_THIS);
	else if(FR_TT_7(lookahead))
		match(TOK_NULL);
	else error();
	printf(" }");
}

void R() {
	printf("R { ");
	if(FR_R_1(lookahead)) {
		match('{')
		printf(", ");
		El();
		printf(", ");
		match('}');
	}
	else if(FR_R_2(lookahead)) {
		match('(');
		printf(", ");
		E();
		printf(", ");
		match(')');
	}
	else error();
	printf(" }");
}

void El() {
	printf("El { ");
	if(FR_El_1(lookahead)) {
		E();
		printf(", ");
		Elp();
	}
	else printf("\u03B5") /* Epsilon */;
	printf(" }");
}

void Elp() {
	printf("Elp { ");
	if(FR_Elp_1(lookahead)) {
		match(',');
		printf(", ");
		E();
		printf(", ");
		Elp();
	}
	else error();
	printf(" }");
}

void Relop() {
	/*
	if(lookahead == less ||
	   lookahead == lesseq ||
	   lookahead == greatereq ||
	   lookahead == greater ||
	   lookahead == isequal ||
	   lookahead == isdiff) // Do Something
		;
	else error();
	*/
}

void Boolop() {
	/*
	if(lookahead == and ||
	   lookahead == or) // Do Something
		;
	else error();
	*/
}

void Addop() {
	/*
	if(lookahead == plus ||
	   lookahead == minus) // Do Something
		;
	else error();
	*/
}

void Multop() {
	/*
	if(lookahead == times ||
	   lookahead == div ||
	   lookahead == mod) // Do Something
		;
	else error();
	*/
}

void Unop() {
	/*
	if(lookahead == minus || ;
	   lookahead == excl) // Do Something
		;
	else error();
	*/
}

// ---------- ^^^^^^^ Gilney ^^^^^^^ ---------- //