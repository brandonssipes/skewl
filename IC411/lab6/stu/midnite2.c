#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>

#define NUM_MIDS			24
#define NUM_HONOR			3
#define NUM_COURAGE			3
#define NUM_COMMITMENT	                3
#define SHORT_WAIT			.2
#define BATTLE				2

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


/* Data structures to track shared resources. The number in each array represents the number of the midshipman thread holding the resource. When not in use, set to -1. */
int honor[NUM_HONOR];
int courage[NUM_COURAGE];
int commitment[NUM_COMMITMENT];
/* Data structures to track shared resources. The number in each array represents the number of the honor, courage, or commitment held by that midshipman thread. When not in use, set to -1. */
int has_honor[NUM_MIDS];
int has_courage[NUM_MIDS];
int has_commitment[NUM_MIDS];

// TODO: declare semaphore(s) globally
semaphore access_semaphore[3];
/*==========================================================================*/

int get_honor(int n)
{
	int i = n % NUM_HONOR;
	while (honor[i] != -1) sleep(SHORT_WAIT);
	has_honor[n] = i;
	honor[i] = n;	// Thread n finds honor i available
	printf("midshipman %i got honor %i\n",n, i); fflush(stdout);
	return i;
}

int get_courage(int n)
{
	int i = n % NUM_COURAGE;
	while (courage[i] != -1) sleep(SHORT_WAIT);
	has_courage[n] = i;
	courage[i] = n;	// Thread n finds courage i available
	printf("midshipman %i got courage %i\n",n, i); fflush(stdout);
	return i;
}

int get_commitment(int n)
{
	int i = n % NUM_COMMITMENT;
	while (commitment[i] != -1) sleep(SHORT_WAIT);
	has_commitment[n] = i;
	commitment[i] = n;	// Thread n finds commitment i available
	printf("midshipman %i got commitment %i\n",n, i); fflush(stdout);
	return i;
}

int drop_honor(int n)
{
	int key_num = has_honor[n];
	honor[key_num] = -1;
	has_honor[n] = -1;
	return key_num;
}

int drop_courage(int n)
{
	int mat_num = has_courage[n];
	courage[mat_num] = -1;
	has_courage[n] = -1;
	return mat_num;
}

int drop_commitment(int n)
{
	int book_num = has_commitment[n];
	commitment[book_num] = -1;
	has_commitment[n] = -1;
	return book_num;
}

/*==========================================================================*/

void * midshipman(void * t_num)
{
    int n = * (int *) t_num;
    
    /* Get Supplies */
    semWait(access_semaphore[n%NUM_HONOR]);
    printf("midshipman %i getting honor %i\n", n, n % NUM_HONOR); fflush(stdout);
    get_honor(n);

    printf("midshipman %i getting courage %i\n", n, n % NUM_COURAGE); fflush(stdout);
    get_courage(n);

    printf("midshipman %i getting commitment %i\n", n, n % NUM_COMMITMENT); fflush(stdout);
    get_commitment(n);	

    sleep(BATTLE);

    /* Release Supplies  and finish */
    printf("midshipman %i released commitment %i\n", n, drop_commitment(n)); fflush(stdout);

    printf("midshipman %i released courage %i\n", n, drop_courage(n)); fflush(stdout);

    printf("midshipman %i released honor %i\n", n, drop_honor(n)); fflush(stdout);

    printf("midshipman %i ........... won Midnite battle!\n", n); fflush(stdout); 

    semSignal(access_semaphore[n%NUM_HONOR]);

}

/*==========================================================================*/

int main( int argc, char *argv[] )
{
	
    int i;
    pthread_t mid[NUM_MIDS];
    int statics[NUM_MIDS];
 
	srand(time(NULL));
    
    for ( i = 0; i < NUM_HONOR; i++ ) honor[i] = -1;
    for ( i = 0; i < NUM_COURAGE; i++ ) courage[i] = -1;
    for ( i = 0; i < NUM_COMMITMENT; i++ ) commitment[i] = -1;

    /* TODO: Initialize semaphores. */
    for ( i = 0; i < NUM_HONOR; ++i) semInit(access_semaphore[i],1);


    /* Initialize data. Create a thread for each midshipman. */
    for ( i = 0; i < NUM_MIDS; i++ )
    {
		statics[i] = i;
		has_honor[i] = -1;
		has_courage[i] = -1;
		has_commitment[i] = -1;
		pthread_create( &mid[i], NULL, midshipman, &statics[i] ); 
    }

    /* TODO: Wait for all midshipman threads to finish. */
    for ( i = 0; i < NUM_MIDS; i++ ) pthread_join( mid[i], NULL );

    /* TODO: Release semaphores. */
    for ( i = 0; i < NUM_HONOR; ++i) semRelease(access_semaphore[i]);


    /* Produce the final report. */
    printf( "All midshipmen have won the Midnite battle!\n" );

    return 0;
}
