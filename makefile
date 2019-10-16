# Paths
BIN = ./bin
OBJ = ./obj
PARSER_PATH = ./parser
GRAMMAR_PATH = ./grammar
SYMTABLE_PATH = ./symtable

# Commands
#FLAGS = -Wall
LEX := flex
YACC := bison
INC := -I $(GRAMMAR_PATH) -I $(PARSER_PATH) -I $(SYMTABLE_PATH)

parser: lexer yaccer
	g++ -x c++ $(OBJ)/yaccer.cpp $(OBJ)/lex.yy.c -ly -ll -o $(BIN)/main.out $(INC)

lexer: $(PARSER_PATH)/lexer.l 
	$(LEX) -o $(OBJ)/lex.yy.c $(PARSER_PATH)/lexer.l

yaccer: $(PARSER_PATH)/yaccer.y 
	$(YACC) -d $(PARSER_PATH)/yaccer.y -o $(OBJ)/yaccer.cpp

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