all:
	lex first.l
	yacc -v second.y -d
	gcc y.tab.c -ly -ll -lfl -o main.out 

clean:
	rm -f *.c
	rm -f main.out