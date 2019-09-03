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
	printf("\n\nSYNTAX ERROR: the non-terminal %s couldn't be matched with the input symbol %s of id %c!\n", nonterminal, lookahead.lexem, lookahead.id);
	exit(EXIT_FAILURE);
}

void parse(){
	lookahead = getNextToken();
    Stmt();
    match(TOK_EOF);
    printf("\n");
}

// Goal -> MainClass ClassDeclarations .
void Goal() {
	printf("Goal { ");
	if(FR_Goal(lookahead.id)){
		MainClass();
		printf(", ");
		ClassDeclarations();
	} else error("Goal");
	printf(" }");
}

// MainClass -> class id lbrace void main ( string lbracket rbracket id ) lbrace Blockstatements rbrace rbrace .
void MainClass() {
	printf("MainClass { ");
	if(FR_Main(lookahead.id)){
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
	} else error("MainClass");
	
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
		Eq();
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
	printf("NonclassVarDec {");
	if(FR_NONCLASS_VAR_DEC(lookahead.id)){
		NonClassType();
		match(TOK_ID);
		Eq();
	} else error("NonClassVarDec");
	printf("}");
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
	} else error("NonClassType");
	printf(" }");
}

// Type -> NonclassType | id Type1 .
void Type() {
	printf("Type { ");
	if(FR_TYPE_1(lookahead.id)) {
		NonClassType();
	} else if (FR_TYPE_2(lookahead.id)) {
		match(TOK_ID);
		Type1();
	}
	else error("Type");
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
		match(TOK_IF);
		match('(');
		E();
		match(')');
		Stmt();
		OptElse();
	} else if(FR_StmtWithoutId_8(lookahead.id)){
		match(';');
	} else error("StmtWithoutId");
	printf("}");
}

// OptElse -> else Stmt | .
void OptElse(){
	printf("OptElse {");
	if(FR_OptElse_1(lookahead.id)){
		match(TOK_ELSE);
		Stmt();
	} else printf("\u03B5") /* Epsilon */;
	printf("}");
}

// AfterIdExceptId -> Dot Eq | Bracket Eq  eq E . 
void AfterIdExceptId(){
	printf("AfterIdExceptId {");
	if(FR_AfterIdExceptId_1(lookahead.id)){
		Dot();
		Eq();
	} else if (FR_AfterIdExceptId_2(lookahead.id)){
		Bracket();
		Eq();
	} else if(FR_AfterIdExceptId_3(lookahead.id)){
		match('=');
		E();
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
	if(FR_CLASS_DCRLT(lookahead.id)){
		match(TOK_CLASS);
		printf(", ");
		match(TOK_ID);
		printf(", ");
		Extends();
		printf(", ");
		ClassBody();	
	} else error("ClassDeclaration");
	
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
	if(FR_CLASS_BODY(lookahead.id)){
		printf("ClassBody { ");
		match('{');
		printf(", ");
		ClassContent();
		printf(", ");
		match('}');	
	} else error("ClassBody");
	
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
	if(FR_CLASS_COMPONENT(lookahead.id)){
		Type();
		printf(", ");
		match(TOK_ID);
		printf(", ");
		RestDec();	
	} else error("ClassComponent");
	
	printf(" }");
}

// RestDec -> Eq semicolon | ( ParamsOpt ) lbrace Blockstatements rbrace .
void RestDec() {
	printf("RestDec { ");
	if(FR_REST_DEC_1(lookahead.id)) {
		Eq();
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
	if(FR_PARAMS(lookahead.id)){
		Param();
		printf(", ");
		ParamsRest();
		printf(" }");
	} else error("Params");
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
	if(FR_PARAM(lookahead.id)){
		Type();
		printf(", ");
		match(TOK_ID);
	} else error("Param");
	
	printf(" }");
}

// E -> E1 Ep .
void E() {
	printf("E {");
	if(FR_E(lookahead.id)){
		E1();
		printf(", ");
		Ep();
	} else error("E");
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
	if(FR_E1(lookahead.id)){
		E2();
		printf(", ");
		E1p();
	} else error("E1");
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
	if(FR_E2(lookahead.id)){
		E3();
		printf(", ");
		E2p();
	} else error("E2");
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
	if(FR_E3(lookahead.id)){
		T();
		printf(", ");
		E3p();
	} else error("E3");
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

// T4 -> comma E T4 | .
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

// X -> dot Xp | lbracket E rbracket .
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

// Xp -> length P | substring ( E T2 ) | id ( T3 ) .
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
	} else error("Xp");
	printf(" }");
}

// P -> ( ) | .
void P() {
	printf("P { ");
	if(FR_P_1(lookahead.id)) {
		match('(');
		printf(", ");
		match(')');
	} else printf("\u03B5") /* Epsilon */;
	printf(" }");
}

// F -> TT | R .
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

// TT -> litint | true | false | id | litstr | this | null | new AfterNew .
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
	} else error("TT");
	printf(" }");
}

// AfterNew -> int FilledBrackets | boolean FilledBrackets | id AfterNewId .
void AfterNew(){
	printf("AfterNew {");
	if(FR_AfterNew_1(lookahead.id)){
		match(TOK_INT);
		FilledBrackets();
	} else if(FR_AfterNew_2(lookahead.id)){
		match(TOK_BOOLEAN);
		FilledBrackets();
	} if(FR_AfterNew_3(lookahead.id)){
		match(TOK_ID);
		AfterNewId();
	} else error("AfterNew");
	printf("}");
}

// AfterNewId -> lbracket E rbracket FilledBrackets | ( T3 ) . 
void AfterNewId(){
	printf("AfterNewId {");
	if(FR_AfterNewId_1(lookahead.id)){
		match('[');
		E();
		match(']');
		FilledBrackets();
	} else if(FR_AfterNewId_2(lookahead.id)){
		match('(');
		T3();
		match(')');
	} else error("AfterNewId");
	printf("}");	
}

// FilledBrackets -> lbracket E rbracket FilledBrackets | .
void FilledBrackets(){
	printf("FilledBrackets {");
	if(FR_FilledBrackets_1(lookahead.id)){
		match('[');
		E();
		match(']');
		FilledBrackets();
	} else printf("\u03B5") /* Epsilon */;
	printf("}");
}

// R -> lbrace El rbrace | ( E ) .
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

// El -> E Elp | .
void El() {
	printf("El { ");
	if(FR_El_1(lookahead.id)) {
		E();
		printf(", ");
		Elp();
	} else printf("\u03B5") /* Epsilon */;
	printf(" }");
}

// Elp -> comma E Elp | .
void Elp() {
	printf("Elp { ");
	if(FR_Elp_1(lookahead.id)) {
		match(',');
		printf(", ");
		E();
		printf(", ");
		Elp();
	} else printf("\u03B5") /* Epsilon */;
	printf(" }");
}

// Relop -> less | lesseq | greatereq | greater | isequal | isdiff .
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

// Boolop -> and | or .
void Boolop() {
	if(FR_Boolop_1(lookahead.id))
		match(TOK_AND);
	else if(FR_Boolop_2(lookahead.id))
		match(TOK_OR);
	else
		error("Boolop");
}

// Addop -> plus | minus .
void Addop() {
	if(FR_Addop_1(lookahead.id))
		match('+');
	else if(FR_Addop_2(lookahead.id))
		match('-');
	else
		error("Addop");
}

// Multop -> times | div | mod .
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

// Unop -> minus | excl .
void Unop() {
	if(FR_Unop_1(lookahead.id))
		match('-');
	else if(FR_Unop_2(lookahead.id))
		match('!');
	else
		error("Unop");
}