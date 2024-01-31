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

#define NUM_THREADS (4)
/******************************************************************************
 *							 DECLRATION								 		  *
 ******************************************************************************/
pthread_t consumer_id[NUM_THREADS] = {0};
pthread_mutex_t mutex = {0};
sem_t sem = {0};
char msg[23] = "what is the reason for";
int counter = 0; 
void *consumer(void *params);
void *producer(void *params);
int Start();
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

    sem_init(&sem, 0 , 0);
    pthread_mutex_init(&mutex, NULL);
    for (i = 0; i < NUM_THREADS; ++i)
    {
        status = pthread_create(&consumer_id[i], NULL, consumer, NULL);
        if (status != SUCCESS)
        {
            return FAIL;
        }

    }

    status = pthread_create(&producer_id, NULL, producer, NULL);
    if (status != SUCCESS)
    {
        return FAIL;
    }

    pthread_join(producer_id, NULL);

    return SUCCESS;
}

void *consumer(void *params)
{
    int i = 0 ;
    int dest = 0;
    (void)params;
    pthread_mutex_lock(&mutex);
    sem_wait(&sem);
    printf("consumer : %s\n", msg); 
    pthread_mutex_unlock(&mutex);
}

void *producer(void *params)
{
    int i = 0;
    (void)params;
    while(i < NUM_THREADS)
    {
        strcpy(msg, "actually this is the str");
        sem_post(&sem);
        i++;
    }
    for (i = 0; i < NUM_THREADS; ++i)
    {
        pthread_join(consumer_id[i], NULL);
    }
}
/******************************************************************************
 *							STATIC FUNCTIONS 								  *
 ******************************************************************************/
