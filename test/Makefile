all:
	flex lexer.l
	bison -d yaccer.y -o yaccer.cpp
	g++ -x c++ yaccer.cpp lex.yy.c -ly -ll