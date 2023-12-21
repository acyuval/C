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

#define TRUE (1)
#define FALSE (0)
#define SUCCESS (0)
#define FAIL (-1)
/******************************************************************************
*							 DECLRATION								  * 
******************************************************************************/

struct scheduler
{
	pq_t *pq;
	int is_running;
};



/******************************************************************************
*							 FUNCTIONS 										  * 
******************************************************************************/


scheduler_t *SchedulerCreate(void)
{
	scheduler_t * schedule = (schedule *)malloc(sizeof(scheduler_t));
	if (NULL == schedule)
	{
		return NULL:	
	}

	schedule->pq = PQCreate(pq_compare_t compare_func);
	if (NULL == schedule->pq)
	{
		free(schedule);
		return NULL:	
	}
	return schedule;
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
	
	return (PQIsEmpty(schedule->pq) && !schedule->is_running);
}


size_t SchedulerSize(const scheduler_t *scheduler)
{
	return (PQSize(schedule) + schedule->is_running);
}

/******************************************************************************
*Description: Adds a task to the scheduler
*Parameters: Scheduler, 
*            op_func - pointer to the operation function
*            params -  params for the operation function
*            time_to_run - the scheduled time of the new task
*            intervals - seconds between tasks repeatitions
*            clean_up_func - pointer to the cleaning function
*            clean_up_params - params for the cleaning function
*Return Value: uid of the added task
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes:
******************************************************************************/
ilrd_uid_t SchedulerAdd(scheduler_t *scheduler, 
							op_func_t op_func, 
							void* params, 
							time_t time_to_run, 
							size_t intervals, 
							clean_up_t clean_up_func, 
							void *clean_up_params);


int SchedulerRemove(scheduler_t *scheduler, ilrd_uid_t uid)
{
	task_t *task = NULL;
	assert(scheduler != NULL);

	task = PQErase(scheduler->pq, &TaskIsMatch, &uid);
	if (NULL == task)
	{
		return FAIL;	
	}
	TaskDestroy(task);
	
	return SUCCESS;
}

/******************************************************************************
*Description: Runs all tasks in the Scheduler.
*Parameters: None
*Return Value: Status (FAIL, SUCCESS, STOPPED)
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes:
******************************************************************************/
int SchedulerRun(scheduler_t *scheduler);


/******************************************************************************
*Description: Stop the Scheduler execution
*Parameters: None
*Return Value:
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes:
******************************************************************************/
void SchedulerStop(const scheduler_t *scheduler);


void SchedulerClear(scheduler_t *scheduler)
{
	assert(NULL != schedule)
	
	while(!SchedulerIsEmpty(scheduler))
	{
		SchedulerRemove(scheduler, scheduler->uid)
	}

}




/******************************************************************************
*							STATIC FUNCTIONS								  * 
******************************************************************************/

