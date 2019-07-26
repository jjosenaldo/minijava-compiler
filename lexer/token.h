#ifndef TOKEN_H
#define TOKEN_H

static const char TOK_LIT_INT = 'i';
static const char TOK_EOF = 'e';

struct token{
    char id;
    char* lexem;
    int lexemLen;
};

struct token getNextToken();

#endif