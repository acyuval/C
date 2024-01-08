/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Yael
*	Date:      
******************************************************************************/
#include <stdio.h>  /* printf()  	  */
#include <stdlib.h>


#include "../include/recursion.h"

#include "../include/stack.h"


/******************************************************************************
*							TYPE DEFS / MACROS 								  * 
******************************************************************************/



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
static void TestHelper(int booll , char * calling_function, int test_no);
/******************************************************************************
*							MAIN											  * 
******************************************************************************/


int main()
{
    
	TestSortedStack();
	
	TestRecursiveStrstr();
	
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
    printf("res is %d", res);
	res = IterativeFibonacci(10);
    printf("res is %d", res);
}

void TestFlipList()
{

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
		printf("%s -> \t\tNO.%d sucsess!\n\n",calling_function, test_no);
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




