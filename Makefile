#DIR_FONTS = ./Fonts
DIR_OBJ = ./TCS34725
DIR_BIN = ./bin

OBJ_C = $(wildcard ${DIR_OBJ}/*.c)
OBJ_O = $(patsubst %.c,${DIR_BIN}/%.o,$(notdir ${OBJ_C}))

TARGET = main
#BIN_TARGET = ${DIR_BIN}/${TARGET}

CC = gcc

DEBUG = -g -O0 -Wall
CFLAGS += $(DEBUG) 

LIB = -lwiringPi -lpthread -lm

${TARGET}:${OBJ_O}
	$(CC) $(CFLAGS) $(OBJ_O) -o $@  $(LIB)

${DIR_BIN}/%.o : $(DIR_OBJ)/%.c
	$(CC) $(CFLAGS) -c  $< -o $@  $(LIB)


	
clean :
	rm $(DIR_BIN)/*.* 
	rm $(TARGET) 