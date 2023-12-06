#ifndef __SLLE_H__
#define __SLLE_H__

#include <stddef.h> /* size_t */




typedef struct node_t
{
	int data;
	struct node_t *next;
	
}node_t;


typedef struct list_t
{
	struct node_t *head;
	struct node_t *tail;
}list_t;



/******************************************************************************
*Description: creates a new list
*Arguments: none
*Return Value: pointer to the created list
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
node_t * Flip(node_t * itr);

node_t * FindIntersection(list_t *listA ,list_t *listB);




#endif /* __SLLE_H__ */

