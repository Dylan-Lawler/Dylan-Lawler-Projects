# Final Project - Sudoku
## CS50 Spring 2022
## Team 10 (Alex Jones, Jordan Kirkbride, Dylan Lawler, Eric Leung)

### Sudoku

### Usage
Run `make` in the both the sudokulib directory and the common directory to compile the
modules necessary to run sudoku. Then run `make` in sudoku directory, followed by running 
`make test` within the same directory to test sudoku. Run `make clean` to delete the 
executables created from `make`. When running sudoku, must have one additional argument on top of the initial `./sudoku` declaration (e.g. `./sudoku create` or `./sudoku solve`).
The user will be prompted from the terminal to provide input via stdin to test the create and solving capabilities of sudoku.

### Organization of Directories and Files
* sudokulib
    - contains major helper files for sudoku, including:
    - `board.c` and `board.h`: files for the abstract data structure that our sudoku boards are based on
    - `make.c` and `make.h`: files that aid in creating a unique sudoku puzzle
    - `solve.c` and `solve.h`: files that aid in solving a provided sudoku puzzle
* libcs50
    - provided cs50 library that contains relevant data structure files (e.g. counters.c, counters.h) and helper 
    files that aid in file processing and managing memory
* testing
    - contains our testing files, including:
    - `fuzztest.c`: uses our creater to generate n puzzles, where n is a command-line argument and test solver for these grids. Also checks whether the solution is valid, and the solver checks if each given puzzle has a unique solution
* sudoku.c
    - compiled file to handle both `create` and `solve` functions of sudoku (corresponding to creating a unique sudoku puzzle and solving any solvable inputted sudoku puzzle respectively)


### Assumptions
No assumptions beyond those that are clear from the `DESIGN.md`, `IMPLEMENTATION.md`, and class project requirements. 
