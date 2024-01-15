/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Chen
*	Date:      
******************************************************************************/

#include <assert.h> /* assert			  */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "uid.h"
#include "task.h"
#include "heap_pq.h"
#include "scheduler.h"

#define TRUE (1)
#define FALSE (0)
#define SUCCESS (0)
#define FAIL (-1)
#define REPEAT (1)
#define NO_REPEAT (0)
#define STOP (0)
/******************************************************************************
*							 DECLRATION								  * 
******************************************************************************/
int counter = 0;

struct scheduler
{
	pq_t *pq;
	int is_running;
	ilrd_uid_t cur_task;
};
		

int CompareFunc(void *task1,void *task2);
int IsMatchFunc(void *task,void *uid);
/******************************************************************************
*							 FUNCTIONS 										  * 
******************************************************************************/


scheduler_t *SchedulerCreate(void)
{
	scheduler_t * scheduler = (scheduler_t *)malloc(sizeof(scheduler_t));
	
	if (NULL == scheduler)
	{
		return NULL;	
	}
	
	scheduler->is_running = 0;
	scheduler->pq = HeapPQCreate(&CompareFunc);
	
	if (NULL == scheduler->pq)
	{
		free(scheduler);
		return NULL;	
	}
	
	return scheduler;
}


void SchedulerDestroy(scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	SchedulerClear(scheduler);
	HeapPQDestroy(scheduler->pq);
	free(scheduler);
}



int SchedulerIsEmpty(const scheduler_t *scheduler)
{
	assert(scheduler != NULL);
	
	return (HeapPQIsEmpty(scheduler->pq) && FALSE == scheduler->is_running);
}


size_t SchedulerSize(const scheduler_t *scheduler)
{
	assert(scheduler != NULL);
	
	return (HeapPQSize(scheduler->pq) + scheduler->is_running);
}


ilrd_uid_t SchedulerAdd(scheduler_t *scheduler,	op_func_t op_func, 
							void* params, time_t time_to_run, 
							size_t intervals, clean_up_t clean_up_func, 
							void *clean_up_params)
{
	int status = 0; 
	task_t * task = NULL;
	
	assert(scheduler != NULL);
	assert(time_to_run != 0);
	
	task = TaskCreate(op_func, params, time_to_run, intervals,
											 clean_up_func, clean_up_params);
		
	if (NULL == task)
	{
		return bad_uid;
	}
	
	if(UIDIsEqual(TaskGetUid(task), bad_uid))
	{
		free(task);
		return bad_uid;
	}
	
	status = HeapPQEnqueue(scheduler->pq, task);
	
	if (FAIL == status)
	{
		TaskDestroy(task);
		return bad_uid;
	}
	
	return TaskGetUid(task);
}		
					


int SchedulerRemove(scheduler_t *scheduler, ilrd_uid_t uid)
{
	task_t *task = NULL;
	assert(scheduler != NULL);
	
	if (TRUE == UIDIsEqual(scheduler->cur_task , uid))
	{
		scheduler->cur_task = bad_uid;
		return SUCCESS;
	}
	
	task = HeapPQErase(scheduler->pq, &IsMatchFunc, &uid);
	
  	if (NULL == task)
	{
		return FAIL;	
	}
	
	TaskDestroy(task);
	return SUCCESS;
}

int SchedulerRun(scheduler_t *scheduler)
{
	task_t * task = NULL;
	time_t time_to_run = 0;
	int status = SUCCESS;
	assert(scheduler != NULL); 
	
	scheduler->is_running = 1;
	
	while (FALSE == HeapPQIsEmpty(scheduler->pq) && STOP != scheduler->is_running)
	{
		task = (task_t *)HeapPQPeek(scheduler->pq);
		scheduler->cur_task = TaskGetUid(task);
		time_to_run = TaskGetTimeToRun(task);
		
		while (time_to_run > time(NULL))
		{
			sleep(1);
		}
		
		HeapPQDequeue(scheduler->pq);
		
		status = TaskRun(task);
		
		if (REPEAT == status)
		{
			if(UIDIsEqual(bad_uid,scheduler->cur_task))
			{
				TaskDestroy(task);
				continue;			
			}

			TaskUpdateTimeToRun(task);	
			status = HeapPQEnqueue(scheduler->pq, task);
			
			if (FAIL == status)
			{
				TaskDestroy(task);
				return FAIL;
			}
		}
		else
		{
			TaskDestroy(task);
		}
	}

	scheduler->is_running = 0;
	
	return  SchedulerIsEmpty(scheduler) ? SUCCESS : STOPPED;
}


void SchedulerStop(scheduler_t *scheduler)
{
	assert(scheduler != NULL);
	scheduler->is_running = 0;
}


void SchedulerClear(scheduler_t *scheduler)
{
	task_t * task = NULL;
	assert(NULL != scheduler);

	scheduler->cur_task = bad_uid;
		
	while(FALSE == HeapPQIsEmpty(scheduler->pq))
	{
		task = (task_t *)HeapPQDequeue(scheduler->pq);
		TaskDestroy(task);
	}
}



int CompareFunc(void *task1,void *task2)
{
	assert(NULL != task1);
	assert(NULL != task2);
		
	return difftime(TaskGetTimeToRun(task1), TaskGetTimeToRun(task2));
}


int IsMatchFunc(void *task1,void *task2)
{
	int return_value = 0; 
	assert(NULL != task1);
	assert(NULL != task2);
	
	return_value = TaskIsMatch((const task_t *)task1,TaskGetUid((task_t *)task2));
	
	return return_value ? TRUE : FALSE;
}

/******************************************************************************
*							STATIC FUNCTIONS								  * 
******************************************************************************/

