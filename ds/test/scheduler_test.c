/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Chen
*	Date:      
******************************************************************************/
#include <stdio.h>  /* printf()  	  */
#include <assert.h> /* assert			  */
#include <time.h>
#include "pq.h"
#include "uid.h"
#include "task.h"
#include "scheduler.h"

/******************************************************************************
*							TYPE DEFS / MACROS 								  * 
******************************************************************************/



/******************************************************************************
*							FUNCTION DECLRATION								  * 
******************************************************************************/

static void TestHelper(int booll , char * calling_function, int test_no); 
int comparefunc(void * src, void *data);
void TestScheduler();
int Print(void * this_node, void *node_counter);
int Match(void * src, void *data);
int PrintMyName(void * name);
int StopTest(void * scheduler);
/******************************************************************************
*							MAIN											  * 
******************************************************************************/


int main()
{
	TestScheduler();
	return (0);
}




/******************************************************************************
*							TEST FUNCTIONS									  * 
******************************************************************************/


void TestScheduler()
{
	
	scheduler_t * scheduler = SchedulerCreate();
	SchedulerAdd(scheduler,&PrintMyName, (void *)"yuval", time(NULL) + 2, 2, NULL, 
							NULL);
	
	SchedulerAdd(scheduler,&PrintMyName, (void *)"Einav", time(NULL) + 1, 5, NULL, 
							NULL);
	
	
	SchedulerRun(scheduler);	
					
	SchedulerDestroy(scheduler);

}


int Match(void * node_data, void *params)
{
	if (*(int *)node_data > *(int *)params)
	{
		return 1;
	}
	
	return 0;
}





/******************************************************************************
*							STATIC FUNCTIONS								  * 
******************************************************************************/

int PrintMyName(void * name)
{
	assert(name != NULL);
	printf("this is my name: %s\n", (char *)name);
	return 1;

}

int StopTest(void * scheduler)
{
	scheduler = (scheduler_t *)scheduler;
	SchedulerStop(scheduler);
	return 0;

}


/*
int SaveTimeInHeap(void * time)
{
	assert(time != NULL);
	time = (time_t)time;
	
	
}
*/



static void TestHelper(int booll , char * calling_function, int test_no)
{
	if(booll)
	{
		printf("%s -> \t\tNO.%d sucsess!\n\n",calling_function, test_no);
	}
	else
	{
		printf("failed in %s, No. %d\n\n",calling_function ,test_no);
	}
}


