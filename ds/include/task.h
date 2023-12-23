#ifndef __TASK_H__
#define __TASK_H__

#include <stddef.h>	/* size_t*/
#include "uid.h"	/* uid, time_t, bad_uid*/

typedef struct task task_t;

typedef void (*clean_up_t)(void *);
typedef int (*op_func_t)(void *);

enum repeat_values
{
	NO_REPEAT = 0,
	REPEAT = 1
};

/*******************************************************************************
*Description: Creates a new task.
*Parameters: op_func - pointer to the operation function
*			 params -  params for the operation function
*			 time_to_run - the scheduled time of the new task
*			 intervals - seconds between tasks repeatitions
*			 clean_up_func - pointer to the cleaning function
*			 clean_up_params - params for the cleaning function
*Return Value: Pointer to the new task.
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: Returns NULL if memory allocation fails.
*******************************************************************************/
task_t *TaskCreate(op_func_t op_func, void* params, 
                        time_t time_to_run, size_t intervals, 
						clean_up_t clean_up_func, void *clean_up_params);

/*******************************************************************************
*Description: Deletes the given task.
*Parameters: Pointer to the task for delete.
*Time Complexity: O(1)
*Space Complexity: O(1)
*******************************************************************************/
void TaskDestroy(task_t *task);

/*******************************************************************************
*Description: Get the UID of the given task.
*Parameters: Pointer to the task.
*Return Value: UID.
*Time Complexity: O(1)
*Space Complexity: O(1)
*******************************************************************************/
ilrd_uid_t TaskGetUid(const task_t *task);

/*******************************************************************************
*Description: Runs the given task.
*Parameters: Pointer to the task.
*Return Value: An indicator to whether the task repeats (NO_REPEAT, REPEAT).
*Time Complexity: O(1)
*Space Complexity: O(1)
*******************************************************************************/
int TaskRun(task_t *task);

/*******************************************************************************
*Description: Gets the time the task is schedueled to run.
*Parameters: Pointer to the task.
*Return Value: The time the task is schedueled to run.
*Time Complexity: O(1)
*Space Complexity: O(1)
*******************************************************************************/
time_t TaskGetTimeToRun(const task_t *task);

/*******************************************************************************
*Description: Checks whether task1 is schedueled before task2.
*Parameters: Pointers to the tasks.
*Return Value: 1 - task1 is schedueled before task2, 
*			   0 - otherwise.
*Time Complexity: O(1)
*Space Complexity: O(1)
*******************************************************************************/
int TaskIsBefore(const task_t *task1,const task_t *task2);

/*******************************************************************************
*Description: Checks whether the UID represent the given task.
*Parameters: Pointers to the tasks and the UID to check.
*Return Value: 1 - UID belongs to the given task,
*              0 - otherwise.
*Time Complexity: O(1)
*Space Complexity: O(1)
*******************************************************************************/
int TaskIsMatch(const task_t *task,const ilrd_uid_t uid);

/*******************************************************************************
*Description: Updates the time to run according to the interval value.
*Parameters: Pointers to the task.
*Time Complexity: O(1)
*Space Complexity: O(1)
*******************************************************************************/
void TaskUpdateTimeToRun(task_t *task);



#endif /*__TASK_H__*/
