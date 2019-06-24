
Solve the classic 9x9 Sudoku puzzle

Partially filled-out input boards are either compiled into the program
or are read from the standard input file in the following format:
  - before each board: empty lines, or comment lines starting with '#'
  - each board can be in one of two formats:
    -  9 lines, each with 9 characters that are the digits 1-9 or blank
    -  1 line starting with '.', then multiple blank-separated 3-digit numbers
       like "rcv", where r=row, c=col, v=value for that cell

 A typical invocation from the command line might be:
     sudoku <test.txt
 where test.txt contains

    #The wikipedia example: 1 solution found with no guessing
   . 115 123 157 216 241 259 265 329 338 386 418 456 493 514 548 563 591 617 652 696 726 772 788 844 851 869 895 958 987 999

   # This has 1 solution found after 12 guesses
   26 71
   87     1 
   1    5  2
    2   1 34

   41 2   6 
   6  1    3
    4     59
       93 76

   #This has 3 solutions found after 6 guesses
     3      
   86 15    
      4 267 
    89   2 1
      381   
   7 1   48 
    178 3   
       15 29
         8 3

   # Reportedly "the hardest one known for a human"
   # This has 1 solution found after 3598 guesses
   .118 233 246 327 359 372 425 467 554 565 577 641 683 731 786 798 838 845 881 929 974

The program finds all possible solutions, so if you give it
a completely blank input board it will try to generate
6,670,903,752,021,072,936,960 of them!

L. Shustek, 6/19/2019
Updated 6/23/2019


C:\data\projects\sudoku\Debug>sudoku <test.txt
Sodoku solver

#The wikipedia example: 1 solution found with no guessing
input board:
5 3   |   7   |
6     | 1 9 5 |
  9 8 |       |   6
------|-------|------
8     |   6   |     3
4     | 8   3 |     1
7     |   2   |     6
------|-------|------
  6   |       | 2 8
      | 4 1 9 |     5
      |   8   |   7 9

solution 1:
5 3 4 | 6 7 8 | 9 1 2
6 7 2 | 1 9 5 | 3 4 8
1 9 8 | 3 4 2 | 5 6 7
------|-------|------
8 5 9 | 7 6 1 | 4 2 3
4 2 6 | 8 5 3 | 7 9 1
7 1 3 | 9 2 4 | 8 5 6
------|-------|------
9 6 1 | 5 3 7 | 2 8 4
2 8 7 | 4 1 9 | 6 3 5
3 4 5 | 2 8 6 | 1 7 9
There was 1 solution found with 0 guesses and 0 recursions of maximum depth 0.

# This has 1 solution found after 12 guesses
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
There was 1 solution found with 12 guesses and 6 recursions of maximum depth 3.

#This has 3 solutions found after 6 guesses
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
There were 3 solutions found with 6 guesses and 3 recursions of maximum depth 2.

# Reportedly "the hardest one known for a human"
# This has 1 solution found after 3598 guesses
input board:
8     |       |
    3 | 6     |
  7   |   9   | 2
------|-------|------
  5   |     7 |
      |   4 5 | 7
      | 1     |   3
------|-------|------
    1 |       |   6 8
    8 | 5     |   1
  9   |       | 4

solution 1:
8 1 2 | 7 5 3 | 6 4 9
9 4 3 | 6 8 2 | 1 7 5
6 7 5 | 4 9 1 | 2 8 3
------|-------|------
1 5 4 | 2 3 7 | 8 9 6
3 6 9 | 8 4 5 | 7 2 1
2 8 7 | 1 6 9 | 5 3 4
------|-------|------
5 2 1 | 9 7 4 | 3 6 8
4 3 8 | 5 2 6 | 9 1 7
7 9 6 | 3 1 8 | 4 5 2
There was 1 solution found with 3598 guesses and 1799 recursions of maximum depth 21.


