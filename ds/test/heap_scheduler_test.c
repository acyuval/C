/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Chen
*	Date:      
******************************************************************************/
#include <stdio.h>  /* printf()  	  */
#include <assert.h> /* assert			  */
#include <stdlib.h>
#include <time.h>
#include "heap_pq.h"
#include "uid.h"
#include "task.h"
#include "heap_scheduler.h"

/******************************************************************************
*							TYPE DEFS / MACROS 								  * 
******************************************************************************/



/******************************************************************************
*							FUNCTION DECLRATION								  * 
******************************************************************************/

static void TestHelper(int booll , char * calling_function, int test_no); 
int comparefunc(void * src, void *data);
void TestSchedulerADDSizeIsEmpty();
int Print(void * this_node, void *node_counter);
int Match(void * src, void *data);
int PrintMyName(void * name);
int StopTest(void * scheduler);
void TestSchedulerClean();
int SaveTimeInHeap(void * data);
void CleanHeap(void * data);
/******************************************************************************
*							MAIN											  * 
******************************************************************************/

	
struct mem_allo
{
	void * data_ptr;
	size_t * counter; 
};

int main()
{
	TestSchedulerClean();
	TestSchedulerADDSizeIsEmpty();
	return (0);
}




/******************************************************************************
*							TEST FUNCTIONS									  * 
******************************************************************************/


void TestSchedulerADDSizeIsEmpty()
{
	
	scheduler_t * scheduler = SchedulerCreate();
	
	TestHelper(1 == SchedulerIsEmpty(scheduler), "TestSchedulerIsEmpty" , 1);	
	
	SchedulerAdd(scheduler,&PrintMyName, (void *)"yuval", time(NULL) + 2, 2, NULL, 
							NULL);
	
	SchedulerAdd(scheduler,&PrintMyName, (void *)"Einav", time(NULL) + 1, 2, NULL, 
							NULL);
	
							
	SchedulerAdd(scheduler,&SchedulerRemove, (void *)scheduler, time(NULL) + 4, 5, NULL, 
							NULL);
							
	SchedulerAdd(scheduler,&StopTest, (void *)scheduler, time(NULL) + 4, 5, NULL, 
							NULL);
							
	TestHelper(0 == SchedulerIsEmpty(scheduler),"TestSchedulerIsEmpty" , 2);	
	TestHelper(3 == SchedulerSize(scheduler),"TestSchedulerSize   " , 1);
				
	SchedulerRun(scheduler);	
	
	SchedulerClear(scheduler);
		
	TestHelper(1 == SchedulerIsEmpty(scheduler),"TestSchedulerIsEmpty" , 2);
	TestHelper(0 == SchedulerSize(scheduler),"TestSchedulerSize   " , 3);	
					
	SchedulerDestroy(scheduler);

}


void TestSchedulerClean()
{
	
	scheduler_t * scheduler = SchedulerCreate();
	
	size_t counter = 1;
		
	struct mem_allo send_it_struct = {0};
	
	send_it_struct.data_ptr = NULL;
	send_it_struct.counter = &counter;
	
	SchedulerAdd(scheduler,&SaveTimeInHeap, &send_it_struct, time(NULL) + 1, 2, &CleanHeap, 
							&send_it_struct);
	
	SchedulerAdd(scheduler,&StopTest, (void *)scheduler, time(NULL) + 4, 5, NULL, 
							NULL);
	
	SchedulerRun(scheduler);	
	
	SchedulerDestroy(scheduler);
}







/******************************************************************************
*							STATIC FUNCTIONS								  * 
******************************************************************************/

int PrintMyName(void * name)
{
	assert(name != NULL);
	printf("name: %s\n\n", (char *)name);
	return 1;
}

int StopTest(void * scheduler)
{
	scheduler = (scheduler_t *)scheduler;
	SchedulerStop(scheduler);
	return 0;

}


int RemoveTest(void * scheduler)
{
	scheduler = (scheduler_t *)scheduler;
	SchedulerRemove(scheduler->);
	return 0;

}

int SaveTimeInHeap(void * data)
{
	struct mem_allo * obj_ptr = (struct mem_allo *)data;
	size_t * data_size_t_ptr = NULL;
	
	assert(data != NULL);

	if (NULL == obj_ptr->data_ptr)
	{
		obj_ptr->data_ptr = malloc(sizeof(time_t));
		*(size_t *)(obj_ptr->data_ptr) = time(NULL);
		*(obj_ptr->counter) += 1;
		return 1;
	}
	
	obj_ptr->data_ptr = realloc(obj_ptr->data_ptr, *(obj_ptr->counter) * sizeof(time_t));
	
	if (NULL == obj_ptr->data_ptr)
	{
		return 0;
	}
	
	data_size_t_ptr = (size_t *)obj_ptr->data_ptr;
	
	*(data_size_t_ptr + *(obj_ptr->counter)) = time(NULL); 
	
	*(obj_ptr->counter) += 1;
	
	return 1;
}


void CleanHeap(void * data)
{
	struct mem_allo * obj_ptr = (struct mem_allo *)data;
	
	free(obj_ptr->data_ptr);
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


