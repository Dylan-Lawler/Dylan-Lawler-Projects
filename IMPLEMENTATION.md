# Final Project - Sudoku
## CS50 Spring 2022

## IMPLEMENTATION.md for Sudoku
## Team 10 (Alex Jones, Jordan Kirkbride, Dylan Lawler, Eric Leung)

According to DESIGN.md and requirements outlined by class project specifications, the *sudoku* is a standalone program, where we can invoke our Sudoku program from the command line with one command line argument and usage must be as follows:
- ./sudoku create to create a random Sudoku puzzle
- ./sudoku solve to solve a given Sudoku puzzle
* Sudoku creator must satisfy the following requirements:
    - Create a puzzle that has a unique solution
    - There must be at least 40 missing numbers in the generated puzzle
    - The puzzle must be randomized
    - The puzzle is printed to stdout
* Sudoku solver must satisfy the following requirements:
    - Be able to accept puzzles that have multiple solutions
    - Generate any one possible solution for the given puzzle
    - Must not change any given numbers in the puzzle
    - Should read the puzzle from stdin and print the solution to stdout.

Refer to the DESIGN.md file and class project specifications for more information regarding sudoku.


## Function Prototypes

### Functions for `board.c`
```c
board_t *board_new(const int num_rows);
void delete_puzzle(board_t *board);
int get_number(board_t *board, int row, int column);
counters_t* get_row(board_t *board, int row);
int get_size(board_t *board);
int get_box_size(board_t *board);
void insert_number(board_t *board, int row, int column, int number);
bool full_board(board_t *board, int *row, int *column);
void print_help(void *arg, const int key, const int count);
void print_board(board_t *board);
bool check(board_t *board, int num, int row, int column);
int load_size(FILE *fp);
board_t *load_sudoku(FILE *fp);
void save_solution(board_t *board);
void print_solution(board_t *board);
void empty_board(board_t *board);
```

### Functions for `make.c`
```c
int *number_list();
bool make_puzzle(board_t *board, int row, int column);
void clear_spaces(board_t *board, int spaces);
```

### Functions for `solve.c`
```c
int solve_puzzle(board_t *board, int row, int column, int count);
```

## Pseudocode for functions

### Pseudocode for `board.c`
Refer to sudoku.c for more detailed descriptions of functions and for comments.

#### main
```
```

## Pseudocode for `make.c`

## Pseudocode for `solve.c`

## Data structures

Furthermore, we made several data structures:
```
```

## Error handling
We handle and catch errors via conditional statements and printing appropriate error messages.
When appropriate, we call 'continue', 'return', or 'exit' preemptively to prevent the program from running into further problems.

## Testing
We tested through the use of fuzz testing (via fuzztest.c) and testing.sh, writing appropriate command line inputs to error check and check for valid cases.
Additionally, we directly called and tested `./sudoku create` and `./sudoku make` with various combinations of sudoku inputs, also checking for memory leaks with myvalgrind.