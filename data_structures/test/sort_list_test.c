/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Chen
*	Date:      
******************************************************************************/
#include <stdio.h>  /* printf()  	  */

#include "sort_list.h"


/******************************************************************************
*							TYPE DEFS / MACROS 								  * 
******************************************************************************/



/******************************************************************************
*							FUNCTION DECLRATION								  * 
******************************************************************************/

static void TestHelper(int booll , char * calling_function, int test_no); 
int comparefunc(void * src, void *data);
void TestSortedListInsertCount();
int Print(void * this_node, void *node_counter);
void TestSortedListRemove();
void TestIsEmptyh();
void TestSortedListNextPrevEnd();
void TestSortedListFind();
int Match(void * src, void *data);
void TestPopBackFront();
void TestSortedListIsEqual();
void TestSortedListMerge();
void TestForEach();
void TestSortedListFindIf();
/******************************************************************************
*							MAIN											  * 
******************************************************************************/


int main()
{
	TestSortedListMerge();

	TestIsEmptyh();

	TestSortedListInsertCount();
	TestForEach();
	TestSortedListRemove();
	TestSortedListIsEqual();
	TestSortedListNextPrevEnd();
	TestSortedListFindIf();
	TestSortedListFind();
	TestPopBackFront();

	
	return (0);
}




/******************************************************************************
*							TEST FUNCTIONS									  * 
******************************************************************************/


void TestSortedListInsertCount()
{
	int input[5] = {50,1,20,10,21};
	int i = 0; 

	sorted_list_t * test_list = SortedListCreate(&comparefunc);
	
	
	for(i = 0 ; i < 5  ; i++)
	{
		SortedListInsert(test_list, &input[i]);
	}
	
	TestHelper(*(int *)SortedListGetData(SortedListBegin(test_list)) == input[1], "TestSortedListInsert" , 1);
	
	TestHelper(SortedListSize(test_list) == 5, "TestSortedListSize  " , 1);
		
	SortedListDestroy(test_list);
}


void TestSortedListRemove()
{
	int input[5] = {50,1,120,12,10};
	int i = 0; 
	sorted_list_t * test_list = SortedListCreate(&comparefunc);
	
	for(i = 0 ; i < 5  ; i++)
	{
		SortedListInsert(test_list, &input[i]);
	}
	
	TestHelper(*(int *)SortedListGetData(SortedListBegin(test_list)) == 1, "TestSortedListRemove" , 1);
	
	SortedListRemove(SortedListBegin(test_list));
	
	TestHelper(*(int *)SortedListGetData(SortedListBegin(test_list)) == 10, "TestSortedListRemove" , 2);
	
	SortedListDestroy(test_list);
}



void TestIsEmptyh()
{
	int input[5] = {50,1,120,12,10};
	int i = 0; 
	sorted_list_t * test_list = SortedListCreate(&comparefunc);
	
	TestHelper(SortedListIsEmpty(test_list) == 1, "TestIsEmptyh \t\t" , 1);
	
	for(i = 0 ; i < 5  ; i++)
	{
		SortedListInsert(test_list, &input[i]);
	}
	
	TestHelper(SortedListIsEmpty(test_list) == 0, "TestIsEmptyh \t\t" , 2);
	SortedListDestroy(test_list);
}


void TestSortedListNextPrevEnd()
{
	int input[5] = {5021,1,120,12,10};
	int i = 0; 
	sorted_list_t * test_list = SortedListCreate(&comparefunc);
	sorted_iter_t test_itr = {0};
	
	for(i = 0 ; i < 5  ; i++)
	{
		SortedListInsert(test_list, &input[i]);
	}
	
	test_itr = SortedListBegin(test_list);
	
	TestHelper(*(int *)SortedListGetData(test_itr) == 1, "TestSortedListNext \t" , 1);
	
	test_itr = SortedListNext(test_itr);
	
	TestHelper(*(int *)SortedListGetData(test_itr) == 10, "TestSortedListNext \t" , 2);
	
	test_itr = SortedListPrev(test_itr);
	
	TestHelper(*(int *)SortedListGetData(test_itr) == 1, "TestSortedListPrev \t" , 1);
	
	test_itr = SortedListPrev(SortedListEnd(test_list));
	
	TestHelper(*(int *)SortedListGetData(test_itr) == 5021, "TestSortedListPrev \t" , 1);
	
	SortedListDestroy(test_list);
}

void TestSortedListFind()
{
	int input[5] = {5021,1,120,12,10};
	int i = 0; 
	sorted_list_t * test_list = SortedListCreate(&comparefunc);
	sorted_iter_t test_itr = {0};
	
	for(i = 0 ; i < 5  ; i++)
	{
		SortedListInsert(test_list, &input[i]);
	}	
	
	test_itr = SortedListFind(SortedListBegin(test_list),SortedListEnd(test_list), &input[0] , test_list);
	TestHelper(*(int *)SortedListGetData(test_itr) == 5021, "TestSortedListFind " , 1);
	SortedListDestroy(test_list);
}


void TestSortedListFindIf()
{
	int input[5] = {5021,1,120,12,10};
	int i = 0; 
	sorted_list_t * test_list = SortedListCreate(&comparefunc);
	sorted_iter_t test_itr = {0};
	
	for(i = 0 ; i < 5  ; i++)
	{
		SortedListInsert(test_list, &input[i]);
	}	
	
	test_itr = SortedListFindIf(SortedListBegin(test_list),SortedListEnd(test_list), &Match ,  &input[2]);
	TestHelper(*(int *)SortedListGetData(test_itr) == 1, "TestSortedListFindIf " , 1);
	SortedListDestroy(test_list);
}




int Match(void * src, void *data)
{
	if (*(int *)src < *(int *)data)
	{
		return 1;
	}
	
	return 0;
}




void TestPopBackFront()
{
	int input[5] = {5021,1,120,12,10};
	int i = 0; 
	void * res = NULL;
	sorted_list_t * test_list = SortedListCreate(&comparefunc);
	
	for(i = 0 ; i < 5  ; i++)
	{
		SortedListInsert(test_list, &input[i]);
	}	
	
	res = SortedListPopFront(test_list);
	TestHelper(*(int *)res == 1, "TestPopFront " , 1);
	
	res = SortedListPopBack(test_list);
	TestHelper(*(int *)res == 5021, "TestPopBack " , 2);
	
	
	SortedListDestroy(test_list);
}




void TestSortedListIsEqual()
{
	int input[5] = {5021,1,120,12,10};
	int i = 0; 
	sorted_list_t * test_list = SortedListCreate(&comparefunc);
	sorted_iter_t test_itr1 = {0};
	sorted_iter_t test_itr2 = {0};
	
	for(i = 0 ; i < 5  ; i++)
	{
		SortedListInsert(test_list, &input[i]);
	}	
	
	test_itr1 = SortedListFind(SortedListBegin(test_list),SortedListEnd(test_list), &input[2] , test_list);
	
	test_itr1 = SortedListNext(test_itr1);
	
	test_itr2 = SortedListFind(SortedListBegin(test_list),SortedListEnd(test_list), &input[0] , test_list);
	
	TestHelper(SortedListIsEqual(test_itr1, test_itr2), "TestSortedListIsEqual \t", 1);
	SortedListDestroy(test_list);
	
}


void TestSortedListMerge()
{
	int inputA[10] = {100,200,300,400,500,600,700,800,900,1000};
	int inputB[10] = {1,2,3,4,5,621,7,850,9,10};
	
	int Node_counter = 0;
	int i = 0;
	sorted_list_t * test_listA = SortedListCreate(&comparefunc);
	sorted_list_t * test_listB = SortedListCreate(&comparefunc);
	
	for(i = 0 ; i < 10 ; i++)
	{
		SortedListInsert(test_listA, &inputA[i]);
	}
	
	for(i = 0 ; i < 10 ; i++)
	{
		SortedListInsert(test_listB, &inputB[i]);
	}
	
	SortedListMerge(test_listA, test_listB);
	
	printf("\n-----------------------\nTestSortedListMerge:\n");
	printf("SortedList A:");
	SortedListForEach(SortedListBegin(test_listA), SortedListEnd(test_listA), &Print, &Node_counter);
	printf("\n\n");
	

	SortedListDestroy(test_listA);
	SortedListDestroy(test_listB);
}



void TestForEach()
{
	
	int input[5] = {5021,1,12012,12,10};
	int i = 0; 
	int Node_counter = 0;
	sorted_list_t * test_list = SortedListCreate(&comparefunc);
	
	for(i = 0 ; i < 5  ; i++)
	{
		SortedListInsert(test_list, &input[i]);
	}	
	
	printf("\n-----------------------\nTestForEach (print all 5 nodes):\n");
	SortedListForEach(SortedListBegin(test_list), SortedListEnd(test_list), &Print, &Node_counter);
	printf("\n-----------------------\n\n");
	SortedListDestroy(test_list);
	
}





/******************************************************************************
*							STATIC FUNCTIONS								  * 
******************************************************************************/


int Print(void * this_node, void *node_counter)
{
	dll_iter_t new_node = (dll_iter_t )this_node;
	
	int value = *(int *)DLLGet(new_node);
	*((int *)node_counter) += 1;
	if((*(int *)node_counter) % 8 == 0)
	{
		printf("\n");	
	}
	printf("Node%d:%d , ", *((int *)node_counter) ,value);
	return 0;
}

int comparefunc(void * src, void *data)
{
	if ((*(int *)src - *(int *)data) == 0)
	{
		return 1;
	} 
	return (*(int *)src - *(int *)data);
}




static void TestHelper(int booll , char * calling_function, int test_no)
{
	if(booll)
	{
		printf("%s -> \t\tNO.%d success!\n\n",calling_function, test_no);
	}
	else
	{
		printf("failed in %s, No. %d\n\n",calling_function ,test_no);
	}
}


