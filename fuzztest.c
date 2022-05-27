#include <stdio.h>
#include <stdlib.h>
#include "sudokulib/board.h"
#include "sudokulib/make.h"
#include "sudokulib/solve.h"

/*
 * usage: ./fuzz numofpuzzles
 *
 */

int main(int argc, char *argv[]) {
	
	int numofpuzzles = atoi(argv[1]);

		
	for (int i=0; i<numofpuzzles; i++){
		board_t *board = board_new(9);
		bool make = make_puzzle(board,0,0);	
		if (!make){
			fprintf(stderr, "ERROR");
			exit(1);
		}
		clear_spaces(board, 40);
    		printf("--------------------------------\n");
		printf("UNSOLVED\n");
		print_board(board);
		printf("\n");
		printf("SOLVED\n");
		
		int t = solve_puzzle(board,0,0);
		if (t != 1) {
			printf("Could not solve\n");
			exit(1);
		}
		print_board(board);	
		
	}		
	return 0;
	






}

