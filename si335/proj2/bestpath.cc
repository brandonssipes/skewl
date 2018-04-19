#include <iostream>
#include <fstream>
#include <cmath>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

int** maxpot(int Nc, int Nr, int** cp);
void bestpath(int Nc, int Nr, int** pot);

int main(int argc, char *argv[]){
  int i,j,Nr,Nc;
  int row, col;

  if (argc < 2) {
    cerr << "usage: part1 <filename>\n";
    exit(7);
  }

  ifstream fin(argv[1]);
  if (!fin) {
    cerr << "Error: file \"" << argv[1] << "\" could not be opened!" << endl;
    exit(8);
  }
  // file input setup
  
  fin >> Nr >> Nc;
  fin.ignore(1024, '\n');
  // getting rows and columns

  int** cp = (int**)calloc(size_t(Nc),sizeof(int*));
  for(i=0; i<Nc;++i)
    cp[i] = (int*)calloc(size_t(Nr),sizeof(int));
  // creating checkpoint array

  do{
    fin >> row >> col;
    if(!fin) break;
    cp[col][row] = 1;
  } while(true);
  // reading in checpoints and inserting them into the array

  int** potential = maxpot(Nc,Nr,cp);
  // creating table of the max potential of checkpoints 
  // rachable from any one point

  bestpath(Nc,Nr,potential);
  // outputs the actual best path

  
  return 0;
}

int** maxpot(int Nc, int Nr, int** cp){
  int i,j;
  int u,s,d;

  int** pot = (int**)calloc(size_t(Nc+1),sizeof(int*));
  for(i=0; i<Nc+1;++i)
    pot[i] = (int*)calloc(size_t(Nr),sizeof(int));
  // creating the array of potential reachable checkpoints

  for(i=Nc-1;i>=0;--i){
    s=pot[i+1][0];
    d=pot[i+1][1];

    pot[i][0] = cp[i][0] + max(s,d);
    // unrolled for row 0

    for(j=1;j<Nr-1;++j){
      u=pot[i+1][j-1];
      s=pot[i+1][j];
      d=pot[i+1][j+1];

      pot[i][j] = cp[i][j] + max(u,max(s,d));
    }
    // geting the potential of spaces that are able to be moved to and then
    // adding one to the max if the current point is a checkpoint

    u=pot[i+1][Nr-2];
    s=pot[i+1][Nr-1];

    pot[i][Nr-1] = cp[i][Nr-1] + max(u,s);
    // unrolled for row Nr-1

  }// assigning potential reachable checkpoints from right to left

  return pot;
}

void bestpath(int Nc, int Nr, int** pot){
  int i=0;
  int j=Nr/2;
  // initalizing starting point
  int u,s,d;

  while(i<Nc-1){
    u = (j>0?pot[i+1][j-1]:0);
    s = pot[i+1][j];
    d = (j<Nr?pot[i+1][j+1]:0);
    int maxval = max(u,max(s,d));
    // getting the maximum checkpoints abailable after next step

    if(maxval==s)
      write(1,"S",1);
    else if(maxval==u){
      write(1,"U",1);
      --j;
    }else{
      write(1,"D",1);
      ++j;
    }// choosing which move to take, moving position up or down as needed

    ++i;
    // moving position right
  }
  write(1,"\n",1);
}
