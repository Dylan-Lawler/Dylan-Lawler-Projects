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

// local function 
static void parse_args(const int argc, char *argv[], char **mode);

int main(int argc, char *argv[]){
    // randomization seed changes with time
    srand(time(NULL));
    // sudoku mode
    char *mode = NULL;
    // ensure correct arguments and run program
    parse_args(argc, argv, &mode);
    // program ran correctly
    return 0;
}

static void parse_args(const int argc, char *argv[], char **mode)
{
    // exit if there aren't two arguments with the program      
    char *program = argv[0];
    // ensures the user follows usage 
    *mode = argv[1];
    if ((argc != 2) || ((strcmp(*mode, "create")) && (strcmp(*mode, "solve")))){
        fprintf(stderr, "Usage: %s solve\nor\nUsage: %s create\n", program, program);
        exit (1); 
    }
    // if the mode is create
    if (!(strcmp(*mode, "create"))){
        printf("Unique 9x9 Sudoku Board:\n");
        // create a new board and make a unique puzzle with 40 empty spaes
        board_t *board = assertp(board_new(9), "new board");
        make_puzzle(board, 0, 0);
        clear_spaces(board, 40);
        // print board to stdout
        print_board(board);
        printf("\n");
        // delete the board struct
        delete_puzzle(board);
        return;
    }

    // if the sudoku mode is solve
    if (!(strcmp(*mode, "solve"))){
        // prompt an input of a 9x9 sudoku board
        printf("Enter Sudoku board:\n");
        int size = 9;
        board_t *board = assertp(load_sudoku(stdin, size), "load board");
        // board couldnt be created and loaded
        if (board == NULL){
            exit(2);
        }
            // solve the puzzle and see if it's unique 
            int sols = solve_puzzle(board, 0, 0, 0);
            // puzzed has no solutio
            if (sols < 1){
                printf("Given Sudoku board is not solvable\n");
                return;
            }
            // puzzle isn't unique, provide one possible solution
            if (sols > 1){
                printf("Given Sudoku board has multiple solutions, here is one:\n");
                print_solution(board);
                printf("\n");
                return;
            }
            // puzzle is unique and provide the solution
            printf("Solved unique Sudoku board:\n");
            print_solution(board);
            printf("\n");
            delete_puzzle(board);
        }
}