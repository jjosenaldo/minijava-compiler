#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

// Compile: gcc stack_test.c model/stack.c -o ./bin/stack -I model
// Run: ./bin/stack

int main() {
	Stack* stack = NULL; // Empty stack
	for(int i = 0; i < 10; i++) {
		printf("Inserting %i\n", i);
		push(&stack, i);
	}

	while(!isEmpty(&stack)) {
		int temp = top(&stack);
		printf("Deleting %i\n", temp);
		pop(&stack);
	}

	printf("Stack is%sempty\n", isEmpty(&stack) ? " " : " not ");

	return 0;
}