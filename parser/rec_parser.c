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
	printf("The input doesn't a valid program! :(\n");
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
	else printf("Epsilon");;
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
	if(FR_Boolop(lookahead)) {
		Boolop();
		E2();
		E1p();
	}
	else /* Epsilon */;
}

void E2() {
	E3();
	E2p();
}

void E2p() {
	if(FR_Addop(lookahead)) {
		Addop();
		E3();
		E2p();
	}
	else /* Epsilon */;
}

void E3() {
	T();
	E3p();
}

void E3p() {
	if(FR_Multop(lookahead)) {
		Multop();
		T();
		E3p();
	}
	else /* Epsilon */;
}

void T() {
	if(FR_F(lookahead)) {
		F();
		Tp();
	}
	else if(FR_Unop(lookahead)) {
		Unop();
		T();
	}
	else error();
}

void Tp() {
	if(FR_X(lookahead)) {
		X();
		Tp()
	}
	else /* Epsilon */;
}

void T2() {
	if(FR_comma(lookahead)) {
		comma();
		E();
	}
	else /* Epsilon */;
}

void T3() {
	if(FR_E(lookahead)) {
		E();
		T4();
	}
	else /* Epsilon */;
}

void T4() {
	if(FR_comma(lookahead)) {
		comma();
		E();
		T4();
	}
	else /* Epsilon */;
}

void X() {
	if(FR_dot(lookahead)) {
		dot();
		Xp();
	}
	else if(FR_lbracket(lookahead)) {
		lookahead();
		E();
		rbracket();
	}
	else error();
}

void Xp() {
	if(FR_length(lookahead)) {
		length();
		P();
	}
	else if(FR_substring(lookahead)) {
		substring();
		lpar();
		E();
		T2();
		rpar();
	}
	else if(FR_id(lookahead)) {
		id();
		lpar();
		T3();
		rpar();
	}
	else error();
}

void P() {
	if(FR_lpar(lookahead)) {
		lpar();
		rpar();
	}
	else /* Epsilon */;
}

void F() {
	if(FR_TT(lookahead)) {
		TT();
	}
	else if(FR_R(lookahead)) {
		R();
	}
	else error();
}

void TT() {
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
	else error();
}

void R() {
	if(FR_lbrace(lookahead)) {
		lbrace();
		El();
		rbrace();
	}
	else if(FR_lpar(lookahead)) {
		lpar();
		E();
		rpar();
	}
	else error();
}

void El() {
	if(FR_E(lookahead)) {
		E();
		Elp();
	}
	else /* Epsilon */;
}

void Elp() {
	if(FR_comma(lookahead)) {
		comma();
		E();
		Elp();
	}
	else error();
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