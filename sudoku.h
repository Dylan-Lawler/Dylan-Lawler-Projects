/* sudoku.h - header file for sudoku.c
 *
 * 
 *
 * Final Project (Sudoku), Team 10, CS 50 Spring 2022
 */

#include <stdio.h>
#include <stdbool.h>
#include "sudokulib/board.h"

 /**************** global types ****************/
// typedef struct board board_t;  // opaque to users of the module

/**************** functions ****************/

/**************** board_new ****************/
int *number_list();
bool full_board(board_t *board);
bool check(board_t *board, int num, int row, int column);
bool fill_rest(board_t *board, int i, int j);
bool make_puzzle(board_t *board, int row, int column);
void print_board(board_t *board);
void print_help(void *arg, const int key, const int count);
void clear_spaces(board_t *board, int spaces);