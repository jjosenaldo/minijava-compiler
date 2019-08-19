#ifndef REC_PARSER_H
#define REC_PARSER_H

void parse();

struct token lookahead;
void error();
void E();
void Ep();
void E1();
void E1p();
void E2();
void E2p();
void E3();
void E3p();
void T();
void Tp();
void T2();
void T3();
void T4();
void X();
void Xp();
void P();
void F();
void TT();
void R();
void El();
void Elp();
void Relop();
void Boolop();
void Addop();
void Multop();
void Unop();

#endif