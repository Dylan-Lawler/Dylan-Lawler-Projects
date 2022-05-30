/*
 * sudoku.c - program to make a sudoku board and solve it using sudoku modules
 *
 * usage: ./sudoku
 *
 * Dylan, Jordan, Alex, Eric
 * CS50 Spring '22
 * 
 */


#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include <sys/time.h>
#include "libcs50/counters.h"
#include "sudokulib/board.h"
#include "sudokulib/make.h"
#include "sudokulib/solve.h"

int main(int argc, char *argv[]){
    
    // Initialize board
    srand(time(NULL));
    board_t *board = board_new(16);
    
    // Make puzzle and print
    make_puzzle(board, 0, 0);
    printf("Made puzzle\n");
    clear_spaces(board, 128);
    print_board(board);
    printf("\n");
    
    // Determine how many solutions were found
    int num_sols;
    num_sols = solve_puzzle(board, 0, 0, 0);
    // Exit if no solutions found
    if (num_sols < 1) {
        fprintf(stderr, "Couldn't find a solution. Exiting.\n");
        delete_puzzle(board);
	exit(1); // exit code 1: unsolvable board
    }
    if (num_sols == 1) {
        printf("Found a unique solution: Here it is:\n");
    }
    else {
        printf("Found at least 2 distinct solutions. Here's one of them:\n");
    }

    // Print final board and clean up
    print_solution(board);
    delete_puzzle(board);

    exit(0);
}
