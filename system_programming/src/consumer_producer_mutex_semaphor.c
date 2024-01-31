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
#include <sys/wait.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <ctype.h>
#include <pthread.h>
#include <stdatomic.h>
#include <semaphore.h>

#include "dll.h"

#define TRUE (1)
#define FALSE (0)
#define SUCCESS (0)
#define FAIL (-1)
#define READER (1)
#define WRITER (-1)
#define BUFFER_SIZE (10000)

#define NUM_THREADS (1 )
/******************************************************************************
 *							 DECLRATION								 		  *
 ******************************************************************************/

dll_t *dll = NULL;
int arr[BUFFER_SIZE];
pthread_mutex_t mutex = {0};
sem_t sem = {0};
size_t index = 0 ;
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
    pthread_t producer_id[NUM_THREADS] = {0};
    pthread_t consumer_id[NUM_THREADS] = {0};
    int i = 0;

    dll = DLLCreate();
    sem_init(&sem, 0 , 0);

    pthread_mutex_init(&mutex, NULL);

    for (i = 0; i < BUFFER_SIZE; ++i)
    {
        arr[i] = i;
    }

    for (i = 0; i < NUM_THREADS; ++i)
    {
        status = pthread_create(&consumer_id[i], NULL, consumer, NULL);
        if (status != SUCCESS)
        {
            return FAIL;
        }
        status = pthread_create(&producer_id[i], NULL, producer, NULL);
        if (status != SUCCESS)
        {
            return FAIL;
        }
    }

    for (i = 0; i < NUM_THREADS; ++i)
    {
        pthread_join(producer_id[i], NULL);
        pthread_join(consumer_id[i], NULL);
    }
    
    return SUCCESS;
}

void *consumer(void *params)
{
    size_t sum = 0;
    int i = 0; 
    (void)params;
    while (1)
    {
        sem_wait(&sem);
        printf("dll size:%ld\n", DLLSize(dll));
        sum = *(int *)DLLPopfront(dll);
        printf("res: %ld\n", sum); 


    }

}

void *producer(void *params)
{
    int i = 0;
    int sem_val = 0;
    while (1)
    {
        pthread_mutex_lock(&mutex);
        if (DLLSize(dll) == BUFFER_SIZE)
        {
            index = 0;
            pthread_mutex_unlock(&mutex);
            continue;
        }
        DLLPushback(dll,(void *)&arr[index]);
        ++index;
        for (i = 0 ; i < 100000000; ++i); 
        sem_post(&sem);
        pthread_mutex_unlock(&mutex);
    }
}
/******************************************************************************
 *							STATIC FUNCTIONS 								  *
 ******************************************************************************/
