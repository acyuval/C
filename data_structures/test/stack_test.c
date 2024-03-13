/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Artur
*	Date:      
******************************************************************************/
#include <stdio.h>  /* printf()  	  */

#include "stack.h"

static void TestHelper(int booll , char * calling_function, int test_no); 
stack_t * TestStackCreate();
void TestStackPush();
void TestStackPop();
void TestStackPeek();
void TestStackIsEmpty();
void TestStackSize();
void TestStackCapacity();

int main()
{
	TestStackCreate();
	TestStackPush();
	TestStackPop();
	TestStackPeek();
	TestStackIsEmpty();
	TestStackSize();
	TestStackCapacity();
	
	return (0);
}


stack_t * TestStackCreate()
{
	stack_t * this_stack = NULL;
	this_stack = StackCreate(12, sizeof(int));
	TestHelper(NULL != this_stack,"TestStackCreate", 1);
	
	return (this_stack);
}



void TestStackPush()
{
	
	int i = 4;
	
	stack_t * this_stack = NULL;
	this_stack = StackCreate(12, sizeof(int));
	
	StackPush(this_stack, &i);
	
	TestHelper(4 == *(int *)StackPeek(this_stack),"TestStackPush", 1);
	StackDestroy(this_stack);
}


void TestStackPop()
{
	int input[2] = {4,2};
	stack_t * this_stack = StackCreate(12, sizeof(int));
	StackPush(this_stack,&input[0]);
	StackPush(this_stack,&input[1]);
	StackPop(this_stack);
	TestHelper(4 == *(int *)StackPeek(this_stack),"TestStackPop", 1);
	StackDestroy(this_stack);
}


void TestStackPeek()
{
	
	int input[2] = {4,2};
	stack_t * this_stack = StackCreate(12, sizeof(int));
	StackPush(this_stack,&input[0]);
	StackPush(this_stack,&input[1]);
	
	TestHelper(2 == *(int *)StackPeek(this_stack),"TestStackPeek", 1);
	StackDestroy(this_stack);
}


void TestStackIsEmpty()
{
	int input[2] = {4,2};
	stack_t * this_stack = StackCreate(12, sizeof(int));
	
	TestHelper(1 == StackIsEmpty(this_stack),"TestStackIsEmpty", 1);
	
	StackPush(this_stack,&input[0]);
	
	TestHelper(0 == StackIsEmpty(this_stack),"TestStackIsEmpty", 2);
	
	StackDestroy(this_stack);
}



void TestStackSize()
{
	
	int input[2] = {4,2};
	stack_t * this_stack = StackCreate(12, sizeof(int));
	
	TestHelper(0 == StackSize(this_stack),"TestStackSize", 1);
	
	StackPush(this_stack,&input[0]);
	
	TestHelper(1 == StackSize(this_stack),"TestStackSize", 2);
	
	StackDestroy(this_stack);

}


void TestStackCapacity()
{
	
	stack_t * this_stack = StackCreate(12, sizeof(int));
	
	TestHelper(12 == StackCapacity(this_stack),"TestStackCapacity", 1);
	
	StackDestroy(this_stack);


}

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

