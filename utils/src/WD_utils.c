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
AddTasks(scheduler_t * scheduler)
{
    
}

int SetSigActions()
{
    struct sigaction signal1_struct= {0};

	pid_t arg_pid = WD_pid;

	signal1_struct.sa_handler = SignalHandler1;
    
    sigaction(SIGUSR1, &signal1_struct, NULL);
}


static int SendSignalTask(void *)
{
    kill(WD_pid, SIGUSR1);
    sig_counter += 1;
}

static int CheckCounterTask(void *)
{

}
static int CheckFlagTask(void *)
{
    if(task_flag == 1)
    {
        CleanUP();
    }
    return T_check_flag
}
static void SignalHandler1()
{
    sig_counter = 0;
}
static void SignalHandler2()
{
    task_flag = 0 ; 
}
/******************************************************************************
*							STATIC FUNCTIONS 								  * 
******************************************************************************/
