// sudoku.c
/*----------------------------------------------------------------------------------

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
-------------------------------------------------------------------------------------*/
/* Copyright(c) 2019, Len Shustek
The MIT License(MIT)
Permission is hereby granted, free of charge, to any person obtaining a copy of this software
and associated documentation files(the "Software"), to deal in the Software without
restriction, including without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include <sys/types.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <limits.h>
#include <stddef.h>
typedef unsigned char byte;

struct board_t {
   byte val[9][9]; };

struct choices_t {
   int first_choice;
   bool val[9]; };

int num_solutions, recursion_depth, max_depth, num_guesses;

void assert(bool b, char *msg) {
   if (!b) {
      printf("*ERROR*: %s\n", msg);
      exit(8); } }

void print_board(struct board_t *b) {
   for (int row = 0; row < 9; ++row) {
      for (int col = 0; col < 9; ++col) {
         if (b->val[row][col] == 0) printf("  ");
         else printf("%u ", b->val[row][col]);
         if (col == 2 || col == 5) printf("| "); }
      printf("\n");
      if (row == 2 || row == 5) printf("------|-------|------\n"); } }

int get_choices(struct board_t *b, int row, int col, struct choices_t *choices) {
   // return an array indicating the possible choices for this cell
   int chkrow, chkcol;
   for (int choice = 0; choice < 9; ++choice) choices->val[choice] = true; // assume all are possible
#define update_map(row,col) if (b->val[row][col] != 0) choices->val[b->val[row][col]-1] = false
   for (chkrow = 0; chkrow < 9; ++chkrow) // look at all rows in the cell's column
      update_map(chkrow, col);
   for (chkcol = 0; chkcol < 9; ++chkcol) // look at all columns in the cell's row
      update_map(row, chkcol);
   int sqrow = (row / 3) * 3; // upper left corner of the cell's square
   int sqcol = (col / 3) * 3;
   for (int incrow = 0; incrow < 3; ++incrow)  // look at all numbers in the square
      for (int inccol = 0; inccol < 3; ++inccol)
         update_map(sqrow + incrow, sqcol + inccol);
   int num_choices = 0; // see how many there were, and identify one of them
   for (int choice = 0; choice < 9; ++choice)
      if (choices->val[choice]) {
         choices->first_choice = choice + 1;
         ++num_choices; }
   return num_choices; }

bool solve_board(struct board_t brd, bool log, int depth) {
   bool progress;
   int cells_done;
   int bestrow, bestcol, bestnumchoices;
   int num_passes = 0;
   if (depth > max_depth) max_depth = depth;
   do { // fill in all the determined cells
      if (log) printf("pass %d\n", ++num_passes);
      progress = false;
      cells_done = 0;
      bestnumchoices = INT_MAX;
      for (int row = 0; row < 9; ++row)
         for (int col = 0; col < 9; ++col)
            if (brd.val[row][col] == 0) {
               struct choices_t choices;
               int num_choices = get_choices(&brd, row, col, &choices);
               if (num_choices == 0) {
                  if (log) printf("no choices for cell %d %d\n", row, col);
                  return false; } // unsolvable board
               if (log) {
                  printf("    cell %d %d has %d choices: ", row, col, num_choices);
                  for (int choice = 0; choice < 9; ++choice)
                     if (choices.val[choice]) printf(" %d", choice + 1);
                  printf("\n"); }
               if (num_choices == 1) { // exactly one possibility for this cell
                  brd.val[row][col] = choices.first_choice; // choose it
                  if (log) printf("  cell %d %d is %d\n", row, col, brd.val[row][col]);
                  ++cells_done;
                  progress = true; }
               else { //remember the cell with the least multiple possibilities
                  if (num_choices < bestnumchoices) {
                     bestrow = row; bestcol = col;
                     bestnumchoices = num_choices; } } }
            else ++cells_done; }
   while (progress && cells_done != 9*9);

   if (cells_done == 9*9) { // all cells were determined: an easy board!
      ++num_solutions;
      printf("solution %d:\n", num_solutions);
      print_board(&brd);
      return true; }

   if (bestnumchoices < INT_MAX) { // pick the cell with the least multiple possibilities
      struct choices_t choices;
      int num_choices = get_choices(&brd, bestrow, bestcol, &choices);
      assert(num_choices == bestnumchoices, "bad num_choices");
      assert(brd.val[bestrow][bestcol] == 0, "cell not zero");
      ++recursion_depth;
      for (int choice = 0; choice < 9; ++choice) // generate a board with each possibility
         if (choices.val[choice]) {
            ++num_guesses;
            brd.val[bestrow][bestcol] = choice + 1;
            if (log) printf("trying with cell %d %d as %d\n", bestrow, bestcol, choice + 1);
            solve_board(brd, log, depth+1); // recursively try to solve that board
         }
      if (num_solutions > 0) return true; // we had at least one recursively solved board
   }
   return false; }

void do_board(struct board_t *b, bool log) {
   printf("input board:\n");
   print_board(b);
   printf("\n");
   num_solutions = num_guesses = recursion_depth = max_depth = 0;
   if (solve_board(*b, log, 0)) {
      if (num_solutions == 1)
         printf("There was 1 solution found with %d guesses and %d recursions of maximum depth %d.\n",
                num_guesses, recursion_depth, max_depth);
      else printf("There were %d solutions found with %d guesses and %d recursions of maximum depth %d.\n",
                     num_solutions, num_guesses, recursion_depth, max_depth); }
   else printf("There is no solution\n"); }

bool input_board(FILE *fid, struct board_t *b) {
   // Read a board: either 9 lines of 9 characters (0, 1, blank)
   // or . rcv rcv rcv...   where r=row, c=col, v=value
   char line[200]; // code here is NOT buffer-overrun safe
   memset(b, 0, sizeof(struct board_t));
   printf("\n");
   do { // read the first line
      memset(line, 0, sizeof(line));
      if (!fgets(line, sizeof(line), fid)) return false;
      if (line[0] == '#') printf("%s", line); }
   while (strlen(line) <= 1  // skip initial null lines
          // (An empty top line needs therefore to have at least one blank)
          || line[0] == '#');  // and comment lines
   if (line[0] == '.') { // rcv... format
      char *ptr = line + 1;
      while (1) {
         int row, col, val, numch;
         if (sscanf(ptr, "%1d%1d%1d%n", &row, &col, &val, &numch) != 3) break;
         b->val[row-1][col-1] = val;
         ptr += numch; } }
   else { // 9 rows of 9 format
      for (int row = 0; row < 9; ++row) {
         if (strlen(line) > 10) return false; // max 9 chars plus newline
         for (int col = 0; col < 9; ++col) {
            char ch = line[col];
            if (ch == ' ' || iscntrl(ch)) ch = 0;  // blank, newline, or null
            else {
               if (ch < '1' || ch > '9') return false; // otherwise only allow digits
               ch = ch - '0'; }
            b->val[row][col] = ch; }
         if (row < 8) {
            memset(line, 0, sizeof(line));
            if (!fgets(line, sizeof(line), fid)) return false; } } }
   return true; }

int main() {
   static struct board_t testb1 = { // 1 solution
      0,9,0, 0,6,7, 0,4,8,
      0,0,0, 0,0,5, 1,0,0,
      7,3,5, 0,0,1, 0,0,0,

      0,6,0, 0,2,8, 3,0,4,
      0,8,4, 0,0,0, 2,5,0,
      3,0,1, 4,5,0, 0,9,0,

      0,0,0, 5,0,0, 6,2,1,
      0,0,6, 7,0,0, 0,0,0,
      4,5,0, 6,1,0, 0,8,0  };

   static struct board_t testb2 = { // 3 solutions
      0,0,3, 0,0,0, 0,0,0,
      8,6,0, 1,5,0, 0,0,0,
      0,0,0, 4,0,2, 6,7,0,

      0,8,9, 0,0,0, 2,0,1,
      0,0,0, 3,8,1, 0,0,0,
      7,0,1, 0,0,0, 4,8,0,

      0,1,7, 8,0,3, 0,0,0,
      0,0,0, 0,1,5, 0,2,9,
      0,0,0, 0,0,0, 8,0,3 };

   static struct board_t testb3 = { // 67 solutions
      0,0,0, 0,0,0, 0,0,0,
      0,0,0, 1,5,0, 0,0,0,
      0,0,0, 4,0,2, 6,7,0,

      0,8,9, 0,0,0, 2,0,1,
      0,0,0, 3,8,1, 0,0,0,
      7,0,1, 0,0,0, 4,8,0,

      0,1,7, 8,0,3, 0,0,0,
      0,0,0, 0,1,5, 0,2,9,
      0,0,0, 0,0,0, 8,0,3 };

   printf("Sodoku solver\n");

   //do_board(&testb1, false);    // do compiled-in test boards
   //do_board(&testb2, false);
   //do_board(&testb3, false);

   struct board_t b;
   while (input_board(stdin, &b))  // get multiple boards from standard input
      do_board(&b, false);

   return 0; }

