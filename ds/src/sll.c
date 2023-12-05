
#include <stddef.h> /* size_t */
#include <stdlib.h> /* malloc() */
#include <assert.h>
#include <stdio.h>
#include "sll.h"


/******************************************************************************
*							FUNCTION DECLRATION								  * 
******************************************************************************/

static int CountNodes(slist_iter_t this_node, void * params);



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
	struct node * this_node = list->head;
	while(this_node->next != NULL)
	{
		this_node = SLLRemove(this_node);
	}
	
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
	return where;	
}


slist_iter_t SLLRemove(slist_iter_t iter)
{
	void * temp_next = iter->next;
	
	iter->data = iter->next->data;
	iter->next = iter->next->next; 
	
	free(temp_next);
	
	return(iter->next);
}


size_t SLLCount(const list_t *list)
{
	struct node * this_node = list-> head;
	size_t counter = 0; 
	
	SLLForEach(list->head, list->tail, &CountNodes, (void *)counter);
	
	return counter-1;
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
			return this_node;
		}
		this_node = this_node->next;
	}

	return NULL;
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
	assert(iterator->next != NULL);

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






int SLLForEach(slist_iter_t from, slist_iter_t to, action_t act_func, void *params)
{
	struct node * this_node = from;

	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != act_func);
	
	while(this_node != to)
	{
		if(act_func((void *)this_node,params))
		{
			return (-1);
		}
		
		this_node = this_node->next;
	}	
	return 0;
}

static int CountNodes(void * this_node, void * params)
{
	
	*(size_t *)params += 1;
	return params;
}

