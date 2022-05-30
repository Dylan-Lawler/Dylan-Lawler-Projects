# CS50 Final Project
## CS50 Spring 2022

### Functionality test

Various functionality tests are conducted in fuzztest.c: 

For n iterations (dependent on user input at command line):
* TEST 1: make_puzzle with random set of numbers
* TEST 2: clear_spaces on known valid board
* TEST 3: print_board on known valid board
* TEST 4: solve_board on a valid, randomized board
* TEST 5: print_solution of a solved board
* TEST 6: delete a solved puzzle



#### Functionality test output
See testing.out for full testing output. 



### Memory test
By default is set to run 500 times, takes about 1 minute to complete 
```bash
$ make val
==42967== HEAP SUMMARY:
==42967==     in use at exit: 0 bytes in 0 blocks
==42967==   total heap usage: 261,517 allocs, 261,517 frees, 7,580,768 bytes allocated
==42967== 
==42967== All heap blocks were freed -- no leaks are possible
==42967== 
==42967== For counts of detected and suppressed errors, rerun with: -v
==42967== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

The above output excludes the compilation output and the test program's normal output.
