/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Yael
*	Date:      
******************************************************************************/

#include <stddef.h> /* size_t 			  */
#include <stdlib.h> /* malloc() , free()  */
#include <assert.h> /* assert			  */

#include "sll.h"

#define SUCCESS (0)
#define FAIL (-1)
/******************************************************************************
*							FUNCTION DECLRATION								  * 
******************************************************************************/

static int CountNodes(void * this_node, void * params);


struct node
{
	void *data;
	struct node *next;
};

struct list
{
	struct node *head;
	struct node *tail;
};


/******************************************************************************
*							 FUNCTIONS 										  * 
******************************************************************************/

list_t * SLLCreate(void)
{
	list_t * list = (struct list *)malloc(sizeof(struct list));
	
	if(NULL == list)
	{
		return NULL;
	}
	
	list->tail = (struct node *)malloc(sizeof(struct node));

	if(NULL == list->tail)
	{
		free(list);
		return NULL;
	}	
	
	list->tail->next = NULL;
	list->tail->data = list;
	list->head = list->tail;
	
	return (list);
}


void SLLDestroy(list_t *list)
{
	struct node * this_node = NULL;
	
	assert(list != NULL);
	
	this_node = list->head;
	
	while(this_node->next != NULL)
	{
		this_node = SLLRemove(this_node);
	}
	
	free(list->tail);
	free(list);
}


slist_iter_t SLLInsert(list_t *list, slist_iter_t where, void *value)
{
	
	struct node * new_node = (struct node *)malloc(sizeof(struct node));
	
	assert(list != NULL);
	assert(where != NULL);
	
	if(NULL == new_node)
	{
		return NULL;
	}
	
	new_node->data = where->data;
	new_node->next = where->next;
	
	where->data = value;
	where->next = new_node; 
	
	if(where == list->tail)
	{
		list->tail = new_node;
	}
	
	return (where);	
}


slist_iter_t SLLRemove(slist_iter_t iter)
{
	slist_iter_t temp_next = NULL;
	
	assert(NULL != iter);
	
	temp_next = iter->next;
	
	iter->data = temp_next->data;
	iter->next = temp_next->next;
	
	if (NULL == iter->next)
	{
		((list_t *)iter->data)->tail = iter; 
	}
	
	free(temp_next);
	
	return (iter);
}



slist_iter_t SLLFind(slist_iter_t from, slist_iter_t to,
				is_match_t is_match_func, void *params)
{
	struct node * this_node = from;

	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != is_match_func);
	
	while(this_node != to)
	{
		if(is_match_func(this_node->data,params))
		{
			return (this_node);
		}
	
		this_node = this_node->next;
	}

	return (NULL);
}


int SLLIsEmpty(const list_t *list)
{
	assert(list != NULL);
	
	return (list->tail == list->head);	
}


slist_iter_t SLLEnd(const list_t *list)
{
	assert(list != NULL);
	
	return (list->tail);	
}

slist_iter_t SLLBegin(const list_t *list)
{
	assert(list != NULL);
	
	return (list->head);
}



slist_iter_t SLLNext(slist_iter_t iterator)
{
	assert(iterator != NULL);
	
	return (iterator->next);
}	



void *SLLGetData(slist_iter_t iterator)
{
	assert(iterator != NULL);

	return (iterator->data);
}

void SLLSetData(slist_iter_t iterator, void *data)
{
	assert(iterator != NULL);
	assert(iterator->next != NULL);

	iterator->data = data;
}


int SLLIsEqual(slist_iter_t iterator_1, slist_iter_t iterator_2)
{
	assert(iterator_1 != NULL);
	assert(iterator_2 != NULL);

	return (iterator_1 == iterator_2);
}





size_t SLLCount(const list_t *list)
{
	size_t counter = 0; 
	
	SLLForEach(list->head, list->tail, &CountNodes, &counter);
	
	return (counter);
}


int SLLForEach(slist_iter_t from, slist_iter_t to, action_t act_func, void *params)
{
	struct node * this_node = from;

	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != act_func);
	
	while(this_node != to)
	{
		if(act_func(this_node, params))
		{
			return (FAIL);
		}
		
		this_node = this_node->next;
	}	

	return (SUCCESS); 
}


void SLLAppend(list_t *dest, list_t *src)
{
	*(dest->tail) = *(src->head);

	src->head->next = NULL;
	src->tail = src->head;
	src->tail->data = src;

	dest->tail = src->tail;
	dest->tail->data = dest;
}
	


static int CountNodes(void * this_node, void * params)
{
	(void)this_node;
	*(size_t *)params += 1;

	return (SUCCESS);
}

