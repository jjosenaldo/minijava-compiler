#ifndef TAB_PARSER_H
#define TAB_PARSER_H
#include <stdlib.h>

struct Stack {
	char data;
	struct Stack* next;
};

typedef struct Stack Stack;
typedef char StackData;

void push(Stack** stack, StackData value);
void pop(Stack** stack);
StackData top(Stack** stack);
Stack* newStack(char data);
int isEmpty(Stack **stack);
void print(Stack** stack);

#endif