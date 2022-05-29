#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include "../libcs50/counters.h"


bool make_puzzle(board_t *board, int row, int column);

int *number_list(int size);

void clear_spaces(board_t *board, int spaces);