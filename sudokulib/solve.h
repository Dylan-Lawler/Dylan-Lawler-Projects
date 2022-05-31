#include <stdio.h>
#include <stdlib.h>
#include "board.h"

/**************** solve_puzzle() ****************/
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
**/
int solve_puzzle(board_t *board, int row, int column, int count);
