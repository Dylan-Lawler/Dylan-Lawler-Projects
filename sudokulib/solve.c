#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "../libcs50/counters.h"
#include "board.h"

int solve_puzzle(board_t *board, int row, int column, int count) {
    /**
     * Solves puzzle recursively using backtracking alogorithm. Checks if there is more than one
     * solution, and saves the second solution if found (else, saves the first).
     * 
     * @param board_t* board    The Suduko board to be solved
     * @param int row           The current row in which the solver is working
     * @param int column        The current column in which the solver is working
     * @param int count         Counter to track number of solutions found (max 2)
     * @return                  The number of solutions found
     *
     */

    // Size of row (== size of column)
    int size = get_size(board);
    // If the board is full, then we're done with this solution
    // Otherwise, set row and column to next empty cell (in full_board)
    if (full_board(board, &row, &column)) {
        // We found a solution, so increment count and save the current solution
        // to the board struct
        save_solution(board);
        return count+1;
    }

    // Try each of the numbers 1-9 in the current cell
    for (int num = 1; num <= size && count < 2; num++)
    {
        // If the number doesn't break sudoku rules
        if ((check(board, num, row , column)))
        {
            // Insert it to the empty cell
            insert_number(board, row, column, num);
            // Go to the next empty cell and do the same
            if ((count = solve_puzzle(board, row, column, count)) > 1){
                return count;
            }
        }
    }
    // No numbers worked, backtrack
    insert_number(board, row, column, 0);
    return count;
}
