/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/
#define _POSIX_SOURCE

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
pid_t WD_pid = 0;
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
}


/******************************************************************************
*							STATIC FUNCTIONS 								  * 
******************************************************************************/


static void * WD_Start_thread(void * params)
{
    int status = 0; 

    char *args[3] = NULL;

    WD_pid = CheckWDPID();
    
    if (WD_pid == 0)
    {
        args[1] = "WD.out";
        args[2] = params;

        WD_pid = RunExe(args);
        if (WD_pid == FAIL)
        {
            return NULL;
        }
    }

    status = pthread_create(&thread_pid, NULL, Scheduler_manager, &params);
    if (status != SUCCESS)
    {
        return; 
    }

    pthread_join(thread_pid, (void **)&status);
    if(status == NULL)
    {
        return FAIL;
    }
}

