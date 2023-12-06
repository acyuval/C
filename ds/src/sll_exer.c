/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Yael
*	Date:      
******************************************************************************/

#include <stddef.h> /* size_t 			  */
#include <stdlib.h> /* malloc() , free()  */
#include <assert.h> /* assert			  */
#include <stdio.h>

#include "sll_exer.h"

#define SUCCESS (0)
#define FAIL (-1)
/******************************************************************************
*							FUNCTION DECLRATION								  * 
******************************************************************************/

node_t * Flip(node_t * itr);

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


node_t * FindIntersection(list_t *listA ,list_t *listB)
{
	node_t * itrA = listA->head;
	node_t * itrB = listB->head;
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
	
	itrA =  listA->head;
	itrB =  listB->head;
	if(itrA == itrB)
	{
		if(counter > 0)
		{
			while(counter--)
			{
				itrA = itrA->next;
			}
		}
		
		if(counter < 0)
		{
			while(counter++)
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

/*
1. run till end of both loops, test if there was intersct
2. find diff in size between two 
3. run only the big loop for the diff 
4. run both when they are allined
*/
