#ifndef TAB_PARSER_H
#define TAB_PARSER_H
#include <stdlib.h>

struct Stack {
	int data;
	struct Stack* next;
};

typedef struct Stack Stack;
typedef int StackData;

void push(Stack** stack, StackData value);
void pop(Stack** stack);
StackData top(Stack** stack);
Stack* newStack(int data);
int isEmpty(Stack **stack);

#endif