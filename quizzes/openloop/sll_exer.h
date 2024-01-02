#ifndef __SLLE_H__
#define __SLLE_H__





typedef struct node
{
	void *data;
	struct node *next;
	
}node_t;


/******************************************************************************
*Description: creates a new list
*Arguments: none
*Return Value: pointer to the created list
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/

node_t * FindIntersection(node_t * head_1 ,node_t * head_2);

node_t * HasLoop(node_t * head);

int OpenLoop(node_t * head);

#endif /* __SLLE_H__ */

