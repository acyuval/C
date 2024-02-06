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
#include <time.h>

#include "scheduler.h"
#include "WD_utils.h"
#include "utils.h"

/******************************************************************************
*							 DECLARATION								 		  * 
******************************************************************************/
#define NUM_OF_TASK (3)
#define T_check_flag (1)
#define T_signal (1)
#define T_check_counter (1)
#define missed_signal_tolerance (5)


pid_t external_pid = 0;
pid_t WD_pid = 0;
atomic_int sig_counter = 0; 
atomic_int stop_flag = 0; 


typedef struct params
{
    char * exe_name;
    scheduler_t * scheduler; 
}s_params;


/******************************************************************************
*							 FUNCTIONS 										  * 
******************************************************************************/
static int AddTasks(scheduler_t * scheduler, char * exe_name);
static int DoILikeBalls();

void CleanUP(scheduler_t * scheduler);

void * Scheduler_manager(void *params)
{
    s_params * s1 = (s_params *)params;
    scheduler_t * scheduler  = NULL;
    
    scheduler  = SchedulerCreate();
    if (scheduler == NULL)
    {
        return NULL;
    }

    if (DoILikeBalls() == TRUE)
    {
        /* i am the watch dog */
        external_pid = getppid();
    }
    else 
    {
        external_pid = GetEnvWDPID();
        WD_pid = external_pid; 
    }    

    SetSigActions();    
    
    AddTasks(scheduler, s1->exe_name);

    OpSem(1, INCREASE);
    
    OpSem(2, DECREASE);         /* wait for both process */
    
    OpSem(2, INCREASE);

    SchedulerRun(scheduler);
}


static int AddTasks(scheduler_t * scheduler, char * exe_name)
{
    
    ilrd_uid_t uid = {0};
    int runner = 0;  
    
    op_func_t task_arr[NUM_OF_TASK] =       {SendSignalTask,    CheckAndReviveTask, CheckFlagTask};
    time_t interval_time[NUM_OF_TASK] =     {T_signal,          T_check_counter,    T_check_flag};
    s_params task_param[NUM_OF_TASK] =      {NULL};
    time_t time_to_start[NUM_OF_TASK] =     {0};
    
    task_param[2].scheduler = scheduler;
    task_param[1].exe_name = exe_name;

    for(runner = 0 ; runner <NUM_OF_TASK ; ++runner)
    {
        time_to_start[runner] = time(NULL) + runner;
    }

    for(runner = 0; runner < NUM_OF_TASK; ++runner)
    {
        uid = SchedulerAdd(scheduler, task_arr[runner], &task_param[runner],
                           time_to_start[runner],interval_time[runner], NULL, NULL);
        
        if(UIDIsEqual(uid,bad_uid) == TRUE)
        {
            SchedulerDestroy(scheduler);
            return FAIL;
        }
    }
    return SUCCESS;
}

static int DoILikeBalls()
{
    return (getpid() == GetEnvWDPID());
}

int SetSigActions()
{
    struct sigaction signals_struct= {0};
	int status = 0; 

	signals_struct.sa_handler = SignalHandler1;
    status = sigaction(SIGUSR1, &signals_struct, NULL);
    if(status != SUCCESS)
    {
        return FAIL;
    }
    
    signals_struct.sa_handler = SignalHandler2;
    status = sigaction(SIGUSR2, &signals_struct, NULL);
    if(status != SUCCESS)
    {   
        return FAIL;
    }
}

int SendSignalTask(void * params)
{
    (void)params;
    kill(external_pid, SIGUSR1);
    sig_counter += 1;
}

int CheckAndReviveTask(void * params)
{
    s_params * s1 = (s_params *)params;

    if(sig_counter > missed_signal_tolerance)
    {
        RunExe(&s1->exe_name);
    }
}

int CheckFlagTask(void * params)
{
    s_params * s1 = (s_params *)params;
    if(stop_flag == 1)
    {
        kill(external_pid, SIGUSR2);
        CleanUP(s1->scheduler);
    }
    return T_check_flag;
}

pid_t RunExe(char ** args)
{
    pid_t child = 0; 
    child = fork();
    if(child == 0)
    {
        execvp(args[0],args);
        printf("couldnt open");
    }

    return child;
}

void SetEnvWDPID(pid_t pid)
{
    char this_pid[20] = {0};
    sprintf(this_pid, "%d", pid);
    setenv("WD_pid", this_pid); 
}


pid_t GetEnvWDPID()
{
    char * pid = getenv("WD_pid");
    if(pid != NULL)
    {
        return atoi(pid);
    }
    return 0;
}

void SignalHandler1()
{
    sig_counter = 0;
}

void SignalHandler2()
{
    stop_flag = 1; 
}

int InitSem(int start_val)
{
    system("WD_sem.out WD");
}

int OpSem(int value, int type)
{
    char command[10] = {0};
    char value_as_str[10]; 

    sprintf(value_as_str, "%d", value);
    if (type == DECREASE)
    {
        strcat(command , "D");    
        strcat(command, value_as_str);    
    }
    else if (type == INCREASE)
    {
        strcat(command , "I"); 
        strcat(command, value_as_str); 
    }
    else if (type == DELETE)
    {
        strcat(command , "I"); 
        strcat(command, value_as_str); 
    }

    system("WD_sem.out WD");
}

void CleanUP(scheduler_t * scheduler)
{
    SchedulerStop(scheduler);
    SchedulerDestroy(scheduler);

}

int stop_all()
{
    kill(external_pid, SIGUSR2);
}

/******************************************************************************
*							STATIC FUNCTIONS 								  * 
******************************************************************************/
