#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#define NUM_MIDS			24
#define NUM_HONOR			3
#define NUM_COURAGE			3
#define NUM_COMMITMENT		        3
#define RESOURCE_COUNT		        3
#define SHORT_WAIT			.5	// must be non-zero
#define BATTLE				1
#define HONOR				0
#define COURAGE				1
#define COMMITMENT			2

/*==========================================================================*/

/* Macros to encapsulate POSIX semaphore functions so they look like Stallings text code. Examples:
 * semaphore my_sem;
 * semInit(my_sem,1);
 * semWait(my_sem);
 * semSignal(my_sem);
 * semRelease(my_sem);
 * */
#define semInit(s,v)	sem_init( &s, 0, v )
#define semWait(s)		sem_wait( &s )
#define semSignal(s)	sem_post( &s )
#define semRelease(s)	sem_destroy( &s )
typedef sem_t semaphore;

/* Semaphores */
semaphore honor_sem[NUM_HONOR];
semaphore courage_sem[NUM_COURAGE];
semaphore commitment_sem[NUM_COMMITMENT];

/* Data structures to track shared resources. The number in each array represents the number of the mid thread holding the resource. When not in use, set to -1. */
int honor[NUM_HONOR];
int courage[NUM_COURAGE];
int commitment[NUM_COMMITMENT];
/* Data structures to track shared resources. The number in each array represents the number of the honor, courage, or commitment held by that mid thread. When not in use, set to -1. */
int has_honor[NUM_MIDS];
int has_courage[NUM_MIDS];
int has_commitment[NUM_MIDS];

/* Deadlock detection data structures */
int R[NUM_MIDS][RESOURCE_COUNT] = {{0}};
int C[NUM_MIDS][RESOURCE_COUNT] = {{0}};
int E[RESOURCE_COUNT] = {NUM_HONOR, NUM_COURAGE, NUM_COMMITMENT};
int A0[RESOURCE_COUNT] = {0};
int A[RESOURCE_COUNT] = {0};

bool done = false;


/*==========================================================================*/

int get_honor(int n)
{
  int i = n % NUM_HONOR;
  semWait(honor_sem[i]);
  honor[i] = n;	// Thread n finds honor i available	
  has_honor[n] = i;
  printf("mid %i got honor %i\n",n, i); fflush(stdout);
  R[n][HONOR] = 0;
  C[n][HONOR]= 1;
  return i;
}

int get_courage(int n)
{
  int i = n % NUM_COURAGE;
  semWait(courage_sem[i]);
  courage[i] = n;	// Thread n finds courage i available
  has_courage[n] = i;
  printf("mid %i got courage %i\n",n, i); fflush(stdout);
  R[n][COURAGE] = 0;
  C[n][COURAGE]= 1;
  return i;
}

int get_commitment(int n)
{
  int i = n % NUM_COMMITMENT;
  semWait(commitment_sem[i]);
  commitment[i] = n;	// Thread n finds commitment i available	
  has_commitment[n] = i;
  printf("mid %i got commitment %i\n",n, i); fflush(stdout);
  R[n][COMMITMENT] = 0;
  C[n][COMMITMENT]= 1;
  return i;
}

int drop_honor(int n)
{
  int honor_num = has_honor[n];
  has_honor[n] = -1;
  C[n][HONOR]= 0;
  honor[honor_num] = -1;	
  semSignal(honor_sem[honor_num]);
  return honor_num;
}

int drop_courage(int n)
{
  int courage_num = has_courage[n];
  has_courage[n] = -1;
  C[n][COURAGE]= 0;
  courage[courage_num] = -1;
  semSignal(courage_sem[courage_num]);
  return courage_num;
}

int drop_commitment(int n)
{
  int commitment_num = has_commitment[n];
  has_commitment[n] = -1;
  C[n][COMMITMENT]= 0;
  commitment[commitment_num] = -1;	
  semSignal(commitment_sem[commitment_num]);
  return commitment_num;
}
/*==========================================================================*/

void * deadlock_detector(void * t_num){
  bool deadlock = false;
  bool all_zero, can_run, some_just_ran;
  bool deadlocked[NUM_MIDS] = {false};
  int R_snapshot[NUM_MIDS][RESOURCE_COUNT] = {{0}};
  int C_snapshot[NUM_MIDS][RESOURCE_COUNT] = {{0}};
  int i,j,sum;

  while (!deadlock && !done) {

    // Snapshot the requests and allocations
    memcpy(R_snapshot, R, sizeof (int) * NUM_MIDS * RESOURCE_COUNT);
    memcpy(C_snapshot, C, sizeof (int) * NUM_MIDS * RESOURCE_COUNT);

    // TODO: Populate A0 using E and C_Snapshot

    for(i=0; i<RESOURCE_COUNT; ++i){//A is E-C
      sum = 0;
      for(j=0; j<NUM_MIDS; ++j)
        sum += C_Snapshot[i][j]; //sum up num of resources that all mids use
      A0[i] = E[i] - sum; 
    }
    



    // A <- A0
    memcpy(A, A0, sizeof (int) * RESOURCE_COUNT);

    // Look for a process that can run, and run it. 
    // Repeat until nothing runs.
    some_just_ran = true;
    while (some_just_ran) {

      some_just_ran = false;
      for (i=0; i<NUM_MIDS; i++) {

        // See if thread has nothing at all Claimed
        all_zero = true;
        for (j=0; j<RESOURCE_COUNT; j++) {
          if (C_snapshot[i][j] != 0) all_zero = false;
        }
        if (all_zero) {
          deadlocked[i] = false;
        }

        else {	// See if it can run

          can_run = true;
          /* TODO: evaluate all R_snapshot needs for this
           * thread -- if some needs exceed what's avaialable,
           * set can_run to false. */



          if (can_run) {
            /* TODO: Notionally 'run' the thread. Add its 
             * Claims to the Available matrix, then zero 
             * the thread's (snapshot) Requests and Claims */



            some_just_ran = true;
            deadlocked[i] = false;
          }
          else {	// thread was not able to run
            deadlocked[i] = true;
          }
        }
      }

      // Do some individual threads remain unable to run? 
      // If yes, and nothing ran this time, we have deadlocked.
      // The threads still unable to run are the deadlock set.
      if (!some_just_ran) {
        deadlock = false;
        for (i=0; i<NUM_MIDS; i++) deadlock = deadlock || deadlocked[i];
      }

    } // End 'while (some_just_ran) ' 


    // Print a report
    printf(deadlock ? "\t\t\t\t**Deadlock detected!**\n" : "\t\t\t\t**No deadlock**\n");
    if (deadlock) {

      /* print C and R for deadlocked processes */
      printf("             C        R\n");
      for (i=0; i<NUM_MIDS; i++) {
        if (deadlocked[i]) {
          printf("thread %2i: ",i);
          for (j=0; j<RESOURCE_COUNT; j++) printf("%1i ",C_snapshot[i][j]);
          printf("   ");
          for (j=0; j<RESOURCE_COUNT; j++) printf("%1i ",R_snapshot[i][j]);
          printf("\n");
        }
      }

      /* Print E, A */
      printf("\nE: ");
      for (i=0; i<RESOURCE_COUNT; i++) printf("%1i ",E[i]);
      printf("   A: ");
      for (i=0; i<RESOURCE_COUNT; i++) printf("%1i ",A[i]);
      printf("\n");
    }

    sleep(BATTLE);

  } // End 'while (!deadlock && !done)'
  return 0;
}
/*==========================================================================*/

void * mid(void * t_num) {
  int n = * (int *) t_num;

  R[n][HONOR] = 1; R[n][COURAGE] = 1; R[n][COMMITMENT] = 1; // Update request matrix R;

  /* Get Supplies */
  int r = rand() % 3;
  if (r == 0) {
    printf("mid %i getting honor %i\n", n, n % NUM_HONOR); fflush(stdout);
    get_honor(n);

    printf("mid %i getting courage %i\n", n, n % NUM_COURAGE); fflush(stdout);
    get_courage(n);

    printf("mid %i getting commitment %i\n", n, n % NUM_COMMITMENT); fflush(stdout);
    get_commitment(n);	
  }
  else if (r == 1) {
    printf("mid %i getting courage %i\n", n, n % NUM_COURAGE); fflush(stdout);
    get_courage(n);

    printf("mid %i getting commitment %i\n", n, n % NUM_COMMITMENT); fflush(stdout);
    get_commitment(n);		

    printf("mid %i getting honor %i\n", n, n % NUM_HONOR); fflush(stdout);
    get_honor(n);	
  }
  else {
    printf("mid %i getting commitment %i\n", n, n % NUM_COMMITMENT); fflush(stdout);
    get_commitment(n);

    printf("mid %i getting honor %i\n", n, n % NUM_HONOR); fflush(stdout);
    get_honor(n);

    printf("mid %i getting courage %i\n", n, n % NUM_COURAGE); fflush(stdout);
    get_courage(n);
  }

  sleep(BATTLE);

  /* Release Supplies  and finish */
  printf("mid %i released commitment %i\n", n, drop_commitment(n)); fflush(stdout);

  printf("mid %i released courage %i\n", n, drop_courage(n)); fflush(stdout);

  printf("mid %i released honor %i\n", n, drop_honor(n)); fflush(stdout);

  printf("mid %i ........... done\n", n); fflush(stdout); 

}

/*==========================================================================*/

int main( int argc, char *argv[] )
{

  int i;
  pthread_t midshipman[NUM_MIDS];
  pthread_t deadlock_detect_thread;
  int statics[NUM_MIDS];

  srand(time(NULL));

  for ( i = 0; i < NUM_HONOR; i++ ) honor[i] = -1;
  for ( i = 0; i < NUM_COURAGE; i++ ) courage[i] = -1;
  for ( i = 0; i < NUM_COMMITMENT; i++ ) commitment[i] = -1;

  /* Initialize data. Create a thread for each mid. */
  for ( i = 0; i < NUM_MIDS; i++ )
  {
    statics[i] = i;
    has_honor[i] = -1;
    has_courage[i] = -1;
    has_commitment[i] = -1;
    pthread_create( &midshipman[i], NULL, mid, &statics[i] ); 
  }

  /* Create deadlock detection thread */
  pthread_create( &deadlock_detect_thread, NULL, deadlock_detector, NULL);

  /* Wait for all mids to finish. */
  for ( i = 0; i < NUM_MIDS; i++ ) pthread_join( midshipman[i], NULL );
  done = true;

  /* Wait for detector to finish. */
  pthread_join(deadlock_detect_thread, NULL);

  /* Produce the final report. */
  printf( "All midshipmen have won the Midnite battle!\n" );

  return 0;
}
