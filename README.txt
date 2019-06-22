
    Solve the classic 9x9 Sudoku puzzle

   Partially filled-out input boards are either compiled into the
   program, or are read from the standard input file as 9 lines,
   each with 9 characters that are the digits 1-9, or blank.
   
   A typical invocation from the command line might be:
       sudoku  <test.txt

   It finds all possible solutions, so if you give it
   a completely blank input board it will try to generate
   6,670,903,752,021,072,936,960 of them!

   L. Shustek, 6/19/2019
   

C:\data\projects\sudoku\Release>sudoku <test.txt
Sodoku solver

input board:
2 6   | 7 1   |
8 7   |       |   1
1     |     5 |     2
------|-------|------
  2   |     1 |   3 4
      |       |
4 1   | 2     |   6
------|-------|------
6     | 1     |     3
  4   |       |   5 9
      |   9 3 |   7 6

solution 1:
2 6 5 | 7 1 4 | 3 9 8
8 7 4 | 9 3 2 | 6 1 5
1 3 9 | 8 6 5 | 7 4 2
------|-------|------
9 2 6 | 5 7 1 | 8 3 4
7 5 8 | 3 4 6 | 9 2 1
4 1 3 | 2 8 9 | 5 6 7
------|-------|------
6 9 2 | 1 5 7 | 4 8 3
3 4 7 | 6 2 8 | 1 5 9
5 8 1 | 4 9 3 | 2 7 6
There was 1 solution found with 12 guesses and 6-deep recursion.

input board:
    3 |       |
8 6   | 1 5   |
      | 4   2 | 6 7
------|-------|------
  8 9 |       | 2   1
      | 3 8 1 |
7   1 |       | 4 8
------|-------|------
  1 7 | 8   3 |
      |   1 5 |   2 9
      |       | 8   3

solution 1:
2 7 3 | 9 6 8 | 1 5 4
8 6 4 | 1 5 7 | 3 9 2
1 9 5 | 4 3 2 | 6 7 8
------|-------|------
6 8 9 | 5 7 4 | 2 3 1
4 5 2 | 3 8 1 | 9 6 7
7 3 1 | 2 9 6 | 4 8 5
------|-------|------
9 1 7 | 8 2 3 | 5 4 6
3 4 8 | 6 1 5 | 7 2 9
5 2 6 | 7 4 9 | 8 1 3
solution 2:
4 7 3 | 9 6 8 | 1 5 2
8 6 2 | 1 5 7 | 3 9 4
1 9 5 | 4 3 2 | 6 7 8
------|-------|------
6 8 9 | 5 7 4 | 2 3 1
2 5 4 | 3 8 1 | 9 6 7
7 3 1 | 2 9 6 | 4 8 5
------|-------|------
9 1 7 | 8 2 3 | 5 4 6
3 4 8 | 6 1 5 | 7 2 9
5 2 6 | 7 4 9 | 8 1 3
solution 3:
4 7 3 | 9 6 8 | 1 5 2
8 6 2 | 1 5 7 | 3 9 4
1 9 5 | 4 3 2 | 6 7 8
------|-------|------
6 8 9 | 5 7 4 | 2 3 1
5 2 4 | 3 8 1 | 9 6 7
7 3 1 | 2 9 6 | 4 8 5
------|-------|------
9 1 7 | 8 2 3 | 5 4 6
3 4 8 | 6 1 5 | 7 2 9
2 5 6 | 7 4 9 | 8 1 3
There were 3 solutions found with 6 guesses and 3-deep recursion.

