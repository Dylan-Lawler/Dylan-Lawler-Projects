# Makefile for 'indexer' program
#
# Dylan Lawler, CS50, Spring 2022
 
# executables
PROG = sudoku


# executables depend on their object files
OBJS = sudoku.o


# libraries
LLIBS = libcs50/libcs50-given.a sudokulib/sudokulib.a

# compilation
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I/sudokulib -I/libcs50
CC = gcc


# make sudoku
$(PROG): $(OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $^ -o $@ -lm


# make libraries
$(LLIBS):
	make -sC libcs50
	make -sC sudokulib

PHONY:  clean

# clean all makefile made files and clean libraries
clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -rf *~ *.o *.out
	rm -f $(PROG)
	make -sC sudokulib clean
