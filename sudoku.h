/* sudoku.h - header file for sudoku.c
 *
 * 
 *
 * Final Project (Sudoku), Team 10, CS 50 Spring 2022
 */


 /**************** global types ****************/
typedef struct board board_t;  // opaque to users of the module

/**************** functions ****************/

/**************** board_new ****************/
board_t *board_new(const int num_rows);

int get_number(board_t *board, int row, int column);

void insert_number(board_t *board, int row, int column, int number);

int *number_list();

int *shuffle_list(int *num_list);

bool full_board(board_t *board);

bool check(board_t *board, int num, int row, int column);

bool make_puzzle(board_t *board);

void print_board(board_t *board);

void print_help(void *arg, const int key, const int count);