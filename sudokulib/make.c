#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include "../libcs50/counters.h"
#include "board.h"

// Local prototypes
int *number_list();


// recursively make the puzzle by checking if each cell can hold any number 1-9
bool make_puzzle(board_t *board, int row, int column){
    int size = get_size(board);
    // shuffled list of numbers
    int *nums = number_list(size);
    // if the board is full, make puzzle is done
    if (full_board(board, &row, &column) == true){
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
                return true;
            }
            // if no numbers work, keep deleting until numbers work again
            insert_number(board, row, column, 0);
        }
    }
    // no numbers worked, backtrack
    return false;
}

// Create a random list of numbers
int *number_list(){
    // create a list of possible numbers to insert to puzzle
    int *num_list = calloc(9, sizeof(int));
    for (int i = 0; i < 9; i++){
        num_list[i] = i + 1;
    }

    // shuffle the numbers around so we can have a randomized puzzle
    for (int i = 0; i < 9; i++){
        int random = rand() % 9;
        int temp = num_list[i];
        num_list[i] = num_list[random];
        num_list[random] = temp;
    }

    return num_list;
}

