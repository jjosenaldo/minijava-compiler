# Paths
BIN = ./bin
OBJ = ./obj
LEXER_PATH = ./lexer
PARSER_PATH = ./parser
STACK_PATH = ./model
MAIN = ./main.c

# Commands
#FLAGS = -Wall
LEX := lex
INC := -I $(LEXER_PATH) -I $(PARSER_PATH)
GCC := gcc

# Compile program (no recompiling if files haven't changed)
all: $(BIN)/main.out

# Force program compilation
$(BIN)/main.out: obj $(MAIN)
	$(GCC) $(FLAGS) $(INC) $(OBJ)/*.o main.c -o $(BIN)/main.out

# Compile object codes
obj: $(OBJ)/lexer.o \
	$(OBJ)/rec_parser.o \
	$(OBJ)/stack.o \

# Compile Lexer
$(OBJ)/lexer.o: $(LEXER_PATH)/lexer.l
	$(LEX) -o $(OBJ)/lex.yy.c $(LEXER_PATH)/lexer.l
	$(GCC) $(FLAGS) $(INC) -c $(OBJ)/lex.yy.c -o $(OBJ)/lexer.o
	rm $(OBJ)/lex.yy.c
	
# Compile Recursive Descendent Parser
$(OBJ)/rec_parser.o: $(PARSER_PATH)/rec_parser.c $(PARSER_PATH)/rec_parser.h
	$(GCC) $(FLAGS) -c $(PARSER_PATH)/rec_parser.c -o $(OBJ)/rec_parser.o $(INC)

# Compile Stack
$(OBJ)/stack.o: $(STACK_PATH)/stack.c $(STACK_PATH)/stack.h
	$(GCC) $(FLAGS) -c $(STACK_PATH)/stack.c -o $(OBJ)/stack.o -I $(STACK_PATH)

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