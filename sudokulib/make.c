#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include "../libcs50/counters.h"
#include "../libcs50/memory.h"
#include "solve.h"
#include "../sudokulib/board.h"

/**************** number_list() ****************/
/* see make.h for description */
int *number_list(int size){
    // create a list of possible numbers to insert to puzzle
    int *num_list = calloc(size, sizeof(int));
    for (int i = 0; i < size; i++){
        num_list[i] = i + 1;
    }
    // shuffle the numbers around so we can have a randomized puzzle
    for (int i = 0; i < size; i++){
        int random = rand() % size;
        int temp = num_list[i];
        num_list[i] = num_list[random];
        num_list[random] = temp;
    }
    return num_list;
}

/**************** make_puzzle() ****************/
/* see make.h for description */
bool make_puzzle(board_t *board, int row, int column){
    int size = get_size(board);

    // shuffled list of numbers
    int *nums = number_list(size);
    // if the board is full, make puzzle is done
    if (full_board(board, &row, &column) == true){
        free(nums);
        return true;
    }
    // for all possible number insertions
    for (int num = 0; num< size; num++)
    {
        // if the number doesn't break sudoku rules
        if (check(board, nums[num], row , column) == true)
        {
            // insert it
            insert_number(board, row, column, nums[num]);
            // go to the next number and do the same
            if (make_puzzle(board, row, column)){
                free(nums);
                return true;
            }
            // if no numbers work, keep deleting until numbers work again
            insert_number(board, row, column, 0);
        }
    }
    // no numbers worked, backtrack
    free(nums);
    return false;
}

void clear_spaces(board_t *board, int spaces){
    int size = get_size(board);
    // list of all possible cell spaces
    int *cells = number_list((size * size) - 1);
    // keeps track of spaces cleared 
    int cleared = 0; 
    for (int i = 0; i < (size * size); i++){
        // get row and column
        int slot = cells[i];
        int row = slot/size;
        int column = slot % size;
        // get the current number
        int number = get_number(board, row, column);
        // empty the cell
        insert_number(board, row, column, 0);
        cleared++;
        // copy the board so the original isnt changed
        board_t *copy = assertp(copy_board(board), "board copy"); 
        // if the board isnt unique anymore, put the number back 
        if ((solve_puzzle(copy, 0, 0,0)) > 1 ){
            insert_number(board, row, column, number);
            cleared --;
        }
        // delete the copy
        delete_puzzle(copy);
        // stop when the board is empty enough
        if (cleared == spaces){
           break;
        }
    }

    // if the board couldn't be emptied enough and be unique, try with a new board
    if (cleared < spaces){
            empty_board(board);
            make_puzzle(board, 0, 0);
            clear_spaces(board, spaces);
        }
    
    // free the list of cells
    free(cells);
}
