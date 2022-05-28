#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "../libcs50/counters.h"
#include "board.h"

// recursively make the puzzle by checking if each cell can hold any number 1-9
int solve_puzzle(board_t *board, int row, int column, int count){
    // size of row/column
    int size = get_size(board);
    // If the board is full, then we're done with this solution
    // Otherwise, set row and column to next empty cell
    if (full_board(board, &row, &column)) {
        // we found a solution, so increment count   
        save_solution(board);
        return count+1;
    }

    for (int num = 1; num <= size && count < 2; num++)
    {
        // if the number doesn't break sudoku rules
        if ((check(board, num, row , column)))
        {
            // insert it to the empty cell
            insert_number(board, row, column, num);
            // go to the next empty cell and do the same
            if ((count = solve_puzzle(board, row, column, count)) > 1){
                return count;
            }
        }
    }
    // no numbers worked, backtrack
    insert_number(board, row, column, 0);

    
    return count;
}
