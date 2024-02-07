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
#include <ctype.h>
#include <pthread.h> 
#include <stdatomic.h> 
#include <signal.h>
#include <time.h>

#include "scheduler.h"
#include "semaphore.h"
#include "WD_utils.h"
#include "utils.h"

/******************************************************************************
*							 DECLARATION								 		  * 
******************************************************************************/

#define T_check_flag (1)
#define T_signal (2)
#define T_check_counter (1)
#define missed_signal_tolerance (5)

pid_t sender_pid = 0;
pid_t external_pid = 0;
pid_t WD_pid = 0;
atomic_int sig_counter = 0; 
atomic_int stop_flag = 0; 

typedef struct params
{
    char * my_exe;
    char * watch_exe;
    scheduler_t * scheduler;
}s_params;

enum tasks
{
    SEND_SIGNAL = 0,
    Check_COUNTER = 1, 
    Check_STOP = 2, 
    NUM_OF_TASKS
};

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short int *array;
	struct seminfo *__buf;
};

/******************************************************************************
*							 FUNCTIONS 										  * 
******************************************************************************/
void SignalHandler1(int sig, siginfo_t *info, void *context);
void SignalHandler2(int sig, siginfo_t *info, void *context);

static void CleanUP(scheduler_t * scheduler);
static int AddTasks(scheduler_t * scheduler, s_params *task_params);
static int DoILikeBalls();
static int OpSem(int value, int type, int undo);
static void ShowYourself();
static int SetSigActions();
static int SendSignalTask(void *);
static int CheckAndReviveTask(void *);
static int CheckFlagTask(void *);


void * Scheduler_manager(void *params)
{
    scheduler_t * scheduler  = NULL;

    s_params task_params = {0};
    
    scheduler  = SchedulerCreate();
    if (scheduler == NULL)
    {
        return NULL;
    }

    task_params.scheduler = scheduler;
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
    SetSigActions();    
    
    AddTasks(scheduler, &task_params);

    OpSem(1, INCREASE, 0);
    OpSem(2, DECREASE, 0);         /* wait for both process */
    OpSem(2, INCREASE, 0);

    SchedulerRun(scheduler);
    CleanUP(scheduler);

    return (void *)(size_t *)1;
}


pid_t RunExe(char ** args)
{
    pid_t child = 0; 
    child = fork();
    external_pid = child;
    
    if(child == 0)
    {
        execvp(args[0],args);
        printf("could'nt open file\n");
        exit(0);
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

    if(sender_pid != external_pid)
    {
        printf("other pid");
        return;
    }
    sig_counter = 0;
}

void SignalHandler2(int sig, siginfo_t *info, void *context)
{
    (void)sig;
    (void)context;
    (void)info;
    if(sender_pid == external_pid)
    {
        write(1, "stop sig received\n", 18);
        stop_flag = TRUE; 
    }
}

int stop_all()
{ 
    int status = 0;
    status = kill(external_pid, SIGUSR2); 
    OpSem(0, DELETE, 0); 
    return status;
}

/******************************************************************************
*							STATIC FUNCTIONS 								  * 
******************************************************************************/

static int CheckFlagTask(void * params)
{
    s_params * s1 = (s_params *)params;
    int status = 0; 
    if(stop_flag == TRUE)
    {
        status = stop_all();
        SchedulerStop(s1->scheduler);
        if(status == SUCCESS)
        {
            return NO_REPEAT;
        }
    }
    return REPEAT;
}



static void CleanUP(scheduler_t * scheduler)
{
    SchedulerDestroy(scheduler);
}

static void ShowYourself()
{
    if(DoILikeBalls() == TRUE)
    {   
        write(1,"by the DOG\n", 12);
    }
    else 
    {
        write(1,"by the user\n", 13);
    }
}


static int OpSem(int value, int type, int undo)
{
    int sem_id = SemaphoreInit("WD");
    if(type == DELETE)
    {
        sem_delete(sem_id);
    }
    else 
    {
        SemOp(sem_id , type , value, undo);
    }
    
    return SUCCESS;
}



static int AddTasks(scheduler_t * scheduler, s_params *task_params)
{
    
    ilrd_uid_t uid = {0};
    int runner = 0;  
    
    op_func_t task_arr[NUM_OF_TASKS] = {NULL};
    time_t interval_time[NUM_OF_TASKS] = {0};
    time_t start_time[NUM_OF_TASKS] =     {0};
    
    task_arr[SEND_SIGNAL] = SendSignalTask; 
    task_arr[Check_COUNTER] = CheckAndReviveTask;
    task_arr[Check_STOP] = CheckFlagTask;
    
    start_time[SEND_SIGNAL] = time(NULL) + 1;
    start_time[Check_COUNTER] = time(NULL) + 3;
    start_time[Check_STOP] = time(NULL) + 5;
    
    interval_time[SEND_SIGNAL] = 2; 
    interval_time[Check_COUNTER] = 1;
    interval_time[Check_STOP] = 1;
    
    for(runner = 0; runner < NUM_OF_TASKS; ++runner)
    {
        uid = SchedulerAdd(scheduler, task_arr[runner], task_params,
                           start_time[runner],interval_time[runner], NULL, NULL);
        
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

static int SetSigActions()
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

static int SendSignalTask(void * params)
{
    (void)params;
    kill(external_pid, SIGUSR1);
    sig_counter += 1;
    printf("last sig received from %d\n", sender_pid);
    return REPEAT;
}

static int CheckAndReviveTask(void * params)
{
    s_params * s1 = (s_params *)params;
    char *args[3] = {NULL};

    if(sig_counter > missed_signal_tolerance)
    {
        write(1,"i WAS revive ", 13);
        ShowYourself();

        args[0] = s1->watch_exe;
        args[1] = s1->my_exe;
        sig_counter = 0;
        RunExe(args);
        OpSem(1, DECREASE, 0);
        OpSem(2, INCREASE, 0); 
    }
    return REPEAT;
}