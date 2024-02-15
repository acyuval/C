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
#include "sort.h"

#define TRUE (1)
#define FALSE (0)
#define SUCCESS (0)
#define FAIL (-1)

#define MAX_THREADS (64)
 
/******************************************************************************
*							 DECLARATION								 		  * 
******************************************************************************/
typedef struct params
{
    char ** arr;
    size_t iteration; 

}params;

void MergeHalfs(char **arr, size_t start,size_t mid ,size_t end);
void swap(char ** a , char ** b);
void *SortByThread(void * args);
int comparator(const void * arg1,const void * arg2);

/******************************************************************************
*							 FUNCTIONS 										  * 
******************************************************************************/

int SortAndMerge(char **arr, size_t size, size_t num_of_threads)
{
    pthread_t thread_id[MAX_THREADS] = {0};
    params params_arr[MAX_THREADS] = {0};
    size_t i = 0;
    size_t this_thread = 0;
    size_t work_load = size / num_of_threads;
    size_t mid = 0, end = 0;
    int status = 0;


    for(this_thread = 0 ;this_thread  < num_of_threads; ++this_thread)
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


    for(i = 0 ; i < num_of_threads-1; ++i)
    {
        mid =  (i+1)*work_load; 
        end = (i+2)*work_load;
        end += (i == (num_of_threads-2))? size%num_of_threads : 0; 
        MergeHalfs(arr, 0, mid , end);
    } 

    return SUCCESS;
}

/******************************************************************************
*							STATIC FUNCTIONS 								  * 
******************************************************************************/

void *SortByThread(void * args)
{
    params *param_ptr = (params *)args;
    QuickSort(param_ptr->arr, param_ptr->iteration, sizeof(size_t) , comparator);
    return NULL;
}




void swap(char ** a , char ** b)
{   
    char ** temp = a; 
    *a = *b;
    *b = *temp;
}


int comparator(const void * arg1,const void * arg2)
{
    char * str1 = *(char **)arg1;
    char * str2 = *(char **)arg2;
    return strcmp(str1,str2); 
}

void MergeHalfs(char **arr, size_t start,size_t mid ,size_t end)
{
    size_t first_index = start, last_index = mid, counter =start;
    size_t i = 0;

    char ** arr_extra = (char **)calloc((end-start + 1),sizeof(size_t));

    while (first_index < mid && last_index < end)
    {
        if(strcmp(arr[first_index], arr[last_index]) < 0)
        {
            arr_extra[counter] = arr[first_index];
            ++first_index;
        }
        else 
        {
            arr_extra[counter] = arr[last_index];
            ++last_index;
        }
        ++counter;    
    }

    while(first_index < mid)
    {
        arr_extra[counter] = arr[first_index];
        ++counter;
        ++first_index;
    }

    while(last_index < end)
    {
        arr_extra[counter] = arr[last_index];
        ++counter;
        ++last_index;
    }

    for (i = start; i < end; ++i) 
    {
        arr[i] = arr_extra[i];
    }

    free(arr_extra);

}