/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Yael
*	Date:      
******************************************************************************/
#include <stdio.h>  /* printf()  	  */
#include <stdlib.h>


#include "../include/recursion.h"

#include "../include/stack.h"
#include "../include/utiles.h"

/******************************************************************************
*							TYPE DEFS / MACROS 								  * 
******************************************************************************/

extern int counter;

/******************************************************************************
*							FUNCTION DECLRATION								  * 
******************************************************************************/
void TestFibonaci();
void TestSortedStack();
void TestRecursiveStrLen();
void TestRecursiveStrcmp();
void TestRecursiveStrCpy();
void TestRecursiveStrcat();
void TestSortedStack();
void TestRecursiveStrstr();
int TestRecursiveFlipList(void);
static void TestHelper(int booll , char * calling_function, int test_no);
/******************************************************************************
*							MAIN											  * 
******************************************************************************/


int main()
{
    TestRecursiveFlipList();
	
	TestSortedStack();
	
	TestRecursiveStrstr();
	TestFibonaci();
	TestRecursiveStrcat();
	
	TestRecursiveStrCpy();
	TestRecursiveStrcmp();
	TestRecursiveStrLen();
	
	return (0);
}




/******************************************************************************
*							TEST FUNCTIONS									  * 
******************************************************************************/
void TestFibonaci()
{
    
	int res = RecursiveFibonacci(10);
    printf("\nres is recu %d counter: %d \n", res , counter);
	counter = 0; 
	res = IterativeFibonacci(10);
    printf("\nres iter is %d counter: %d\n", res , counter);
}

int TestRecursiveFlipList(void)
{
	int code = SUCCESS;
	int i = 0;
	int results[10] = {0};
	node_t list[10];
	node_t *tail;

	for (i = 0; i < 10; ++i)
	{
		results[i] = i;
		list[i].data = &results[i];
		list[i].next = &list[i + 1];
	}
	list[9].next = NULL;

	tail = RecursiveFlipList(list);

	for (i = 9; i >= 0; --i)
	{
		if (*(int *)tail->data != results[i])
		{
			printf("Your Flipping list function is not flipping working, go fix your code!\n");
			code = FAIL;
		}

		tail = tail->next;
	}

	return (printf("\nstatus = %d\n", code));
}

void TestSortedStack()
{
	stack_t * unsorted = StackCreate(20, sizeof(int));
	int i = 0;
	int randnum = 0;
	int l_peek = 0;
	int s_peek = 0; 

	for(i = 0 ; i < 10 ; i++)
	{
		randnum = rand()%10;
		StackPush(unsorted , &randnum);
	}
	SortStack(unsorted);

	for(i = 0 ; i < 10 ; i+=2)
	{
		l_peek = *(int *)StackPeek(unsorted);
		StackPop(unsorted);
		s_peek = *(int *)StackPeek(unsorted);
		StackPop(unsorted);
		TestHelper(l_peek >= s_peek, "TestSortedStack" , i/2);
	}
	StackDestroy(unsorted);
}


void TestRecursiveStrLen()
{
	char * str = "leangth is 8";

	TestHelper(12 == RecursiveStrLen(str), "TestRecursiveStrLen" , 1 );
}


void TestRecursiveStrcmp()
{
	char * str1 = "leangth is 8";
	char * str2 = "leangth is 8";
	char * str3 = "leangth it 8";
	TestHelper(0 == RecursiveStrcmp(str1, str2), "TestRecursiveStrcmp" , 1 );
	TestHelper(-1 == RecursiveStrcmp(str1, str3), "TestRecursiveStrcmp" , 2);
}


void TestRecursiveStrCpy()
{
	char * src = "leangth is 8";
	char dest[12] = {0};
	RecursiveStrcpy(dest, src);
	TestHelper(0 == RecursiveStrcmp(dest, src), "TestRecursiveStrCpy" , 1 );
	
}



void TestRecursiveStrcat()
{
	char * src = " is 8";
	char dest[12] = "length";
	char * expected  = "length is 8";
	RecursiveStrcat(dest, src);
	TestHelper(0 == RecursiveStrcmp(dest, expected), "TestRecursiveStrcat" , 1 );
	
}


void TestRecursiveStrstr()
{
	char * needle = "is";
	char * haystack  = "length is 8";
	char * result = NULL;
	result = RecursiveStrstr(haystack, needle);
	TestHelper(0 == RecursiveStrcmp(result, "is 8"), "TestRecursiveStrstr" , 1 );
	
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

int cmpfunc (const void * a, const void * b)
{
   return ( *(int *)a - *(int *)b );
}




