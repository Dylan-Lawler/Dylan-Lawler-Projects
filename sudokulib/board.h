#include <math.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "../libcs50/counters.h"

/**************** global types ****************/
typedef struct board board_t;

/**************** functions ****************/

/**************** board_new ****************/
/* Purpose: Create a new empty Sudoku board struct in heap memory
 * Input:   The number of rows (== number of columns) in the board
 * Output:  A board struct filled with all 0s
*/
board_t *board_new(const int num_rows);

/**************** delete_puzzle ****************/
/* Purpose: Free all heap memory allocated to Sudoku board
 * Input:   Board to be deleted
*/
void delete_puzzle(board_t *board);

/**************** get_number ****************/
/* Purpose: Fetch the number in the given space in the board
 * Input:   A board struct and (row, column) coordinates
 * Output:  The number at space (row, column) in the board
*/
int get_number(board_t *board, int row, int column);

/**************** insert_number ****************/
/* Purpose: Insert the given number into the given space in the board
 * Input:   A board struct, a (row, column) coordinate, and the number to be inserted
*/
void insert_number(board_t *board, int row, int column, int number);

/**************** full_board ****************/
/* Purpose: Check if the board is full, and update row/column pointers to the coordinate of the first empty space, if any
 * Input:   A board struct and (row, column) coordinate *pointers* to be updated in-place
 * Output:  True if board is full, False otherwise
*/
bool full_board(board_t *board, int* row, int *column);

bool is_empty(board_t *board);

void print_board(board_t *board);

/**************** get_row ****************/
/* Purpose: Fetch given row in Sudoku board
 * Input:   A board struct and a row
 * Output:  The Counters object representing the requested row
*/
counters_t* get_row(board_t *board, int row);

/**************** get_size ****************/
/* Purpose: Get the number of rows (== num of columns) in the board
 * Input:   A board struct
 * Output:  The number of rows in the board
*/
int get_size(board_t *board);

/**************** get_box_size ****************/
/* Purpose: Get the size of one side of a Sudoku box for the given board
 * Input:   A board struct
 * Output:  The square root of the number of rows in the board (must be a perfect square)
*/
int get_box_size(board_t *board);

/**************** check ****************/
/* Purpose: Check if inserting a number in the given space in the board yields any rule violations
 * Input:   A board struct, a number to be tested, and a (row, column) coordinate
 * Output:  True if no rules were violated, False otherwise
*/
bool check(board_t *board, int num, int row, int column);

/**************** load_size ****************/
/* Purpose: Load the size of the board from a Sudoku board file
 * Input:   A pointer to a Sudoku board file
 * Output:  The size of the loaded board
*/
int load_size(FILE *fp);

/**************** load_sudoku ****************/
/* Purpose: Load a Sudoku board from a file
 * Input:   A pointer to a Sudoku board file
 * Output:  A board struct containing the loaded board
*/
board_t *load_sudoku(FILE *fp, int size);

/**************** save_solution ****************/
/* Purpose: Save a solution to the board struct
 * Input:   A board struct
*/
void save_solution(board_t *board);

board_t* copy_board(board_t *board);

void print_solution(board_t *board);

/**************** empty_board ****************/
/* Purpose: Re-populate a board with all 0s
 * Input:   A board struct
*/
void empty_board(board_t *board);