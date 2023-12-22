/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/

#include <assert.h> /* assert			  */
#include <stdlib.h>
#include <stdio.h>

#include "uid.h"
#include "task.h"
#include "pq.h"
#include "scheduler.h"

#define TRUE (1)
#define FALSE (0)
#define SUCCESS (0)
#define FAIL (-1)
#define REPEAT (1)
#define NO_REPEAT (0)
/******************************************************************************
*							 DECLRATION								  * 
******************************************************************************/

struct scheduler
{
	pq_t *pq;
	int is_running;
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

	scheduler->pq = PQCreate(&CompareFunc);
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
	PQDestroy(scheduler->pq);
	free(scheduler);
}



int SchedulerIsEmpty(const scheduler_t *scheduler)
{
	assert(scheduler != NULL);
	
	return (PQIsEmpty(scheduler->pq) && !scheduler->is_running);
}


size_t SchedulerSize(const scheduler_t *scheduler)
{
	assert(scheduler != NULL);
	
	return (PQSize(scheduler->pq) + scheduler->is_running);
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
	
	status = PQEnqueue(scheduler->pq, &task);
	if (FAIL == status)
	{
		return bad_uid;
	}
}		
					


int SchedulerRemove(scheduler_t *scheduler, ilrd_uid_t uid)
{
	task_t *task = NULL;
	assert(scheduler != NULL);

	task = PQErase(scheduler->pq, &IsMatchFunc, &uid);
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
	int status = 0;
	
	assert(scheduler != NULL); 
	
	scheduler->is_running = 1;
	
	while (FALSE == PQIsEmpty(scheduler->pq))
	{
		task = (task_t *)PQPeek(scheduler->pq);
		time_to_run = TaskGetTimeToRun(task);
		
		while (time_to_run--)
		{
			sleep(1);
		}
		
		PQDequeue(scheduler->pq);
		
		status = TaskRun(task);
		
		if (0 == scheduler->is_running)
		{
			return STOPPED;
		}
		
		if (REPEAT == status)
		{
			TaskUpdateTimeToRun(task);	
			status = PQEnqueue(scheduler->pq, &task);
			
			if (FAIL == status)
			{
				return FAIL;
			}
		}
	}
}


void SchedulerStop(scheduler_t *scheduler)
{
	assert(scheduler != NULL);
	scheduler->is_running = 0;
}


void SchedulerClear(scheduler_t *scheduler)
{
	assert(NULL != scheduler);
	
	while(!SchedulerIsEmpty(scheduler))
	{
		SchedulerRemove(scheduler, GetUIDFromTask((task_t *)PQPeek(scheduler->pq)));
	}

}



int CompareFunc(void *task1,void *task2)
{
	int return_value = 0;
	assert(NULL != task1);
	assert(NULL != task2);
	
	return_value = TaskIsBefore((const task_t *)task1,(const task_t *) task2);
	
	return return_value ? SUCCESS : FAIL;
}


int IsMatchFunc(void *task1,void *task2)
{
	int return_value = 0; 
	assert(NULL != task1);
	assert(NULL != task2);
	
	return_value = TaskIsMatch((const task_t *)task1,GetUIDFromTask((task_t *)task2));
	
	return return_value ? TRUE : FALSE;
}

/******************************************************************************
*							STATIC FUNCTIONS								  * 
******************************************************************************/

