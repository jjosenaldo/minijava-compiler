CC := gcc
LEX := lex

# path #
LEXER_PATH = lexer
PARSER_PATH = parser

#flags #
FLAGS =
INC = -I $(LEXER_PATH) -I $(PARSER_PATH)

main.out: lex.yy.c
	$(CC) $(FLAGS) $(INC) $(LEXER_PATH)/lex.yy.c main.c -o main.out

lex.o: lex.yy.c
	$(CC) $(FLAGS) 	-c $(LEXER_PATH)/lex.yy.c -o $(LEXER_PATH)/lex.o

lex.yy.c: $(LEXER_PATH)/lexer.l
	$(LEX) -o $(LEXER_PATH)/lex.yy.c $(LEXER_PATH)/lexer.l

clean:
	rm -f $(LEXER_PATH)/lex.yy.c *.o main.out core output