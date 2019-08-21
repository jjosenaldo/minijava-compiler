#include "rec_parser.h"
#include "pred_sets.h"
#include "stdio.h"
#include <stdlib.h> // exit()

void match(char tok_id){
	if (lookahead == tok_id){
		lookahead = getNextToken().id;
	} else{
		printf("\n\nSYNTAX ERROR: the token %c couldn't be matched \
		with the input symbol of id %c!\n", tok_id, lookahead);
		exit(EXIT_FAILURE);
	}
}

void parse(){
	lookahead = getNextToken().id;
    printf("not parsing anything yet...\n");
}

// ---------- vvvvvvv Gilney vvvvvvv ---------- //

void error(char* nonterminal) {
	printf("\n\nSYNTAX ERROR: the non-terminal %s couldn't be matched \
	with the input symbol of id %c!\n", nonterminal, lookahead);
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
	if(FR_Relop(lookahead)) {
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
	if(FR_Boolop(lookahead)) {
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
	if(FR_Addop(lookahead)) {
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
	if(FR_Multop(lookahead)) {
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
	if(FR_F(lookahead)) {
		F();
		printf(", ");
		Tp();
	}
	else if(FR_Unop(lookahead)) {
		Unop();
		printf(", ");
		T();
	}
	else error("T");
	printf(" }");
}

void Tp() {
	printf("Tp { ");
	if(FR_X(lookahead)) {
		X();
		printf(", ");
		Tp()
	}
	else printf("\u03B5") /* Epsilon */;
	printf(" }");
}

void T2() {
	printf("T2 { ");
	if(FR_comma(lookahead)) {
		comma();
		printf(", ");
		E();
	}
	else printf("\u03B5") /* Epsilon */;
	printf(" }");
}

void T3() {
	printf("T3 { ");
	if(FR_E(lookahead)) {
		E();
		printf(", ");
		T4();
	}
	else printf("\u03B5") /* Epsilon */;
	printf(" }");
}

void T4() {
	printf("T4 {");
	if(FR_comma(lookahead)) {
		comma();
		printf(", ");
		E();
		printf(", ");
		T4();
	}
	else printf("\u03B5") /* Epsilon */;
	printf(" }");
}

void X() {
	printf("X {");
	if(FR_dot(lookahead)) {
		dot();
		printf(", ");
		Xp();
	}
	else if(FR_lbracket(lookahead)) {
		lbracket();
		printf(", ");
		E();
		printf(", ");
		rbracket();
	}
	else error("X");
	printf(" }");
}

void Xp() {
	printf("Xp { ");
	if(FR_length(lookahead)) {
		length();
		printf(", ");
		P();
	}
	else if(FR_substring(lookahead)) {
		substring();
		printf(", ");
		lpar();
		printf(", ");
		E();
		printf(", ");
		T2();
		printf(", ");
		rpar();
	}
	else if(FR_id(lookahead)) {
		id();
		printf(", ");
		lpar();
		printf(", ");
		T3();
		printf(", ");
		rpar();
	}
	else error("Xp");
	printf(" }");
}

void P() {
	printf("P { ");
	if(FR_lpar(lookahead)) {
		lpar();
		printf(", ");
		rpar();
	}
	else printf("\u03B5") /* Epsilon */;
	printf(" }");
}

void F() {
	printf("F { ");
	if(FR_TT(lookahead)) {
		TT();
	}
	else if(FR_R(lookahead)) {
		R();
	}
	else error();
	printf(" }");
}

void TT() {
	printf("TT { ");
	if(FR_litint(lookahead))
		litint();
	else if(FR_true(lookahead)) {
		//true();
	}
	else if(FR_false(lookahead)) {
		//false();
	}
	else if(FR_id(lookahead)) {
		id();
	}
	else if(FR_litstr(lookahead)) {
		litstr();
	}
	else if(FR_this(lookahead)) {
		//this();
	}
	else if(FR_null(lookahead)) {
		//null();
	}
	else error("TT");
	printf(" }");
}

void R() {
	printf("R { ");
	if(FR_lbrace(lookahead)) {
		lbrace();
		printf(", ");
		El();
		printf(", ");
		rbrace();
	}
	else if(FR_lpar(lookahead)) {
		lpar();
		printf(", ");
		E();
		printf(", ");
		rpar();
	}
	else error("R");
	printf(" }");
}

void El() {
	printf("El { ");
	if(FR_E(lookahead)) {
		E();
		printf(", ");
		Elp();
	}
	else printf("\u03B5") /* Epsilon */;
	printf(" }");
}

void Elp() {
	printf("Elp { ");
	if(FR_comma(lookahead)) {
		comma();
		printf(", ");
		E();
		printf(", ");
		Elp();
	}
	else error("Elp");
	printf(" }");
}

void Relop() {
	if(FR_Relop_1(lookahead))
		match('<');
	else if(FR_Relop_2(lookahead))
		match(TOK_LESS_EQ);
	else if(FR_Relop_3(lookahead))
		match(TOK_GREATER_EQ);
	else if(FR_Relop_4(lookahead))
		match('>');
	else if(FR_Relop_5(lookahead))
		match(TOK_EQ);
	else if(FR_Relop_6(lookahead))
		match(TOK_DIFF);	
	else
		error("Relop");
}

void Boolop() {
	if(FR_Boolop_1(lookahead))
		match(TOK_AND);
	else if(FR_Boolop_2(lookahead))
		match(TOK_OR);	
	else
		error("Boolop");
}

void Addop() {
	if(FR_Addop_1(lookahead))
		match('+');
	else if(FR_Addop_2(lookahead))
		match('-');	
	else
		error("Addop");
}

void Multop() {
	if(FR_Multop_1(lookahead))
		match('*');
	else if(FR_Multop_2(lookahead))
		match('/');
	else if(FR_Multop_3(lookahead))
		match('%');
	else
		error("Multop");
}

void Unop() {
	if(FR_Unop_1(lookahead))
		match('-');
	else if(FR_Unop_2(lookahead))
		match('!');	
	else
		error("Unop");
}

// ---------- ^^^^^^^ Gilney ^^^^^^^ ---------- //