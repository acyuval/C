#ifndef __TASK_H__
#define __TASK_H__

#include <stddef.h>	/* size_t*/
#include "uid.h"	/* uid, time_t */

typedef struct task task_t;

/* in task.c

struct task
{
	ilrd_uid_t uid;
	op_func_t op_func;
	void *params;
	clean_up_t clean_up_func;
	void *clean_up_params;
	time_t time_to_run;
	size_t interval;
};
*/


typedef void (*clean_up_t)(void *);
typedef int (*op_func_t)(void *);

enum repeat_values
{
	NO_REPEAT = 0,
	REPEAT = 1
};


/******************************************************************************
*Description: Creates new task.
*Parameters:    op_func - pointer to the operation function
*               params -  params for the operation function
*               time_to_run - the scheduled time of the new task
*               intervals - seconds between tasks repeatitions
*               clean_up_func - pointer to the cleaning function
*               clean_up_params - params for the cleaning function
*Return Value: pointer to the new task.
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: Returns NULL if memory allocation fails.
******************************************************************************/
task_t *TaskCreate(op_func_t op_func, void* params, 
                        time_t time_to_run, size_t intervals, 
						clean_up_t clean_up_func, void *clean_up_params);

/******************************************************************************
*Description: Deletes the given task.
*Parameters: pointer to the task for delete
*Return Value:
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
void TaskDestroy(task_t *task);


/******************************************************************************
*Description: Get the uid of the given task
*Parameters: pointer to the task.
*Return Value: uid.
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
ilrd_uid_t TaskGetUid(const task_t *task);


/******************************************************************************
*Description: Runs the given task.
*Parameters: pointer to the task.
*Return Value: whether the task repeats.
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
int TaskRun(task_t *task);


/******************************************************************************
*Description: gets the time the task is schedueled to run.
*Parameters: pointer to the task.
*Return Value: time the task is schedueled to run.
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
time_t TaskGetTimeToRun(const task_t *task);


/******************************************************************************
*Description: checks whether task1 is schedueled before task2.
*Parameters: pointers to the tasks.
*Return Value: 1 - task1 is schedueled before task2, 0 - otherwise.
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
int TaskIsBefore(const task_t *task1,const task_t *task2);


/******************************************************************************
*Description: checks whether the uid represent the given task.
*Parameters: pointers to the tasks and the uid to check.
*Return Value: 1 - uid belongs to the given task
*              0 - otherwise.
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
int TaskIsMatch(const task_t *task,const ilrd_uid_t uid);


/******************************************************************************
*Description: updates the time to run according to the interval value.
*Parameters: pointers to the task.
*Return Value: 
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
void TaskUpdateTimeToRun(task_t *task);

#endif /* __TASK_H__ */
