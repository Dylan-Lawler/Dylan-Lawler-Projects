/* sudokusolver.c - solves a given sudoku puzzle from stdin
 *
 * Using backtracing to approach solving the sudoku puzzle
 *
 *
 */

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include <time.h>

void load_sudoku()

