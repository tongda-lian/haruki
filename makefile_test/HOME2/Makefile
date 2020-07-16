SHELL = /bin/sh
CFLAG = -Wall -g
CC = gcc
TARGET = calculate
OBJ = main.o add.o minus.o multiply.o divide.o order.o
INC =  my_math.h order.h
#VPATH = src:include
vpath %.c src
vpath %.h include

$(TARGET):$(OBJ)
	@echo "Linking ..."
	@${CC}  -o $@ ${OBJ} -lm
	@echo "Finished compiling."
	
${OBJ} : %.o : %.c
	@echo "Compiling $< ..."
	@${CC} -c ${CFLAG} -Iinclude  $< -o $@
 
.PHONY: clean

clean:
	@rm -f $(TARGET) 
	@echo "Target and .o files are cleaned."
