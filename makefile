# Paths
BIN = ./bin
OBJ = ./obj
YACC_PARSER_PATH = ./lr1-yacc-parser
GRAMMAR_PATH = ./grammar
MAIN = ./main.c
SYMTABLE_PATH = ./symtable

# Commands
#FLAGS = -Wall
LEX := lex
YACC := yacc
INC := -I $(GRAMMAR_PATH) -I $(YACC_PARSER_PATH) -I $(SYMTABLE_PATH)
GCC := gcc

yacc_parser: 
	$(LEX) -o $(OBJ)/lex.yy.c $(YACC_PARSER_PATH)/lexer_for_yacc.l 
	$(YACC) $(YACC_PARSER_PATH)/yacc.y  -d -o $(OBJ)/y.tab.c
	$(GCC) $(OBJ)/y.tab.c $(SYMTABLE_PATH)/symtable.c $(SYMTABLE_PATH)/trie.c $(SYMTABLE_PATH)/types.c -ly -ll -lfl -o $(BIN)/main.out -D YACC_PARSER

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