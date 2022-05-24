#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "../libcs50/counters.h"
#include "board.h"

// recursively make the puzzle by checking if each cell can hold any number 1-9
bool solve_puzzle(board_t *board, int row, int column){
    // size of row/ column
    int size = get_size(board);
    // if the board is full, make puzzle is done, sets row and column to next empty cell otherwise
    if (full_board(board, &row, &column) == true){
        return true;
    }

    for (int num = 1; num <= size; num++)
    {
        // if the number doesn't break sudoku rules
        if ((check(board, num, row , column) == true))
        {
            // insert it to the empty cell
            insert_number(board, row, column, num);
            // go to the next empty cell and do the same
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
