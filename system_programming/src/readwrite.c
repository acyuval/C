/******************************************************************************
*	Author:    Yuval 
*	Reviewer : igal
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

#define TRUE (1)
#define FALSE (0)
#define SUCCESS (0)
#define FAIL (-1)

#define BUFFER_SIZE (10000)
#define NUM_TEST (1000)
/******************************************************************************
*							 DECLRATION								 		  * 
******************************************************************************/
struct params
{
    int * arr;
    int size;
};


atomic_int writer_flag = 0;
atomic_int reader_flag = 1;
void *writer(void * params);
int StartReadWrite();
void *reader(void * params);
/******************************************************************************
*							 FUNCTIONS 										  * 
******************************************************************************/
int main()
{
    StartReadWrite();
    return 0;
}

int StartReadWrite()
{
    int arr[BUFFER_SIZE] = {0};
    int status = 0;
    pthread_t writer_id = 0;
    pthread_t reader_id = 0;
    struct params param = {0};
    param.arr = arr;

    param.size = BUFFER_SIZE;

    status = pthread_create(&writer_id, NULL, reader, (void *)&param);
    if (status != SUCCESS)
    {
        return FAIL;
    }
    status = pthread_create(&reader_id, NULL, writer, (void *)&param);
    if (status != SUCCESS)
    {
        return FAIL;
    }

    pthread_join(reader_id, NULL);
    pthread_join(writer_id, NULL);
        
    return SUCCESS;
}


void *reader(void * params)
{
    size_t sum = 0;
    int counter = 1;
    int i = 0;
    int times = NUM_TEST;
    struct params * param = (struct params * )params;
    while(counter < NUM_TEST)
    {
        sum = 0;
        while (__sync_lock_test_and_set(&reader_flag, 1) == TRUE);
        for(i = 0 ; i < param->size ; ++i)
        {
            sum += param->arr[i];

        }
        printf("      sum is %ld \n" ,sum);
        counter++;
        __sync_lock_release(&writer_flag);
    }
}

void *writer(void * params)
{
    int counter = 0;
    int max_int = ~0;
    int i = 0;
    struct params * param = (struct params *)params;
    while(counter < NUM_TEST)
    {
        while (__sync_lock_test_and_set(&writer_flag, 1) == TRUE);
        
        for(i = 0 ; i < param->size ; ++i)
        {
            param->arr[i] = counter;
        }
        ++counter;
        __sync_lock_release(&reader_flag);
    }
}
/******************************************************************************
*							STATIC FUNCTIONS 								  * 
******************************************************************************/

