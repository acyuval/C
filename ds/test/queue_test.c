/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Yael
*	Date:      
******************************************************************************/
#include <stdio.h>  /* printf()  	  */

#include "queue.h"


/******************************************************************************
*							TYPE DEFS / MACROS 								  * 
******************************************************************************/



/******************************************************************************
*							FUNCTION DECLRATION								  * 
******************************************************************************/

static void TestHelper(int booll , char * calling_function, int test_no); 
void TestQueueEnQueueSize();
void TestQueueDeQueue();
void TestIssEmpty();
void TestQueueAppend();
/******************************************************************************
*							MAIN											  * 
******************************************************************************/


int main()
{
	TestQueueAppend();
	
	TestQueueEnQueueSize();
	TestQueueDeQueue();
	TestIssEmpty();
	return (0);
}




/******************************************************************************
*							TEST FUNCTIONS									  * 
******************************************************************************/


void TestQueueEnQueueSize()
{
	int input[5] = {50,30,20,10,1};
	
	
	queue_t * test_queue = QueueCreate();
	
	QueueEnqueue(test_queue, &input[1]);
	QueueEnqueue(test_queue, &input[2]);
	QueueEnqueue(test_queue, &input[3]);
	
	TestHelper(*(int *)QueuePeek(test_queue) == input[1], "TestQueueEnQueue" , 1);
	
	TestHelper(QueueSize(test_queue) == 3, "TestQueueSize" , 1);
		
	QueueDestroy(test_queue);
}



void TestQueueDeQueue()
{
	int input[5] = {50,30,20,10,1};
	
	queue_t * test_queue = QueueCreate();
	
	QueueEnqueue(test_queue, &input[1]);
	QueueEnqueue(test_queue, &input[2]);
	QueueEnqueue(test_queue, &input[3]);
	
	TestHelper(*(int *)QueuePeek(test_queue) == 30, "TestQueueDeQueue" , 1);
	
	QueueDequeue(test_queue);
	TestHelper(*(int *)QueuePeek(test_queue) == 20, "TestQueueDeQueue" , 2);
	
	QueueDestroy(test_queue);
}




void TestIssEmpty()
{
	int input[5] = {50,30,20,10,1};
	queue_t * test_queue = QueueCreate();
	QueueEnqueue(test_queue, &input[1]);
	QueueEnqueue(test_queue, &input[2]);
	QueueEnqueue(test_queue, &input[3]);
	
	
	TestHelper(QueueIsEmpty(test_queue) == 0, "TestIsEmpty  " , 1);
	QueueDestroy(test_queue);
	
}


void TestQueueAppend()
{
	int inputA[5] = {50,30,20,10,1};
	int inputB[5] = {95,13,55,12,22};
	
	queue_t * test_queueA = QueueCreate();
	queue_t * test_queueB = QueueCreate();
	
	QueueEnqueue(test_queueA, &inputA[1]);
	QueueEnqueue(test_queueA, &inputA[2]);
	QueueEnqueue(test_queueA, &inputA[3]);
	
	QueueEnqueue(test_queueB, &inputB[1]);
	QueueEnqueue(test_queueB, &inputB[2]);
	QueueEnqueue(test_queueB, &inputB[3]);
	
	QueueAppend(test_queueA, test_queueB);
	
	TestHelper(QueueSize(test_queueA) == 6, "TestQueueAppend  " , 1);
	QueueDestroy(test_queueA);
	QueueDestroy(test_queueB);
	
}


/******************************************************************************
*							STATIC FUNCTIONS								  * 
******************************************************************************/




static void TestHelper(int booll , char * calling_function, int test_no)
{
	if(booll)
	{
		printf("%s -> \t\tNO.%d success!\n\n",calling_function, test_no);
	}
	else
	{
		printf("failed in %s, No. %d\n",calling_function ,test_no);
	}
}


