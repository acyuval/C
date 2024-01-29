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
#define READER (1)
#define WRITER (-1)
#define BUFFER_SIZE (100)

/******************************************************************************
*							 DECLRATION								 		  * 
******************************************************************************/
struct params
{
    int * arr;
    int * R_ptr;
    int * W_ptr;
    int size;
};


atomic_int mode = WRITER;
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
    param.R_ptr = arr;
    param.W_ptr = arr;
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
    int counter = 0;
    struct params * param = (struct params * )params;
    while(counter < 100)
    {
        while (mode != READER)
        {
        }
        printf("%d-", *param->R_ptr);
        ++param->R_ptr;
        if(param->arr + param->size == param->R_ptr)
        {
            param->R_ptr = param->arr;
        }
        counter++;
        mode = WRITER;
    }
}

void *writer(void * params)
{
    int counter = 0;
    int max_int = ~0;

    struct params * param = (struct params *)params;
    while(counter < 100)
    {
        while (mode != WRITER)
        {
        }

        *param->W_ptr = counter;
        ++counter;
        counter = (counter == max_int)? 0 : counter ; 
        ++(param->W_ptr);

        if(param->arr + param->size == param->W_ptr)
        {
            param->W_ptr = param->arr;
        }
        mode = READER;
    }
}
/******************************************************************************
*							STATIC FUNCTIONS 								  * 
******************************************************************************/

