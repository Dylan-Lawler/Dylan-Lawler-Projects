#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include "../libcs50/counters.h"

/**************** make_puzzle() ****************/
/* Purpose: Create an unsolved suoku board that has a unique solution
 * Input:  board struct and row and column to start at
 * Output:  a unique puzzle board
*/
bool make_puzzle(board_t *board, int row, int column);

/**************** number_list() ****************/
/* Purpose: Create a list of all possible board cell positions
 * Input:  dimension of the board
 * Output: a list of numbers in randomized order of the dimension squared
*/
int *number_list(int size);

/**************** clear_spaces() ****************/
/* Purpose: clear a full sudoku board to be solved
 * Input:  board struct and number of spaces to be emptied
 * Output: the board with emptied cells that has a unique solution
*/
void clear_spaces(board_t *board, int spaces);