# testing file for sudoku program
#
# results are printed to testing.out 
# 
# Dylan Lawler, CS50, Spring 2022
#

# TEST 1: No arguments
echo "Testing program with no command arguments"
./sudoku 
echo -e "\n"

# TEST 2: create mode
echo "Testing sudoku create mode"
./sudoku create
echo -e "\n"

# TEST 3: solve with too many puzzle entries
echo "Testing sudoku solve mode with two puzzle entries at once"
./sudoku solve < testing/twoboards
echo -e "\n"

# TEST 4: solve with too small of a board
echo "Testing sudoku solve mode with a board with insufficient rows"
./sudoku solve < testing/smallboard
echo -e "\n"

# TEST 5: solve with letter in board
echo "Testing sudoku solve mode with a board with an alphabet character"
./sudoku solve < testing/alphaboard
echo -e "\n"

# TEST 6: solve with a double digit in board
echo "Testing sudoku solve mode with a board with a number out of range"
./sudoku solve < testing/rangeboard
echo -e "\n"

# TEST 7: solve mode with empty file input
echo "Testing sudoku solve mode with a board with a number out of range"
./sudoku solve < testing/emptyboard
echo -e "\n"

# TEST 8: fuzztest make and solve with 10 boards
echo "Fuzz testing make and solve modules"
./fuzz 10
echo -e "\n"




