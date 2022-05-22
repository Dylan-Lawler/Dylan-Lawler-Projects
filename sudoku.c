#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "libcs50/counters.h"

typedef struct board {
    counters_t **ptr_array;       // array of sets
    int num_rows;              // number of rows in the hashboard
} board_t;

board_t *board_new(const int num_rows){
    board_t *board = malloc(sizeof(board_t)); 

    if (board == NULL){
    return NULL;              // error allocating hashboard
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

int *number_list();
int *shuffle_list(int *num_list);
bool full_board(board_t *board);
bool check(board_t *board, int num, int row, int column);
bool make_puzzle(board_t *board, int prevrow, int prevcol);
void print_board(board_t *board);
void print_help(void *arg, const int key, const int count);


int main(int argc, char *argv[]){
    board_t *board = board_new(9);
    make_puzzle(board, 0, 0);
    print_board(board);
}

bool make_puzzle(board_t *board, int prevrow, int prevcol){
    int *numbers = number_list();
    bool stop = true;
    int row; 
    int column;
    for (row = 0; (row < 9) && (stop == true); row ++){
        for (column = 0; column < 9; column++){
            if ((get_number(board, row, column)) == 0){
                for (int num = 0; num < 9; num++){
                    srand(time(NULL));
                    int *shuffled = shuffle_list(numbers);
                    if ((check(board, shuffled[num], row, column)) == true){
                        insert_number(board, row, column, shuffled[num]);
                        if (full_board(board)){
                            return true;
                        }
                        if ((make_puzzle(board, row, column)) == true){
                            return true;
                        }
                    }

                }
                stop = false;
            }
        }
    }
    insert_number(board, prevrow, prevcol, 0);
    return false;
}
bool check(board_t *board, int num, int row, int column){
    for (int i = 0; i < board->num_rows; i++){
        if ((counters_get(board->ptr_array[row], i) == num) || (counters_get(board->ptr_array[i], column) == num)){
            return false; 
        }
    }
    int boxrow = row - (row % 3);
    int boxcol = column - (column % 3);

    for (int i = boxrow; i < boxrow + 3; i ++){
        for (int j = boxcol; j < boxcol + 3; j ++){
            if (counters_get(board->ptr_array[i], j) == num){
                return false;
            }
        }
    }
    return true; 
}

bool full_board(board_t *board){
    for (int i = 0; i < 9; i ++){
        for (int j = 0; j < 9; j ++){
            if (counters_get(board->ptr_array[i], j) == 0){
                return false;
            }
        }
    }
    return true;
}

void print_board(board_t *board){
    for (int i = 0; i < 9; i ++){
        if (((i + 1) % 3 == 0) && i != 8){
            counters_iterate(board->ptr_array[i], NULL, print_help);
            printf("\n-------------------\n");

        }
        else{
        counters_iterate(board->ptr_array[i], NULL, print_help);
        printf("\n");
        }
    
    }
}

void print_help(void *arg, const int key, const int count){
    if ((key + 1) % 3 == 0 && key != 8){
            printf("%d|", count);
    }
    else{
            printf("%d ", count);
    }
}

int *number_list(){
    srand(time(NULL));
    int *num_list = calloc(9, sizeof(int));
    for (int i = 0; i < 9; i++){
        num_list[i] = i + 1;
    }

    for (int i = 0; i < 9; i++){
        int random = rand() % 9;
        int temp = num_list[i];
        num_list[i] = num_list[random];
        num_list[random] = temp;
    }

    return num_list;
}

int *shuffle_list(int *num_list){
    srand(time(NULL));
    for (int i = 0; i < 9; i++){
        int random = rand() % 9;
        int temp = num_list[i];
        num_list[i] = num_list[random];
        num_list[random] = temp;
    }

    return num_list;
}