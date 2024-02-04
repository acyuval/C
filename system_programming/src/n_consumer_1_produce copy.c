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
pthread_t consumer_id[NUM_THREADS] = {0};
pthread_mutex_t mutex = {0};
pthread_cond_t cond = {0};
sem_t sem = {0};
int arr[10] = {0};
char msg[25] = "what is the reason for";
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
    pthread_cond_init(&cond,NULL);

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
        
    for (i = 0; i < NUM_THREADS; ++i)
    {
        pthread_join(consumer_id[i], NULL);
    }

    pthread_join(producer_id, NULL);

    return SUCCESS;
}

void *consumer(void *params)
{
    int i = 0 ;
    int dest = 0;
    int sem_val= 0;
    (void)params;
    while (1)
    {

        sem_wait(&sem);
        sem_getvalue(&sem, &sem_val);

        pthread_mutex_lock(&mutex);
        printf("consumer: %s by id:%ld\n", msg, pthread_self());
        for(i = 0 ; i < 10; ++i)
        {
            printf("%d-", arr[i]); 
        }

        if (sem_val == 0)
        {
            pthread_cond_broadcast(&cond); 
        }
        else
        {
            pthread_cond_wait(&cond, &mutex);
        }   
        for(i = 0; i < 10000000; ++i);
        pthread_mutex_unlock(&mutex);
    }
}

void *producer(void *params)
{
    int i = 0;
    int j = 0;
    (void)params;
    strcpy(msg, "actually this is the str");
    while(1)
    {
        for(j = 0 ; j < 10 ; ++j)
        {
            arr[j] = i;
        }

        sem_post(&sem);
        pthread_cond_wait(&cond, &mutex);
        i++;
        if (i == 100)
        {
            break;
        }
    }

}
/******************************************************************************
 *							STATIC FUNCTIONS 								  *
 ******************************************************************************/
