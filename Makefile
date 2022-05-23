# Makefile for 'indexer' program
#
# Team 10 (), CS50, Spring 2022
 
# executables
PROG = sudoku


# executables depend on their object files
OBJS = sudoku.o


# libraries
LLIBS = libcs50/libcs50-given.a

# compilation
CFLAGS = -Wall -pedantic -std=c11 -ggdb  -I/libcs50
CC = gcc


# make indexer
$(PROG): $(OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $^ -o $@ 

# make libraries
$(LLIBS):
	@make -sC /libcs50

PHONY: test clean

# test a few indexer cases and indextest into testing.out
test: 
	bash testing.sh &> testing.out

# clean all makefile made files and clean libraries
clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -rf *~ *.o *.out
	rm -f $(PROG)
