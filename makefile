# Paths
SRC = ./src
BIN = ./bin
OBJ = ./obj
GRAMMAR_PATH = ./grammar
NODE_PATH = ./src/node
PARSER_PATH = ./src/parser
SYMTABLE_PATH = ./src/symtable
SYMTABLEPOOL_PATH = ./src/symtable-pool
TABLECONTENT_PATH = ./src/table-content
TYPE_PATH = ./src/type

# Commands
FLAGS = -Wno-write-strings
LEX := flex
YACC := bison
INC := -I $(GRAMMAR_PATH) -I $(PARSER_PATH) -I $(SYMTABLE_PATH) -I $(SYMTABLEPOOL_PATH) -I $(NODE_PATH) -I $(TABLECONTENT_PATH) -I $(TYPE_PATH)
SRCS = $(SYMTABLE_PATH)/symtable.cpp $(TABLECONTENT_PATH)/table-content.cpp $(TYPE_PATH)/type.cpp $(SYMTABLEPOOL_PATH)/symtable-pool.cpp

parser: lexer yaccer
	g++ -x c++ $(OBJ)/yaccer.cpp $(OBJ)/lex.yy.c $(SRCS) -ly -ll -o $(BIN)/main.out $(INC) $(FLAGS)

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