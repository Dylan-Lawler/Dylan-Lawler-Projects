# Makefile for 'indexer' program
#
# Team 10 (), CS50, Spring 2022
 
# executables
PROG = sudoku
#PROG2 = sudokusolver
PROG3 = ECsudokusolver


# executables depend on their object files
OBJS = sudoku.o
#OBJS2 = sudokusolver.o
OBJS3 = ECsudokusolver.o


# libraries
LLIBS = libcs50/libcs50-given.a sudokulib/sudokulib.a

# compilation
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I/sudokulib -I/libcs50 
CC = gcc
MAKE = make

all: sudoku ECsudokusolver #sudokusolver ECsudokusolver

# make sudoku
sudoku: $(OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $^ -o $@ -lm

# # solve sudoku
# sudokusolver: $(OBJS2) $(LLIBS)
# 	$(CC) $(CFLAGS) $^ -o $@ -lm

# solve sudoku EC
ECsudokusolver: $(OBJS3) $(LLIBS)
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
#	rm -f $(PROG2)
	rm -f $(PROG3)
	make -sC sudokulib clean
