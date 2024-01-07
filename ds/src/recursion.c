    
    /******************************************************************************
*	Author:    Yuval 
*	Reviewer : Dor
*	Date:      
******************************************************************************/

#include <stdlib.h> /* malloc() , free()  */
#include <assert.h> /* assert			  */

#include "../include/recursion.h"
#include "../include/stack.h"
#include "../include/utiles.h"

/******************************************************************************
*							 DECLRATION								  * 
******************************************************************************/

typedef struct Node
{
    struct node * next; 
}Node;


/******************************************************************************
*							 FUNCTIONS 										  * 
******************************************************************************/

int Fibonacci(int element_index)
{
    if (element_index <= 1)
    {
        return element_index;
    }
    return (Fibonacci(element_index - 1) + Fibonacci(element_index - 2));

}



Node * FlipList(Node * node)
{
    if(node->next == NULL)
    {
        return node;
    }
    (FlipList(node->next))->next = node;

}

Node * SortLists(stack_t * unsorted_stack )
{
    if(StackSize(unsorted_stack) == 1)
    {
        return StackPeek(unsorted_stack);
    }
    (FlipList(node->next))->next = node;

}


/******************************************************************************
*							STATIC FUNCTIONS								  * 
******************************************************************************/


