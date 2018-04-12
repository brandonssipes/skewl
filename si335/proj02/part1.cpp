/* SI335 Spring 2018 
 * Project 2: ~~~~~~~~
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <list>

struct Coord{
  int x;
  int y;
};
int buffer = 1024;

int main(int argc, char** argv){
  if (argc < 2) {
    std::cerr << "usage: part1 <filename>\n";
    exit(1);
  }

  std::ifstream fin(argv[1]);
  if (!fin) {
    std::cerr << "Error: file \"" << argv[1] << "\" could not be opened!" << std::endl;
    exit(2);
  }
  
  int row, col;
  fin >> row >> col;
  printf("row = %d, col = %d\n", row, col);
  fin.ignore(1024, '\n');

  bool matrix[row][col];

  
  //We can use bascially an adjacency list where there is an array of BSTs
  //the array is gonna be size col 
  //each time we read in we will O(1) go to that column and add to the BST a node for that row
  //Then for that lookup we O(1) go to the column that we want to look at and O(lg(r)) look for that key point

  for(int i = 0; i < row; ++i)
    for(int j = 0; j < col; ++j)
      matrix[i][j] = false;

  int start = row/2;
  int end = col;
  int bound = row;
  do{
    fin >> row >> col;
    if(!fin) break;
    matrix[row][col] = true;
  } while(true);

  int pos = 0;
  col = 0;
  row = start;
  int mask;
  while(col+1 < end){
    mask = 0;
    col++;
    if(row > 0 && matrix[row-1][col]) mask += 1;
    if(matrix[row][col]) mask += 2;
    if(row < bound-1 && matrix[row+1][col]) mask += 4;
    switch(mask){
      case 0:
      case 2:
        break;
      case 1:
        row--;
        break;
      case 3:
        if(abs(row - start) >= abs(row-1 - start))
          row--;
        break;
      case 4:
        row++;
        break;
      case 5:
        if(abs(row +1 -start) >= abs(row-1 - start))
          row--;
        else
          row++;
        break;
      case 6:
        if(abs(row - start) > abs(row + 1 - start))
          row++;
        break;
      case 7:
        if(abs(row - start) > abs(row - 1 - start))
          row--;
        else if(abs(row - start) > abs(row+1 - start))
          row++;
        break;
    }
  }
  return 0;
}
