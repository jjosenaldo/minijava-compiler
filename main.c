#include "stack_parser.h"
#include "rec_parser.h"
#include <stdio.h>

int main(){
#ifdef REC_PARSER
	rec_parse();
#elif STACK_PARSER
    stack_parse();
#elif LEX
    struct token t = getNextToken();
    while(t.id != TOK_EOF) {
    	printf("id: %c, lexem: %s\n", t.id, t.lexem);
    	t = getNextToken();
    }
#endif
    return 0;
}