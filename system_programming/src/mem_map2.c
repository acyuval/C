/******************************************************************************
 *	Author:    Yuval
 *	Reviewer : 
 *	Date:
 ******************************************************************************/

#include <assert.h> /* assert			  */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <ctype.h>
#include <pthread.h>

#define TRUE (1)
#define FALSE (0)
#define SUCCESS (0)
#define FAIL (-1)

#define BUFFER_SIZE (100)

#define NUM_THREADS (10 )
/******************************************************************************
 *							 DECLRATION								 		  *
 ******************************************************************************/
pthread_t consumer_id = 0;
pthread_mutex_t mutex = {0};
pthread_cond_t cond = {0};
sem_t sem = {0};
int arr[10] = {0};
char msg[25] = "what is the reason for";
int counter = 0; 
void *consumer(void *params);
void *producer(void *params);
int Start();
__thread int idds = 0;
/******************************************************************************
 *							 FUNCTIONS 										  *
 ******************************************************************************/
int main()
{
    Start();
    return 0;
}

int Start()
{
    int status = 0;
    pthread_t producer_id = 0;
    int i = 0;
    int * mall23 = malloc(100);
    sem_init(&sem, 0 , 0);
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond,NULL);

    status = pthread_create(&consumer_id, NULL, consumer, NULL);
    status = pthread_create(&consumer_id, NULL, consumer, NULL);
    if (status != SUCCESS)
    {
        return FAIL;
    }

        
    pthread_join(consumer_id, NULL);
    
 
    return SUCCESS;
}

void *consumer(void *params)
{
    int i = 0 ;
    int dest = 0;
    int sem_val= 0;

    int* p_i = &i;
    char a = 'h';
    char* p_a = &a;
    char b = 'w';
    char* p_b = &b;
    int j = 1;
    int* p_j = &j;
    int * mall = malloc(0x9876542);
    sem_wait(&sem);
}

/******************************************************************************
 *							STATIC FUNCTIONS 								  *
 ******************************************************************************/
