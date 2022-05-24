#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "../libcs50/counters.h"
#include "board.h"

// recursively make the puzzle by checking if each cell can hold any number 1-9
bool solve_puzzle(board_t *board, int row, int column){
    // if the board is full, make puzzle is done

    if (full_board(board) == true){
        return true;
    }

    for (int i = 0; i < get_size(board); i ++){
        for (int j = 0; j < get_size(board); j ++){
            if (counters_get(get_row(board, i), j) == 0){
                row = i;
                column = j;
            }
        }
    }

    // for all possible number insertions
    for (int num = 1; num<=9; num++)
    {
        // if the number doesn't break sudoku rules
        if ((check(board, num, row , column) == true))
        {
            // insert it
            insert_number(board, row, column, num);
            // go to the next number and do the same
            if (solve_puzzle(board, row, column)){
                return true;
            }
            // if no numbers work, keep deleting until numbers work again
            insert_number(board, row, column, 0);
        }
    }
    // no numbers worked, backtrack
    return false;
}
