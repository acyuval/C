/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Yael
*	Date:      
******************************************************************************/

#include <stddef.h> /* size_t 			  */
#include <stdio.h>

#include "sll_exer.h"

#define SUCCESS (0)
#define FAIL (-1)
/******************************************************************************
*							FUNCTION DECLRATION								  * 
******************************************************************************/


/******************************************************************************
*							 FUNCTIONS 										  * 
******************************************************************************/


node_t * Flip(node_t * itr)
{
	node_t * prev = NULL;
	node_t * cur = itr;
	node_t * next = NULL;
	
	prev = NULL;
 	
	while(cur->next != NULL)
	{
		next =  cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	cur->next = prev;	
	return next;

}

int HasLoop(node_t * head)
{
	node_t * slow = head;
	node_t * fast = head->next;
	
	if(NULL == head->next)
	{
		return 0;
	}
	
	while(slow != fast)
	{
		if(NULL == fast->next || NULL == slow->next )
		{
			return 0;
		}
		fast = fast->next->next;
		slow = slow->next;
	}
	return 1;

}

node_t * FindIntersection(node_t *node_1 ,node_t *node_2)
{
	node_t * itrA = node_1;
	node_t * itrB = node_2;
	int counter = 0; 
	
	while(itrA != NULL)
	{
		itrA = itrA->next;
		counter++;
		
	}
	
	while(itrB != NULL)
	{
		itrB = itrB->next;
		counter--;
	}

	if(itrA == itrB)
	{
		node_t * itrA = node_1;
		node_t * itrB = node_2;
		if(counter > 0)
		{
			while(0 != counter--)
			{
				itrA = itrA->next;
			}
		}
		
		if(counter < 0)
		{
			while(0 != counter++)
			{
				itrB = itrB->next;
			}
		}
		
		while(itrA != itrB)
		{
			itrA = itrA->next;
			itrB = itrB->next;
		}	
		
		return itrA;	
	}	
	
	return NULL;
}

