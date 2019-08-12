#ifndef TOKEN_H
#define TOKEN_H

static const char TOK_LIT_INT = '1';
static const char TOK_PUBLIC = 'b';
static const char TOK_BREAK = 'B';
static const char TOK_BOOLEAN = 'o';
static const char TOK_CONTINUE = 'C';
static const char TOK_CLASS = 'c';
static const char TOK_ID = 'd';
static const char TOK_DIFF = 'D';
static const char TOK_ERROR = 'e';
static const char TOK_EOF = 'E';
static const char TOK_IF = 'f';
static const char TOK_FALSE = 'F';
static const char TOK_STRING = 'g';
static const char TOK_GREAT_EQ = 'G';
static const char TOK_INT = 'i';
static const char TOK_LENGTH = 'l';
static const char TOK_LESS_EQ = 'L';
static const char TOK_MAIN = 'm';
static const char TOK_NEW = 'n';
static const char TOK_NULL = 'N';
static const char TOK_PRINT = 'p';
static const char TOK_EQ = 'q';
static const char TOK_RETURN = 'r';
static const char TOK_LIT_STR = 'R';
static const char TOK_ELSE = 's';
static const char TOK_STATIC = 'S';
static const char TOK_THIS = 't';
static const char TOK_TRUE = 'T';
static const char TOK_VOID = 'v';
static const char TOK_WHILE = 'w';
static const char TOK_EXTENDS = 'x';
static const char TOK_AND = '&';
static const char TOK_OR = '|';
static const char EPS = '@';


struct token{
    char id;
    char* lexem;
    int lexemLen;
    int row;
    int col;
};

struct token getNextToken();

#endif