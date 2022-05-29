# Final Project - Sudoku
## CS50 Spring 2022

## IMPLEMENTATION.md for Sudoku
## Team 10 (Alex Jones, Jordan Kirkbride, Dylan Lawler, Eric Leung)

According to DESIGN.md and requirements outlined by class project specifications, the *sudoku* is a standalone program, where we can invoke our Sudoku program from the command line with one command line argument and usage must be as follows:
- ./sudoku create to create a random Sudoku puzzle
- ./sudoku solve to solve a given Sudoku puzzle
Sudoku creator must satisfy the following requirements:
- Create a puzzle that has a unique solution
- There must be at least 40 missing numbers in the generated puzzle
- The puzzle must be randomized
- The puzzle is printed to stdout
Sudoku solver must satisfy the following requirements:
- Be able to accept puzzles that have multiple solutions
- Generate any one possible solution for the given puzzle
- Must not change any given numbers in the puzzle
- Should read the puzzle from stdin and print the solution to stdout.

Refer to the DESIGN.md file and class project specifications for more information regarding sudoku.

## Pseudo code for `board.c`
Refer to sudoku.c for more detailed descriptions of functions and for comments.

### main
```
```

## Pseudo code for `make.c`

## Pseudo code for `solve.c`

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