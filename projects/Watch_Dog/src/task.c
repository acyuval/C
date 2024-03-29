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

#define TRUE (1)
#define FALSE (0)
#define SUCCESS (0)
#define FAIL (-1)
/******************************************************************************
*							 DECLRATION								  * 
******************************************************************************/



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



/******************************************************************************
*							 FUNCTIONS 										  * 
******************************************************************************/



task_t *TaskCreate(op_func_t op_func, void* params, 
                        time_t time_to_run, size_t intervals, 
						clean_up_t clean_up_func, void *clean_up_params)
{
	task_t * task = NULL;
	
	assert(time_to_run != 0);

	task = (task_t *)malloc(sizeof(task_t));	

	if(NULL == task)
	{
		return NULL;
	}
	task->uid = UIDCreate();
	task->op_func = op_func;
	task->params = params;
	task->time_to_run = time_to_run;
	task->interval = intervals;
	task->clean_up_func = clean_up_func;
	task->clean_up_params = clean_up_params;
	
	return task;
}


void TaskDestroy(task_t *task)
{
	assert(NULL != task);
	if (task->clean_up_func != NULL)
	{
		task->clean_up_func(task->clean_up_params);
	}

	free(task);
}

ilrd_uid_t TaskGetUid(const task_t *task)
{
	assert(NULL != task);
	return task->uid;
}


int TaskRun(task_t *task)
{
	assert(NULL != task);
	return (task->op_func(task->params));
}


time_t TaskGetTimeToRun(const task_t *task)
{
	assert(NULL != task);
	
	return (task->time_to_run);
}


int TaskIsBefore(const task_t *task1,const task_t *task2)
{
	assert(NULL != task1);
	assert(NULL != task2);
	return (TaskGetTimeToRun(task2) > TaskGetTimeToRun(task1));
}


int TaskIsMatch(const task_t *task,const ilrd_uid_t uid)
{
	assert(NULL != task);
	
	return (UIDIsEqual(task->uid, uid));
}


void TaskUpdateTimeToRun(task_t *task)
{
	assert(NULL != task);
	task->time_to_run += task->interval;
}





/******************************************************************************
*							STATIC FUNCTIONS								  * 
******************************************************************************/

