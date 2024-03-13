#ifndef __STACK_H__
#define __STACK_H__

#include <stddef.h> /* size_t */

typedef struct stack stack_t;

/******************************************************************************
*Description: creates a new stack
*Arguments: capacity of the stack and the size of the elements
*Return Value: pointer to the stack 
*Time Complexity: O(1)
*Space Complexity: O(n)
Notes: capacity or element size of 0 is an undefined behavior
******************************************************************************/
stack_t *StackCreate(size_t capacity, size_t element_size);


/******************************************************************************
*Description: destroys the given stack
*Arguments: pointer to the stack
*Return Value: void
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
void StackDestroy(stack_t *stack);


/******************************************************************************
*Description: pushes the given data to the top of the stack
*Arguments: pointer to the stack and the data to be pushed
*Return Value: void
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: pushing to a full stack leads to undefined behavior
******************************************************************************/
void StackPush(stack_t *stack, const void *data);


/******************************************************************************
*Description: pops the top of the stack out
*Arguments: pointer to the stack
*Return Value: void
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: popping out of an empty stack leads to undefined behavior
******************************************************************************/
void StackPop(stack_t *stack);


/******************************************************************************
*Description: returns the data at the top of the stack
*Arguments: pointer to the stack
*Return Value: the data at the top of the stack
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: peeking into an empty stack leads to undefined behavior
******************************************************************************/
void *StackPeek(const stack_t *stack);


/******************************************************************************
*Description: checks whether the stack is empty or not 
*Arguments: pointer to the stack
*Return Value: boolean, TRUE if the stack is empty and FALSE otherwise
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
int StackIsEmpty(const stack_t *stack);


/******************************************************************************
*Description: returns the current size of the stack
*Arguments: pointer to the stack
*Return Value: the current size of the stack
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
size_t StackSize(const stack_t *stack);


/******************************************************************************
*Description: returns the capacity of the stack
*Arguments: pointer to the stack
*Return Value: the capacity of the stack
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
size_t StackCapacity(const stack_t *stack);

void PrintStack(stack_t *stack);
#endif	/* __STACK_H__*/

