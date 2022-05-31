#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include "solve.h"
#include "../libcs50/counters.h"
#include "../libcs50/file.h"
#include "../libcs50/memory.h"
#include "make.h"

typedef struct board {
    counters_t **ptr_array;     // array of counters
    int num_rows;              // number of rows in the sudoku board
    counters_t **solution;      // solved board
} board_t;

/**************** board_new() ****************/
/* see board.h for description */
board_t *board_new(const int num_rows){
    board_t *board = assertp(malloc(sizeof(board_t)), "Failed to allocate memory for new board\n"); 
    // dimension of the board
    board->num_rows = num_rows; 
    // allocate memory for the counter arrays
    board->ptr_array = assertp(calloc(board->num_rows, sizeof(counters_t*)), "Failed to allocate memory for ptr_array\n");
    board->solution = assertp(calloc(board->num_rows, sizeof(counters_t*)), "Failed to allocate memory for solution board\n");
    // fill every cell in the original and solution boards with 0
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

/**************** delete_puzzle() ****************/
/* see board.h for description */
void delete_puzzle(board_t *board) {
    int size = get_size(board);
    if (board != NULL) { // if there is something to free
        for (int i = 0; i < size; i++) {
            counters_delete(board->ptr_array[i]); // freeing individual counters
            counters_delete(board->solution[i]);
        }
        free(board->ptr_array); // freeing array of counters
        free(board->solution); // freeing array of counters
    }
    free(board);
}

/**************** get_number() ****************/
/* see board.h for description */
int get_number(board_t *board, int row, int column){
    return counters_get(board->ptr_array[row], column);
}

/**************** get_row() ****************/
/* see board.h for description */
counters_t* get_row(board_t *board, int row){
    return board->ptr_array[row];
}

/**************** get_size() ****************/
/* see board.h for description */
int get_size(board_t *board){
    return board->num_rows;
}

/**************** get_box_size() ****************/
/* see board.h for description */
int get_box_size(board_t *board){
    return (int)sqrt(board->num_rows);
}

/**************** insert_number() ****************/
/* see board.h for description */
void insert_number(board_t *board, int row, int column, int number){
    counters_set(board->ptr_array[row], column, number);
}

/**************** full_board() ****************/
/* see board.h for description */
bool full_board(board_t *board, int *row, int *column){
    int size = get_size(board);
    // return false if the board has a 0
    for (int i = 0; i < (board->num_rows * board->num_rows); i ++){
        int r = i/size;
        int c = i % size;
        if (counters_get(board->ptr_array[r], c) == 0){
            //  set the row and column to the position of the next 0
            *row = r;
            *column = c;
            return false;
        }
    }
    // board has no 0's
    return true;
}

/**************** fprint_help() ****************/
/* prints every cell value depending on its position*/
void print_help(void *arg, const int key, const int count){
    board_t *board = arg;
    // border for left side
    if (key == 0){
        printf("| %d ", count);
    }
    // box and right side borders
    else if ((key + 1) % get_box_size(board) == 0 ){
        printf("%d | ", count);
    }
    else{
        printf("%d ", count);
    }
}

/**************** print_board() ****************/
/* see board.h for description */
void print_board(board_t *board){
    for (int i = 0; i < board->num_rows; i ++){
        if (i == 0){
            // top border
            printf("-------------------------\n");
            counters_iterate(get_row(board, i), board, print_help);
            printf("\n");
        }
        else if (((i + 1 )% get_box_size(board) == 0)){
            // box and bottom borders
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

/**************** check() ****************/
/* see board.h for description */
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

/**************** load_sudoku() ****************/
/* see board.h for description */
board_t *load_sudoku(FILE *fp, int size){
    // checking if invalid sudoku dimensions already
    if (size == 0){
        fprintf(stderr, "Sudoku is of invalid size. Please input a sudoku of proper dimensions (e.g. 9x9, 16x16).\n");
        return NULL;
    }
    
    board_t *board = assertp(board_new(size), "new board");
    char currValue;
    char prevValue = '\0';
    int digit;
    int row = 0;
    int column = 0;
    int totalValues = 0;
    int product = size*size;
    bool valid_format = true; // overarching valid_format checker
    bool valid_alpha = true; // tracking if any alphabetical characters in sudoku format appear, set to false
    bool valid_double_digit = true; // checking if valid to have double-digits given size
    bool valid_rc = true; // checking if valid row or column numbers
    bool valid_total = true; // checking if total number of values is appropriate for size

    while ((currValue = fgetc(fp)) != EOF){ // while the current value is not end of file
        if (isalpha(currValue) || totalValues > product){ // error checking: not valid if alphabetical character present
            valid_alpha = false;
            valid_format = false;
        }
        if (currValue != '\n') { // if not at end of the row
            if (isdigit(currValue)){
                if (isdigit(prevValue) && size < 16){ // if sudoku board size is < 16x16 size, can't have any 2 digit nubmers
                    valid_double_digit = false;
                    valid_format = false;
                }
                totalValues++; // incrementing value count (eventually checking if precisely 81)
                digit = currValue - '0'; // if not double-digit, convert digit to int

                if (column > size || row > size){ // error checking: if number of columns or rows exceeds the size x size dimensions, invalid sudoku
                    valid_rc = false;
                    valid_format = false;
                }
            }

            else if (isdigit(prevValue) && isspace(currValue)){ // represents a valid digit
                if (valid_format){
                    insert_number(board, row, column, digit); // inserting previous value into board
                }
                column++; // tracking number of columns
            }
            prevValue = currValue; // if still in same row, reassigning prevValue to currValue before next read
        }
        else{ // if at end of row (reading '\n')
            if (column == size){ 
                row++; // incrementing row
            }
            prevValue = '\0'; // resetting prevValue to '\0'
            column = 0; // resetting column to 0
        }
    }
    if (totalValues != (product)){ // error checking if more than size^2 total values
        valid_total = false;
        valid_format = false;
    }
    // error specific message

    // checking invalid alphabetical characters
    if (!valid_alpha){ 
        fprintf(stderr, "\nError: Cannot have alphabetical characters.\n");
        delete_puzzle(board);
        return NULL;   
    }

    // checking if invalid double-digits
    if (!valid_double_digit){ 
        fprintf(stderr, "\nError: Cannot have double-digit numbers for specified size.\n");
        delete_puzzle(board);
        return NULL;   
    }

     // checking if invalid dimensions (rows x columns)
    if (!valid_rc){ 
        fprintf(stderr, "\nError: Dimensions of sudoku are invalid for specified size.\n");
        delete_puzzle(board);
        return NULL;   
    }

    // checking if invalid total number of values in sudoku board
    if (!valid_total){ 
        fprintf(stderr, "\nError: Provided input is empty or sudoku puzzle doesn't have the correct number of values.\n", product);
        delete_puzzle(board);
        return NULL;   
    }
    return board;
}

/**************** save_solution() ****************/
/* see board.h for description */
void save_solution(board_t *board){

    int size = get_size(board);
    for (int i = 0; i < (size * size) ; i ++){
        int r = i/size;
        int c = i % size;
        int number = get_number(board, r, c);
        counters_set(board->solution[r], c, number);

    }
}

/**************** copy_board() ****************/
/* see board.h for description */
board_t* copy_board(board_t *board){
    int size = get_size(board);
    board_t *copy = assertp(board_new(size), "new board");
    // assert the number in the original board in the same slot of the copy
    for (int i = 0; i < (size * size) ; i ++){
        int r = i/size;
        int c = i % size;
            int number = get_number(board, r, c);
            insert_number(copy, r,c, number);
    }
    return copy;
}

/**************** print_solution() ****************/
/* see board.h for description */
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

/**************** empty_board() ****************/
/* see board.h for description */
void empty_board(board_t *board){
    // set all cells to 0
    for (int i = 0; i < (board->num_rows * board->num_rows); i ++){
        int r = i/board->num_rows;
        int c = i % board->num_rows;
        
            insert_number(board, r, c, 0);

    }
}
