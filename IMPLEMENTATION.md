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
board_t *load_sudoku(FILE *fp, int size);
void save_solution(board_t *board);
board_t* copy_board(board_t *board);
void print_solution(board_t *board);
void empty_board(board_t *board);
```

### Functions for `make.c`
```c
int *number_list(int size);
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

`board_new`
1. Create a new board struct by first allocating memory to the board. 
2. Initialize the dimensions of the board
3. Allocate memory to counter arrays that are part of board struct
4. Initialize every cell in the original and solution boards to 0 using counters_set
5. Return the board

`delete_puzzle`
1. Check if there is board is not NULL (so something to free)
2. Loop over board and call counters_delete to delete every entry within counters array
3. Free the board struct

`get_number`
1. Call counters_get to retrieve specific value at specified location
2. Return retrieved value

`get_row`
1. Retrieve specified row from within counters array
2. Return the retrieved row

`get_size`
1. Retrieve total number of rows within board struct
2. Return the total number

`get_box_size`
1. Retrieve the square root of the number of rows in the board
2. Return the calculated value

`insert_number`
1. Call counters_set to insert value into specified location on board

`full_board`
1. Loop through entire board, checking if any entries are '0'
    1. If any values are '0', return false
    2. Otherwise, return true

`print_help`
1. If specified key is a left border value, print "| key" format
2. If specified key is a right side border or box border, print " key |" format
3. If specified key is neither of the two aforementioned entries and just a typical key, print "key " (noting the space after key)

`print_board`
1. Loop through each row of the board
    1. For first row, print a row of dashes
    2. For box border and bottom border rows, print row of dashes
    3. For number entries, call counters_iterate to print entries of board

`check`
1. Check if either row or column of specified entry already contains the specified parameter number, returning false if number is present in either row or column
2. Check the specific square and see if it contains the specific value from the parameter, returning false if already present
3. If number is not in either row, column, nor square, return true

`load_sudoku`
1. First check if the specified size of sudoku to load is 0, printing error message and returning NULL if so
2. Loop through entire stdin character by character
    1. If the total number of values loaded is larger than specified size limit, set a bool that tracks valid format to false
    2. If any characters are alphabetical, setting a bool that tracks valid format to false
    3. If the current character is not the end of the line
        1. If the current character is a digit (0-9)
            1. If the previous character is also a digit, but the size of the sudoku is less than a 16x16, set a bool that tracks valid format to false
            2. Convert the current character to an int
            3. If the column or row amount exceeds size, set a bool that tracks valid format to false
        2. Else if the previous character is a valid digit and current character is a space
            1. If the format of sudoku is still valid
                1. Insert the digit into the board at specific location
                2. Increment total number of values loaded
            2. Increment column count 
        3. Set the previous stored character variable to the current character
    4. If at the end of the row reading from stdin
        1. Increment row by one if the column is equal to size
        2. Reassign the previous character value to a NULL character
        3. Reassign the column value to 0
3. If the total number of inserted values is not equal to the expected total number of values, set a bool that tracks valid format to false
4. Error check based on specific valid format bool
    1. If error, print error message
    2. Delete sudoku board
    3. Return NULL
5. If no errors, return sudoku board


`save_solution`
1. Loop through entire board, retrieving the values within board by calling get_number
2. Call counters_set to insert the values into the board struct, ending when fully saved the solution board to the board struct

`copy_board`
1. Create a new board struct
2. Loop through the original board and get all numbers from the original board, inserting to the copy board
3. Return the copy board

`print_solution`
1. Loop through the solution counters array within the board struct row by row
    1. If the row is either the top border or a subsequent bottom or box border, print a row of dashes
    2. Otherwise, iterate through row and print the solution values

`empty_board`
1. Loop through the entire board
    1. Replace or insert every entry in the board with 0


## Pseudocode for `make.c`

`number_list`
1. Create a list of possible numbers to insert into puzzle
2. Shuffle the numbers around to help randomize puzzle
3. Return shuffled number list

`make_puzzle`
1. If the board is full
    1. Free number list
    2. Return true to signify make_puzzle is done
2. Loop over all possible number insertions
    1. If the number does not break sudoku rules
        1. Insert number into board
        2. Progress to next number by recursively calling make_puzzle with newly updated board
            1. Free number list
            2. Return true if no errors
        3. If no numbers work, keep deleting by inserting 0 in board spot until numbers work
3. If no numbers worked, backtrack
    1. Free number list
    2. Return false

`clear_spaces`
1. Create list of possible cell spaces
2. Loop through total number of possible cell spaces
    1. Replace current value with 0
    2. Increment total of cleared spaces
    3. Create a board struct copy so original board isn't changed
    4. If cannot solve puzzle
        1. Put removed number back
        2. Decrement total of cleared spaces
    5. Delete copy of puzzle
    6. Break loop if board is empty enough
3. If board could not be emptied enough and be unique
    1. Empty board
    2. Make a new puzzle
    3. Recursively call clear_spaces to try to make a board that meets our specifications again
4. Free the list of cells

## Pseudocode for `solve.c`

`solve_puzzle`
1. If there is a completely filled board (suggesting it is solved)
    1. Save the board struct solution to the board struct
    2. Return the count for number of solutions found to help with checking for uniqueness
2. If not fully solved, set row and column to next empty cell
3. Loop through all possible numbers for the specific space on the sudoku board
    1. If the number does not violate sudoku rules
        1. Insert number into sudoku board
        2. Proceed to next empty cell and recursively call solve_puzzle
        3. If there is more than one solution, the sudoku puzzle is not unique. Return count
4. If no numbers could be inserted, backtrack
5. Return count

## Data structures

In sudoku, we created one main data structure called `board_t`:
```
typedef struct board {
    counters_t **ptr_array;     // array of counters
    int num_rows;              // number of rows in the sudoku board
    counters_t **solution;      // solved board
} board_t;
```
This struct contains the functionality to store the original sudoku board and its solution sudoku board as an array of counters, alongside an integer storing the number of rows of the sudoku board. board_t contains three struct elements:

1. counters_t **ptr_array
    - An array of counters to keep track of the original sudoku board
2. int num_rows
    - An integer to keep track of the number of rows within the sudoku
3. counters_t **solution
    - An array of counters to keep track of the solution to the original sudoku board

We also used counters, specifically an array of counters, to store a counter at each value in a sudoku board so we could apply convenient counter functionalities such as counters_set, counters_get, and counters_delete when manipulating the values on the sudoku board.
    

## Error handling
We handle and catch errors via conditional statements and printing appropriate error messages.
When appropriate, we call 'continue', 'return', or 'exit' preemptively to prevent the program from running into further problems.

## Testing
We tested through the use of fuzz testing (via fuzztest.c) and testing.sh, writing appropriate command line inputs to error check and check for valid cases.
Additionally, we directly called and tested `./sudoku create` and `./sudoku make` with various combinations of sudoku inputs, also checking for memory leaks with myvalgrind.