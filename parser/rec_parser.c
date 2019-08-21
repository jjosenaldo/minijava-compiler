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
	E1();
	Ep();
}

void Ep() {
	if(FR_Relop(lookahead.id)) {
		Relop();
		E1();
	}
	else /* Epsilon */;
}

void E1() {
	E2();
	E1p();
}

void E1p() {
	if(FR_Boolop(lookahead.id)) {
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
	if(FR_Addop(lookahead.id)) {
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
	if(FR_Multop(lookahead.id)) {
		Multop();
		T();
		E3p();
	}
	else /* Epsilon */;
}

void T() {
	if(FR_F(lookahead.id)) {
		F();
		Tp();
	}
	else if(FR_Unop(lookahead.id)) {
		Unop();
		T();
	}
	else error();
}

void Tp() {
	if(FR_X(lookahead.id)) {
		X();
		Tp()
	}
	else /* Epsilon */;
}

void T2() {
	if(FR_comma(lookahead.id)) {
		comma();
		E();
	}
	else /* Epsilon */;
}

void T3() {
	if(FR_E(lookahead.id)) {
		E();
		T4();
	}
	else /* Epsilon */;
}

void T4() {
	if(FR_comma(lookahead.id)) {
		comma();
		E();
		T4();
	}
	else /* Epsilon */;
}

void X() {
	if(FR_dot(lookahead.id)) {
		dot();
		Xp();
	}
	else if(FR_lbracket(lookahead.id)) {
		lookahead();
		E();
		rbracket();
	}
	else error();
}

void Xp() {
	if(FR_length(lookahead.id)) {
		length();
		P();
	}
	else if(FR_substring(lookahead.id)) {
		substring();
		lpar();
		E();
		T2();
		rpar();
	}
	else if(FR_id(lookahead.id)) {
		id();
		lpar();
		T3();
		rpar();
	}
	else error();
}

void P() {
	if(FR_lpar(lookahead.id)) {
		lpar();
		rpar();
	}
	else /* Epsilon */;
}

void F() {
	if(FR_TT(lookahead.id)) {
		TT();
	}
	else if(FR_R(lookahead.id)) {
		R();
	}
	else error();
}

void TT() {
	if(FR_litint(lookahead.id))
		litint();
	else if(FR_true(lookahead.id)) {
		//true();
	}
	else if(FR_false(lookahead.id)) {
		//false();
	}
	else if(FR_id(lookahead.id)) {
		id();
	}
	else if(FR_litstr(lookahead.id)) {
		litstr();
	}
	else if(FR_this(lookahead.id)) {
		//this();
	}
	else if(FR_null(lookahead.id)) {
		//null();
	}
	else error();
}

void R() {
	if(FR_lbrace(lookahead.id)) {
		lbrace();
		El();
		rbrace();
	}
	else if(FR_lpar(lookahead.id)) {
		lpar();
		E();
		rpar();
	}
	else error();
}

void El() {
	if(FR_E(lookahead.id)) {
		E();
		Elp();
	}
	else /* Epsilon */;
}

void Elp() {
	if(FR_comma(lookahead.id)) {
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