#include "stack_parser.h"
#include "rec_parser.h"
#include <stdio.h>

int main(){
#ifdef REC_PARSER
	rec_parse();
#elif STACK_PARSER
    stack_parse();
#endif
    return 0;
}