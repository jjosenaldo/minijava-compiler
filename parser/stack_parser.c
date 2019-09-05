#include "stack_parser.h"
#include <stdio.h>

#define lid lookahead.id

void stack_parse(){
	struct token lookahead = getNextToken(); 

	// empty stack
	Stack* stack = NULL; 

	// current grammar symbol
	char X = symbol_id("E"); 
	push(&stack, X);

	while(X != TOK_EOF){
		if(X == lookahead.id){
			pop(&stack);
			lookahead = getNextToken();
		} else if(is_terminal(X)){
			printf("%c is terminal and it's not equal to the lookahead, which has id %c and lexem %s",X,lookahead.id,lookahead.lexem );
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
	if(X == TOK_PRINT) return 1;
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
		if(lookahead.id == ',' || lookahead.id == '(' || lookahead.id == '}' || lookahead.id == '{'
			|| lookahead.id == ']' || lookahead.id == TOK_ID || lookahead.id == TOK_BOOLEAN || lookahead.id == TOK_INT
			|| lookahead.id == TOK_THIS || lookahead.id == ';' || lookahead.id == TOK_ELSE || lookahead.id == TOK_IF
			|| lookahead.id == TOK_RETURN || lookahead.id == TOK_BREAK || lookahead.id == TOK_CONTINUE || lookahead.id == TOK_SYSOUT
			|| lookahead.id == TOK_WHILE || lookahead.id == TOK_VOID){
			printf("Ep -> .\n");
			pop(stack);
			return 1;	
		}
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
	}
	if(X == TERM_E1p){
		if(lid == TOK_OR || lid == TOK_AND){
			printf("E1p -> Boolop E2 E1p .");
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
			printf("E1p -> .");
			pop(stack);
			return 1;
		}
	}
	return 0;
}

void stackparse_error(char X, struct token lookahead){
	printf("ERROR with grammar symbol %c and lookahead %s\n", X, lookahead.lexem);
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
	printf("ERROR AT symbol_id WITH SYMBOL %s\n", X);
	printf("%i\n",strcmp(X,"E2"));
}