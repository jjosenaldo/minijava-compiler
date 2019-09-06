#ifndef TOKEN_H
#define TOKEN_H

static const char TOK_LIT_INT = '1';
static const char TOK_SUBSTRING = 'a';
static const char TOK_PUBLIC = 'b';
static const char TOK_BREAK = 'B';
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
static const char TOK_SYSOUT = 'o';
static const char TOK_BOOLEAN = 'O';
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

static const int TERM_E = 0;
static const int TERM_Ep = 1;
static const int TERM_E1 = 2;
static const int TERM_E2p = 3;
static const int TERM_E3 = 4;
static const int TERM_E3p = 5;
static const int TERM_T = 6;
static const int TERM_Tp = 7;
static const int TERM_T2 = 8;
static const int TERM_T3 = 9;
static const int TERM_T4 = 10;
static const int TERM_X = 11;
static const int TERM_Xp = 12;
static const int TERM_P = 13;
static const int TERM_F = 14;
static const int TERM_TT = 15;
static const int TERM_AfterThisInExp = 16;
static const int TERM_RestThisInExp = 17;
static const int TERM_AfterNew = 18;
static const int TERM_AfterNewId = 19;
static const int TERM_FilledBrackets = 20;
static const int TERM_R = 21;
static const int TERM_El = 22;
static const int TERM_Elp = 23;
static const int TERM_Relop = 24;
static const int TERM_Boolop = 25;
static const int TERM_Addop = 26;
static const int TERM_Multop = 27;
static const int TERM_Unop = 28;
static const int TERM_E2 = 29;
static const int TERM_E1p = 30;

static const int TERM_Goal = 31;
static const int TERM_MainClass = 32;
static const int TERM_Blockstatements = 33;
static const int TERM_Blockstatement = 34;
static const int TERM_AfterId = 35;
static const int TERM_Eq = 36;
static const int TERM_NonclassVarDec = 37;
static const int TERM_Type1 = 38;
static const int TERM_Blockstatements = 39;
static const int TERM_NonclassType = 40;
static const int TERM_Type = 41;
static const int TERM_Stmt = 42;
static const int TERM_StmtWithoutId = 43;
static const int TERM_OptElse = 44;
static const int TERM_OptExp = 45;
static const int TERM_AfterThisInStmt = 46;
static const int TERM_OptAfterIdExceptId = 47;
static const int TERM_Dot = 48;
static const int TERM_DotR = 49;
static const int TERM_Bracket = 50;
static const int TERM_BracketR = 51;
static const int TERM_BracketEmpty = 52;
static const int TERM_ClassDeclarations = 53;
static const int TERM_ClassDeclaration = 54;
static const int TERM_Extends = 55;
static const int TERM_ClassBody = 56;
static const int TERM_ClassContent = 57;
static const int TERM_ClassComponent = 58;
static const int TERM_RestDec= 59;
static const int TERM_ParamsOpt = 60;
static const int TERM_Params = 61;
static const int TERM_ParamsRest = 62;
static const int TERM_Param = 63;








struct token{
    char id;
    char* lexem;
    int lexemLen;
    int row;
    int col;
};

struct token getNextToken();

#endif