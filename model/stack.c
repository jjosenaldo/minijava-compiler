#include "stack.h"
#include "grammar.h"
#include <stdio.h>

void push(Stack** stack, StackData data) {
	Stack* newNode = (Stack*) malloc(sizeof(Stack));
	newNode->data = data;
	newNode->next = *stack;
	*stack = newNode;
}

void pop(Stack** stack) {
	Stack* temp = *stack;
	*stack = (*stack)->next;
	free(temp);
}

StackData top(Stack** stack) {
	return (*stack)->data;
}

int isEmpty(Stack** stack) {
	return *stack == NULL;
}

void print(Stack** stack){
	Stack* aux = *stack;
	if(aux == NULL) printf("NULLSTACK");
	else{
		printf("STACK: ");
		do{
			if(aux->data > 0 )
				printf("%c",aux->data);
			else 
				print_nonterminal(aux->data);
			printf(" ");
			aux = aux->next;
		} while(aux->next != NULL);
	}
	printf("\n");
}