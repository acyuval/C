/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Artur
*	Date:      
******************************************************************************/
#include <stdio.h>  /* printf()  	  */

#include "sll.h"


/******************************************************************************
*							TYPE DEFS / MACROS 									  * 
******************************************************************************/



/******************************************************************************
*							FUNCTION DECLRATION								  * 
******************************************************************************/

static void TestHelper(int booll , char * calling_function, int test_no); 
void TestSSLInsertCount();
void TestSLLSetData();
void TestSLLRemove();
void TestSLLFind();
int Match(void * src, void *data);
void TestIsEmptyh();

/******************************************************************************
*							MAIN											  * 
******************************************************************************/


int main()
{
	TestSLLFind();
	TestSSLInsertCount();
	TestSLLSetData();
	TestSLLRemove();
	TestIsEmptyh();
	return (0);
}




/******************************************************************************
*							TEST FUNCTIONS									  * 
******************************************************************************/


void TestSSLInsertCount()
{
	int input[5] = {50,30,20,10,1};
	
	slist_iter_t new_next = NULL;
	
	list_t * test_list = SLLCreate();
	
	new_next = SLLInsert(test_list, SLLBegin(test_list), (void *)&input[1]);
	new_next = SLLInsert(test_list, SLLBegin(test_list), (void *)&input[2]);
	new_next = SLLInsert(test_list, SLLBegin(test_list), (void *)&input[3]);
	TestHelper(*(int *)SLLGetData(new_next) == 10, "TestSSLInsert" , 1);
	
	TestHelper(SLLCount(test_list) == 3, "TestSSLCount" , 1);
		
	SLLDestroy(test_list);
}

void TestSLLSetData()
{
	int input[5] = {50,30,20,10,1};
	
	slist_iter_t new_next = NULL;
	
	list_t * test_list = SLLCreate();
	
	new_next = SLLInsert(test_list, SLLBegin(test_list), (void *)&input[1]);
	new_next = SLLInsert(test_list, SLLBegin(test_list), (void *)&input[2]);
	new_next = SLLInsert(test_list, SLLBegin(test_list), (void *)&input[3]);
	SLLSetData(new_next, (void *)&input[4]);
	TestHelper(*(int *)SLLGetData(new_next) == 1, "TestSLLSetData" , 1);
	SLLDestroy(test_list);
}


void TestSLLRemove()
{
	int input[5] = {50,30,20,10,1};
	slist_iter_t new_next = NULL;
	list_t * test_list = SLLCreate();

	new_next = SLLInsert(test_list, SLLBegin(test_list), (void *)&input[1]);
	new_next = SLLInsert(test_list, SLLBegin(test_list), (void *)&input[2]);
	new_next = SLLInsert(test_list, SLLBegin(test_list), (void *)&input[3]);
	TestHelper(*(int *)SLLGetData(new_next) == 10, "TestSLLRemove" , 1);
	SLLRemove(new_next);
	TestHelper(*(int *)SLLGetData(new_next) == 20, "TestSLLRemove" , 2);
	SLLDestroy(test_list);
}


void TestSLLFind()
{
	int input[5] = {50,30,20,10,1};
	slist_iter_t new_next = NULL;
	list_t * test_list = SLLCreate();
	new_next = SLLInsert(test_list, SLLBegin(test_list), (void *)&input[1]);
	new_next = SLLInsert(test_list, SLLBegin(test_list), (void *)&input[2]);
	new_next = SLLInsert(test_list, SLLBegin(test_list), (void *)&input[3]);
	
	new_next = SLLFind(SLLBegin(test_list),SLLEnd(test_list), &Match , (void *)&input[1]);

	TestHelper(*(int *)SLLGetData(new_next) == 30, "SLLFind" , 1);
	SLLDestroy(test_list);
}


void TestIsEmptyh()
{
	int input[5] = {50,30,20,10,1};
	slist_iter_t new_next = NULL;
	list_t * test_list = SLLCreate();
	new_next = SLLInsert(test_list, SLLBegin(test_list), (void *)&input[1]);
	new_next = SLLInsert(test_list, SLLBegin(test_list), (void *)&input[2]);
	new_next = SLLInsert(test_list, SLLBegin(test_list), (void *)&input[3]);
	
	
	TestHelper(SLLIsEmpty(test_list) == 0, "TestDestroy" , 1);
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



/******************************************************************************
*							STATIC FUNCTIONS								  * 
******************************************************************************/




static void TestHelper(int booll , char * calling_function, int test_no)
{
	if(booll)
	{
		printf("%s -> \t\tNO.%d sucsess!\n\n",calling_function, test_no);
	}
	else
	{
		printf("failed in %s, No. %d\n",calling_function ,test_no);
	}
}


