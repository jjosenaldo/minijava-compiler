#ifndef Stack_parser_H
#define Stack_parser_H

#include "token.h"
#include "stack.h"
#include <string.h>

static const char DELIMITER = '@';

void stack_parse();

int is_terminal(char X);

// Returns false if the table entry is empty; true otherwise 
int add_rule_to_stack(char X, Stack** stack, struct token lookahead);

void stackparse_error(char X, struct token lookahead);

char* get_lexem_token(char* lexem);

char symbol_id(char* X);

#endif