# Makefile for common library
#
# Dylan Lawler, CS50, Spring 2022

# object files, and the target library
OBJS = board.o
LIB = sudokulib.a

CFLAGS = -Wall -pedantic -std=c11 -ggdb
CC = gcc

# Build the library by archiving object files
$(LIB): $(OBJS)
	ar rc $(LIB) $(OBJS)

# Dependencies: object files depend on header files
board.o: board.h

.PHONY: clean

# clean up after  compilation
clean:
	rm -f core
	rm -f $(LIB) *~ *.o