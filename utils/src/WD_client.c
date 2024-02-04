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


#include "scheduler.h"


/******************************************************************************
*							 DECLARATION								 		  * 
******************************************************************************/
pid_t WD_pid = 0;
pthread_t thread_pid = 0;
atomic_int sig_counter = 0; 
int task_flag = 0; 


#define T_check_flag (1);
#define T_signal (1);

/******************************************************************************
*							 FUNCTIONS 										  * 
******************************************************************************/

int WatchdogStart(char **args)
{
    int status = 0;

    WD_pid = CheckWDPID(args);
    
    if (WD_pid == 0)
    {
        WD_pid = CreateWD(args);
    }

    status = pthread_create(&thread_pid, NULL, Scheduler_manager, (void *)&param);
}


pid_t CheckWDPID(char **env)
{

    while(*env != NULL)
    {
        if (strncmp(*env, 6 ,"WD_PID"))
        {
            return atoi(*env+6);
        }
        ++env;
    }
    return 0;
}

pid_t CreateWD(char **args)
{
    pid_t child = 0; 

    child = fork();
    if(child == 0)
    {
        execvp(args[0],args);
    }
    else 
    {
        return child;
    }
}


void * Scheduler_manager(void *args)
{
    scheduler_t * scheduler  = SchedulerCreate();
    if (scheduler == NULL)
    {
        return NULL;
    }

    AddTasks(scheduler);

    SetSigActions();

    if (task_flag == 1)
    {
        SchedulerRun(scheduler);
    }

}

/******************************************************************************
*							STATIC FUNCTIONS 								  * 
******************************************************************************/
