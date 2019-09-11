# Paths
BIN = ./bin
OBJ = ./obj
LEXER_PATH = ./lexer
NONRECURSIVE_PARSER_PATH = ./nonrecursive-topdown-parser
RECURSIVE_PARSER_PATH = ./recursive-topdown-parser
YACC_PARSER_PATH = ./yacc-bottomup-parser
STACK_PATH = ./model
GRAMMAR_PATH = ./grammar
MAIN = ./main.c

# Commands
#FLAGS = -Wall
LEX := lex
YACC := yacc
INC := -I $(LEXER_PATH) -I $(RECURSIVE_PARSER_PATH) -I $(STACK_PATH) -I $(GRAMMAR_PATH) -I $(YACC_PARSER_PATH) -I $(NONRECURSIVE_PARSER_PATH)
GCC := gcc

# Compile program (no recompiling if files haven't changed)
#all: $(BIN)/main.out

yacc_parser: $(OBJ)/yacc.o $(MAIN)
	$(GCC) $(FLAGS) $(INC) $(OBJ)/*.o main.c -o $(BIN)/main.out -D YACC_PARSER

rec_parser: obj $(MAIN)
	$(GCC) $(FLAGS) $(INC) $(OBJ)/*.o main.c -o $(BIN)/main.out -D REC_PARSER

stack_parser: obj $(MAIN)
	$(GCC) $(FLAGS) $(INC) $(OBJ)/*.o main.c -o $(BIN)/main.out -D STACK_PARSER

lex:
	$(GCC) $(FLAGS) $(INC) $(OBJ)/*.o main.c -o $(BIN)/main.out -D LEX

# Force program compilation
$(BIN)/main.out: obj $(MAIN)
	$(GCC) $(FLAGS) $(INC) $(OBJ)/*.o main.c -o $(BIN)/main.out

# Compile object codes
obj: $(OBJ)/lexer.o \
	$(OBJ)/rec_parser.o \
	$(OBJ)/stack.o \
	$(OBJ)/stack_parser.o \
	$(OBJ)/grammar.o \
	$(OBJ)/yacc_parser.o

# Compile Lexer
$(OBJ)/lexer.o: $(LEXER_PATH)/lexer.l
	$(LEX) -o $(OBJ)/lex.yy.c $(LEXER_PATH)/lexer.l
	$(GCC) $(FLAGS) $(INC) -c $(OBJ)/lex.yy.c -o $(OBJ)/lexer.o
	rm $(OBJ)/lex.yy.c

# Compile Lexer for Yacc
$(OBJ)/yacc.o: $(LEXER_PATH)/lex_for_yacc.l $(YACC_PARSER_PATH)/yacc_parser.y
	$(LEX) -o $(OBJ)/lex_for_yacc.yy.c $(LEXER_PATH)/lex_for_yacc.l
	$(YACC) -o $(OBJ)/y.tab.c $(YACC_PARSER_PATH)/yacc_parser.y -d
	$(GCC) -o $(OBJ)/yacc.o $(FLAGS) $(INC) $(OBJ)/lex_for_yacc.yy.c $(OBJ)/y.tab.c  -lfl
	rm $(OBJ)/lex_for_yacc.yy.c $(OBJ)/y.tab.c

# compile grammar
$(OBJ)/grammar.o: $(GRAMMAR_PATH)/grammar.c $(GRAMMAR_PATH)/grammar.h
	$(GCC) $(FLAGS) -c $(GRAMMAR_PATH)/grammar.c -o $(OBJ)/grammar.o $(INC)
	
# Compile nonrecursive descent parser
$(OBJ)/stack_parser.o: $(PARSER_PATH)/stack_parser.c $(PARSER_PATH)/stack_parser.h
	$(GCC) $(FLAGS) -c $(PARSER_PATH)/stack_parser.c -o $(OBJ)/stack_parser.o $(INC)

# Compile Recursive Descendent Parser
$(OBJ)/rec_parser.o: $(PARSER_PATH)/rec_parser.c $(PARSER_PATH)/rec_parser.h
	$(GCC) $(FLAGS) -c $(PARSER_PATH)/rec_parser.c -o $(OBJ)/rec_parser.o $(INC)

# Compile Stack
$(OBJ)/stack.o: $(STACK_PATH)/stack.c $(STACK_PATH)/stack.h
	$(GCC) $(FLAGS) -c $(STACK_PATH)/stack.c -o $(OBJ)/stack.o $(INC)

# Clean project
clean:
	@# @ symbol at beginning indicates that it will not be printed
	@if [ "$$(ls -A $(OBJ))" ]; then \
		echo "rm $(OBJ)/*"; \
		rm $(OBJ)/*; \
	fi
	@if [ "$$(ls -A $(BIN))" ]; then \
		echo "rm $(BIN)/*"; \
		rm $(BIN)/*; \
	fi

# Run all code examples
test: $(BIN)/main.out
	@for filename in ./code-examples/*; do \
		echo "------ TEST --------------------------\nFile: $$filename\n"; \
		./bin/main.out < "$$filename"; \
		echo "--------------------------------------\n\n"; \
	done