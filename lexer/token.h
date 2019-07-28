#ifndef TOKEN_H
#define TOKEN_H

static const char TOK_LIT_INT = '1';
static const char TOK_PUBLIC = 'b';
static const char TOK_CLASS = 'c';
static const char TOK_ID = 'd';
static const char TOK_ERROR = 'e';
static const char TOK_EOF = 'E';
static const char TOK_IF = 'f';
static const char TOK_FALSE = 'F';
static const char TOK_STRING = 'g';
static const char TOK_INT = 'i';
static const char TOK_LENGTH = 'l';
static const char TOK_MAIN = 'm';
static const char TOK_NEW = 'n';
static const char TOK_PRINT = 'p';
static const char TOK_RETURN = 'r';
static const char TOK_ELSE = 's';
static const char TOK_STATIC = 'S';
static const char TOK_THIS = 't';
static const char TOK_TRUE = 'T';
static const char TOK_VOID = 'v';
static const char TOK_WHILE = 'w';
static const char TOK_EXTENDS = 'x';

// Tokens whose ID is the token's lexeme itself
static const char TOK_PLUS = '+';
static const char TOK_MINUS = '-';
static const char TOK_TIMES  = '*';
static const char TOK_AND = '&';
static const char TOK_EQUAL = '=';
static const char TOK_LESSTHAN = '<';
static const char TOK_LBRACE = '{';
static const char TOK_RBRACE = '}';
static const char TOK_LPAREN = '(';
static const char TOK_RPAREN = ')';
static const char TOK_LBRACKET = '[';
static const char TOK_RBRACKET = ']';
static const char TOK_SEMICOLON = ';';
static const char TOK_COMMA = ',';
static const char TOK_DOT = '.';
static const char TOK_EXCLAMATION = '!';

struct token{
    char id;
    char* lexem;
    int lexemLen;
};

struct token getNextToken();

#endif