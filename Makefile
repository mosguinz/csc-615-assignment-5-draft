# Directories
DIR_SRC = ./src
DIR_LIB = ./lib
DIR_BIN = ./bin
DIR_CONFIG = $(DIR_LIB)/config
DIR_TCS34725 = $(DIR_LIB)/TCS34725

# Source and object files
SRC_C = $(wildcard $(DIR_SRC)/*.c) \
        $(wildcard $(DIR_CONFIG)/*.c) \
        $(wildcard $(DIR_TCS34725)/*.c)
OBJ_O = $(patsubst %.c,$(DIR_BIN)/%.o,$(notdir $(SRC_C)))

# Target executable
TARGET = main

# Compiler and flags
CC = gcc
DEBUG = -g -O0 -Wall
CFLAGS += $(DEBUG) -I$(DIR_CONFIG) -I$(DIR_TCS34725)

# Libraries
LIB = -lpigpio -lpthread -lm

# Build the main target by linking all object files
$(TARGET): $(OBJ_O)
	$(CC) $(CFLAGS) $(OBJ_O) -o $@ $(LIB)

# Compile object files from source files
$(DIR_BIN)/%.o: $(DIR_SRC)/%.c | $(DIR_BIN)
	$(CC) $(CFLAGS) -c $< -o $@

$(DIR_BIN)/%.o: $(DIR_CONFIG)/%.c | $(DIR_BIN)
	$(CC) $(CFLAGS) -c $< -o $@

$(DIR_BIN)/%.o: $(DIR_TCS34725)/%.c | $(DIR_BIN)
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure the bin directory exists before compiling
$(DIR_BIN):
	mkdir -p $(DIR_BIN)

# Clean up generated files
clean:
	rm -f $(DIR_BIN)/*.o
	rm -f $(TARGET)

