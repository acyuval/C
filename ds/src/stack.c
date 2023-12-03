/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Artur
*	Date:      
******************************************************************************/

#include <string.h> /* memcpy()				*/
#include <stdlib.h> /* malloc()	free()		*/ 
#include <assert.h> /* assert()				*/
#include <assert.h>
#include "stack.h"



struct stack 
{
	char * stack_ptr;
	size_t element_size ; 
	size_t size;
	size_t capacity;
};


stack_t *StackCreate(size_t capacity, size_t element_size)
{
	stack_t * this_stack = (stack_t *)malloc(sizeof(stack_t)); 
	
	if (NULL == this_stack)
	{
		return this_stack;
	} 
	
	this_stack->stack_ptr = malloc(element_size*capacity);
	
	if (NULL == this_stack->stack_ptr)
	{
		free(this_stack);
		return this_stack;
	}
	
	this_stack->element_size = element_size; 
	this_stack->size = 0;
	this_stack->capacity = capacity; 
	
	return (this_stack);
}

void StackDestroy(stack_t *stack)
{
	assert(NULL != stack);
	free((stack-> stack_ptr) - (stack->size * stack->element_size ));
	free(stack);
}

void StackPush(stack_t *stack, const void *data)
{
	assert(NULL != stack);
	assert(stack->size < stack->capacity);
	
	memcpy(stack-> stack_ptr, data, stack-> element_size);
	
	stack-> stack_ptr +=  stack-> element_size;
		
	stack-> size += 1;
}



void StackPop(stack_t *stack)
{
	assert(NULL != stack);
	assert(stack->size != 0);
	
	stack-> stack_ptr -=  stack-> element_size;
	stack->size -= 1;
}


void *StackPeek(const stack_t *stack)
{
	assert(NULL != stack);
	
	return (stack->stack_ptr - stack->element_size);
}

int StackIsEmpty(const stack_t *stack)
{
	assert(NULL != stack);
	
	return (stack->size ? 0 : 1);
}


size_t StackSize(const stack_t *stack)
{
	assert(NULL != stack);
	
	return (stack->size);
}


size_t StackCapacity(const stack_t *stack)
{
	assert(NULL != stack);
	
	return (stack->capacity);
}

