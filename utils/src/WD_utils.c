/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/
#define _POSIX_C_SOURCE 200112L 

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
static int OpSem(int value, int type);
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
        write(1,"i_am_watch\n", 11);
        external_pid = getppid(); 
    }
    else 
    {
        write(1,"i_am_user\n", 10);
        external_pid = GetEnvWDPID();
        WD_pid = external_pid; 
    }    

    printf("i am: %d i send to exteranal: %d\n", getpid(), external_pid );
    SetSigActions();    
    
    AddTasks(scheduler, s1->exe_name);


    OpSem(1, INCREASE);
    
    OpSem(2, DECREASE);         /* wait for both process */
    
    OpSem(2, INCREASE);

    SchedulerRun(scheduler);
    
    return NULL;
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

    return SUCCESS;
}

int SendSignalTask(void * params)
{
    (void)params;
    printf("SendSignalTask to : %d\n", external_pid);
    kill(external_pid, SIGUSR1);
    sig_counter += 1;
    return REPEAT;
}

int CheckAndReviveTask(void * params)
{
    s_params * s1 = (s_params *)params;
    write(1,"CheckAndReviveTask\n", 18);
    if(sig_counter > missed_signal_tolerance)
    {
        RunExe(&s1->exe_name);
    }
    return REPEAT;
}

int CheckFlagTask(void * params)
{
    s_params * s1 = (s_params *)params;
    write(1,"CheckFlagTask\n", 14);
    if(stop_flag == 1)
    {
        kill(external_pid, SIGUSR2);
        CleanUP(s1->scheduler);
    }
    return REPEAT;
}

pid_t RunExe(char ** args)
{
    pid_t child = 0; 
    child = fork();
    
    if(child == 0)
    {
        execvp(args[1],args);
        printf("couldnt open\n");
    }

    external_pid = child;
    
    return child;
}

void SetEnvWDPID(pid_t pid)
{
    char this_pid[20] = {0};
    sprintf(this_pid, "%d", pid);
    setenv("WD_pid", this_pid, TRUE); 
    system("env |grep WD_pid");
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
    write(1,"sig_handl1\n", 11);
    printf("my pid %d\n", getpid());
    sig_counter = 0;
}

void SignalHandler2()
{
    write(1,"sig_handl2\n", 11);

    stop_flag = 1; 
}


static int OpSem(int value, int type)
{
    char command[10] = {0};
    char value_as_str[10]; 
    write(1,"sem_op\n", 7);
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

    system("./WD_sem.out WD ");

    return SUCCESS;
}

void CleanUP(scheduler_t * scheduler)
{
    SchedulerStop(scheduler);
    SchedulerDestroy(scheduler);

}

int stop_all()
{
    kill(external_pid, SIGUSR2);
    return SUCCESS;
}

/******************************************************************************
*							STATIC FUNCTIONS 								  * 
******************************************************************************/
