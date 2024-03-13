/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/



#include <stdlib.h>
#include <stdio.h>
#include <pthread.h> 
#include <stdatomic.h> 
#include <signal.h>

#include "utils.h"
#include "WD_utils.h"


/******************************************************************************
*							 DECLARATION								 		  * 
******************************************************************************/
static void * WD_Start_thread(void * params);

pthread_t thread_pid[2] = {0};

/******************************************************************************
*							 FUNCTIONS 										  * 
******************************************************************************/

int WatchdogStart(char **args)
{
    int status = 0; 
    char * name = *(void **)args;
    status = pthread_create(&thread_pid[0], NULL, WD_Start_thread, name);
    if (status != SUCCESS)
    {
        return FAIL; 
    }
    return SUCCESS;
}

void WatchdogStop()
{
    StopAll();
    pthread_join(thread_pid[0], NULL);
    
}


/******************************************************************************
*							STATIC FUNCTIONS 								  * 
******************************************************************************/


static void * WD_Start_thread(void * params)
{
    int status = 0; 
    pid_t env_pid = 0;

    char *args[3] = {NULL};
    
    env_pid = GetEnvWDPID();
    if (env_pid == 0)
    {
        args[0] = "./WD.out";
        args[1] = (char *)params;

        env_pid = RunExe(args);
        if (env_pid == FAIL)
        {
            return NULL;
        }
        SetEnvWDPID(env_pid);
    }


    status = pthread_create(&thread_pid[1], NULL, SchedulerManager, params);
    if (status != SUCCESS)
    {
        return NULL; 
    }
    
    pthread_join(thread_pid[1], NULL);
    
    if(status != SUCCESS)
    {
        printf("error\n");
    }
    pthread_exit(NULL);
}

