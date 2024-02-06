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

pid_t sender_pid = 0;
pid_t external_pid = 0;
pid_t WD_pid = 0;
atomic_int sig_counter = 0; 
atomic_int stop_flag = 0; 
int num_of_rev = 5;

typedef struct params
{
    char * my_exe;
    char * watch_exe;
    scheduler_t * scheduler;
}s_params;


/******************************************************************************
*							 FUNCTIONS 										  * 
******************************************************************************/
static int AddTasks(scheduler_t * scheduler, s_params *task_params);
static int DoILikeBalls();
static int OpSem(int value, int type);
void CleanUP(scheduler_t * scheduler);

void SignalHandler1(int sig, siginfo_t *info, void *context);
void SignalHandler2(int sig, siginfo_t *info, void *context);



void * Scheduler_manager(void *params)
{
    scheduler_t * scheduler  = NULL;

    s_params task_params = {0};
    
    scheduler  = SchedulerCreate();
    if (scheduler == NULL)
    {
        return NULL;
    }

    if (DoILikeBalls() == TRUE)
    {
        /* i am the watch dog */
        task_params.my_exe = "./WD.out";
        task_params.watch_exe = (char *)params;
        external_pid = getppid();
    
    }
    else 
    {
        task_params.my_exe = (char *)params;
        task_params.watch_exe = "./WD.out";
        external_pid = GetEnvWDPID();
        WD_pid = external_pid; 
    }    

    printf("i am: %d i send to exteranal: %d\n", getpid(), external_pid );
    SetSigActions();    
    
    AddTasks(scheduler, &task_params);


    OpSem(1, INCREASE);
    
    OpSem(2, DECREASE);         /* wait for both process */
    
    OpSem(2, INCREASE);

    SchedulerRun(scheduler);
    CleanUP(scheduler);
    return NULL;
}


static int AddTasks(scheduler_t * scheduler, s_params *task_params)
{
    
    ilrd_uid_t uid = {0};
    int runner = 0;  
    
    op_func_t task_arr[NUM_OF_TASK] =       {SendSignalTask,    CheckAndReviveTask, CheckFlagTask};
    time_t interval_time[NUM_OF_TASK] =     {T_signal,          T_check_counter,    T_check_flag};
    time_t time_to_start[NUM_OF_TASK] =     {0};
    
    for(runner = 0 ; runner <NUM_OF_TASK ; ++runner)
    {
        time_to_start[runner] = time(NULL) + (runner*2+1);
    }

    for(runner = 0; runner < NUM_OF_TASK; ++runner)
    {
        uid = SchedulerAdd(scheduler, task_arr[runner], task_params,
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
	signals_struct.sa_flags = SA_SIGINFO;
	signals_struct.sa_sigaction = SignalHandler1;
    
    status = sigaction(SIGUSR1, &signals_struct, NULL);
    if(status != SUCCESS)
    {
        return FAIL;
    }
    
    signals_struct.sa_sigaction = SignalHandler2;
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
    kill(external_pid, SIGUSR1);
    sig_counter += 1;
    printf("sig recived from %d \n", sender_pid);
    return REPEAT;
}

int CheckAndReviveTask(void * params)
{
    s_params * s1 = (s_params *)params;
    char *args[3] = {NULL};

    if(sig_counter > missed_signal_tolerance)
    {
        write(1,"i WAS revive\n", 13);
        if(DoILikeBalls() == TRUE)
        {   
            write(1,"by the DOG\n", 12);
        }
        else 
        {
            write(1,"by the user\n", 13);
        }
        args[0] = s1->watch_exe;
        args[1] = s1->my_exe;
        sig_counter = 0;
        RunExe(args);
    }
    return REPEAT;
}

int CheckFlagTask(void * params)
{
    s_params * s1 = (s_params *)params;
    if(stop_flag == 1)
    {
        SchedulerStop(s1->scheduler);
        kill(external_pid, SIGUSR2);
    }
    return REPEAT;
}

pid_t RunExe(char ** args)
{
    pid_t child = 0; 
    child = fork();
    external_pid = child;
    
    if(child == 0)
    {
        execvp(args[0],args);
        printf("could'nt open\n");
    }

    return child;
}

void SetEnvWDPID(pid_t pid)
{
    char this_pid[20] = {0};
    sprintf(this_pid, "%d", pid);
    setenv("WD_pid", this_pid, TRUE); 
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

void SignalHandler1(int sig, siginfo_t *info, void *context)
{
    (void)sig;
    (void)context;
    sender_pid = info->si_pid;
    sig_counter = 0;
}

void SignalHandler2(int sig, siginfo_t *info, void *context)
{
    (void)sig;
    (void)context;
    sender_pid = info->si_pid;
    stop_flag = 1; 
}


static int OpSem(int value, int type)
{
    char command[30] = {0};
    char value_as_str[10]; 

    strcat(command, "./WD_sem.out WD ");
    sprintf(value_as_str, "%d", value);
    if (type == DECREASE)
    {
        strcat(command , "D ");    
        strcat(command, value_as_str);    
    }
    else if (type == INCREASE)
    {
        strcat(command , "I "); 
        strcat(command, value_as_str); 
    }
    else if (type == DELETE)
    {
        strcat(command , "R "); 
        strcat(command, value_as_str); 
    }

    system(command);

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
