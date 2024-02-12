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
#include <sys/sem.h>
#include <ctype.h>
#include <pthread.h> 
#include <stdatomic.h> 
#include <semaphore.h>

#define TRUE (1)
#define FALSE (0)
#define SUCCESS (0)
#define FAIL (-1)

#define MAX_THREADS (64)
#define ASCII_SIZE (256)
#define LINE_SIZE (64)
/******************************************************************************
*							 DECLARATION								 		  * 
******************************************************************************/
typedef struct params
{
    unsigned char * arr;
    size_t iteration;    
}params;

sem_t sem = {0};
size_t count[ASCII_SIZE] = {0};

static void PrintArr(unsigned char * arr , size_t size);
void *SortByThread(void * args);
/******************************************************************************
*							 FUNCTIONS 										  * 
******************************************************************************/

int MTCountingSort(unsigned char *arr, size_t size, size_t num_of_threads)
{
    pthread_t thread_id[MAX_THREADS] = {0};
    params params_arr[MAX_THREADS] = {0};
    int j = 0, i = 0;
    size_t this_thread = 0;

    size_t work_load = size / num_of_threads;

    int status = 0;

    sem_init(&sem, 0 ,1);

    for( this_thread = 0 ;this_thread  < num_of_threads; ++this_thread)
    {
        params_arr[this_thread].arr = arr + (this_thread*work_load);
        params_arr[this_thread].iteration = work_load;
        
        if (this_thread == num_of_threads-1)
        {
            params_arr[this_thread].iteration += size%num_of_threads;
        }        

        status = pthread_create(&thread_id[this_thread], NULL, SortByThread, &params_arr[this_thread]);
        if(status != SUCCESS)
        {
            break;
        }
    }

    for(i = 0 ; i < num_of_threads; ++i)
    {
       pthread_join(thread_id[i], NULL);
    }

    for(i = 0; i < ASCII_SIZE; ++i)
    {
        while(count[i] > 0)
        {
            count[i] -= 1;
            arr[j] = i;
            ++j;
        }
    }

    sem_destroy(&sem);

    return SUCCESS;
}

/******************************************************************************
*							STATIC FUNCTIONS 								  * 
******************************************************************************/

void *SortByThread(void * args)
{
    params *param_ptr = (params *)args;
    size_t runner = 0;
    size_t count_local[ASCII_SIZE] = {0};

    while(runner < param_ptr->iteration)
    {
        count_local[param_ptr->arr[runner]] += 1;
        ++runner;
    }

    sem_wait(&sem);
    for(runner = 0; runner < ASCII_SIZE; ++runner)
    {
        count[runner] += count_local[runner];
    }
    sem_post(&sem);

    return NULL;
}



static void PrintArr(unsigned char * arr , size_t size)
{
	int i = 0;
	printf("\narr :\n");
	for(i = 0 ; i < size; ++i)
	{
		printf("%d -", arr[i]);
	}
}