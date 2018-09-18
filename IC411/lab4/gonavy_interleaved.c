#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NTHREADS 10
void *army_function(void *);
void *navy_function(void *);

int statics[NTHREADS];      // will be initialized to 1,2,3...etc.
int army_scores[NTHREADS];     // will be initialized to 0
int navy_scores[NTHREADS];     // will be initialized to 0
pthread_mutex_t lock;

int main()
{
   // TODO: declare two arrays of threads, one each for army and navy threads.
   //   Array size should be NTHREADS.


  pthread_t navy[NTHREADS];
  pthread_t army[NTHREADS];


  int i, j;

  srand(time(NULL));

  // Initialize the scores and the static numeric array
  for(i=0; i < NTHREADS; i++)
  {
    statics[i] = i;
    army_scores[i] = 0;
    navy_scores[i] = 0;
  }   

  /* The statics[] array is useful because &i may increment
     before it is referenced, resulting in the wrong thread_num being assigned.
     We use &statics[i] instead of &i to initalize the (common) thread number. */

  // TODO: Create the Army threads. 
  for(i=0; i < NTHREADS; ++i){
    pthread_create( &army[i], NULL, army_function, &statics[i]);
    pthread_create( &navy[i], NULL, navy_function, &statics[i]);
  }



  // TODO: Join all Army threads when complete
  for(j = 0; j < NTHREADS; ++j){
    pthread_join(army[j], NULL);
    pthread_join(navy[j], NULL);
  }



  // Reveal final scores
  printf("Final scores:\n");
  for(i=0; i < NTHREADS; i++)
  {
    printf("Thread:%d Navy:%d, Army:%d\n", i, navy_scores[i], army_scores[i]);
  }    
}

void *army_function(void * arg)
{
  pthread_mutex_lock(&lock);
  // thread_num is a "common" thread index between 0 and (NTHREADS-1)	
  int thread_num = * (int *) arg;


  // TODO: Give Army a random integer score between 0 and 100
  army_scores[thread_num] = (rand() % 99) + 1;

  pthread_mutex_unlock(&lock);
  return NULL;


}

void *navy_function(void * arg)
{
  int thread_num = * (int *) arg;
  while(army_scores[thread_num] == 0);

  pthread_mutex_lock(&lock);
    
  // thread_num is a "common" thread index between 0 and (NTHREADS-1)

  // TODO: Give Navy double the score of Army for this thread
  navy_scores[thread_num] = army_scores[thread_num] * 2;
  pthread_mutex_unlock(&lock);

  return NULL;

}
