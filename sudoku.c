#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "libcs50/counters.h"
#include "sudokulib/board.h"
#include "sudokulib/make.h"
#include "sudokulib/solve.h"


int main(int argc, char *argv[]){
    srand(time(NULL));
    board_t *board = board_new(9);
    make_puzzle(board, 0, 0);
    clear_spaces(board, 40);
    print_board(board);
    printf("\n");
    solve_puzzle(board, 0, 0);
    print_board(board);
}

