/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Yael
*	Date:      
******************************************************************************/
#include <stdio.h>  /* printf()  	  */

#include "dll.h"


/******************************************************************************
*							TYPE DEFS / MACROS 								  * 
******************************************************************************/



/******************************************************************************
*							FUNCTION DECLRATION								  * 
******************************************************************************/

static void TestHelper(int booll , char * calling_function, int test_no); 
void TestDLLInsertCount();
void TestDLLSetData();
void TestDLLRemove();
void TestDLLFind();
void TestDLLSetData();
void TestIsEmptyh();
void TestDLLNextPrevEnd();
void TestDLLRemove();
void TestDLLIsEqual();
void TestForEach();
void TestPushPopBackFront();
int Match(void * src, void *data);
int Print(void * this_node, void *node_counter);
void TestDLLSplice();

/******************************************************************************
*							MAIN											  * 
******************************************************************************/


int main()
{
	
	TestDLLSplice();
	TestForEach();
	TestDLLNextPrevEnd();
	TestDLLInsertCount();
	TestDLLSetData();
	TestDLLRemove();
	TestIsEmptyh();
	TestDLLFind();
	

	TestDLLIsEqual();
	
	TestPushPopBackFront();

	TestForEach();

	return (0);
}




/******************************************************************************
*							TEST FUNCTIONS									  * 
******************************************************************************/


void TestDLLInsertCount()
{
	int input[5] = {50,30,20,10,1};
	
	dll_iter_t * test_itr = NULL;
	dll_iter_t * test_itr2 = NULL;
	
	dll_t * test_dll = DLLCreate();
	
	test_itr = DLLInsert(test_dll, DLLBegin(test_dll), &input[1]);
	test_itr2 = DLLInsert(test_dll, DLLBegin(test_dll), &input[2]);
	test_itr = DLLInsert(test_dll, DLLBegin(test_dll), &input[0]);
	TestHelper(*(int *)DLLGet(DLLPrev(test_itr2)) == input[2], "TestDLLInsert" , 1);
	
	TestHelper(DLLSize(test_dll) == 3, "TestDLLSize " , 1);
		
	DLLDestroy(test_dll);
}

void TestDLLSetData()
{
	int input[5] = {50,30,20,10,1};
	
	dll_iter_t *test_itr = NULL;
	
	dll_t * test_dll = DLLCreate();
	
	test_itr = DLLInsert(test_dll, DLLBegin(test_dll), &input[1]);
	test_itr = DLLInsert(test_dll, DLLBegin(test_dll), &input[2]);
	test_itr = DLLInsert(test_dll, DLLBegin(test_dll), &input[3]);
	
	DLLSet(test_itr,&input[4]);
	
	TestHelper(*(int *)DLLGet(test_itr) == input[4], "TestDLLSetData" , 1);
	DLLDestroy(test_dll);
}


void TestDLLRemove()
{
	int input[5] = {50,30,20,10,1};
	dll_iter_t * test_itr = NULL;
	dll_t * test_dll = DLLCreate();
	test_itr = DLLInsert(test_dll, DLLBegin(test_dll), &input[0]);
	test_itr = DLLInsert(test_dll, test_itr, &input[1]);
	test_itr = DLLInsert(test_dll, test_itr, &input[2]);
	test_itr = DLLPrev(DLLInsert(test_dll, test_itr, &input[3]));
	
	TestHelper(*(int *)DLLGet(test_itr) == 10, "TestDLLRemove" , 1);
	
	test_itr = DLLRemove(DLLPrev(test_itr));
	
	TestHelper(*(int *)DLLGet(DLLPrev(test_itr)) == 30, "TestDLLRemove" , 2);
	DLLDestroy(test_dll);
}


void TestIsEmptyh()
{
	int input[5] = {50,30,20,10,1};
	dll_t * test_dll = DLLCreate();
	TestHelper(DLLIsEmpty(test_dll) == 1, "TestIsEmptyh" , 1);
	
	DLLInsert(test_dll, DLLBegin(test_dll), &input[1]);
	DLLInsert(test_dll, DLLBegin(test_dll), &input[2]);
	DLLInsert(test_dll, DLLBegin(test_dll), &input[3]);
	
	TestHelper(DLLIsEmpty(test_dll) == 0, "TestIsEmptyh" , 2);
	DLLDestroy(test_dll);
	
}


void TestDLLNextPrevEnd()
{
	int input[5] = {50,30,20,10,1};
	dll_iter_t *test_itr = NULL;
	dll_t * test_dll = DLLCreate();
	DLLInsert(test_dll, DLLBegin(test_dll), &input[1]);
	DLLInsert(test_dll, DLLBegin(test_dll), &input[2]);
	test_itr = DLLInsert(test_dll, DLLBegin(test_dll), &input[3]);
	
	TestHelper(*(int *)DLLGet(test_itr) == 20, "TestDLLNext " , 1);
	test_itr = DLLNext(test_itr);
	TestHelper(*(int *)DLLGet(test_itr) == 30, "TestDLLNext " , 2);
	test_itr = DLLPrev(test_itr);
	TestHelper(*(int *)DLLGet(test_itr) == 20, "TestDLLPrev " , 1);
	
	test_itr = DLLPrev(DLLEnd(test_dll));
	TestHelper(*(int *)DLLGet(test_itr) == 30, "TestDLLPrev " , 1);
	
	DLLDestroy(test_dll);
	
}


void TestDLLFind()
{
	int input[5] = {50,30,20,10,1};
	dll_iter_t *test_itr = NULL;
	dll_t *test_dll = DLLCreate();
	
	test_itr = DLLInsert(test_dll, DLLBegin(test_dll), &input[0]);
	test_itr = DLLInsert(test_dll, test_itr, &input[1]);
	test_itr = DLLInsert(test_dll, test_itr, &input[2]);
	test_itr = DLLPrev(DLLInsert(test_dll, test_itr, &input[3]));
	
	test_itr = DLLFind(DLLBegin(test_dll),DLLEnd(test_dll), &Match , &input[1]);
	
	TestHelper(*(int *)DLLGet(test_itr) == 30, "TestDLLFind " , 1);
	DLLDestroy(test_dll);
}


int Match(void * src, void *data)
{
	if (*(int *)src == *(int *)data)
	{
		return 1;
	}
	
	return 0;
}




void TestPushPopBackFront()
{
	int input[5] = {50,30,20,10,1};
	int Node_counter = 0;
	dll_iter_t *test_itr = NULL;
	dll_t *test_dll = DLLCreate();
	test_itr = DLLPushfront(test_dll, &input[0]);
	test_itr = DLLPushfront(test_dll, &input[1]);
	test_itr = DLLPushback(test_dll, &input[2]);
	test_itr = DLLPushback(test_dll, &input[3]);	
	printf("\n-----------------------\nTestPushBackFront\n");
	DLLForEach(DLLBegin(test_dll), DLLEnd(test_dll), &Print, &Node_counter);
	printf("\n-----------------------\n");
	
	DLLPopfront(test_dll);
	DLLPopback(test_dll);
	printf("\n-----------------------\nTestPopBackFront\n");
	DLLForEach(DLLBegin(test_dll), DLLEnd(test_dll), &Print, &Node_counter);
	printf("\n-----------------------\n");
	
	DLLDestroy(test_dll);
}




void TestDLLIsEqual()
{
	int input[5] = {50,30,20,10,1};
	dll_iter_t *test_itr1 = NULL;
	dll_iter_t *test_itr2 = NULL;
	dll_t * test_dll = DLLCreate();
	DLLInsert(test_dll, DLLBegin(test_dll), &input[3]);
	DLLInsert(test_dll, DLLBegin(test_dll), &input[2]);
	DLLInsert(test_dll, DLLBegin(test_dll), &input[1]);
	
	test_itr1 = DLLFind(DLLBegin(test_dll),DLLEnd(test_dll), &Match, &input[1]);
	test_itr1 = DLLNext(test_itr1);
	test_itr2 = DLLFind(DLLBegin(test_dll),DLLEnd(test_dll), &Match, &input[2]);
	
	TestHelper(DLLIsEqual(test_itr1, test_itr2), "TestDLLIsEqual ", 1);
	DLLDestroy(test_dll);
	
}



void TestDLLSplice()
{
	int inputA[5] = {60,70,80,90,100};
	int inputB[5] = {1,2,3,4,5};
	dll_iter_t *from = NULL;
	dll_iter_t *to = NULL;
	dll_iter_t *where = NULL;
	int Node_counter = 0;
	dll_t * test_dllA = DLLCreate();
	dll_t * test_dllB = DLLCreate();
	
	DLLInsert(test_dllA, DLLBegin(test_dllA), &inputA[4]);
	DLLInsert(test_dllA, DLLBegin(test_dllA), &inputA[3]);
	DLLInsert(test_dllA, DLLBegin(test_dllA), &inputA[3]);
	DLLInsert(test_dllA, DLLBegin(test_dllA), &inputA[1]);
	DLLInsert(test_dllA, DLLBegin(test_dllA), &inputA[3]);
	DLLInsert(test_dllA, DLLBegin(test_dllA), &inputA[3]);
	DLLInsert(test_dllA, DLLBegin(test_dllA), &inputA[3]);
	DLLInsert(test_dllA, DLLBegin(test_dllA), &inputA[0]);
	DLLInsert(test_dllA, DLLBegin(test_dllA), &inputA[2]);
	DLLInsert(test_dllA, DLLBegin(test_dllA), &inputA[0]);
	
	from = DLLFind(DLLBegin(test_dllA),DLLEnd(test_dllA), &Match, &inputA[2]);
	to   = DLLFind(DLLBegin(test_dllA),DLLEnd(test_dllA), &Match, &inputA[1]);
	
	DLLInsert(test_dllB, DLLBegin(test_dllB), &inputB[3]);
	DLLInsert(test_dllB, DLLBegin(test_dllB), &inputB[1]);
	DLLInsert(test_dllB, DLLBegin(test_dllB), &inputB[0]);
	DLLInsert(test_dllB, DLLBegin(test_dllB), &inputB[2]);
	DLLInsert(test_dllB, DLLBegin(test_dllB), &inputB[2]);
	DLLInsert(test_dllB, DLLBegin(test_dllB), &inputB[2]);
	DLLInsert(test_dllB, DLLBegin(test_dllB), &inputB[2]);
	DLLInsert(test_dllB, DLLBegin(test_dllB), &inputB[2]);
	DLLInsert(test_dllB, DLLBegin(test_dllB), &inputB[4]);
	
	where = DLLPrev(DLLFind(DLLBegin(test_dllB),DLLEnd(test_dllB), &Match, &inputB[0]));

	printf("\n-----------------------\nTestDLLSplice- before A\n");
	DLLForEach(DLLBegin(test_dllA), DLLEnd(test_dllA), &Print, &Node_counter);
	printf("\n-----------------------\n\n");
	
	Node_counter = 0;
	
	printf("\n-----------------------\nTestDLLSplice before B\n");
	DLLForEach(DLLBegin(test_dllB), DLLEnd(test_dllB), &Print, &Node_counter);
	printf("\n-----------------------\n\n");
	
	Node_counter = 0;

	DLLSplice(from, to , where);
	
		printf("\n-----------------------\nTestDLLSplice- after A\n");
	DLLForEach(DLLBegin(test_dllA), DLLEnd(test_dllA), &Print, &Node_counter);
	printf("\n-----------------------\n\n");
	
	Node_counter = 0;
	
	printf("\n-----------------------\nTestDLLSplice after B\n");
	DLLForEach(DLLBegin(test_dllB), DLLEnd(test_dllB), &Print, &Node_counter);
	printf("\n-----------------------\n\n");
	
	
	
}



void TestForEach()
{
	int input[5] = {50,30,20,10,1};
	int Node_counter = 0;
	dll_t * test_dll = DLLCreate();
	DLLInsert(test_dll, DLLEnd(test_dll), &input[1]);
	DLLInsert(test_dll, DLLEnd(test_dll), &input[2]);
	DLLInsert(test_dll, DLLEnd(test_dll), &input[3]);
	
	printf("\n-----------------------\nTestForEach\n");
	DLLForEach(DLLBegin(test_dll), DLLEnd(test_dll), &Print, &Node_counter);
	printf("\n-----------------------\n\n");
	DLLDestroy(test_dll);
	
}



int Print(void * this_node, void *node_counter)
{
	dll_iter_t * new_node = (dll_iter_t *)this_node;
	int value = *(int *)DLLGet(new_node);
	*((int *)node_counter) += 1;
	printf("Node%d:%d , ", *((int *)node_counter) ,value);
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
		printf("failed in %s, No. %d\n\n",calling_function ,test_no);
	}
}


