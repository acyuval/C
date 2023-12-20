/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Chen
*	Date:      
******************************************************************************/
#include <stdio.h>  /* printf()  	  */

#include "pq.h"


/******************************************************************************
*							TYPE DEFS / MACROS 								  * 
******************************************************************************/



/******************************************************************************
*							FUNCTION DECLRATION								  * 
******************************************************************************/

static void TestHelper(int booll , char * calling_function, int test_no); 
int comparefunc(void * src, void *data);
void TestPQEnqueueCount();
void TestIsEmptyh();
void TestPQEnqueue();
void TestPQClear();
void TestPQErase();
int Print(void * this_node, void *node_counter);
int Match(void * src, void *data);
/******************************************************************************
*							MAIN											  * 
******************************************************************************/


int main()
{
	TestPQClear();
	TestPQEnqueueCount();
	TestPQEnqueueCount();
	TestIsEmptyh();
	TestPQEnqueue();
	TestPQErase();
	return (0);
}




/******************************************************************************
*							TEST FUNCTIONS									  * 
******************************************************************************/


void TestPQEnqueueCount()
{
	int input[5] = {50,1,20,10,21};
	int i = 0; 

	pq_t * test_list = PQCreate(&comparefunc);
	
	for(i = 0 ; i < 5  ; i++)
	{
		PQEnqueue(test_list, &input[i]);
	}
	
	TestHelper(*(int *)PQPeek(test_list) == input[1], "TestPQInsert" , 1);
	
	TestHelper(PQSize(test_list) == 5, "TestPQSize  " , 1);
		
	PQDestroy(test_list);
}


void TestPQEnqueue()
{
	int input[5] = {50,1,120,12,10};
	int i = 0; 
	pq_t * test_list = PQCreate(&comparefunc);
	
	for(i = 0 ; i < 5  ; i++)
	{
		PQEnqueue(test_list, &input[i]);
	}
	
	TestHelper(*(int *)PQPeek(test_list) == 1, "TestPQEnqueue" , 1);
	
	TestHelper(*(int *)PQDequeue(test_list) == 1, "TestPQEnqueue" , 2);
	
	TestHelper(*(int *)PQPeek(test_list) == 10, "TestPQEnqueue" , 3);
	
	PQDestroy(test_list);
}


void TestIsEmptyh()
{
	int input[5] = {50,1,120,12,10};
	int i = 0; 
	pq_t * test_list = PQCreate(&comparefunc);
	
	TestHelper(PQIsEmpty(test_list) == 1, "TestIsEmptyh" , 1);
	
	for(i = 0 ; i < 5  ; i++)
	{
		PQEnqueue(test_list, &input[i]);
	}
	
	TestHelper(PQIsEmpty(test_list) == 0, "TestIsEmptyh" , 2);
	PQDestroy(test_list);
}


void TestPQClear()
{
	int input[5] = {50,1,120,12,10};
	int i = 0; 
	pq_t * test_list = PQCreate(&comparefunc);
	
	for(i = 0 ; i < 5  ; i++)
	{
		PQEnqueue(test_list, &input[i]);
	}
	
	
	TestHelper(PQSize(test_list) == 5, "TestPQSize  " , 1);
	
	PQClear(test_list);

	TestHelper(PQSize(test_list) == 0, "TestPQSize  " , 2);
	
	PQDestroy(test_list);
}


void TestPQErase()
{
	void * return_data = NULL;
	int input[5] = {1,2,120,150,190};
	int i = 0; 
	pq_t * test_list = PQCreate(&comparefunc);
	
	for(i = 0 ; i < 5  ; i++)
	{
		PQEnqueue(test_list, &input[i]);
	}
	TestHelper(PQSize(test_list) == 5, "TestPQErase  " , 1);
	return_data = PQErase(test_list, &Match, &input[3]);
	TestHelper(*(int *)return_data == 190, "TestPQErase  " , 3);
	TestHelper(PQSize(test_list) == 4, "TestPQErase  " , 2);
	
	PQDestroy(test_list);
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


