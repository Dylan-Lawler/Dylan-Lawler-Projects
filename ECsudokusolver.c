/* sudokusolver.c - solves a given sudoku puzzle from stdin
 *
 * Using backtracing to approach solving the sudoku puzzle
 *
 * Final Project (Sudoku), Team 10, CS 50 Spring 2022
 */

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "sudoku.h"
#include "sudokulib/board.h"

typedef struct board {
    counters_t **ptr_array;       // array of sets
    int num_rows;              // number of rows in the hashboard
} board_t;

board_t *load_sudoku(FILE *fp, int size);
void solve_puzzle(board_t *board);
void delete_puzzle(board_t *board, int size);


int main(int argc, char *argv[]){
    board_t *board = load_sudoku(stdin, 16); // make sure size is correct and matches inputted dimensions
    printf("\n\n");
    printf("Loaded board:\n");
    print_board(board);
    solve_puzzle(board);
}

// size --> either 9, 16 (the dimension size of sudoku board)
board_t *load_sudoku(FILE *fp, int size){
    // checking if invalid sudoku dimensions already
    if (size == 0){
        fprintf(stderr, "Sudoku is of invalid size. Please input a sudoku of proper dimensions (e.g. 9x9, 16x16).\n");
        return NULL;
    }
    
    board_t *board = board_new(size);
    char currValue;
    char prevValue = '\0';
    int digit;
    int row = 0;
    int column = 0;
    int totalValues = 0;

    while ((currValue = fgetc(fp)) != EOF){ // while the current value is not end of file
        if (isalpha(currValue)){ // erro checking: not valid if alphabetical character present
            fprintf(stderr, "Error: %c is not a valid value in the sudoku board. Cannot have alphabetical characters.\n", currValue);
            delete_puzzle(board, size);
            return NULL;
        }
        if (currValue != '\n') { // if not at end of the row
            if (isdigit(currValue)){
                if (isdigit(prevValue)){ // cannot be possible if 2 digit number in provided board
                    fprintf(stderr, "Error: %c%c is not a valid value in the sudoku board. Must be a single digit from 0-9.\n", prevValue, currValue);
                    delete_puzzle(board, size);
                    return NULL;
                }
                totalValues++; // incrementing value count (eventually checking if precisely 81)
                if (totalValues > (size*size)){ // error checking if more than size^2 total values
                    fprintf(stderr, "Error: Provided sudoku puzzle must have exactly 81 total values (including 0's).\n");
                    delete_puzzle(board, size);
                    return NULL;
                }
                digit = currValue - '0'; // if not double-digit, convert digit to int

                // note: row > size checker may not be needed
                if (column > size || row > size){ // error checking: if number of columns or rows exceeds the size x size dimensions, invalid sudoku
                    fprintf(stderr, "Error: Dimensions of sudoku are invalid (e.g. 9 rows, 9 columns). Cannot exceed dimensions.\n");
                    delete_puzzle(board, size);
                    return NULL;
                }
            }

            else if (isdigit(prevValue) && isspace(currValue)){ // represents a valid digit
                insert_number(board, row, column, digit); // inserting previous value into board
                column++; // tracking number of columns
            }
            prevValue = currValue; // if still in same row, reassigning prevValue to currValue before next read
        }
        else{ // if at end of row (reading '\n')
            if (column == size){ 
                row++; // incrementing row
            };
            prevValue = '\0'; // resetting prevValue to '\0'
            column = 0; // resetting column to 0
        }
    }
    
    return board;
}

// loop through sudoku to check which values are 0
// if they are 0, check row, column, and square to see what is allowed
void solve_puzzle(board_t *board){
    // board_t *board = load_sudoku(stdin);
}


// have a "check_solvable" function at very end to see if sudoku was able to be solved
// here, loop through entire sudoku board & if there are any 0's, then print error message

// deleting sudoku puzzle
void delete_puzzle(board_t *board, int size) {
    if (board != NULL) { // if there is something to free
        for (int i = 0; i < size; i++) {
            counters_delete(board->ptr_array[i]); // freeing individual counters
        }
        free(board->ptr_array); // freeing array of counters
        free(board); // freeing the board struct
    }
}