#include <stdio.h>
#include "lexer/token_defs.h"

int main(){
    char tok;

    // Reads all the tokens from the input file
    while((tok = yylex()) != TOK_EOF){
        printf("Token read: %c\n", tok);
    }
    
    return 0;
}