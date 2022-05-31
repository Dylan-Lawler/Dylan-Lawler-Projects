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

   // Create array of all board positions and shuffle it
   int size = get_size(board);
   struct position positions[size*size]; // Initialize array of size 81
   int idx = 0;
   struct position pos; // Track current position
   for (int row = 0; row < size; row++) {
       for (int col = 0; col < size; col++) {
           pos.row = row;
           pos.col = col;
           positions[idx] = pos;
           idx++;
       }
   }

   // Randomly shuffle positions
   for (int i = 0; i < size*size; i++) {
       int random = rand() % (size*size);
       struct position temp = positions[i];
       positions[i] = positions[random];
       positions[random] = temp;
   }

   int currIdx = 0; // Current index in positions array
   board_t* board_copy;
   // Keeps track of spaces already made empty
   int cleared = 0;
   // Loop until the desired amount of spaces are cleared
   while (cleared < spaces) {
       // Pick a random cell
       if (currIdx == size*size) {
           empty_board(board);
           make_puzzle(board, 0, 0);
           currIdx = 0;
           cleared = 0;
       }
       int row = positions[currIdx].row;
       int col = positions[currIdx].col;
       // If it's not already emptied, set it to 0 and increment number of empty cells
       int currNum = get_number(board, row, col);
       if (currNum != 0) {
           // Set current cell to 0
           insert_number(board, row, col, 0);
          
           // If our puzzle is 16x16 or larger, don't bother with uniqueness
           if (size >= 16) {
               cleared++;
               currIdx++;
           }

           // If our puzzle is 4x4 or 9x9, create a puzzle with a unique solution
           else {
               // Create board copy to use for validation
               board_copy = copy_board(board);
               // Check if this move leads to a non-unique solution
               if (solve_puzzle(board_copy, 0, 0, 0) > 1) {
                   // If so, put number back in and continue with loop
                   insert_number(board, row, col, currNum);
                   currIdx++; // Move to next board position
                   delete_puzzle(board_copy);
                   continue;
               }
               // If puzzle was unique, increment counter and move to next position
               else {
                   cleared++;
                   currIdx++;
                   delete_puzzle(board_copy);
               }
           }
       }
   }
}


