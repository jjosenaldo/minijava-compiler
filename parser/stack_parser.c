#include "stack_parser.h"
#include <stdio.h>

#define lid lookahead.id

void stack_parse(){
	struct token lookahead = getNextToken();

	// empty stack
	Stack* stack = NULL;

	push(&stack, TOK_EOF);

	// current grammar symbol
	char X = symbol_id("Goal");
	push(&stack, X);

	while(X != TOK_EOF){
		//print(&stack);
		if(X == lookahead.id){
			//printf("match: %s\n", lookahead.lexem);
			pop(&stack);
			lookahead = getNextToken();
		} else if(is_terminal(X)){
			printf("%c is terminal and it's not equal to the lookahead, which has id %c and lexem %s\n",X,lookahead.id,lookahead.lexem );
			break;
		} else if(!add_rule_to_stack(X, &stack, lookahead)){
			stackparse_error(X, lookahead);
			break;
		}
		X = top(&stack);
	}
}

int is_terminal(char X){
	if(X == TOK_LIT_INT) return 1;
	if(X == TOK_SUBSTRING) return 1;
	if(X == TOK_PUBLIC) return 1;
	if(X == TOK_BREAK) return 1;
	if(X == TOK_CONTINUE) return 1;
	if(X == TOK_CLASS) return 1;
	if(X == TOK_ID) return 1;
	if(X == TOK_DIFF) return 1;
	if(X == TOK_ERROR) return 1;
	if(X == TOK_EOF) return 1;
	if(X == TOK_IF) return 1;
	if(X == TOK_FALSE) return 1;
	if(X == TOK_STRING) return 1;
	if(X == TOK_GREAT_EQ) return 1;
	if(X == TOK_INT) return 1;
	if(X == TOK_LENGTH) return 1;
	if(X == TOK_LESS_EQ) return 1;
	if(X == TOK_MAIN) return 1;
	if(X == TOK_NEW) return 1;
	if(X == TOK_NULL) return 1;
	if(X == TOK_SYSOUT) return 1;
	if(X == TOK_BOOLEAN) return 1;
	if(X == TOK_SYSOUT) return 1;
	if(X == TOK_EQ) return 1;
	if(X == TOK_RETURN) return 1;
	if(X == TOK_LIT_STR) return 1;
	if(X == TOK_ELSE) return 1;
	if(X == TOK_STATIC) return 1;
	if(X == TOK_THIS) return 1;
	if(X == TOK_TRUE) return 1;
	if(X == TOK_VOID) return 1;
	if(X == TOK_WHILE) return 1;
	if(X == TOK_EXTENDS) return 1;
	if(X == TOK_AND) return 1;
	if(X == TOK_OR) return 1;
	return 0;
}

int add_rule_to_stack(char X, Stack** stack, struct token lookahead){
	if(X == TERM_E){
		if(lookahead.id == '!' || lookahead.id == '-' || lookahead.id == '(' || lookahead.id == '{'
			|| lookahead.id == TOK_ID || lookahead.id == TOK_NEW || lookahead.id == TOK_NULL
			|| lookahead.id == TOK_LIT_STR || lookahead.id == TOK_FALSE || lookahead.id == TOK_TRUE
			|| lookahead.id == TOK_LIT_INT || lookahead.id == TOK_THIS){
			printf("E -> E1 Ep .\n");
			pop(stack);
			push(stack,symbol_id("Ep"));
			push(stack,symbol_id("E1"));
			return 1;
		}
		return 0;
	}
	if(X == TERM_Ep){
		if(lookahead.id == TOK_DIFF || lookahead.id == TOK_EQ || lookahead.id == '>'
			|| lookahead.id == TOK_GREAT_EQ || lookahead.id == '<' || lookahead.id == TOK_LESS_EQ){
			printf("Ep -> Relop E1 Ep .\n");
			pop(stack);
			push(stack,symbol_id("Ep"));
			push(stack,symbol_id("E1"));
			push(stack,symbol_id("Relop"));
			return 1;
		}
		if(lookahead.id == ',' || lookahead.id == ')' || lookahead.id == '}' || lookahead.id == '{'
			|| lookahead.id == ']' || lookahead.id == TOK_ID || lookahead.id == TOK_BOOLEAN || lookahead.id == TOK_INT
			|| lookahead.id == TOK_THIS || lookahead.id == ';' || lookahead.id == TOK_ELSE || lookahead.id == TOK_IF
			|| lookahead.id == TOK_RETURN || lookahead.id == TOK_BREAK || lookahead.id == TOK_CONTINUE || lookahead.id == TOK_SYSOUT
			|| lookahead.id == TOK_WHILE || lookahead.id == TOK_VOID){
			printf("Ep -> .\n");
			pop(stack);
			return 1;
		}
		return 0;
	}
	if(X == TERM_E1){
		if(lookahead.id == '!' || lookahead.id == '-' || lookahead.id == '(' || lookahead.id == '{' || lookahead.id == TOK_ID
			|| lookahead.id == TOK_NEW || lookahead.id == TOK_NULL || lookahead.id == TOK_LIT_STR || lookahead.id == TOK_FALSE
			 || lookahead.id == TOK_TRUE || lookahead.id == TOK_LIT_INT || lookahead.id == TOK_THIS){
			printf("E1 -> E2 E1p .\n");
			pop(stack);
			push(stack,symbol_id("E1p"));
			push(stack,symbol_id("E2"));
			return 1;
		}
		return 0;
	}
	if(X == TERM_E1p){
		if(lid == TOK_OR || lid == TOK_AND){
			printf("E1p -> Boolop E2 E1p .\n");
			pop(stack);
			push(stack, symbol_id("E1p"));
			push(stack, symbol_id("E2"));
			push(stack, symbol_id("Boolop"));
			return 1;
		}
		if(lid == TOK_EQ || lid == TOK_DIFF || lid == '>' || lid == TOK_GREAT_EQ || lid == TOK_LESS_EQ || lid == '<'
		 || lid == ',' || lid == ')' || lid == '}' || lid == '{' || lid == ']' || lid == TOK_ID || lid == TOK_BOOLEAN
		  || lid == TOK_INT || lid == TOK_THIS || lid == ';' || lid == TOK_ELSE || lid == TOK_IF || lid == TOK_RETURN
		   || lid == TOK_BREAK || lid == TOK_CONTINUE || lid == TOK_SYSOUT || lid == TOK_WHILE || lid == TOK_VOID ){
			printf("E1p -> .\n");
			pop(stack);
			return 1;
		}
		return 0;
	}
	if(X == TERM_E2){
		if(lid == '!' || lid == '-' || lid == '(' || lid == '{' || lid == TOK_ID || lid == TOK_NEW || lid == TOK_NULL
			 || lid == TOK_LIT_STR || lid == TOK_TRUE || lid == TOK_FALSE || lid == TOK_LIT_INT || lid == TOK_THIS){
			printf("E2 -> E3 E2p .\n");
			pop(stack);
			push(stack, symbol_id("E2p"));
			push(stack, symbol_id("E3"));
			return 1;
		}
		return 0;
	}
	if(X == TERM_E2p){
		if(lid == '-' || lid == '+'){
			printf("E2p -> Addop E3 E2p .\n");
			pop(stack);
			push(stack, symbol_id("E2p"));
			push(stack, symbol_id("E3"));
			push(stack, symbol_id("Addop"));
			return 1;
		}
		if(lid == TOK_AND || lid == TOK_DIFF || lid == TOK_EQ || lid == '>' || lid == TOK_GREAT_EQ || lid == TOK_LESS_EQ || lid == '<' || lid == ',' || lid == ')' || lid == '}' || lid == '{' || lid == ']' || lid == TOK_ID || lid == TOK_BOOLEAN || lid == TOK_INT || lid == TOK_THIS || lid == ';' || lid == TOK_ELSE || lid == TOK_IF || lid == TOK_RETURN || lid == TOK_BREAK || lid == TOK_CONTINUE || lid == TOK_SYSOUT || lid == TOK_WHILE || lid == TOK_VOID){
			printf("E2p -> .\n");
			pop(stack);
			return 1;
		}
		return 0;
	}
	if(X == TERM_E3){
		if(lid == '!' || lid == '-' || lid == '(' || lid == '{' || lid == TOK_ID || lid == TOK_NEW || lid == TOK_NULL || lid == TOK_LIT_STR || lid == TOK_FALSE || lid == TOK_TRUE || lid == TOK_LIT_INT || lid == TOK_THIS){
			printf("E3 -> T E3p .\n");
			pop(stack);
			push(stack, symbol_id("E3p"));
			push(stack, symbol_id("T"));
			return 1;
		}
		return 0;
	}
	if(X == TERM_E3p){
		if(lid == '/' || lid == '*' || lid == '%'){
			printf("E3p -> Multop T E3p .\n");
			pop(stack);
			push(stack, symbol_id("E3p"));
			push(stack, symbol_id("T"));
			push(stack, symbol_id("Multop"));
			return 1;
		}
		if(lid == '-' || lid == '+' || lid == TOK_OR || lid == TOK_AND || lid == TOK_DIFF || lid == TOK_EQ || lid == '>' || lid == TOK_GREAT_EQ || lid == TOK_LESS_EQ || lid == '<' || lid == ',' || lid == ')' || lid == '}' || lid == '{' || lid == ']' || lid == TOK_ID || lid == TOK_BOOLEAN || lid == TOK_INT || lid == TOK_THIS || lid == ';' || lid == TOK_ELSE || lid == TOK_IF || lid == TOK_RETURN || lid == TOK_BREAK || lid == TOK_CONTINUE || lid == TOK_SYSOUT || lid == TOK_WHILE || lid == TOK_VOID
		){
			printf("E3p -> .\n");
			pop(stack);
			return 1;
		}
		return 0;
	}
	if(X == TERM_T){
		if(lid == '!' || lid == '-'){
			printf("T -> Unop T .\n");
			pop(stack);
			push(stack, symbol_id("T"));
			push(stack, symbol_id("Unop"));
			return 1;
		}
		if(lid == '(' || lid == '{' || lid == TOK_ID || lid == TOK_NEW || lid == TOK_NULL || lid == TOK_LIT_STR || lid == TOK_FALSE || lid == TOK_TRUE || lid == TOK_LIT_INT){
			printf("T -> F Tp .\n");
			pop(stack);
			push(stack, symbol_id("Tp"));
			push(stack, symbol_id("F"));
			return 1;
		}
		if(lid == TOK_THIS){
			printf("T -> this AfterThisInExp .\n");
			pop(stack);
			push(stack, symbol_id("AfterThisInExp"));
			push(stack, TOK_THIS);
			return 1;
		}
		return 0;
	}
	if(X == TERM_Tp){
		if(lid == '.' || lid == '['){
			printf("Tp -> X Tp .\n");
			pop(stack);
			push(stack, symbol_id("Tp"));
			push(stack, symbol_id("X"));
			return 1;
		}
		if(lid == '-' || lid == '%' || lid == '/' || lid == '*' || lid == '+' || lid == TOK_OR || lid == TOK_AND || lid == TOK_DIFF || lid == TOK_EQ || lid == '>' || lid == TOK_GREAT_EQ || lid == TOK_LESS_EQ || lid == '<' || lid == ',' || lid == ')' || lid == '}' || lid == '{' || lid == ']' || lid == TOK_ID || lid == TOK_BOOLEAN || lid == TOK_INT || lid == '.' || lid == TOK_THIS || lid == ';' || lid == TOK_ELSE || lid == TOK_IF || lid == TOK_RETURN || lid == TOK_BREAK || lid == TOK_CONTINUE || lid == TOK_SYSOUT || lid == TOK_WHILE || lid == TOK_VOID){
			printf("Tp -> .\n");
			pop(stack);
			return 1;
		}
	}
	if(X == TERM_T2){
		if(lid == ','){
			printf("T2 -> , E .\n");
			pop(stack);
			push(stack, symbol_id("E"));
			push(stack, '.');
			return 1;
		}
		if(lid == ')'){
			printf("T2 -> .\n");
			pop(stack);
			return 1;
		}
	}
	if(X == TERM_T3){
		if(lid == '!' || lid == '-' || lid == '(' || lid == '{' || lid == TOK_ID || lid == TOK_NEW || lid == TOK_NULL || lid == TOK_LIT_STR || lid == TOK_FALSE || lid == TOK_TRUE || lid == TOK_LIT_INT || lid == TOK_THIS){
			printf("T3 -> E T4 .\n");
			pop(stack);
			push(stack, symbol_id("T4"));
			push(stack, symbol_id("E"));
			return 1;
		}
		if(lid == ')'){
			printf("T3 -> .\n");
			pop(stack);
			return 1;
		}
		return 0;
	}
	if(X == TERM_T4){
		if(lid == ','){
			printf("T4 -> , E T4 .\n");
			pop(stack);
			push(stack, symbol_id("T4"));
			push(stack, symbol_id("E"));
			push(stack, ',');
			return 1;
		}
		if(lid == ')'){
			printf("T4 -> .\n");
			pop(stack);
			return 1;
		}
		return 0;
	}
	if(X == TERM_X){
		if(lid == '['){
			printf("X -> [ E ] .\n");
			pop(stack);
			push(stack, ']');
			push(stack, symbol_id("E"));
			push(stack, '[');
			return 1;
		}
		if(lid == '.'){
			printf("X -> . Xp .\n");
			pop(stack);
			push(stack, symbol_id("Xp"));
			push(stack, '.');
			return 1;
		}
		return 0;
	}
	if(X == TERM_Xp){
		if(lid == TOK_ID){
			printf("Xp -> <id> ( T3 ) .\n");
			pop(stack);
			push(stack, ')');
			push(stack, symbol_id("T3"));
			push(stack, '(');
			push(stack, TOK_ID);
			return 1;
		}
		if(lid == TOK_SUBSTRING){
			printf("Xp -> substring ( E T2 ) .\n");
			pop(stack);
			push(stack, ')');
			push(stack, symbol_id("T2"));
			push(stack, symbol_id("E"));
			push(stack, '(');
			push(stack, TOK_SUBSTRING);
			return 1;
		}
		if(lid == TOK_LENGTH){
			printf("Xp -> length P .\n");
			pop(stack);
			push(stack, symbol_id("P"));
			push(stack, TOK_LENGTH);
			return 1;
		}
		return 0;
	}
	if(X == TERM_P){
		if(lid == '-' || lid == '%' || lid == '/' || lid == '*' || lid == '+' || lid == TOK_OR || lid == TOK_AND || lid == TOK_DIFF || lid == TOK_EQ || lid == '>' || lid == TOK_GREAT_EQ || lid == TOK_LESS_EQ || lid == '<' || lid == ',' || lid == ')' || lid == '}' || lid == '{' || lid == ']' || lid == '[' || lid == TOK_ID || lid == TOK_BOOLEAN || lid == TOK_INT || lid == '.' || lid == TOK_THIS || lid == ';' || lid == TOK_ELSE || lid == TOK_IF || lid == TOK_RETURN || lid == TOK_BREAK || lid == TOK_CONTINUE || lid == TOK_SYSOUT || lid == TOK_WHILE || lid == TOK_VOID){
			printf("P -> .\n");
			pop(stack);
			return 1;
		}
		if(lid == '('){
			printf("P -> ( ) .\n");
			pop(stack);
			push(stack, ')');
			push(stack, '(');
			return 1;
		}
		return 0;
	}
	if(X == TERM_F){
		if(lid == '(' || lid == '{'){
			printf("F -> R .\n");
			pop(stack);
			push(stack, symbol_id("R"));
			return 1;
		}
		if(lid == TOK_ID || lid == TOK_NEW || lid == TOK_NULL || lid == TOK_LIT_STR || lid == TOK_FALSE || lid == TOK_TRUE || lid == TOK_LIT_INT){
			printf("F -> TT .\n");
			pop(stack);
			push(stack, symbol_id("TT"));
			return 1;
		}
		return 0;
	}
	if(X == TERM_TT){
		if(lid == TOK_ID){
			printf("TT -> <id> .\n");
			pop(stack);
			push(stack, TOK_ID);
			return 1;
		}
		if(lid == TOK_NEW){
			printf("TT -> new AfterNew .\n");
			pop(stack);
			push(stack, symbol_id("AfterNew"));
			push(stack, TOK_NEW);
			return 1;
		}
		if(lid == TOK_NULL){
			printf("TT -> null .\n");
			pop(stack);
			push(stack, TOK_NULL);
			return 1;
		}
		if(lid == TOK_LIT_STR){
			printf("TT -> <litstr> .\n");
			pop(stack);
			push(stack, TOK_LIT_STR);
			return 1;
		}
		if(lid == TOK_FALSE){
			printf("TT -> false .\n");
			pop(stack);
			push(stack, TOK_FALSE);
			return 1;
		}
		if(lid == TOK_TRUE){
			printf("TT -> true .\n");
			pop(stack);
			push(stack, TOK_TRUE);
			return 1;
		}
		if(lid == TOK_LIT_INT){
			printf("TT -> <litint> .\n");
			pop(stack);
			push(stack, TOK_LIT_INT);
			return 1;
		}
		return 0;
	}
	if(X == TERM_AfterThisInExp){
		if(lid == '-' || lid == '%' || lid == '/' || lid == '*' || lid == '+' || lid == TOK_OR || lid == TOK_AND || lid == TOK_DIFF || lid == TOK_EQ || lid == '>' || lid == TOK_GREAT_EQ || lid == TOK_LESS_EQ || lid == '<' || lid == ',' || lid == ')' || lid == '}' || lid == '{' || lid == ']' || lid == TOK_ID || lid == TOK_BOOLEAN || lid == TOK_INT || lid == TOK_THIS || lid == ';' || lid == TOK_ELSE || lid == TOK_IF || lid == TOK_RETURN || lid == TOK_BREAK || lid == TOK_CONTINUE || lid == TOK_SYSOUT || lid == TOK_WHILE || lid == TOK_VOID){
			printf("AfterThisInExp -> .\n");
			pop(stack);
			return 1;
		}
		if(lid == '.'){
			printf("AfterThisInExp -> dot id RestThisInExp .\n");
			pop(stack);
			push(stack, symbol_id("RestThisInExp"));
			push(stack, TOK_ID);
			push(stack, '.');
			return 1;
		}
		return 0;
	}
	if(X == TERM_RestThisInExp){
		if(lid == '-' || lid == '%' || lid == '/' || lid == '*' || lid == '+' || lid == TOK_OR || lid == TOK_AND || lid == TOK_DIFF || lid == TOK_EQ || lid == '>' || lid == TOK_GREAT_EQ || lid == TOK_LESS_EQ || lid == '<' || lid == ',' || lid == ')' || lid == '}' || lid == '{' || lid == ']' || lid == TOK_ID || lid == TOK_BOOLEAN || lid == TOK_INT || lid == TOK_THIS || lid == ';' || lid == TOK_ELSE || lid == TOK_IF || lid == TOK_RETURN || lid == TOK_BREAK || lid == TOK_CONTINUE || lid == TOK_SYSOUT || lid == TOK_WHILE || lid == TOK_VOID){
			printf("RestThisInExp -> .\n");
			pop(stack);
			return 1;
		}
		if(lid == '('){
			printf("RestThisInExp -> ( T3 ) Tp .\n");
			pop(stack);
			push(stack, symbol_id("Tp"));
			push(stack, ')');
			push(stack, symbol_id("T3"));
			push(stack, '(');
			return 1;
		}
		return 0;
	}
	if(X == TERM_AfterNew){
		if(lid == TOK_ID){
			printf("AfterNew -> <id> AfterNewId .\n");
			pop(stack);
			push(stack, symbol_id("AfterNewId"));
			push(stack, TOK_ID);
			return 1;
		}
		if(lid == TOK_BOOLEAN){
			printf("AfterNew -> boolean FilledBrackets .\n");
			pop(stack);
			push(stack, symbol_id("FilledBrackets"));
			push(stack, TOK_BOOLEAN);
			return 1;
		}
		if(lid == TOK_INT){
			printf("AfterNew -> int FilledBrackets .\n");
			pop(stack);
			push(stack, symbol_id("FilledBrackets"));
			push(stack, TOK_INT);
			return 1;
		}
		return 0;
	}
	if(X == TERM_AfterNewId){
		if(lid == '('){
			printf("AfterNewId -> ( T3 ) .\n");
			pop(stack);
			push(stack, ')');
			push(stack, symbol_id("T3"));
			push(stack, '(');
			return 1;
		}
		if(lid == '{'){
			printf("AfterNewId -> [ E ] FilledBrackets .\n");
			pop(stack);
			push(stack, symbol_id("FilledBrackets"));
			push(stack, ']');
			push(stack, symbol_id("E"));
			push(stack, '[');
			return 1;
		}
		return 0;
	}
	if(X == TERM_FilledBrackets){
		if(lid == '-' || lid == '%' || lid == '/' || lid == '*' || lid == '+' || lid == TOK_OR || lid == TOK_AND || lid == TOK_DIFF || lid == TOK_EQ || lid == '>' || lid == TOK_GREAT_EQ || lid == TOK_LESS_EQ || lid == '<' || lid == ',' || lid == ')' || lid == '}' || lid == '{' || lid == ']' || lid == TOK_ID || lid == TOK_BOOLEAN || lid == TOK_INT || lid == '.' || lid == TOK_THIS || lid == ';' || lid == TOK_ELSE || lid == TOK_IF || lid == TOK_RETURN || lid == TOK_BREAK || lid == TOK_CONTINUE || lid == TOK_SYSOUT || lid == TOK_WHILE || lid == TOK_VOID){
			printf("RestFilledBracketsThisInExp -> .\n");
			pop(stack);
			return 1;
		}
		if(lid == '['){
			printf("FilledBrackets -> [ E ] .\n");
			pop(stack);
			push(stack, ']');
			push(stack, symbol_id("E"));
			push(stack, '[');
			return 1;
		}
		return 0;
	}
	if(X == TERM_R){
		if(lid == '('){
			printf("R -> ( E ) .\n");
			pop(stack);
			push(stack, ')');
			push(stack, symbol_id("E"));
			push(stack, '(');
			return 1;
		}
		if(lid == '{'){
			printf("R -> { El } .\n");
			pop(stack);
			push(stack, '}');
			push(stack, symbol_id("El"));
			push(stack, '{');
			return 1;
		}
		return 0;
	}
	if(X == TERM_El){
		if(lid == '!' || lid == '-' || lid == '(' || lid == '{' || lid == TOK_ID || lid == TOK_THIS || lid == TOK_NEW || lid == TOK_NULL || lid == TOK_LIT_STR || lid == TOK_FALSE || lid == TOK_TRUE || lid == TOK_LIT_INT){
			printf("El -> E Elp .\n");
			pop(stack);
			push(stack, symbol_id("Elp"));
			push(stack, symbol_id("E"));
			return 1;
		}
		if(lid == '}'){
			printf("El -> .\n");
			pop(stack);
			return 1;
		}
		return 0;
	}
	if(X == TERM_Elp){
		if(lid == ','){
			printf("Elp -> , E Elp .\n");
			pop(stack);
			push(stack, symbol_id("Elp"));
			push(stack, symbol_id("E"));
			push(stack, ',');
			return 1;
		}
		if(lid == '}'){
			printf("Elp -> .\n");
			pop(stack);
			return 1;
		}
		return 0;
	}
	if(X == TERM_Relop){
		if(lid == TOK_DIFF){
			printf("Relop -> != .\n");
			pop(stack);
			push(stack, TOK_DIFF);
			return 1;
		}
		if(lid == TOK_EQ){
			printf("Relop -> == .\n");
			pop(stack);
			push(stack, TOK_EQ);
			return 1;
		}
		if(lid == '>'){
			printf("Relop -> > .\n");
			pop(stack);
			push(stack, '>');
			return 1;
		}
		if(lid == TOK_GREAT_EQ){
			printf("Relop -> >= .\n");
			pop(stack);
			push(stack, TOK_GREAT_EQ);
			return 1;
		}
		if(lid == TOK_LESS_EQ){
			printf("Relop -> <= .\n");
			pop(stack);
			push(stack, TOK_LESS_EQ);
			return 1;
		}
		if(lid == '<'){
			printf("Relop -> < .\n");
			pop(stack);
			push(stack, '<');
			return 1;
		}
		return 0;
	}
	if(X == TERM_Boolop){
		if(lid == TOK_OR){
			printf("Boolop -> || .\n");
			pop(stack);
			push(stack, TOK_OR);
			return 1;
		}
		if(lid == TOK_AND){
			printf("Boolop -> && .\n");
			pop(stack);
			push(stack, TOK_AND);
			return 1;
		}
		return 0;
	}
	if(X == TERM_Addop){
		if(lid == '-'){
			printf("Addop -> - .\n");
			pop(stack);
			push(stack, '-');
			return 1;
		}
		if(lid == '+'){
			printf("Addop -> + .\n");
			pop(stack);
			push(stack, '+');
			return 1;
		}
		return 0;
	}
	if(X == TERM_Multop){
		if(lid == '%'){
			printf("Multop -> %%.\n");
			pop(stack);
			push(stack, '%');
			return 1;
		}
		if(lid == '/'){
			printf("Multop -> / .\n");
			pop(stack);
			push(stack, '/');
			return 1;
		}
		if(lid == '*'){
			printf("Multop -> * .\n");
			pop(stack);
			push(stack, '*');
			return 1;
		}
		return 0;
	}
	if(X == TERM_Unop){
		if(lid == '-'){
			printf("Unop -> - .\n");
			pop(stack);
			push(stack, '-');
			return 1;
		}
		if(lid == '!'){
			printf("Unop -> ! .\n");
			pop(stack);
			push(stack, '!');
			return 1;
		}
		return 0;
	}

	if(X == TERM_Goal){
		if(lid == TOK_CLASS){
			printf("Goal -> MainClass ClassDeclarations .\n");
			pop(stack);
			push(stack, symbol_id("ClassDeclarations"));
			push(stack, symbol_id("MainClass"));
			return 1;
		}
		return 0;
	}

	if(X == TERM_MainClass){
		if(lid == TOK_CLASS){
			printf("MainClass -> class <id> { void main ( string [ ] <id> ) { Blockstatements } } .\n");
			pop(stack);
			push(stack, '}');
			push(stack, '}');
			push(stack, symbol_id("Blockstatements"));
			push(stack, '{');
			push(stack, ')');
			push(stack, TOK_ID);
			push(stack, ']');
			push(stack, '[');
			push(stack, TOK_STRING);
			push(stack, '(');
			push(stack, TOK_MAIN);
			push(stack, TOK_VOID);
			push(stack, '{');
			push(stack, TOK_ID);
			push(stack, TOK_CLASS);
			return 1;
		}
		return 0;
	}

	if(X == TERM_Blockstatements){
		if(lid == '{'  || lid == TOK_ID || lid == TOK_BOOLEAN || lid ==  TOK_INT || lid == TOK_THIS || lid == ';' || lid == TOK_IF || lid == TOK_RETURN || lid == TOK_BREAK || lid == TOK_CONTINUE || lid == TOK_SYSOUT || lid == TOK_WHILE || lid == TOK_VOID){
			printf("Blockstatements -> BlockStatement Blockstatements .\n");
			pop(stack);
			push(stack, symbol_id("Blockstatements"));
			push(stack, symbol_id("Blockstatement"));
			return 1;
		}
		if(lookahead.id == '}'){
			printf("Blockstatements -> .\n");
			pop(stack);
			return 1;
		}
		return 0;
	}

	if(X == TERM_Blockstatement){
		if(lid == TOK_ID) {
			printf("BlockStatement -> <id> AfterId ; .\n");
			pop(stack);
			push(stack, ';');
			push(stack, symbol_id("AfterId"));
			push(stack, TOK_ID);
			return 1;
		}
		if(lid == TOK_BOOLEAN || lid == TOK_INT || lid == TOK_VOID) {
			printf("BlockStatement -> NonclassVarDec ; .\n");
			pop(stack);
			push(stack, ';');
			push(stack, symbol_id("NonclassVarDec"));
			return 1;
		}
		if(lid == '{' || lid == TOK_THIS || lid == ';' || lid == TOK_IF || lid == TOK_RETURN || lid == TOK_BREAK || lid == TOK_CONTINUE || lid == TOK_SYSOUT || lid == TOK_WHILE) {
			printf("BlockStatement -> StmtWithoutId .\n");
			pop(stack);
			push(stack, symbol_id("StmtWithoutId"));
			return 1;
		}
		return 0;
	}

	if(X == TERM_AfterId){
		if(lid == TOK_ID) {
			printf("AfterId -> <id> Eq .\n");
			pop(stack);
			push(stack, symbol_id("Eq"));
			push(stack, TOK_ID);
			return 1;
		}
		if(lid == '[' || lid == '.' || lid == '='){
			printf("AfterId -> AfterIdExceptId .\n");
			pop(stack);
			push(stack, symbol_id("AfterIdExceptId"));
			return 1;
		}
		return 0;
	}

	if(X == TERM_Eq){
		if(lid == '=') {
			printf("Eq -> = E .\n");
			pop(stack);
			push(stack, symbol_id("E"));
			push(stack, '=');
			return 1;
		}
		if(lid == '}' || lid == '{' || lid == TOK_ID || lid == TOK_BOOLEAN || lid == TOK_INT || lid == TOK_THIS || lid == ';' || lid == TOK_ELSE || lid == TOK_IF || lid == TOK_RETURN || lid == TOK_BREAK || lid == TOK_CONTINUE || lid == TOK_SYSOUT || lid == TOK_WHILE || lid == TOK_VOID) {
			printf("Eq ->. \n");
			pop(stack);
			return 1;
		}
		return 0;
	}

	if(X == TERM_NonclassVarDec){
		if(lid == TOK_BOOLEAN || lid == TOK_INT || lid == TOK_VOID) {
			printf("NonclassVarDec -> NonclassType <id> Eq .\n");
			pop(stack);
			push(stack, symbol_id("Eq"));
			push(stack, TOK_ID);
			push(stack, symbol_id("NonclassType"));
			return 1;
		}
		return 0;
	}

	if(X == TERM_Type1){
		if(lid == '[') {
			printf("Type1 -> [ ] Type1 .\n");
			pop(stack);
			push(stack, symbol_id("Type1"));
			push(stack, ']');
			push(stack, '[');
			return 1;
		}
		if(lid == TOK_ID) {
			printf("Type1 -> .\n");
			pop(stack);
			return 1;
		}
		return 0;
	}

	if(X == TERM_NonclassType){
		if(lid == TOK_BOOLEAN) {
			printf("NonclassType -> boolean Type1 .\n");
			pop(stack);
			push(stack, symbol_id("Type1"));
			push(stack, TOK_BOOLEAN);
			return 1;
		}
		if(lid == TOK_INT) {
			printf("NonclassType -> int Type1 .\n");
			pop(stack);
			push(stack, symbol_id("Type1"));
			push(stack, TOK_INT);
			return 1;
		}
		if(lid == TOK_VOID) {
			printf("NonclassType -> void .\n");
			pop(stack);
			push(stack, TOK_VOID);
			return 1;
		}
		return 0;
	}

	if(X == TERM_Type){
		if(lid == TOK_BOOLEAN || lid == TOK_INT || lid == TOK_VOID) {
			printf("Type -> NonclassType .\n");
			pop(stack);
			push(stack, symbol_id("NonclassType"));
			return 1;
		}
		if(lid == TOK_ID) {
			printf("Type -> <id> Type1 .\n");
			pop(stack);
			push(stack, symbol_id("Type1"));
			push(stack, TOK_ID);
			return 1;
		}
		return 0;
	}

	if(X == TERM_Stmt){
		if(lid == TOK_ID) {
			printf("Stmt -> <id> AfterIdExceptId ; .\n");
			pop(stack);
			push(stack, ';');
			push(stack, symbol_id("AfterIdExceptId"));
			push(stack, TOK_ID);
			return 1;
		}
		if(lid == '{' || lid == TOK_THIS || lid == ';' || lid == TOK_IF || lid == TOK_RETURN || lid == TOK_BREAK || lid == TOK_CONTINUE || lid == TOK_SYSOUT || lid == TOK_WHILE) {
			printf("Stmt -> StmtWithoutId .\n");
			pop(stack);
			push(stack, symbol_id("StmtWithoutId"));
			return 1;
		}
		return 0;
	}

	if(X == TERM_StmtWithoutId){
		if(lid == '{') {
			printf("StmtWithoutId -> { Blockstatements } .\n");
			pop(stack);
			push(stack, '}');
			push(stack, symbol_id("Blockstatements"));
			push(stack, '{');
			return 1;
		}
		if(lid == TOK_WHILE) {
			printf("StmtWithoutId -> while ( E ) Stmt .\n");
			pop(stack);
			push(stack, symbol_id("Stmt"));
			push(stack, ')');
			push(stack, symbol_id("E"));
			push(stack, '(');
			push(stack, TOK_WHILE);
			return 1;
		}
		if(lid == TOK_SYSOUT) {
			printf("StmtWithoutId -> systemoutprintln ( E ) semicolon .\n");
			pop(stack);
			push(stack, ';');
			push(stack, ')');
			push(stack, symbol_id("E"));
			push(stack, '(');
			push(stack, TOK_SYSOUT);
			return 1;
		}
		if(lid == TOK_CONTINUE) {
			printf("StmtWithoutId -> continue ; .\n");
			pop(stack);
			push(stack, ';');
			push(stack, TOK_CONTINUE);
			return 1;
		}
		if(lid == TOK_BREAK) {
			printf("StmtWithoutId -> break ; .\n");
			pop(stack);
			push(stack, ';');
			push(stack, TOK_BREAK);
			return 1;
		}
		if(lid == TOK_RETURN) {
			printf("StmtWithoutId -> return OptExp ; .\n");
			pop(stack);
			push(stack, ';');
			push(stack, symbol_id("OptExp"));
			push(stack, TOK_RETURN);
			return 1;
		}
		if(lid == TOK_IF) {
			printf("StmtWithoutId -> if ( E ) Stmt OptElse .\n");
			pop(stack);
			push(stack, symbol_id("OptElse"));
			push(stack, symbol_id("Stmt"));
			push(stack, ')');
			push(stack, symbol_id("E"));
			push(stack, '(');
			push(stack, TOK_IF);
			return 1;
		}
		if(lid == ';') {
			printf("StmtWithoutId -> ;.\n");
			pop(stack);
			push(stack, ';');
			return 1;
		}
		if(lid == TOK_THIS) {
			printf("StmtWithoutId -> this . <id> AfterThisInStmt .\n");
			pop(stack);
			push(stack, symbol_id("AfterThisInStmt"));
			push(stack, TOK_ID);
			push(stack, '.');
			push(stack, TOK_THIS);
			return 1;
		}
		return 0;
	}

	if(X == TERM_OptElse){
		if(lid == TOK_ELSE) {
			printf("OptElse -> else Stmt .\n");
			pop(stack);
			push(stack, symbol_id("Stmt"));
			push(stack, TOK_ELSE);
			return 1;
		}
		//Possivel conflito aqui. lid == TOK_ELSE nas duas produções
		if(lid == '{' || lid == '}' || lid == TOK_ID || lid == TOK_BOOLEAN || lid == TOK_INT || lid == TOK_THIS || lid == ';' || lid == TOK_ELSE || lid == TOK_IF || lid == TOK_RETURN || lid == TOK_BREAK || lid == TOK_CONTINUE || lid == TOK_SYSOUT || lid == TOK_WHILE || lid == TOK_VOID) {
			printf("OptElse -> .\n");
			pop(stack);
			return 1;
		}
		return 0;
	}

	if(X == TERM_OptExp){
		if(lid == '!' || lid == '-' || lid == '(' || lid == '}' || lid == TOK_ID || lid == TOK_NEW || lid == TOK_NULL || lid == TOK_LIT_STR || lid == TOK_FALSE || lid == TOK_TRUE || lid == TOK_LIT_INT || lid == TOK_THIS)  {
			printf("OptExp -> E .\n");
			pop(stack);
			push(stack, symbol_id("E"));
			return 1;
		}
		if(lid == ';') {
			printf("OptExp -> .\n");
			pop(stack);
			return 1;
		}
		return 0;
	}

	if(X == TERM_AfterThisInStmt){
		if(lid == '[' || lid == '.' || lid == '=' ) {
			printf("AfterThisInStmt -> AfterIdExceptId .\n");
			pop(stack);
			push(stack, symbol_id("AfterIdExceptId"));
			return 1;
		}
		if(lid == '('){
			printf("AfterThisInStmt -> ( T3 ) OptAfterIdExceptId .\n");
			pop(stack);
			push(stack, symbol_id("OptAfterIdExceptId"));
			push(stack, ')');
			push(stack, symbol_id("T3"));
			push(stack, '(');
			return 1;
		}
		return 0;
	}

	if(X == TERM_OptAfterIdExceptId){
		if(lid == '[' || lid == '.' || lid == '='){
			printf("OptAfterIdExceptId -> AfterIdExceptId . \n");
			pop(stack);
			push(stack, symbol_id("AfterIdExceptId"));
			return 1;
		}
		if(lid == '}' || lid == '{' || lid == TOK_ID || lid == TOK_BOOLEAN || lid == TOK_INT || lid == TOK_THIS || lid == ';' || lid == TOK_ELSE || lid == TOK_IF || lid == TOK_RETURN || lid == TOK_BREAK || lid == TOK_CONTINUE || lid == TOK_SYSOUT || lid == TOK_WHILE || lid == TOK_VOID) {
			printf("OptAfterIdExceptId -> .\n");
			pop(stack);
			return 1;
		}
		return 0;
	}

	if(X == TERM_AfterIdExceptId) {
		if(lid == '.') {
			printf("AfterIdExceptId -> Dot Eq . \n");
			pop(stack);
			push(stack, symbol_id("Eq"));
			push(stack, symbol_id("Dot"));
			return 1;
		}
		if(lid == '[') {
			printf("AfterIdExceptId -> Bracket Eq . \n");
			pop(stack);
			push(stack, symbol_id("Eq"));
			push(stack, symbol_id("Bracket"));
			return 1;
		}
		if(lid == '=') {
			printf("AfterIdExceptId -> = E .\n");
			pop(stack);
			push(stack, symbol_id("E"));
			push(stack, '=');
			return 1;
		}
		return 0;
	}

	if(X == TERM_Dot){
		if(lid == '.') {
			printf("Dot -> dot <id> ( T3 ) DotR .\n");
			pop(stack);
			push(stack, symbol_id("DotR"));
			push(stack, ')');
			push(stack, symbol_id("T3"));
			push(stack, '(');
			push(stack, TOK_ID);
			push(stack, '.');
			return 1;
		}
		return 0;
	}

	if(X == TERM_DotR){
		if(lid == '.') {
			printf("DotR -> dot <id> ( T3 ) DotR .\n");
			pop(stack);
			push(stack, symbol_id("DotR"));
			push(stack, ')');
			push(stack, symbol_id("T3"));
			push(stack, '(');
			push(stack, TOK_ID);
			push(stack, '.');
			return 1;
		}
		if(lid == '[') {
			printf("DotR -> [ E ] DotR .\n");
			pop(stack);
			push(stack, symbol_id("DotR"));
			push(stack, ']');
			push(stack, symbol_id("E"));
			push(stack, '[');
			return 1;
		}
		if(lid == '}' || lid == '{' || lid == TOK_ID || lid == TOK_BOOLEAN || lid == TOK_INT || lid == TOK_THIS || lid == ';' || lid == '=' || lid == TOK_ELSE || lid == TOK_IF || lid == TOK_RETURN || lid == TOK_BREAK || lid == TOK_CONTINUE || lid == TOK_SYSOUT || lid == TOK_WHILE || lid == TOK_VOID) {
			printf("DotR -> .\n");
			pop(stack);
			return 1;
		}
		return 0;
	}

	if(X == TERM_Bracket){
		if(lid == '[') {
			printf("Bracket -> [ BracketR .\n");
			pop(stack);
			push(stack, symbol_id("BracketR"));
			push(stack, '[');
			return 1;
		}
		return 0;
	}
	if(X == TERM_BracketR){
		if(lid == '!' || lid == '-' || lid == '(' || lid == '}' || lid == TOK_ID || lid == TOK_NEW || lid == TOK_NULL || lid == TOK_LIT_STR || lid == TOK_FALSE || lid == TOK_TRUE || lid == TOK_LIT_INT || lid == TOK_THIS) {
			printf("BracketR -> E ] DotR .\n");
			pop(stack);
			push(stack, symbol_id("DotR"));
			push(stack, ']');
			push(stack, symbol_id("E"));
			return 1;
		}
		if(lid == '}') {
			printf("BracketR -> ] BracketEmpty <id> .\n");
			pop(stack);
			push(stack, TOK_ID);
			push(stack, symbol_id("BracketEmpty"));
			push(stack, '[');
			return 1;
		}
		return 0;
	}

	if(X == TERM_BracketEmpty){
		if(lid == '{') {
			printf("BracketEmpty -> [ ]  BracketEmpty .\n");
			pop(stack);
			push(stack, symbol_id("BracketEmpty"));
			push(stack, '}');
			push(stack, '{');
			return 1;
		}
		if(lid == TOK_ID) {
			printf("BracketEmpty -> .\n");
			pop(stack);
			return 1;
		}
		return 0;
	}

	if(X == TERM_ClassDeclarations){
		if(lid == TOK_CLASS) {
			printf("ClassDeclarations -> ClassDeclaration ClassDeclarations .\n");
			pop(stack);
			push(stack, symbol_id("ClassDeclarations"));
			push(stack, symbol_id("ClassDeclaration"));
			return 1;
		}
		if(lid == TOK_EOF) {
			printf("ClassDeclarations -> .\n");
			pop(stack);
			return 1;
		}
		return 0;
	}
	if(X == TERM_ClassDeclaration){
		if(lid == TOK_CLASS) {
			printf("ClassDeclaration -> class <id> Extends ClassBody .\n");
			pop(stack);
			push(stack, symbol_id("ClassBody"));
			push(stack, symbol_id("Extends"));
			push(stack, TOK_ID);
			push(stack, TOK_CLASS);
			return 1;
		}
		return 0;
	}

	if(X == TERM_Extends){
		if(lid == TOK_EXTENDS) {
			printf("Extends -> extends <id> .\n");
			pop(stack);
			push(stack, TOK_ID);
			push(stack, TOK_EXTENDS);
			return 1;
		}
		if(lid == '{') {
			printf("Extends -> .\n");
			pop(stack);
			return 1;
		}
		return 0;
	}

	if(X == TERM_ClassBody){
		if(lid == '{') {
			printf("ClassBody -> { ClassContent } .\n");
			pop(stack);
			push(stack, '}');
			push(stack, symbol_id("ClassContent"));
			push(stack, '{');
			return 1;
		}
		return 0;
	}

	if(X == TERM_ClassContent){
		if(lid == TOK_ID || lid == TOK_BOOLEAN || lid == TOK_INT || lid == TOK_VOID) {
			printf("ClassContent -> ClassComponent ClassContent .\n");
			pop(stack);
			push(stack, symbol_id("ClassContent"));
			push(stack, symbol_id("ClassComponent"));
			return 1;
		}
		if(lid == '}') {
			printf("ClassContent -> .\n");
			pop(stack);
			return 1;
		}
		return 0;
	}
	if(X == TERM_ClassComponent){
		if(lid == TOK_ID || lid == TOK_BOOLEAN || lid == TOK_INT || lid == TOK_VOID) {
			printf("ClassComponent -> Type <id> RestDec .\n");
			pop(stack);
			push(stack, symbol_id("RestDec"));
			push(stack, TOK_ID);
			push(stack, symbol_id("Type"));
			return 1;
		}
		return 0;
	}

	if(X == TERM_RestDec){
		if(lid == ';' || lid == '=') {
			printf("RestDec -> Eq ; .\n");
			pop(stack);
			push(stack, ';');
			push(stack, symbol_id("Eq"));
			return 1;
		}
		if(lid == '(') {
			printf("RestDec -> ( ParamsOpt ) { Blockstatements } .\n");
			pop(stack);
			push(stack, '}');
			push(stack, symbol_id("Blockstatements"));
			push(stack, '{');
			push(stack, ')');
			push(stack, symbol_id("ParamsOpt"));
			push(stack, '(');
			return 1;
		}
		return 0;
	}

	if(X == TERM_ParamsOpt){
		if(lid == TOK_ID|| lid == TOK_BOOLEAN || lid == TOK_INT || lid == TOK_VOID) {
			printf("ParamsOpt -> Params .\n");
			pop(stack);
			push(stack, symbol_id("Params"));
			return 1;
		}
		if(lid == ')') {
			printf("ParamsOpt -> .\n");
			pop(stack);
			return 1;
		}
		return 0;
	}

	if(X == TERM_Params){
		if(lid == TOK_ID|| lid == TOK_BOOLEAN || lid == TOK_INT || lid == TOK_VOID) {
			printf("Params -> Param ParamsRest .\n");
			pop(stack);
			push(stack, symbol_id("ParamsRest"));
			push(stack, symbol_id("Param"));
			return 1;
		}
		return 0;
	}

	if(X == TERM_ParamsRest){
		if(lid == ',') {
			printf("ParamsRest -> , Params .\n");
			pop(stack);
			push(stack, symbol_id("Params"));
			push(stack, ',');
			return 1;
		}
		if(lid == ')') {
			printf("ParamsRest -> .\n");
			pop(stack);
			return 1;
		}
		return 0;
	}

	if(X == TERM_Param){
		if(lid == TOK_ID|| lid == TOK_BOOLEAN || lid == TOK_INT || lid == TOK_VOID) {
			printf("Param -> Type <id> .\n");
			pop(stack);
			push(stack, TOK_ID);
			push(stack, symbol_id("Type"));
			return 1;
		}
		return 0;
	}
	return 0;
}

void stackparse_error(char X, struct token lookahead){
	printf("ERROR with grammar symbol ");
	if(X>0) printf("%c",X);
	else printf("%d",X);
	printf(" and lookahead %s\n", lookahead.lexem);
}

char* get_lexem_token(char* lexem){
	// TODO
	return NULL;
}

char symbol_id(char* X){
	if(strcmp(X,"E")==0) return TERM_E;
	if(strcmp(X,"Ep")==0) return TERM_Ep;
	if(strcmp(X,"E1")==0) return TERM_E1;
	if(strcmp(X,"E1p")==0) return TERM_E1p;
	if(strcmp(X,"E2")==0) return TERM_E2;
	if(strcmp(X,"E2p")==0) return TERM_E2p;
	if(strcmp(X,"E3")==0) return TERM_E3;
	if(strcmp(X,"E3p")==0) return TERM_E3p;
	if(strcmp(X,"T")==0) return TERM_T;
	if(strcmp(X,"Tp")==0) return TERM_Tp;
	if(strcmp(X,"T2")==0) return TERM_T2;
	if(strcmp(X,"T3")==0) return TERM_T3;
	if(strcmp(X,"T4")==0) return TERM_T4;
	if(strcmp(X,"X")==0) return TERM_X;
	if(strcmp(X,"Xp")==0) return TERM_Xp;
	if(strcmp(X,"P")==0) return TERM_P;
	if(strcmp(X,"F")==0) return TERM_F;
	if(strcmp(X,"TT")==0) return TERM_TT;
	if(strcmp(X,"AfterThisInExp")==0) return TERM_AfterThisInExp;
	if(strcmp(X,"RestThisInExp")==0) return TERM_RestThisInExp;
	if(strcmp(X,"AfterNew")==0) return TERM_AfterNew;
	if(strcmp(X,"AfterNewId")==0) return TERM_AfterNewId;
	if(strcmp(X,"FilledBrackets")==0) return TERM_FilledBrackets;
	if(strcmp(X,"R")==0) return TERM_R;
	if(strcmp(X,"El")==0) return TERM_El;
	if(strcmp(X,"Elp")==0) return TERM_Elp;
	if(strcmp(X,"Relop")==0) return TERM_Relop;
	if(strcmp(X,"Boolop")==0) return TERM_Boolop;
	if(strcmp(X,"Addop")==0) return TERM_Addop;
	if(strcmp(X,"Multop")==0) return TERM_Multop;
	if(strcmp(X,"Unop")==0) return TERM_Unop;

	if(strcmp(X,"Goal")==0) return TERM_Goal;
	if(strcmp(X,"MainClass")==0) return TERM_MainClass;
	if(strcmp(X,"Blockstatements")==0) return TERM_Blockstatements;
	if(strcmp(X,"Blockstatement")==0) return TERM_Blockstatement;
	if(strcmp(X,"AfterId")==0) return TERM_AfterId;
	if(strcmp(X,"Eq")==0) return TERM_Eq;
	if(strcmp(X,"NonclassVarDec")==0) return TERM_NonclassVarDec;
	if(strcmp(X,"Type1")==0) return TERM_Type1;
	if(strcmp(X,"Blockstatements")==0) return TERM_Blockstatements;
	if(strcmp(X,"NonclassType")==0) return TERM_NonclassType;
	if(strcmp(X,"Type")==0) return TERM_Type;
	if(strcmp(X,"Stmt")==0) return TERM_Stmt;
	if(strcmp(X,"StmtWithoutId")==0) return TERM_StmtWithoutId;
	if(strcmp(X,"OptElse")==0) return TERM_OptElse;
	if(strcmp(X,"OptExp")==0) return TERM_OptExp;
	if(strcmp(X,"AfterThisInStmt")==0) return TERM_AfterThisInStmt;
	if(strcmp(X,"OptAfterIdExceptId")==0) return TERM_OptAfterIdExceptId;
	if(strcmp(X,"AfterIdExceptId")==0) return TERM_AfterIdExceptId;
	if(strcmp(X,"Dot")==0) return TERM_Dot;
	if(strcmp(X,"DotR")==0) return TERM_DotR;
	if(strcmp(X,"Bracket")==0) return TERM_Bracket;
	if(strcmp(X,"BracketR")==0) return TERM_BracketR;
	if(strcmp(X,"BracketEmpty")==0) return TERM_BracketEmpty;
	if(strcmp(X,"ClassDeclarations")==0) return TERM_ClassDeclarations;
	if(strcmp(X,"ClassDeclaration")==0) return TERM_ClassDeclaration;
	if(strcmp(X,"Extends")==0) return TERM_Extends;
	if(strcmp(X,"ClassBody")==0) return TERM_ClassBody;
	if(strcmp(X,"ClassContent")==0) return TERM_ClassContent;
	if(strcmp(X,"ClassComponent")==0) return TERM_ClassComponent;
	if(strcmp(X,"RestDec")==0) return TERM_RestDec;
	if(strcmp(X,"ParamsOpt")==0) return TERM_ParamsOpt;
	if(strcmp(X,"Params")==0) return TERM_Params;
	if(strcmp(X,"ParamsRest")==0) return TERM_ParamsRest;
	if(strcmp(X,"Param")==0) return TERM_Param;
	printf("ERROR AT symbol_id WITH SYMBOL %s\n", X);
}