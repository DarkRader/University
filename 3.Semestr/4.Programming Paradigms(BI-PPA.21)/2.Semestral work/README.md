# Sudoku solver

The program solves Sudoku of any size in the form ({n^2 * n^2 | n ≥ 1}). She solves the correct Sudokus and makes checks in all possible ways to put the number in the right place to which it belongs. The program first includes preparatory functions, and then solutions for the grid, row and column. There are also several other checks, for greater accuracy of the solution for all cases

## Example usage

You can set the Sudoku matrix manually or write a function in the form:

(define any-sudoku

                    '((5 0 0  0 4 0  0 9 0)
                      (0 6 4  8 2 0  1 0 0)
                      (0 0 3  1 5 7  0 6 4)
                   
                      (0 2 8  0 0 0  4 7 0)
                      (0 4 6  0 9 1  8 5 0)
                      (0 5 7  2 8 0  6 1 0)
                   
                      (2 8 0  6 1 5  3 0 0)
                      (0 0 5  0 7 8  9 2 0)
                      (0 7 0  0 3 0  0 0 6)))
                      
After that, it is enough to use the following function:

(SudokuSolver (name your sudoku function or write it manually))

The main thing is to set the correct size and numbers in your Sudoku.

At the end, the program will simply output you the answer.
