#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include "../libcs50/counters.h"

typedef struct board {
    counters_t **ptr_array;       // array of sets
    int num_rows;              // number of rows in the hashboard
} board_t;

board_t *board_new(const int num_rows){
    board_t *board = malloc(sizeof(board_t)); 
    if (board == NULL){
    return NULL;             
    } 
    else{
      board->num_rows = num_rows; 
      board->ptr_array = calloc(board->num_rows, sizeof(counters_t*));
      for (int i = 0; i < board->num_rows; i++){
          board->ptr_array[i] = counters_new();
          for (int j = 0; j < board->num_rows; j++){
            counters_set(board->ptr_array[i], j, 0 );
        }
      }
      return board;
    }
}

int get_number(board_t *board, int row, int column){
    return counters_get(board->ptr_array[row], column);
}

void insert_number(board_t *board, int row, int column, int number){
    counters_set(board->ptr_array[row], column, number);
}

bool full_board(board_t *board){
    for (int i = 0; i < board->num_rows; i ++){
        for (int j = 0; j < board->num_rows; j ++){
            if (counters_get(board->ptr_array[i], j) == 0){
                return false;
            }
        }
    }
    return true;
}

void print_help(void *arg, const int key, const int count){
    board_t *board = arg;
    if ((key + 1) % (int)sqrt(board->num_rows) == 0 && key != board->num_rows - 1){
            printf("%d|", count);
    }
    else{
            printf("%d ", count);
    }
}

void print_board(board_t *board){
    for (int i = 0; i < board->num_rows; i ++){
        if (((i + 1) % (int)sqrt(board->num_rows) == 0) && i != board->num_rows - 1){
            counters_iterate(board->ptr_array[i], NULL, print_help);
            printf("\n-------------------\n");

        }
        else{
        counters_iterate(board->ptr_array[i], board, print_help);
        printf("\n");
        }
    }
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