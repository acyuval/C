/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/
#define _POSIX_SOURCE

#include <assert.h> /* assert			  */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h> 
#include <time.h> 
#define TRUE (1)
#define FALSE (0)
#define SUCCESS (0)
#define FAIL (-1)
#define k100 (10)
#define BIG_NUMBER (1000000000)
#define RANGE (BIG_NUMBER/k100) 

/******************************************************************************
*							 DECLRATION								 		  * 
******************************************************************************/
void * myThreadFun(void *range);
int arr[k100] ={0};

size_t SumOfDiv(size_t num);

 

/******************************************************************************
*							 FUNCTIONS 										  * 
******************************************************************************/

int main()
{
    size_t runner = 0 ;
    time_t timer = 0;
    size_t final_ret = 0;
    pthread_t thread_id[k100] = {0};
    
    size_t arr[k100] = {0};
    for(runner = 0 ; runner < k100-1; ++runner)
    {
        arr[runner+1] = arr[runner] + RANGE +1;
    }
    arr[0] = 1;

    timer = time(NULL);

    for (runner = 0 ; runner < k100 ; ++runner)
    {
        while (SUCCESS != pthread_create(&thread_id[runner], NULL, myThreadFun, (void *)&arr[runner]))
        {
            printf("error : %ld", runner);
        }
    }

    for(runner = 0 ; runner < k100 ; ++runner)
    {
        pthread_join(thread_id[runner], NULL); 
        final_ret += arr[runner];
    }

    timer = time(NULL) -  timer;

    printf("\n\n\nsum is  : %ld\n", final_ret);
    printf("\n\n\ntime took : %ld sec\n", timer);
    timer = time(NULL);
    SumOfDiv(BIG_NUMBER);
    timer = time(NULL) -  timer;    
    printf("\n\n\ntime took : %ld sec\n", timer);
}



void * myThreadFun(void *range)
{
    size_t i = 0;
    size_t sum = 0;
    size_t start = *(size_t *)range;
    size_t end = start + RANGE;  
 
    *(size_t *)range = 0;
    for(i=start ; i < end && i<BIG_NUMBER ; ++i)
    {
        if(0 == (BIG_NUMBER % i))
        {
            sum += i;
        }
    }
    *(size_t *)range = sum;
    return NULL;
}


size_t SumOfDiv(size_t num) 
{ 
    size_t num_of_divisor  = 0;
    size_t i = 0 ;
    #pragma omp parallel for
    for(i = 1 ; i < num; ++i) 
    {
        if(0 == (BIG_NUMBER % i))
        {
            #pragma omp critical
            num_of_divisor += i;
        }
    }
    
    printf("\n%ld\n", num_of_divisor);

    return num_of_divisor;
} 
