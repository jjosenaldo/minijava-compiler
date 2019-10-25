# Paths
SRC = ./src
BIN = ./bin
OBJ = ./obj
GRAMMAR_PATH = ./grammar
AST_PATH = ./src/ast
PARSER_PATH = ./src/parser
SYMTABLE_PATH = ./src/symtable
UTILS_PATH = ./src/utils

# Commands
FLAGS = -Wno-write-strings -g -std=c++11
LEX := flex
YACC := bison
INC := -I $(GRAMMAR_PATH) -I $(PARSER_PATH) -I $(SYMTABLE_PATH) -I $(SYMTABLE_PATH) -I $(SYMTABLE_PATH) -I $(AST_PATH) -I $(UTILS_PATH)
SRCS = $(SYMTABLE_PATH)/symtable.cpp $(AST_PATH)/type.cpp $(AST_PATH)/ast.cpp $(AST_PATH)/statement.cpp $(AST_PATH)/expression.cpp $(UTILS_PATH)/error.cpp $(AST_PATH)/operator.cpp $(UTILS_PATH)/global.cpp

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