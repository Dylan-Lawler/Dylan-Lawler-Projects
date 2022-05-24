#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "libcs50/counters.h"
#include "sudokulib/board.h"
#include "sudokulib/make.h"
#include "sudokulib/solve.h"

// Local functions
void clear_spaces(board_t *board, int spaces);

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


void clear_spaces(board_t *board, int spaces){
    // keeps track of spaces made empty
    int cleared = 0; 
    // until the desired amount of spaces are cleared
    while(cleared < spaces){
        // find a random cell
        int row = rand() % 9;
        int col = rand() % 9;
        // if its not already emptied, empty it and increment number of empty cells
        if (get_number(board, row, col) != 0){
            insert_number(board, row, col, 0);
            cleared++;
        }
    }
}
