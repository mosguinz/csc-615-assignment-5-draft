# Directories
DIR_OBJ = ./TCS34725
DIR_BIN = ./bin

# Source and object files
OBJ_C = $(wildcard ${DIR_OBJ}/*.c)
OBJ_O = $(patsubst %.c,${DIR_BIN}/%.o,$(notdir ${OBJ_C}))

# Target executable
TARGET = main

# Compiler and flags
CC = gcc
DEBUG = -g -O0 -Wall
CFLAGS += $(DEBUG) 

# Libraries
LIB = -lpigpio -lpthread -lm

# Compile the main target by linking all object files
${TARGET}: ${OBJ_O}
	$(CC) $(CFLAGS) $(OBJ_O) -o $@ $(LIB)

# Compile object files from source files in DIR_OBJ
${DIR_BIN}/%.o: ${DIR_OBJ}/%.c | ${DIR_BIN}
	$(CC) $(CFLAGS) -c $< -o $@ $(LIB)

# Ensure the bin directory exists before compiling
${DIR_BIN}:
	mkdir -p ${DIR_BIN}

# Clean up generated files
clean:
	rm -f $(DIR_BIN)/*.o
	rm -f $(TARGET)

