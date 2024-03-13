/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Yael
*	Date:      
******************************************************************************/
#include <stdio.h>  /* printf()  	  */

#include "sll.h"


/******************************************************************************
*							TYPE DEFS / MACROS 								  * 
******************************************************************************/



/******************************************************************************
*							FUNCTION DECLRATION								  * 
******************************************************************************/

static void TestHelper(int booll , char * calling_function, int test_no); 
void TestSSLInsertCount();
void TestSLLSetData();
void TestSLLRemove();
void TestSLLFind();
void TestSLLSetData();
void TestIsEmptyh();
void TestSLLRemove();
void TestSLLIsEqual();
void TestForEach();
int Match(void * src, void *data);
int Print(void * this_node, void *node_counter);

/******************************************************************************
*							MAIN											  * 
******************************************************************************/


int main()
{
	TestSSLInsertCount();
	TestSLLSetData();
	TestSLLRemove();
	TestSLLFind();
	TestSLLSetData();
	TestIsEmptyh();
	TestSLLRemove();
	TestSLLIsEqual();
	TestForEach();
	return (0);
}




/******************************************************************************
*							TEST FUNCTIONS									  * 
******************************************************************************/


void TestSSLInsertCount()
{
	int input[5] = {50,30,20,10,1};
	
	slist_iter_t test_itr = NULL;
	slist_iter_t test_itr2 = NULL;
	
	list_t * test_list = SLLCreate();
	
	test_itr2 = SLLInsert(test_list, SLLBegin(test_list), &input[1]);
	test_itr = SLLInsert(test_list, SLLBegin(test_list), &input[2]);
	test_itr = SLLInsert(test_list, test_itr2, &input[3]);
	TestHelper(*(int *)SLLGetData(test_itr) == input[3], "TestSSLInsert" , 1);
	
	TestHelper(SLLCount(test_list) == 3, "TestSSLCount" , 1);
		
	SLLDestroy(test_list);
}

void TestSLLSetData()
{
	int input[5] = {50,30,20,10,1};
	
	slist_iter_t test_itr = NULL;
	
	list_t * test_list = SLLCreate();
	
	test_itr = SLLInsert(test_list, SLLBegin(test_list), &input[1]);
	test_itr = SLLInsert(test_list, SLLBegin(test_list), &input[2]);
	test_itr = SLLInsert(test_list, SLLBegin(test_list), &input[3]);
	SLLSetData(test_itr,&input[4]);
	
	TestHelper(*(int *)SLLGetData(test_itr) == input[4], "TestSLLSetData" , 1);
	SLLDestroy(test_list);
}


void TestSLLRemove()
{
	int input[5] = {50,30,20,10,1};
	slist_iter_t test_itr = NULL;
	list_t * test_list = SLLCreate();

	test_itr = SLLInsert(test_list, SLLBegin(test_list), (void *)&input[1]);
	test_itr = SLLInsert(test_list, SLLBegin(test_list), (void *)&input[2]);
	test_itr = SLLInsert(test_list, SLLBegin(test_list), (void *)&input[3]);
	
	TestHelper(*(int *)SLLGetData(test_itr) == 10, "TestSLLRemove" , 1);
	SLLRemove(test_itr);
	TestHelper(*(int *)SLLGetData(test_itr) == 20, "TestSLLRemove" , 2);
	SLLDestroy(test_list);
}


void TestSLLFind()
{
	int input[5] = {50,30,20,10,1};
	slist_iter_t test_itr = NULL;
	list_t * test_list = SLLCreate();
	test_itr = SLLInsert(test_list, SLLBegin(test_list), (void *)&input[1]);
	test_itr = SLLInsert(test_list, SLLBegin(test_list), (void *)&input[2]);
	test_itr = SLLInsert(test_list, SLLBegin(test_list), (void *)&input[3]);
	
	test_itr = SLLFind(SLLBegin(test_list),SLLEnd(test_list), &Match , (void *)&input[1]);
	
	TestHelper(*(int *)SLLGetData(test_itr) == 30, "TestSLLFind " , 1);
	SLLDestroy(test_list);
}


void TestIsEmptyh()
{
	int input[5] = {50,30,20,10,1};
	list_t * test_list = SLLCreate();
	SLLInsert(test_list, SLLBegin(test_list), (void *)&input[1]);
	SLLInsert(test_list, SLLBegin(test_list), (void *)&input[2]);
	SLLInsert(test_list, SLLBegin(test_list), (void *)&input[3]);
	
	
	TestHelper(SLLIsEmpty(test_list) == 0, "TestIsEmptyh" , 1);
	SLLDestroy(test_list);
	
}


void TestSLLNext()
{
	int input[5] = {50,30,20,10,1};
	slist_iter_t test_itr = NULL;
	list_t * test_list = SLLCreate();
	SLLInsert(test_list, SLLBegin(test_list), (void *)&input[1]);
	SLLInsert(test_list, SLLBegin(test_list), (void *)&input[2]);
	SLLInsert(test_list, SLLBegin(test_list), (void *)&input[3]);
	
	test_itr = SLLFind(SLLBegin(test_list),SLLEnd(test_list), &Match , (void *)&input[2]);
	TestHelper(*(int *)SLLGetData(test_itr) == 20, "TestSLLNext " , 1);
	test_itr = SLLNext(test_itr);
	TestHelper(*(int *)SLLGetData(test_itr) == 30, "TestSLLNext " , 2);
	SLLDestroy(test_list);
	
}

void TestSLLIsEqual()
{
	int input[5] = {50,30,20,10,1};
	slist_iter_t test_itr1 = NULL;
	slist_iter_t test_itr2 = NULL;
	list_t * test_list = SLLCreate();
	SLLInsert(test_list, SLLBegin(test_list), (void *)&input[3]);
	SLLInsert(test_list, SLLBegin(test_list), (void *)&input[2]);
	SLLInsert(test_list, SLLBegin(test_list), (void *)&input[1]);
	
	test_itr1 = SLLFind(SLLBegin(test_list),SLLEnd(test_list), &Match , (void *)&input[1]);
	test_itr1 = SLLNext(test_itr1);
	test_itr2 = SLLFind(SLLBegin(test_list),SLLEnd(test_list), &Match , (void *)&input[2]);
	
	TestHelper(SLLIsEqual(test_itr1, test_itr2), "TestSLLIsEqual " , 1);
	SLLDestroy(test_list);
	
}

void TestForEach()
{
	int input[5] = {50,30,20,10,1};
	int Node_counter = 0;
	list_t * test_list = SLLCreate();
	SLLInsert(test_list, SLLEnd(test_list), (void *)&input[1]);
	SLLInsert(test_list, SLLEnd(test_list), (void *)&input[2]);
	SLLInsert(test_list, SLLEnd(test_list), (void *)&input[3]);
	
	printf("\n-----------------------\nTestForEach\n");
	SLLForEach(SLLBegin(test_list), SLLEnd(test_list), &Print, (void *)&Node_counter);
	printf("\n-----------------------\n\n");
	SLLDestroy(test_list);
	
}


int Match(void * src, void *data)
{
	if (*(int *)src == *(int *)data)
	{
		return 1;
	}
	
	return 0;
}



int Print(void * this_node, void *node_counter)
{
	slist_iter_t new_node = (slist_iter_t)this_node;
	int value = *(int *)SLLGetData(new_node);
	*((int *)node_counter) += 1;
	printf("Node: %d-Value: %d , ", *((int *)node_counter) ,value);
	return 0;
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


