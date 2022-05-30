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

// Local prototypes
int *number_list(int size);
void clear_spaces(board_t *board, int spaces);

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
    // no numbers worked, backtrack
    free(nums);
    return false;
}

// Create a random list of numbers
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

void clear_spaces(board_t *board, int spaces){
    int size = get_size(board);

    // keeps track of spaces made 
    int *cells = number_list((size * size) - 1);
    int cleared = 0; 

    for (int i = 0; i < (size * size); i++){
        int slot = cells[i];
        int row = slot/size;
        int column = slot % size;
        int number = get_number(board, row, column);
        insert_number(board, row, column, 0);
        cleared++;
        board_t *copy = copy_board(board); 
        if ((solve_puzzle(copy, 0, 0,0)) > 1 ){
            insert_number(board, row, column, number);
            cleared --;
        }
        delete_puzzle(copy);
        if (cleared == spaces){
           break;
        }
    }

    if (cleared < spaces){
            empty_board(board);
            make_puzzle(board, 0, 0);
            clear_spaces(board, spaces);
        }
    
    free(cells);
}
