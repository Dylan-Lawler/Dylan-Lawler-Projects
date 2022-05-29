# Makefile for 'sudoku' program and fuzz tester
#
# Dylan, Jordan, Alex, Eric
#
# CS50 Spring '22
 
# executables
ALL = sudoku fuzz
PROG = sudoku
FUZZ = fuzz

# executables depend on their object files
OBJS = sudoku.o
OBJF = fuzztest.o

# libraries
LLIBS = sudokulib/sudokulib.a libcs50/libcs50-given.a

# compilation
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I/sudokulib -I/libcs50
CC = gcc

all: $(ALL)

# make sudoku + fuzz
$(FUZZ): $(OBJF) $(LLIBS)
	$(CC) $(CFLAGS) $^ -o $@ -lm

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
	rm -f $(PROG) $(FUZZ)
	make -sC sudokulib clean
