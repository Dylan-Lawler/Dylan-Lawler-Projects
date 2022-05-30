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
int *number_list();

// Struct for storing puzzle positions
struct position {
    int row;
    int col;
};

// Globals
bool PRINT_WARNING = true;

bool make_puzzle(board_t *board, int row, int column) {
    /**
     * Makes full Sudoku board using recursive backtracking algorithm. Starts by trying random numbers from the set {1,...,9},
     * but backtracks if the inserted number causes the algorithm to fail later on. 
     *
     * @param board_t* board    The (initially empty) board to be filled
     * @param int row           The current row in which the maker is working
     * @param int column        The current column in which the maker is working
     * @return                  True if some number was able to be inserted in the current space, False otherwise                            
     *
    */

    // Get size of board
    int size = get_size(board);
    if (size > 16 && PRINT_WARNING) {
        printf("You have entered a Sudoku grid larger than 16x16. We will print the algorithm's progress periodically (about once every 100,000 steps), but don't expect it to finish any time soon!\n");
        PRINT_WARNING = false;
    }
    // Get shuffled list of numbers in set {1,...,size}
    int *nums = number_list(size);
    // If the board is full, we are done
    if (full_board(board, &row, &column) == true) {
        free(nums);
        return true;
    }
    if ((size > 16) && (rand() % 100000 == 1)) printf("Now working on cell (%d, %d)\n", row, column);
    // Loop over all possible number insertions
    for (int num = 0; num < size; num++) {
        // If the number doesn't break sudoku rules...
        if (check(board, nums[num], row , column) == true)
        {
            // Insert it
            insert_number(board, row, column, nums[num]);
            // Go to the next number and tru the same
            if (make_puzzle(board, row, column)){
                free(nums);
                return true;
            }
            // If no numbers work, keep deleting until numbers work again
            insert_number(board, row, column, 0);
        }

    }
    // No numbers worked, backtrack
    free(nums);
    return false;
}


int *number_list(int size) {
    /**
     * Generates a randomly shuffled array of numbers in the interval [1,size].
     * @return  An integer array of randomly shuffled numbers
    */

    // Create a list of possible numbers to insert to puzzle
    int *num_list = assertp(calloc(size, sizeof(int)), "Failed to allocate memory for number list\n");
    // Add the numbers 1 through size to the array
    for (int i = 0; i < size; i++) {
        num_list[i] = i + 1;
    }

    // Shuffle the numbers around so we can have a randomized puzzle
    for (int i = 0; i < size; i++) {
        int random = rand() % size; // Get random int in range [0,size-1]
        int temp = num_list[i]; // Grab the element at index i
        num_list[i] = num_list[random]; // Reassign index i to random element
        num_list[random] = temp; // Reassign index random to element at index i
    }

    return num_list;
}


void clear_spaces(board_t *board, int spaces) {
    /**
     * Clears (sets to 0) a given number of spaces on a premade board. Guarantees that the board ends up with a unique solution
     * by calling solve_puzzle and checking for uniqueness, and remaking
     *
     * @param board_t* board    A premade Sudoku board
     * @param int spaces        The number of spaces to clear
     *
    */

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

