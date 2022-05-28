#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include "solve.h"
#include "../libcs50/counters.h"
#include "make.h"

typedef struct board {
    counters_t **ptr_array;       // array of sets
    int num_rows;              // number of rows in the hashboard
    counters_t **solution;
} board_t;

board_t *board_new(const int num_rows){
    board_t *board = malloc(sizeof(board_t)); 
    if (board == NULL){
    return NULL;             
    } 
    else{
      board->num_rows = num_rows; 
      board->ptr_array = calloc(board->num_rows, sizeof(counters_t*));
      board->solution = calloc(board->num_rows, sizeof(counters_t*));
      for (int i = 0; i < board->num_rows; i++){
          board->ptr_array[i] = counters_new();
          board->solution[i] = counters_new();
          for (int j = 0; j < board->num_rows; j++){
            counters_set(board->ptr_array[i], j, 0 );
            counters_set(board->solution[i], j, 0 );
        }
      }
      return board;
    }
}

void delete_puzzle(board_t *board) {
    if (board != NULL) { // if there is something to free
        for (int i = 0; i < 9; i++) {
            counters_delete(board->ptr_array[i]); // freeing individual counters
            counters_delete(board->solution[i]);
        }
        free(board->ptr_array); // freeing array of counters
        free(board->solution); // freeing array of counters

    }
}

int get_number(board_t *board, int row, int column){
    return counters_get(board->ptr_array[row], column);
}

counters_t* get_row(board_t *board, int row){
    return board->ptr_array[row];
}

int get_size(board_t *board){
    return board->num_rows;
}

int get_box_size(board_t *board){
    return (int)sqrt(board->num_rows);
}

void insert_number(board_t *board, int row, int column, int number){
    counters_set(board->ptr_array[row], column, number);
}

bool full_board(board_t *board, int *row, int *column){
    for (int i = 0; i < board->num_rows; i ++){
        for (int j = 0; j < board->num_rows; j ++){
            if (counters_get(board->ptr_array[i], j) == 0){
                *row = i;
                *column = j;
                return false;
            }
        }
    }
    return true;
}

void print_help(void *arg, const int key, const int count){
    board_t *board = arg;
    if (key == 0){
        printf("| %d ", count);
    }
    else if ((key + 1) % get_box_size(board) == 0 ){
        printf("%d | ", count);
    }
    else{
        printf("%d ", count);
    }
}

void print_board(board_t *board){
    for (int i = 0; i < board->num_rows; i ++){
        if (i == 0){
            printf("-------------------------\n");
            counters_iterate(get_row(board, i), board, print_help);
            printf("\n");
        }
        else if (((i + 1 )% get_box_size(board) == 0)){
            counters_iterate(get_row(board, i), board, print_help);
            printf("\n-------------------------\n");
            continue;
        }
        else{
            counters_iterate(get_row(board, i), board, print_help);
            printf("\n");
        }
    }
}

// Check for sudoku rule violations
bool check(board_t *board, int num, int row, int column){
    // if the number matches any number in the same row or column, return false
    for (int i = 0; i < get_size(board); i++){
        if ((counters_get(get_row(board, row), i) == num) || (counters_get(get_row(board, i), column) == num)){
            return false;
        }
    }
    // start at the top left corner of the square
    int boxrow = row - (row % 3);
    int boxcol = column - (column % 3);

    // if the number matches any number in the square, return false 
    for (int i = boxrow; i < boxrow + 3; i ++){
        for (int j = boxcol; j < boxcol + 3; j ++){
            if (counters_get(get_row(board, i), j) == num){
                return false;
            }
        }
    }
    // the number is valid
    return true;
}


int load_size(FILE *fp){
    char c;
    int boardsize = 0;
    int line = 0; 

    while ((c = fgetc(fp)) != EOF){
        if (c == '\n'){
                line++;
        }
        if (line == 1){
            if (isdigit(c)){
                boardsize++;
            }
        }

    }

    double root = sqrt(boardsize);
    if ((root * root) != boardsize){
        return 0;
    }
    return boardsize;
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
    
    return board;
}

void save_solution(board_t *board){

    int size = get_size(board);
    for (int i = 0; i < size; i ++){
        for (int j = 0; j < size; j ++){
            int number = get_number(board, i, j);
            counters_set(board->solution[i], j, number);
        }
    }
}

void print_solution(board_t *board){
    for (int i = 0; i < board->num_rows; i ++){
        if (i == 0){
            printf("-------------------------\n");
            counters_iterate(board->solution[i], board, print_help);
            printf("\n");
        }
        else if (((i + 1 )% get_box_size(board) == 0)){
            counters_iterate(board->solution[i], board, print_help);
            printf("\n-------------------------\n");
            continue;
        }
        else{
            counters_iterate(board->solution[i], board, print_help);
            printf("\n");
        }
    }
}

void empty_board(board_t *board){
    for (int i = 0; i < board->num_rows; i ++){
        for (int j = 0; j < board->num_rows; j ++){
            insert_number(board, i, j, 0);
        }
    }
}