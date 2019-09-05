#include "stack.h"

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