all:
	lex first.l
	yacc second.y
	gcc y.tab.c -ly -ll -lfl -o main.out

clean:
	rm -f *.c
	rm -f main.out