//Optimized version

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
  //check args
  if(argc < 2){
    fprintf(stderr, "Usage: selection <filename>\n");
    exit(1);
  }

  //open the file
  int fd = open(argv[1], O_RDONLY);

  //get the size
  size_t fdsize = lseek(fd, 0, SEEK_END);
  lseek(fd, 0, SEEK_SET);

  char* wholeFile = malloc(fdsize);
  //read in the whole file
  read(fd, wholeFile, fdsize);

  int k = 0, n = 0;
  char *cur = wholeFile;//save a pointer
  //char *next = cur;

  /*int myAtoi(char* str) 
   * { 
   *  int res = 0; // Initialize result 
   *
   *  // Iterate through all characters of input string and 
   *  // update result 
   *  for (int i = 0; str[i] != '\0'; ++i) 
   *      res = res * 10 + str[i] - '0'; 
   *
   *  // return result. 
   *  return res; 
   * } */

  //This should be a smidge faster than calling atoi
  for(;(*cur) != '\n'; ++cur)
    k = k * 10 + (*cur) - '0';

  //next++;
  //cur = next; //pointing to the first community
  cur++;

  //create an array of all the jobs names??
  //not sure if this is necessary
  char ** comNames = malloc(k * sizeof(char*));
  for(int j = 0; j < k; ++j){ //use j for communities
    comNames[j] = cur;
    for(;(*cur) != '\n'; ++cur);
    (*cur) = '\0';
    //next++;
    //cur = next;
    cur++;
  }

  for(;(*cur) != '\n'; ++cur)
    n = n * 10 + (*cur) - '0';

  //next++;
  //cur = next; //pointing to the first name
  cur++;

  char ** names = malloc(n * sizeof(char*));

  int ** selection = malloc(k * sizeof(int*));//This is a weird hack, it's gonna be ints at first but then char*s
  for(int j = 0; j < k; ++j){
    selection[j] = malloc(n * sizeof(int));
  }
  
  for(int i = 0; i < n; ++i){ //use i for names
    names[i] = cur;
    for(;(*cur) != ' '; ++cur);//go to the end of the name
    (*cur) = '\0';//null out the end of the name
    cur++;//get over the space
    for(int j = 0; j < k-1; ++j){
      int num = 0;
      for(;(*cur) != ' '; ++cur)
        num = num * 10 + (*cur) - '0';
      selection[j][num-1] = i;//cast to make the array happy
      cur++;//space
    }
    int num1 = 0;
    for(;(*cur) != '\n'; ++cur)
      num1 = num1 * 10 + (*cur) - '0';
    selection[k-1][num1-1] = i;
    cur++;//newline
  }


  //Do the selecting
  //I need an array for each job
  //selection[0] will be for job 1
  //selection[0][0] will be an index to job 1's first pick in the names array
  //then I set selection[0][0] to be the actual pointer
  //and that index in names to a null
  //if selection[j][i] is taken (i.e. that index in names array is NULL)
  //Then set selection[j][i] to NULL and inc i
  
  //This could be improved by making jobPos a linked list and not an array
  int * jobPos = calloc(k, sizeof(int));//where each job is in their pick number
  int numJobsLeft = k;//How many jobs still have choices avalible
  for(int j = 0,i;numJobsLeft > 0;){
    i = jobPos[j];//get where we are
    if(i == n){//we have gone through all the names
      j = (j+1)%k;
      continue;
    }
    int cnt = 0;
    while(42069){
      int curChoice = selection[j][i];//the k'th jobs i'th choice
      if(names[curChoice] == NULL){//taken
        //selection[j][i] = NULL;
        i++;//if that choice is taken then go to the next choice
        if(i == n){
          numJobsLeft --;
          cnt = 1;
          break;
        }
      } else {//if we found a valid person
        printf("%s %s\n", names[curChoice], comNames[j]);
        names[curChoice] = NULL;
        jobPos[j] = i;
        j = (j+1)%k;
        break;
      }
    }
  }

  return 0;
}














   

