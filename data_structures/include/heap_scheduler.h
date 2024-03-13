#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include "task.h"

typedef struct scheduler scheduler_t;


enum return_values
{
	FAIL = -1,
	SUCCESS = 0,
	STOPPED = 1
};

/******************************************************************************
*Description: Creates a new Scheduler.
*Parameters: None
*Return Value: Pointer to the created Scheduler.
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: Returns NULL if memory allocation fails.
******************************************************************************/
scheduler_t *HeapSchedulerCreate(void);


/******************************************************************************
*Description: Destroys the given Scheduler.
*Parameters: None
*Return Value: Pointer to the created Scheduler.
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes:
******************************************************************************/
void HeapSchedulerDestroy(scheduler_t *scheduler);


/******************************************************************************
*Description: checks whether schedule is empty.
*Parameters: Pointer to a Scheduler.
*Return Value: 1 - If Scheduler Is Empty
*              0 - otherwise.
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: 
******************************************************************************/
int HeapSchedulerIsEmpty(const scheduler_t *scheduler);


/******************************************************************************
*Description: Gets the number of tasks in the scheduler 
*             (indcluding running tasks).
*Parameters:  Pointer to the Scheduler.
*Return Value: Number of tasks.
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes:
******************************************************************************/
size_t HeapSchedulerSize(const scheduler_t *scheduler);


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
ilrd_uid_t HeapSchedulerAdd(scheduler_t *scheduler, 
							op_func_t op_func, 
							void* params, 
							time_t time_to_run, 
							size_t intervals, 
							clean_up_t clean_up_func, 
							void *clean_up_params);


/******************************************************************************
*Description: Remove task that match the given uid
*Parameters: Pointer to the Scheduler, uid
*Return Value: Status (FAIL,SUCCESS)
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes:
******************************************************************************/
int HeapSchedulerRemove(scheduler_t *scheduler, ilrd_uid_t uid);


/******************************************************************************
*Description: Runs all tasks in the Scheduler.
*Parameters: None
*Return Value: Status (FAIL, SUCCESS, STOPPED)
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes:
******************************************************************************/
int HeapSchedulerRun(scheduler_t *scheduler);


/******************************************************************************
*Description: Stop the Scheduler execution
*Parameters: None
*Return Value:
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes:
******************************************************************************/
void HeapSchedulerStop(scheduler_t *scheduler);


/******************************************************************************
*Description: clear the tasks of the scheduler.
*Parameters: Pointer to the Scheduler
*Return Value: None
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: 
******************************************************************************/
void HeapSchedulerClear(scheduler_t *scheduler);

#endif /* __SCHEDULER_H__ */
