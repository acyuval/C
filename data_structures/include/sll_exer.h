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
node_t *Flip(node_t * head);

int HasLoop(node_t * head);

node_t * FindIntersection(node_t * head_1 ,node_t * head_2);



#endif /* __SLLE_H__ */

