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
    counters_t **ptr_array;     // array of sets
    int num_rows;              // number of rows in the hashboard
    counters_t **solution;
} board_t;

/**************** board_new() ****************/
/* see board.h for description */
board_t *board_new(const int num_rows){
    board_t *board = assertp(malloc(sizeof(board_t)), "Failed to allocate memory for new board\n"); 
    if (board == NULL) {
    return NULL;             
    } 
    else {
      board->num_rows = num_rows; 
      board->ptr_array = assertp(calloc(board->num_rows, sizeof(counters_t*)), "Failed to allocate memory for ptr_array\n");
      board->solution = assertp(calloc(board->num_rows, sizeof(counters_t*)), "Failed to allocate memory for solution board\n");
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
    for (int i = 0; i < (board->num_rows * board->num_rows); i ++){
        int r = i/size;
        int c = i % size;
        if (counters_get(board->ptr_array[r], c) == 0){
            *row = r;
            *column = c;
            return false;
        }
    }
    return true;
}

bool is_empty(board_t *board){
    int size = get_size(board);
    for (int i = 0; i < (size * size); i ++){
        int r = i/size;
        int c = i % size;
        if (counters_get(board->ptr_array[r], c) != 0){
            return false;
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

/**************** print_board() ****************/
/* see board.h for description */
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

/**************** load_size() ****************/
/* see board.h for description */
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

/**************** load_sudoku() ****************/
/* see board.h for description */
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
    int product = size*size;
    bool valid_format = true; // tracking if any errors in sudoku format appear, set to false

    while ((currValue = fgetc(fp)) != EOF){ // while the current value is not end of file
        if (isalpha(currValue) || totalValues > product){ // error checking: not valid if alphabetical character present
            valid_format = false;
        }
        if (currValue != '\n') { // if not at end of the row
            if (isdigit(currValue)){
                if (isdigit(prevValue) && size < 16){ // cannot be possible if 2 digit number in provided board
                    valid_format = false;
                }
                totalValues++; // incrementing value count (eventually checking if precisely 81)
                digit = currValue - '0'; // if not double-digit, convert digit to int

                if (column > size || row > size){ // error checking: if number of columns or rows exceeds the size x size dimensions, invalid sudoku
                    valid_format = false;
                }
            }

            else if (isdigit(prevValue) && isspace(currValue)){ // represents a valid digit
                if(valid_format){
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
        valid_format = false;
    }
    if (!valid_format){ // checking if any errors occurred in sudoku, and if so delete board and return NULL board
        fprintf(stderr, "\nError: Invalid sudoku board format.\n");
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

board_t* copy_board(board_t *board){
    int size = get_size(board);
    board_t *copy = board_new(size);
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
    for (int i = 0; i < (board->num_rows * board->num_rows); i ++){
        int r = i/board->num_rows;
        int c = i % board->num_rows;
        
            insert_number(board, r, c, 0);

    }
}
