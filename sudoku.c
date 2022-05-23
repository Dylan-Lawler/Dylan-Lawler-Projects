#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "libcs50/counters.h"
#include "sudokulib/board.h"

// local functions
int *number_list();
bool full_board(board_t *board);
bool check(board_t *board, int num, int row, int column);
bool fill_rest(board_t *board, int i, int j);
bool make_puzzle(board_t *board, int row, int column);
void print_board(board_t *board);
void print_help(void *arg, const int key, const int count);
void clear_spaces(board_t *board, int spaces);

int main(int argc, char *argv[]){
    srand(time(NULL));
    board_t *board = board_new(9);
    make_puzzle(board, 0, 0);
    clear_spaces(board, 40);
    print_board(board);
}

// recursively make the puzzle by checking if each cell can hold any number 1-9
bool make_puzzle(board_t *board, int row, int column){
    // shuffled list of numbers 1-9
    int *nums = number_list();
    // if the board is full, make puzzle is done
    if (full_board(board) == true){
        return true;
    }
    // if its the end of the row, go to the next 
    if (column >= 9 && row < 8){
        row += 1; 
        column = 0;
    }
    // for all possible number insertions
    for (int num = 0; num<9; num++)
    {
        // if the number doesn't break sudoku rules
        if (check(board, nums[num], row , column) == true)
        {
            // insert it
            insert_number(board, row, column, nums[num]);
            // go to the next number and do the same
            if (make_puzzle(board, row, column+1)){
                return true;
            }
            // if no numbers work, keep deleting until numbers work again
            insert_number(board, row, column, 0);
        }
    }
    // no numbers worked, backtrack
    return false;
}

void clear_spaces(board_t *board, int spaces){
    // keeps track of spaces made empty
    int cleared = 0; 
    // until the desired amount of spaces are cleared
    while(cleared < spaces){
        // find a random cell
        int row = rand() % 9;
        int col = rand() % 9;
        // if its not already emptied, empty it and increment number of empty cells
        if (get_number(board, row, col) != 0){
            insert_number(board, row, col, 0);
            cleared++;
        }
    }
}

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


int *number_list(){
    // create a list of possible numbers to insert to puzzle
    int *num_list = calloc(9, sizeof(int));
    for (int i = 0; i < 9; i++){
        num_list[i] = i + 1;
    }

    // shuffle the numbers around so we can have a randomized puzzle
    for (int i = 0; i < 9; i++){
        int random = rand() % 9;
        int temp = num_list[i];
        num_list[i] = num_list[random];
        num_list[random] = temp;
    }

    return num_list;
}

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