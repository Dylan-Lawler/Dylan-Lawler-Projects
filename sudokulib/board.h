#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "../libcs50/counters.h"

typedef struct board board_t;

board_t *board_new(const int num_rows);

int get_number(board_t *board, int row, int column);

void insert_number(board_t *board, int row, int column, int number);

bool full_board(board_t *board);

void print_board(board_t *board);

counters_t* get_row(board_t *board, int row);

int get_size(board_t *board);

int get_box_size(board_t *board);