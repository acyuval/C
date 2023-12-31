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


node_t * HasLoop(node_t * head)
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
			return fast->next;
		}
		fast = fast->next->next;
		slow = slow->next;
	}
	return NULL;
}


