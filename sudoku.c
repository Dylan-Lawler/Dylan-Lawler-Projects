/*
 * sudoku.c - program to make a sudoku board and solve it using sudoku modules
 *
 * usage: ./sudoku
 *
 * Dylan, Jordan, Alex, Eric
 * CS50 Spring '22
 * 
 */


#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include <sys/time.h>
#include "libcs50/counters.h"
#include "sudokulib/board.h"
#include "sudokulib/make.h"
#include "sudokulib/solve.h"

static void parse_args(const int argc, char *argv[], char **mode);
int main(int argc, char *argv[]){
    
    // Initialize board
    srand(time(NULL));
    char *mode = NULL;
    parse_args(argc, argv, &mode);
    return 0;
}

static void parse_args(const int argc, char *argv[], char **mode)
{
    // exit if there aren't two arguments with the program      
    char *program = argv[0];
    *mode = argv[1];
    if ((argc < 2) || ((strcmp(*mode, "create")) && (strcmp(*mode, "solve")))){
        fprintf(stderr, "Usage: %s solve\nor\nUsage: %s create\n", program, program);
        exit (1); 
    }

    if (!(strcmp(*mode, "create"))){
        int size;
        if (argv[2] == NULL) {
            size = 9;
        }
        else {
            size = atoi(argv[2]);
        }
        board_t *board = board_new(size);
        make_puzzle(board, 0, 0);
        clear_spaces(board, (size*size)/2);
        print_board(board);
        printf("\n");
        delete_puzzle(board);
        return;
    }

    if (!(strcmp(*mode, "solve"))){
        printf("Enter Sudoku board:\n");
        int size;
        if (argv[2] == NULL) {
            size = 9;
        }
        else {
            size = atoi(argv[2]);
        }
        board_t *board = load_sudoku(stdin, size);
        if (board == NULL){
            exit(2);
        }
        if (is_empty(board)){
            fprintf(stderr, "Nothing/empty boards are not valid\n");
            return;
        }
        int sols = solve_puzzle(board, 0, 0, 0);
        if (sols < 1){
            printf("Given Sudoku board is not solvable\n");
            return;
        }
        if (sols == 2){
            printf("Given Sudoku board has multiple solutions, here is one:\n");
            print_solution(board);
            printf("\n");
            return;
        }
        printf("Solved Sudoku board:\n");
        print_solution(board);
        printf("\n");
        delete_puzzle(board);
    }
}
