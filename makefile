# Paths
SRC = ./src
BIN = ./bin
OBJ = ./obj
GRAMMAR_PATH = ./grammar
AST_PATH = ./src/ast
PARSER_PATH = ./src/parser
SYMTABLE_PATH = ./src/symtable
UTILS_PATH = ./src/utils
CG_PATH = ./src/code-generator

# Commands
FLAGS = -Wno-write-strings -g -std=c++11
LEX := flex
YACC := bison

INC := -I $(PARSER_PATH) -I $(SYMTABLE_PATH) -I $(SYMTABLE_PATH) -I $(SYMTABLE_PATH) -I $(AST_PATH) -I $(UTILS_PATH) -I $(CG_PATH)

OBJS = $(OBJ)/activation-record.o $(OBJ)/ast.o $(OBJ)/code-generator.o $(OBJ)/code-visitor.o $(OBJ)/error.o $(OBJ)/expression.o $(OBJ)/global.o $(OBJ)/operator.o $(OBJ)/statement.o $(OBJ)/symtable.o $(OBJ)/type.o $(OBJ)/value.o $(OBJ)/static-visitor.o  

all: $(BIN)/main.out 

$(BIN)/main.out: lexer yaccer $(OBJS) $(SRC)/main.cpp 
	g++ -x c++ $(SRC)/main.cpp $(PARSER_PATH)/yaccer.cpp $(OBJ)/lex.yy.c $(OBJS) -ly -ll -o $(BIN)/main.out $(INC) $(FLAGS) 

lexer: $(PARSER_PATH)/lexer.l 
	$(LEX) -o $(OBJ)/lex.yy.c $(PARSER_PATH)/lexer.l

yaccer: $(PARSER_PATH)/yaccer.y 
	$(YACC) --defines=$(PARSER_PATH)/yaccer.hpp $(PARSER_PATH)/yaccer.y -o $(PARSER_PATH)/yaccer.cpp

$(OBJ)/activation-record.o: $(CG_PATH)/activation-record.cpp $(CG_PATH)/activation-record.hpp
	g++ -c -o $(OBJ)/activation-record.o $(CG_PATH)/activation-record.cpp $(INC) $(FLAGS) 

$(OBJ)/ast.o: $(AST_PATH)/ast.cpp $(AST_PATH)/ast.hpp
	g++ -c -o $(OBJ)/ast.o $(AST_PATH)/ast.cpp $(INC) $(FLAGS) 

$(OBJ)/code-generator.o: $(CG_PATH)/code-generator.cpp $(CG_PATH)/code-generator.hpp
	g++ -c -o $(OBJ)/code-generator.o $(CG_PATH)/code-generator.cpp $(INC) $(FLAGS) 

$(OBJ)/code-visitor.o: $(CG_PATH)/code-visitor.cpp $(CG_PATH)/code-visitor.hpp
	g++ -c -o $(OBJ)/code-visitor.o $(CG_PATH)/code-visitor.cpp $(INC) $(FLAGS) 

$(OBJ)/error.o: $(UTILS_PATH)/error.cpp $(UTILS_PATH)/error.hpp
	g++ -c -o $(OBJ)/error.o $(UTILS_PATH)/error.cpp $(INC) $(FLAGS) 

$(OBJ)/expression.o: $(AST_PATH)/expression.cpp $(AST_PATH)/expression.hpp
	g++ -c -o $(OBJ)/expression.o $(AST_PATH)/expression.cpp $(INC) $(FLAGS) 

$(OBJ)/global.o: $(UTILS_PATH)/global.cpp $(UTILS_PATH)/global.hpp
	g++ -c -o $(OBJ)/global.o $(UTILS_PATH)/global.cpp $(INC) $(FLAGS) 

$(OBJ)/operator.o: $(AST_PATH)/operator.cpp $(AST_PATH)/operator.hpp
	g++ -c -o $(OBJ)/operator.o $(AST_PATH)/operator.cpp $(INC) $(FLAGS) 

$(OBJ)/statement.o: $(AST_PATH)/statement.cpp $(AST_PATH)/statement.hpp
	g++ -c -o $(OBJ)/statement.o $(AST_PATH)/statement.cpp $(INC) $(FLAGS) 

$(OBJ)/static-visitor.o: $(CG_PATH)/static-visitor.cpp $(CG_PATH)/static-visitor.hpp
	g++ -c -o $(OBJ)/static-visitor.o $(CG_PATH)/static-visitor.cpp $(INC) $(FLAGS) 

$(OBJ)/symtable.o: $(SYMTABLE_PATH)/symtable.cpp $(SYMTABLE_PATH)/symtable.hpp
	g++ -c -o $(OBJ)/symtable.o $(SYMTABLE_PATH)/symtable.cpp $(INC) $(FLAGS) 

$(OBJ)/type.o: $(AST_PATH)/type.cpp $(AST_PATH)/type.hpp
	g++ -c -o $(OBJ)/type.o $(AST_PATH)/type.cpp $(INC) $(FLAGS) 

$(OBJ)/value.o: $(CG_PATH)/value.cpp $(CG_PATH)/value.hpp
	g++ -c -o $(OBJ)/value.o $(CG_PATH)/value.cpp $(INC) $(FLAGS) 


# Clean project
clean:
	@# @ symbol at beginning indicates that it will not be printed
	@if [ "$$(ls -A $(OBJ))" ]; then \
		rm $(OBJ)/*; \
	fi
	@if [ "$$(ls -A $(BIN))" ]; then \
		rm $(BIN)/*; \
	fi
	@rm $(PARSER_PATH)/*.cpp $(PARSER_PATH)/*.hpp 

# Run all code examples
test: $(BIN)/main.out
	@for filename in ./code-examples/*; do \
		echo "------ TEST --------------------------\nFile: $$filename\n"; \
		./bin/main.out < "$$filename"; \
		echo "--------------------------------------\n\n"; \
	done