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

#include "Cbuffer.h"

#define TRUE (1)
#define FALSE (0)
#define SUCCESS (0)
#define FAIL (-1)

#define BUFFER_SIZE (100)

#define NUM_THREADS (4)
/******************************************************************************
 *							 DECLRATION								 		  *
 ******************************************************************************/

buffer_t *buffer = NULL;
int arr[BUFFER_SIZE];
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
    pthread_t producer_id[NUM_THREADS] = {0};
    pthread_t consumer_id[NUM_THREADS] = {0};
    int i = 0;

    buffer = BufferCreate(BUFFER_SIZE*sizeof(int));

    for (i = 0; i < BUFFER_SIZE; ++i)
    {
        arr[i] = i;
    }

    for (i = 0; i < NUM_THREADS; ++i)
    {
        status = pthread_create(&consumer_id[i], NULL, consumer, &arr[i]);
        if (status != SUCCESS)
        {
            return FAIL;
        }
        status = pthread_create(&producer_id[i], NULL, producer,NULL);
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
    int i = 0 ;
    int dest = 0;
    (void)params;
    while (1)
    {
        BufferRead(&dest, buffer,sizeof(int));
        printf("consume : %d by %d\n", dest, *(int *)params); 
        for (i = 0 ; i < 100000000; ++i);
    }
}

void *producer(void *params)
{
    (void)params;
    while (1)
    {
        BufferWrite(&counter, buffer , sizeof(int));
        ++counter;
    }
    
}
/******************************************************************************
 *							STATIC FUNCTIONS 								  *
 ******************************************************************************/
