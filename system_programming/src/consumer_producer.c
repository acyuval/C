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

#include "dll.h"

#define TRUE (1)
#define FALSE (0)
#define SUCCESS (0)
#define FAIL (-1)
#define READER (1)
#define WRITER (-1)
#define BUFFER_SIZE (100)

#define NUM_THREADS (4)
/******************************************************************************
 *							 DECLRATION								 		  *
 ******************************************************************************/
struct params
{
    dll_t *dll;
    int arr[BUFFER_SIZE];
    pthread_mutex_t *mutex;
    int index;
    atomic_int flag;
};

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
    dll_t *dll = NULL;
    int status = 0;
    pthread_t producer_id[NUM_THREADS] = {0};
    pthread_t consumer_id[NUM_THREADS] = {0};
    struct params param = {0};
    pthread_mutex_t mutex = {0};
    int i = 0;
    dll = DLLCreate();
    param.dll = dll;
    param.index = 0;
    status = pthread_mutex_init(&mutex, NULL);
    param.flag = 1;
    param.mutex = &mutex;

    for (i = 0; i < BUFFER_SIZE; ++i)
    {
        param.arr[i] = i;
    }

    for (i = 0; i < NUM_THREADS; ++i)
    {
        status = pthread_create(&consumer_id[i], NULL, consumer, (void *)&param);
        if (status != SUCCESS)
        {
            return FAIL;
        }
        status = pthread_create(&producer_id[i], NULL, producer, (void *)&param);
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
    struct params *param = (struct params *)params;
    size_t sum = 0;
    size_t sum_of_sum = 0;
    while (1)
    {
        while (DLLIsEmpty(param->dll) == TRUE)
        {
            pthread_mutex_unlock(param->mutex);
            sleep(0);
            pthread_mutex_lock(param->mutex);
        }

        sum = *(int *)DLLPopfront(param->dll);
        printf("val : %ld , %ld \n", sum, pthread_self());
        pthread_mutex_unlock(param->mutex);
    } 
}

void *producer(void *params)
{
    struct params *param = (struct params *)params;

    while (1)
    {
        pthread_mutex_lock(param->mutex);
        if((param->index) >= BUFFER_SIZE)
        {
            param->index = 0;
            pthread_mutex_unlock(param->mutex);
            break;
        }
        DLLInsert(param->dll, DLLEnd(param->dll), (void *)&param->arr[param->index]);
        ++(param->index);

        pthread_mutex_unlock(param->mutex);
    }
}
/******************************************************************************
 *							STATIC FUNCTIONS 								  *
 ******************************************************************************/
