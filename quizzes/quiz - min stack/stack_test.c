/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Artur
*	Date:      
******************************************************************************/
#include <stdio.h>  /* printf()  	  */

#include "stack.h"
int add(void *data,stack_t * this_stack, stack_t * min_stack);
int remover(stack_t * this_stack, stack_t * min_stack);

int main()
{
	int i = 0 ;
	stack_t * this_stack = NULL;
	stack_t * min_stack = NULL;
	int input[5] = {12, 4, 42, 1, 9};
	this_stack = StackCreate(12, sizeof(int));
	min_stack = StackCreate(12, sizeof(int));
	StackPush(min_stack, &input[0]);
	for(i=0 ; i<5 ; i++)
	{
		add(&input[i], this_stack, min_stack);
	}
	
	for(i=0 ; i<5 ; i++)
	{
		printf("min val: %d\n", *(int*)StackPeek(min_stack));
		printf("stack val: %d\n", *(int*)StackPeek(this_stack));
		 remover(this_stack,min_stack);
	}
	
	
	
	return (0);
}



int add(void *data,stack_t * this_stack, stack_t * min_stack)
{
	StackPush(this_stack, data);
	if(*(int *)data < *(int *)StackPeek(min_stack))
	{
		StackPush(min_stack, data);
	}
	else
	{
		StackPush(min_stack, StackPeek(min_stack));
	}
	
}

int remover(stack_t * this_stack, stack_t * min_stack)
{
	
	StackPop(this_stack);
	
	StackPop(min_stack);
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

