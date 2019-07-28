#ifndef TOKEN_H
#define TOKEN_H

static const char TOK_LIT_INT = 'i';
static const char TOK_EOF = 'E';
static const char TOK_PLUS = '+';
static const char TOK_MINUS = '-';
static const char TOK_TIMES  = '+';
static const char TOK_ERROR = 'e';

struct token{
    char id;
    char* lexem;
    int lexemLen;
};

struct token getNextToken();

#endif