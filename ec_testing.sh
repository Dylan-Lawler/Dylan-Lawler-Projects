#!/bin/bash

ret=0

start=$SECONDS

# Argument checking
if [ $# -ne 0 ]; then
	echo >&2 "Please don't enter any arguments"
	((ret+=1))
	exit $ret
fi

make

printf "\nMaking and solving 4x4 grid\n"
./sudoku create 4 | tee 4x4.txt
./sudoku solve 4 < 4x4.txt
printf "\n"

printf "\nMaking and solving 9x9 grid\n"
./sudoku create 9 | tee 9x9.txt
./sudoku solve 9 < 9x9.txt
printf "\n"

printf "\nMaking and solving 16x16 grid\n"
./sudoku create 16 | tee 16x16.txt
./sudoku solve 16 < 16x16.txt
printf "\n"

printf "\nTrying to make 25x25 grid\n"
# Try to make the enormous grid in under 30s
timeout 30s bash -c "./sudoku create 25 | tee 25x25.txt"
# If we miraculously made it in time, try solving it in under 2 mins
status=$?
if [ "${status}" -eq 0 ]; then
	timeout 120s ./sudoku solve 25 < 25x25.txt
	printf "\n"
else 
	printf "Failed to make puzzle in under 30s\n"
fi

exit $ret