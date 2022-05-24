#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "libcs50/counters.h"
#include "sudokulib/board.h"

// local functions
int *number_list();
bool check(board_t *board, int num, int row, int column);
bool fill_rest(board_t *board, int i, int j);
bool make_puzzle(board_t *board, int row, int column);
bool solve_puzzle(board_t *board, int row, int column);
void clear_spaces(board_t *board, int spaces);

int main(int argc, char *argv[]){
    srand(time(NULL));
    board_t *board = board_new(9);
    make_puzzle(board, 0, 0);
    clear_spaces(board, 40);
    print_board(board);
    printf("\n");
    solve_puzzle(board, 0, 0);
    print_board(board);
}

// recursively make the puzzle by checking if each cell can hold any number
bool make_puzzle(board_t *board, int row, int column){
    int size = get_size(board);
    // shuffled list of numbers
    int *nums = number_list(size);
    // if the board is full, make puzzle is done
    if (full_board(board) == true){
        return true;
    }
    // if its the end of the row, go to the next 
    if (column >= size && row < size){
        row += 1; 
        column = 0;
    }
    // for all possible number insertions
    for (int num = 0; num< size; num++)
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


// recursively solve the puzzle by checking if every empty cell can hold any number
bool solve_puzzle(board_t *board, int row, int column){
    // size of row/ column
    int size = get_size(board);
    // if the board is full, make puzzle is done
    if (full_board(board) == true){
        return true;
    }
    // find the next empty cell
    for (int i = 0; i < size; i ++){
        for (int j = 0; j < size; j ++){
            if (counters_get(get_row(board, i), j) == 0){
                row = i;
                column = j;
            }
        }
    }
    // for all possible number insertions
    for (int num = 1; num <= size; num++)
    {
        // if the number doesn't break sudoku rules
        if ((check(board, num, row , column) == true))
        {
            // insert it to the empty cell
            insert_number(board, row, column, num);
            // go to the next empty cell and do the same
            if (solve_puzzle(board, row, column)){
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
    int size = get_size(board);
    // keeps track of spaces made empty
    int cleared = 0; 
    // until the desired amount of spaces are cleared
    while(cleared < spaces){
        // find a random cell
        int row = rand() % size;
        int col = rand() % size;
        // if its not already emptied, empty it and increment number of empty cells
        if (get_number(board, row, col) != 0){
            insert_number(board, row, col, 0);
            cleared++;
        }
    }
}

bool check(board_t *board, int num, int row, int column){
    int size = get_size(board);
    int box = get_box_size(board);
    // if the number matches any number in the same row or column, return false
    for (int i = 0; i < size; i++){
        if ((counters_get(get_row(board, row), i) == num) || (counters_get(get_row(board, i), column) == num)){
            return false; 
        }
    }
    // start at the top left corner of the square
    int boxrow = row - (row % box);
    int boxcol = column - (column % box);

    // if the number matches any number in the square, return false 
    for (int i = boxrow; i < boxrow + box; i ++){
        for (int j = boxcol; j < boxcol + box; j ++){
            if (counters_get(get_row(board, i), j) == num){
                return false;
            }
        }
    }
    // the number is valid
    return true; 
}


int *number_list(int size){
    // create a list of possible numbers to insert to puzzle
    int *num_list = calloc(size, sizeof(int));
    for (int i = 0; i < size; i++){
        num_list[i] = i + 1;
    }

    // shuffle the numbers around so we can have a randomized puzzle
    for (int i = 0; i < size; i++){
        int random = rand() % size;
        int temp = num_list[i];
        num_list[i] = num_list[random];
        num_list[random] = temp;
    }

    return num_list;
}