#include <stdio.h>
#include <stdlib.h>
#include "sudokulib/board.h"
#include "sudokulib/make.h"
#include "sudokulib/solve.h"

/*
 * fuzztest.c - Fuzz tester for sudoku make and solve modulues
 *
 * usage: ./fuzz numofpuzzles
 * 
 * Jordan, Dylan, Alex, Eric
 * CS50 Spring '22
 *
 */

// Local functions
void print_error(board_t *unsolved_board);

int main(int argc, char *argv[]) {
	
	// Convert input number of puzzles to int
	int numofpuzzles = atoi(argv[1]);

	// Create numofpuzzles boards, solve numofpuzzle boards. Exit on error
	for (int i=0; i<numofpuzzles; i++){
		
		// Make board
		board_t *board = board_new(9);
		bool make = make_puzzle(board,0,0);	
		
		// Check for valid creation of board
		if (!make){
			fprintf(stderr, "Could not make board\n");
			exit(1);
		}

		// Format board and print
		clear_spaces(board, 40);
    		printf("--------------------------------\n");
		printf("UNSOLVED\n");
		print_board(board);
	
		// Check if board can be solved
		board_t *unsolved_board = board;
		int t = solve_puzzle(board,0,0, 0);
		if (t != 1) {
			print_error(unsolved_board);
			exit(1);
		}
		
		// Print solved board, repeat
		printf("\n");
                printf("SOLVED\n");
		print_solution(board);
		delete_puzzle(board);	
	}		
	return 0;
}


// Print solve error and board that could not be solved, exit
void print_error(board_t *unsolved_board) {
	printf("\n\n\n\n");
	printf("************************)");
	printf("COULD NOT SOLVE:\n");
	print_board(unsolved_board);
	printf("************************)");
}
