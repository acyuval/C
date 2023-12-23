/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Chen
*	Date:      
******************************************************************************/
#include <stdio.h>  /* printf()  	  */

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
	SchedulerAdd(scheduler,&PrintMyName, (void *)"yuval", 2, 4, NULL, 
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
	printf("this is my name: %s\n", (char *)name);
	return 1;

}

int comparefunc(void * node_data, void *params)
{
	if ((*(int *)node_data - *(int *)params) == 0)
	{
		return 1;
	} 
	return (*(int *)node_data - *(int *)params);
}




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


