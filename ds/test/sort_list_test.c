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
/******************************************************************************
*							MAIN											  * 
******************************************************************************/


int main()
{
	TestPopBackFront();
	TestSortedListFind();
	TestSortedListNextPrevEnd();
	TestIsEmptyh();
	TestSortedListInsertCount();
	TestSortedListRemove();
	
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
	
	sorted_iter_t test_itr = SortedListBegin(test_list);
	
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
	sorted_iter_t test_itr = SortedListBegin(test_list);
	
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
	sorted_iter_t test_itr = SortedListBegin(test_list);
	
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


int Match(void * src, void *data)
{
	if (*(int *)src == *(int *)data)
	{
		return 1;
	}
	
	return 0;
}




void TestPopBackFront()
{
	int Node_counter = 0;
	int input[5] = {5021,1,120,12,10};
	int i = 0; 
	void * res = NULL;
	sorted_list_t * test_list = SortedListCreate(&comparefunc);
	sorted_iter_t test_itr = {0};
	
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
	int Node_counter = 0;
	int input[5] = {5021,1,120,12,10};
	int i = 0; 
	void * res = NULL;
	sorted_list_t * test_list = SortedListCreate(&comparefunc);
	sorted_iter_t test_itr = {0};
	
	for(i = 0 ; i < 5  ; i++)
	{
		SortedListInsert(test_list, &input[i]);
	}	
	
	test_itr1 = SortedListFind(SortedListBegin(test_list),SortedListEnd(test_list), &Match, &input[1]);
	test_itr1 = SortedListNext(test_itr1);
	test_itr2 = SortedListFind(SortedListBegin(test_list),SortedListEnd(test_list), &Match, &input[2]);
	
	TestHelper(SortedListIsEqual(test_itr1, test_itr2), "TestSortedListIsEqual ", 1);
	SortedListDestroy(test_list);
	
}

/*

void TestSortedListSplice()
{
	int inputA[10] = {100,200,300,400,500,600,700,800,900,1000};
	int inputB[10] = {1,2,3,4,5,6,7,8,9,10};
	sorted_iter_t from = NULL;
	sorted_iter_t to = NULL;
	sorted_iter_t where = NULL;
	int Node_counter = 0;
	int i = 0;
	sorted_list_t * test_listA = SortedListCreate();
	sorted_list_t * test_listB = SortedListCreate();
	
	for(i = 0 ; i < 10 ; i++)
	{
		SortedListInsert(test_listA, SortedListBegin(test_listA), &inputA[i]);
	}
	
	for(i = 0 ; i < 10 ; i++)
	{
		SortedListInsert(test_listB, SortedListBegin(test_listB), &inputB[i]);
	}
	
	
	from = SortedListFind(SortedListBegin(test_listA),SortedListEnd(test_listA), &Match, &inputA[6]);
	to   = SortedListFind(SortedListBegin(test_listA),SortedListEnd(test_listA), &Match, &inputA[2]);
	where = SortedListPrev(SortedListFind(SortedListBegin(test_listB),SortedListEnd(test_listB), &Match, &inputB[4]));

	printf("\n-----------------------\nTestSortedListSplice- before\n");
	printf("SortedList A:");
	SortedListForEach(SortedListBegin(test_listA), SortedListEnd(test_listA), &Print, &Node_counter);
	Node_counter = 0;
	printf("\nSortedList B:");
	SortedListForEach(SortedListBegin(test_listB), SortedListEnd(test_listB), &Print, &Node_counter);
	printf("\n-----------------------\n");
	
	TestHelper(SortedListSize(test_listA) == 10, "TestSortedListSplice ", 1);
	TestHelper(SortedListSize(test_listB) == 10, "TestSortedListSplice ", 2);
	Node_counter = 0;

	SortedListSplice(from, to , where);
	
	printf("-----------------------\nTestSortedListSplice- after\n");
	printf("SortedList A:");
	SortedListForEach(SortedListBegin(test_listA), SortedListEnd(test_listA), &Print, &Node_counter);
	Node_counter = 0;
	printf("\nSortedList B:");
	SortedListForEach(SortedListBegin(test_listB), SortedListEnd(test_listB), &Print, &Node_counter);
	printf("\n-----------------------\n");
	
	TestHelper(SortedListSize(test_listA) == 6, "TestSortedListSplice ", 3);
	TestHelper(SortedListSize(test_listB) == 14, "TestSortedListSplice ", 4);

	SortedListDestroy(test_listA);
	SortedListDestroy(test_listB);
}



void TestForEach()
{
	int input[5] = {50,30,20,10,1};
	int Node_counter = 0;
	sorted_list_t * test_list = SortedListCreate();
	SortedListInsert(test_list, SortedListEnd(test_list), &input[1]);
	SortedListInsert(test_list, SortedListEnd(test_list), &input[2]);
	SortedListInsert(test_list, SortedListEnd(test_list), &input[3]);
	
	printf("\n-----------------------\nTestForEach\n");
	SortedListForEach(SortedListBegin(test_list), SortedListEnd(test_list), &Print, &Node_counter);
	printf("\n-----------------------\n\n");
	SortedListDestroy(test_list);
	
}

void TestMultiFind()
{
	int input[7] = {50,30,20,10,1, 20, 20};
	int i = 0;
	sorted_list_t * test_list = SortedListCreate();
	sorted_list_t * output = SortedListCreate();
	sorted_iter_t iter = NULL;
	int value = 0;
	int counter = 0;
	for(i = 0 ; i < 7 ; i++)
	{
		SortedListInsert(test_list, SortedListEnd(test_list), &input[i]);
	}
	
	SortedListInsert(test_list, SortedListEnd(test_list), &input[6]);
	SortedListInsert(test_list, SortedListEnd(test_list), &input[1]);
	SortedListInsert(test_list, SortedListEnd(test_list), &input[2]);
	
	counter = SortedListMultiFind(SortedListBegin(test_list),SortedListEnd(test_list),&Match,&input[1], output);
	i = 0;	
	iter = SortedListBegin(output);
	
	while(counter > 0)  
	{
		value = *(int *)SortedListGet(iter);
		TestHelper(value == input[1],"TestMultiFind", i);
		iter = SortedListNext(iter);
		i++;
		counter--;
	}
	SortedListDestroy(output);
	SortedListDestroy(test_list);
}




/******************************************************************************
*							STATIC FUNCTIONS								  * 
******************************************************************************/


int Print(void * this_node, void *node_counter)
{
	sorted_iter_t* new_node = (sorted_iter_t *)this_node;
	
	int value = *(int *)SortedListGetData(*new_node);
	*((int *)node_counter) += 1;
	printf("Node%d:%d , ", *((int *)node_counter) ,value);
	return 0;
}


int comparefunc(void * src, void *data)
{
	if(NULL == src)
	{
		return 1;
	}
	return (*(int *)src - *(int *)data);
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


