#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include "../libcs50/counters.h"
#include "solve.h"

// Local prototypes
int *number_list();


// recursively make the puzzle by checking if each cell can hold any number 1-9
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
    
    free(nums);
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
            if (solve_puzzle(board, 0, 0, 0) > 1){
                empty_board(board);
                make_puzzle(board, 0, 0);
                cleared = 0;
                continue;
            }
            cleared++;
        }
    }
}
