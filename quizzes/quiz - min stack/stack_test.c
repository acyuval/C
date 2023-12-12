/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Artur
*	Date:      
******************************************************************************/
#include <stdio.h>  /* printf()  	  */

#include "stack.h"

int main()
{
	stack_t * this_stack = NULL;
	stack_t * min_stack = NULL;
	this_stack = StackCreate(12, sizeof(int));
	min_stack = StackCreate(12, sizeof(int));
	
	return (0);
}

int add(void *data,stack_t * this_stack, stack_t * min_stack)
{
	if(data < StackPeek(min_stack))
	{
		StackPush(min_stack, data);
	}
	else
	{
		StackPush(min_stack, StackPeek(min_stack));
	}
	
	stackPush(this_stack, data);
}

int remove(stack_t * this_stack, stack_t * min_stack)
{
	
	stackPop(this_stack);
	
	stackPop(min_stack);
}

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

