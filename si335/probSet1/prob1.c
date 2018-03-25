#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct pair{
  int a;
  int b;
  char DNE;
};

struct pair sumsq(int);

int main(int argv, char* argv[]){
  sumsq(argv[1]);
}

struct pair sumsq(int n){
  struct pair answer;
  answer.a = 0;
  answer.b = 0;
  char DNS = 'F';
  for (int i = 0; i < int(sqrt(n)/2); ++i){
    answer.a = i*i;
    answer.b = n - answer.a;
    if(sqrt(b) - int(sqrt(b)))
      continue;
    else
      break
  }
  return answer;
}

