#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include "solve.h"
#include "../libcs50/counters.h"
#include "../libcs50/memory.h"
#include "make.h"

typedef struct board {
    counters_t **ptr_array;     // array of sets
    int num_rows;              // number of rows in the hashboard
    counters_t **solution;
} board_t;

/**************** constants ****************/
int BOARD_SIZE;


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

/**************** is_empty() ****************/
/* see board.h for description */
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


/**************** print_help() ****************/
/* see board.h for description */
void print_help(void *arg, const int key, const int count) {
    if (count > 81) {
        fprintf(stderr, "Sudoku board must be no bigger than 81x81\n");
        exit(1);
    }
    board_t *board = arg;
    BOARD_SIZE = get_size(board);
    if (key == 0) {
        if (BOARD_SIZE > 9) {
            if (count < 10) printf("| %d  ", count);
            else printf("| %d ", count);
        }
        else printf("| %d ", count);
    }
    else if ((key + 1) % get_box_size(board) == 0 ) {
        if (BOARD_SIZE > 9) {
            if (count < 10) printf("%d  | ", count);
            else printf("%d | ", count);
        }
        else printf("%d | ", count);
    }
    else {
        if (BOARD_SIZE > 9) {
            if (count < 10) printf("%d  ", count);
            else printf("%d ", count);
        }
        else printf("%d ", count);
    }
}

/**************** print_board() ****************/
/* see board.h for description */
void print_board(board_t *board) {
    int size = get_size(board);
    //BOARD_SIZE = size;
    int box_size = get_box_size(board);
    int num_dashes;
    if (size < 16) {
        num_dashes = 3 + 2*size + 2*(box_size-1);
    }
    else {
        num_dashes = 3 + 3*size + 2*(box_size-1);
    }
    char separator[num_dashes]; // create row separator
    for (int d = 0; d <= num_dashes; d++) {
        separator[d] = '-';
    }
    separator[num_dashes] = '\0';
    for (int i = 0; i < board->num_rows; i ++){
        if (i == 0){
            printf("%s\n", separator);
            counters_iterate(get_row(board, i), board, print_help);
            printf("\n");
        }
        else if (((i + 1 )% get_box_size(board) == 0)){
            counters_iterate(get_row(board, i), board, print_help);
            printf("\n%s\n", separator);
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
    int boxsize = get_box_size(board);
    // start at the top left corner of the square
    int boxrow = row - (row % boxsize);
    int boxcol = column - (column % boxsize);

    // if the number matches any number in the square, return false 
    for (int i = boxrow; i < boxrow + boxsize; i ++){
        for (int j = boxcol; j < boxcol + boxsize; j ++){
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
    if (size == 0 || size > 81){
        fprintf(stderr, "Sudoku is of invalid size. Please input a sudoku board between 4x4 and 81x81.\n");
        return NULL;
    }
    
    board_t *board = board_new(size);
    char currValue;
    char prevValue = '\0';
    int digit;
    int row = 0;
    int column = 0;
    int totalValues = 0;
    char number[4];
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
                if (isdigit(prevValue) && size < 16){
                    valid_double_digit = false;
                    valid_format = false;
                }
                digit = currValue - '0'; // if not double-digit, convert digit to int
                if (isdigit(prevValue) && size >= 16){
                    sprintf(number, "%c%c", prevValue, currValue);
                    digit = atoi(number);
                }

                if (column > size || row > size){ // error checking: if number of columns or rows exceeds the size x size dimensions, invalid sudoku
                    valid_rc = false;
                    valid_format = false;
                }
            }

            else if (isdigit(prevValue) && isspace(currValue)){ // represents a valid digit
                if (valid_format){
                    insert_number(board, row, column, digit); // inserting previous value into board
                    totalValues++;
                    //printf("Total values: %d\n", totalValues);
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
        fprintf(stderr, "\nError: Provided sudoku puzzle must have exactly %d values based on specified size.\n", product);
        delete_puzzle(board);
        return NULL;   
    }
    return board;
}

/**************** save_solution() ****************/
/* see board.h for description */
void save_solution(board_t *board){

    int size = get_size(board);
    for (int i = 0; i < size; i ++){
        for (int j = 0; j < size; j ++){
            int number = get_number(board, i, j);
            counters_set(board->solution[i], j, number);
        }
    }
}

/**************** copy_board() ****************/
/* see board.h for description */
board_t* copy_board(board_t *board) {
    int size = get_size(board);
    board_t* board_copy = board_new(size);
    for (int i = 0; i < size; i ++){
        for (int j = 0; j < size; j ++){
            int number = get_number(board, i, j);
            insert_number(board_copy, i, j, number);
        }
    }
    return board_copy;
}

/**************** print_solution() ****************/
/* see board.h for description */
void print_solution(board_t *board){
    int size = get_size(board);
    int box_size = get_box_size(board);
    int num_dashes;
    if (size < 16) {
        num_dashes = 3 + 2*size + 2*(box_size-1);
    }
    else {
        num_dashes = 3 + 3*size + 2*(box_size-1);
    }
    char separator[num_dashes]; // create row separator
    for (int d = 0; d <= num_dashes; d++) {
        separator[d] = '-';
    }
    separator[num_dashes] = '\0';
    for (int i = 0; i < board->num_rows; i ++){
        if (i == 0){
            printf("%s\n", separator);
            counters_iterate(board->solution[i], board, print_help);
            printf("\n");
        }
        else if (((i + 1 )% get_box_size(board) == 0)){
            counters_iterate(board->solution[i], board, print_help);
            printf("\n%s\n", separator);
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
    for (int i = 0; i < board->num_rows; i ++){
        for (int j = 0; j < board->num_rows; j ++){
            insert_number(board, i, j, 0);
        }
    }
}
