#include <stdio.h>
#include "lexer/token.h"

int main(){
    struct token tokRead;

    // Reads all the tokens from the input file
    while((tokRead = getNextToken()).id != TOK_EOF){
        if(tokRead.id != TOK_ERROR)
            printf("Token read: %s\n", tokRead.lexem);
        else
            printf("%s is not a valid symbol\n", tokRead.lexem);
    }

    return 0;
}