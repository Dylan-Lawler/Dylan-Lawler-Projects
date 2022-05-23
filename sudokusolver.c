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

void load_sudoku(FILE *fp);
void solve_puzzle(board_t *board);
void delete_puzzle(board_t *board);

int main(int argc, char *argv[]){
    board_t *board = load_sudoku(stdin);
    solve_puzzle(board);
}


board_t *board load_sudoku(FILE *fp){
    board_t *board = board_new(9);
    char currValue;
    char prevValue = '\0';
    int digit;
    int row = 0;
    int column = 0;
    int missingValues = 0;
    int totalValues = 0;

    // while the current value is not end of file
    while ((currValue = fgetc(fp)) != EOF){
        // if (column == 0){
        //     row++;
        // }
        if (isalpha(currValue)){ // not valid if alphabetical character present
            fprintf(stderr, "Error: %c is not a valid value in the sudoku board. Cannot have alphabetical characters.\n", currValue);
            delete_puzzle(board);
            exit(1);
        }
        if (currValue != "\n") { // if not at end of the row
            if (isdigit(currValue)){
                if (isdigit(prevValue){ // cannot be possible if 2 digit number in provided board
                    fprintf(stderr, "Error: %c%c is not a valid value in the sudoku board. Must be a single digit from 0-9.\n", prevValue, currValue);
                    delete_puzzle(board);
                    exit(2);
                }
                digit = currValue - '0'; // if not double-digit, convert digit to int
                totalValues++; // incrementing total values, checking eventually if = 81 to be valid
                
                if (digit == 0){
                    missingValues++; // incrementing missing values (provided as 0), checking eventually if >= 40 to be valid
                }

                // check if >8 or >9 is correct
                if (column > 8 || row > 8){ // if number of columns or rows exceeds the 9x9 dimensions, invalid sudoku
                    fprintf(stderr, "Error: Dimensions of sudoku must be exactly 9x9 (9 rows, 9 columns). Cannot exceed dimensions.\n");
                    delete_puzzle(board);
                    exit(3);
                }
            }

            // double check this is the format for sudoku --> like I'm assuming each digit has to have a space but 
            // is this actually a requirement? may have to add additional insert part if not required to have a space after digit
            else if (isdigit(prevValue) && isspace(currValue)){ // represents a valid digit
                insert_number(board, row, column, prevValue); // inserting previous value into board
                column++; // tracking number of columns
                valueCount++; // incrementing value count (eventually checking if precisely 40 )
                }
            }
            prevValue = currValue; // if still in same row, reassigning prevValue to currValue before next read
        }
        else{ // if at end of row (reading '\n')
            // note: have to check if row++ fits here as not sure if I increment it too much here
            
            // see if ==9 or == 8
            if (column == 9){ // also gotta check --> what specifically is the provided input sudoku? 
            // like I don't want to increment row if it's just a line of "----------" for instance
                row++; // incrementing row
            }
            prevValue = '\0'; // resetting prevValue to '\0'
            column = 0; // resetting column to 0
        }
    }

    // is this necessary? do have a row check above when checking for columns too at digit int conversion
    // also check if !=9 or != 8 is correct
    if (row != 9){ // error checking if sudoku has more than 9 rows
        fprintf(stderr, "Error: Dimensions of sudoku must be exactly 9x9 (9 rows, 9 columns).\n");
        delete_puzzle(board);
        exit(4);
    }
    if (missingValues < 40){
        fprintf(stderr, "Error: Provided sudoku puzzle must have at least 40 missing values.\n");
        delete_puzzle(board);
        exit(5);
    }
    if (totalValues != 81){
        fprintf(stderr, "Error: Provided sudoku puzzle must have exactly 81 total values (including 0's).\n");
        delete_puzzle(board);
        exit(6);
    }
    return board;
}

// loop through sudoku to check which values are 0
// if they are 0, check row, column, and square to see what is allowed
void solve_puzzle(board_t *board){
    board_t *board = load_sudoku(stdin);
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