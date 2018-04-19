/* SI335 Spring 2018 
 * Project 2: ~~~~~~~~
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <list>
#include <string>
#include <cmath>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

struct Coord{
  int row;
  int col;
};

struct Node {
  struct Node* next;
  int row;
  int col;
};
void push(struct Node**,int,int);
void print_list(struct Node*);

int main(int argc, char** argv){
  if (argc < 2) {
    std::cerr << "usage: part1 <filename>\n";
    exit(7);
  }

  std::ifstream fin(argv[1]);
  if (!fin) {
    std::cerr << "Error: file \"" << argv[1] << "\" could not be opened!" << std::endl;
    exit(8);
  }
  
  int row, col;
  fin >> row >> col;
  fin.ignore(1024, '\n');

  Node **LL = new Node*[col]; 

  char direction[col]; 
  int string = 0;
  int middle = row/2;
  int end = col;
  int bound = row;
  do{
    fin >> row >> col;
    if(!fin) break;
    push(&LL[col], row, col);
  } while(true);

  Coord pos;
  pos.row = middle;
  pos.col = 0;
  int found = 0;
  //determine if it is in scope if: the row <= (col - pos.col)  + pos.row && row >= (col - pos.col) - pos.row
  Coord best;
  Node*cur;
  for(int col = 1; col < end; ++col){
    cur = LL[col];
    best.row = -1;
    do{
      if(cur == NULL)
        break;
      if(!(cur->row <= (col - pos.col) + pos.row && cur->row >= pos.row - (col - pos.col))) //check for scope
        continue;
      if(best.row == -1){
        best.row = cur->row;
      }
      if(abs(cur->row - middle) < abs(best.row - middle)){
        best.row = cur->row;
        best.col = cur->col;
        found = 1;
      }else if(abs(cur->row - middle) == abs(best.row - middle) && cur->row <= best.row){
        best.row = cur->row;
        best.col = cur->col;
        found = 1;
      }
    }while((cur = cur->next));
    if(found){
      while(pos.row < best.row){
        pos.row++;
        pos.col++;
        direction[string++] = 'D';
      }
      while(pos.row > best.row){
        pos.row--;
        pos.col++;
        direction[string++] = 'U';
      }
      while(pos.col < best.col){
        pos.col++;
        direction[string++] = 'S';
      }
      found = 0;
    }
  }

  while(pos.col < end){
    pos.col++;
    direction[string++] = 'S';
  }
  direction[end-1] = '\00';
  printf("%s\n", direction);
}

void push(struct Node** head, int r, int c){
  struct Node* newNode = new Node;
  newNode->row = r;
  newNode->col = c;
  newNode->next = *head;
  *head = newNode;
}
void print_list(struct Node* cur){
  while(cur){
    printf("coord = %d, %d\n", cur->row, cur->col);
    cur=cur->next;
  }
}
