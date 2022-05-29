#include <math.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "../libcs50/counters.h"

typedef struct board board_t;

board_t *board_new(const int num_rows);

void delete_puzzle(board_t *board);

int get_number(board_t *board, int row, int column);

void insert_number(board_t *board, int row, int column, int number);

bool full_board(board_t *board, int* row, int *column);

void print_board(board_t *board);

counters_t* get_row(board_t *board, int row);

int get_size(board_t *board);

int get_box_size(board_t *board);

bool check(board_t *board, int num, int row, int column);

int load_size(FILE *fp);

board_t *load_sudoku(FILE *fp);

void save_solution(board_t *board);

board_t* copy_board(board_t *board);

void print_solution(board_t *board);

void empty_board(board_t *board);

