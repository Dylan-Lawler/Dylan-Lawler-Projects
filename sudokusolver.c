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

board_t *load_sudoku(FILE *fp);
void solve_puzzle(board_t *board);
void delete_puzzle(board_t *board);


int main(int argc, char *argv[]){
    board_t *board = load_sudoku(stdin);
    print_board(board);
    solve_puzzle(board);
}

board_t *load_sudoku(FILE *fp){
    board_t *board = board_new(9);
    char currValue;
    char prevValue = '\0';
    int digit;
    int row = 0;
    int column = 0;
    int missingValues = 0;
    int totalValues = 0;

    while ((currValue = fgetc(fp)) != EOF){ // while the current value is not end of file
        if (isalpha(currValue)){ // erro checking: not valid if alphabetical character present
            fprintf(stderr, "Error: %c is not a valid value in the sudoku board. Cannot have alphabetical characters.\n", currValue);
            delete_puzzle(board);
            exit(1);
        }
        if (currValue != '\n') { // if not at end of the row
            if (isdigit(currValue)){
                if (isdigit(prevValue)){ // cannot be possible if 2 digit number in provided board
                    fprintf(stderr, "Error: %c%c is not a valid value in the sudoku board. Must be a single digit from 0-9.\n", prevValue, currValue);
                    delete_puzzle(board);
                    exit(2);
                }
                totalValues++; // incrementing value count (eventually checking if precisely 81)
                if (totalValues > 81){ // error checking if more than 81 total values
                    fprintf(stderr, "Error: Provided sudoku puzzle must have exactly 81 total values (including 0's).\n");
                    delete_puzzle(board);
                    exit(3);
                }
                digit = currValue - '0'; // if not double-digit, convert digit to int
                if (digit == 0){
                    missingValues++; // incrementing missing values (provided as 0), checking eventually if >= 40 to be valid
                }

                // note: row > 9 checker may not be needed
                if (column > 9 || row > 9){ // error checking: if number of columns or rows exceeds the 9x9 dimensions, invalid sudoku
                    fprintf(stderr, "Error: Dimensions of sudoku must be exactly 9x9 (9 rows, 9 columns). Cannot exceed dimensions.\n");
                    delete_puzzle(board);
                    exit(4);
                }
            }

            else if (isdigit(prevValue) && isspace(currValue)){ // represents a valid digit
                insert_number(board, row, column, digit); // inserting previous value into board
                column++; // tracking number of columns
            }
            prevValue = currValue; // if still in same row, reassigning prevValue to currValue before next read
        }
        else{ // if at end of row (reading '\n')
            if (column == 9){ 
                row++; // incrementing row
            };
            prevValue = '\0'; // resetting prevValue to '\0'
            column = 0; // resetting column to 0
        }
    }
    
    // error checking if sudoku has less than 40 missing values (0's)
    if (missingValues < 40){
        fprintf(stderr, "Error: Provided sudoku puzzle must have at least 40 missing values (orovided %d missing values).\n", missingValues);
        delete_puzzle(board);
        exit(5);
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
void delete_puzzle(board_t *board) {
    if (board != NULL) { // if there is something to free
        for (int i = 0; i < 9; i++) {
            counters_delete(board->ptr_array[i]); // freeing individual counters
        }
        free(board->ptr_array); // freeing array of counters
        free(board); // freeing the board struct
    }
}