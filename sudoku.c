#pragma GCC target("avx2") 
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
    srand(time(NULL));
    board_t *board = board_new(9);
    make_puzzle(board, 0, 0);
    clear_spaces(board, 5);
    print_board(board);
    printf("\n");
    
    // int num_sols;
    // num_sols = solve_puzzle(board, 0, 0, 0);
    // if (num_sols < 1) {
    //     fprintf(stderr, "Couldn't find a solution. Exiting.\n");
    //     exit(1); // exit code 1: unsolvable board
    // }
    // if (num_sols == 1) {
    //     printf("Found a unique solution: Here it is:\n");
    // }
    // else {
    //     printf("Found at least 2 distinct solutions. Here's one of them:\n");
    // }
    // print_solution(board);
    // delete_puzzle(board);

    // exit(0);
}
