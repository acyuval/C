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
#include <signal.h>

#include "utils.h"
#include "WD_utils.h"


/******************************************************************************
*							 DECLARATION								 		  * 
******************************************************************************/
static void * WD_Start_thread(void * params);



pthread_t thread_pid = 0;


/******************************************************************************
*							 FUNCTIONS 										  * 
******************************************************************************/

int WatchdogStart(char **args)
{
    int status = 0; 

    status = pthread_create(&thread_pid, NULL, WD_Start_thread, *(void **)args);
    if (status != SUCCESS)
    {
        return FAIL; 
    }
    return SUCCESS;
}

void WatchdogStop()
{
    stop_all();
    pthread_join(thread_pid,NULL);
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
        args[1] = "WD.out";
        args[2] = params;

        env_pid = RunExe(args);
        if (env_pid == FAIL)
        {
            return NULL;
        }
    }

    status = pthread_create(&thread_pid, NULL, Scheduler_manager, &params);
    if (status != SUCCESS)
    {
        return NULL; 
    }

    pthread_join(thread_pid, (void **)&status);
    if(status != SUCCESS)
    {
        return NULL;
    }
    
    return NULL;
}

