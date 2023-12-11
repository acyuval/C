/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/

#include <stddef.h> /* size_t 			  */
#include <stdlib.h> /* malloc() , free()  */
#include <assert.h> /* assert			  */

#include "dll.h"

#define SUCCESS (0)
#define FAIL (-1)
/******************************************************************************
*							 DECLRATION								  * 
******************************************************************************/

struct node
{
	void *data;
	struct node *next;
	struct node *prev;
};

struct dll
{
	struct node head;
	struct node tail;
};

static int CountNodes(void * this_node, void * params);
/******************************************************************************
*							 FUNCTIONS 										  * 
******************************************************************************/

dll_t *DLLCreate(void)
{
	dll_t * dll = (dll_t *)malloc(sizeof(dll_t));
	
	if(NULL == dll)
	{
		return NULL;
	}
	
	
	dll->tail.next = NULL;
	dll->tail.prev = &dll->head;
	dll->tail.data = NULL;
	
	dll->head.next = &dll->tail;
	dll->head.prev = NULL;
	dll->head.data = NULL;	
	
	
	return (dll);
}



void DLLDestroy(dll_t *dll)
{
	struct node * node_ptr = NULL;
	
	assert(dll != NULL);
	
	node_ptr = dll->head.next;
	
	while(node_ptr->next != NULL)
	{
		node_ptr = DLLRemove(node_ptr);
	}
	
	free(dll);
}


dll_iter_t *DLLInsert(dll_t *dll, dll_iter_t *iter, void *data)
{
	struct node * node_ptr = (struct node *)malloc(sizeof(struct node));
	
	
	assert(iter != NULL);
	assert(dll != NULL);
	
	if(NULL == node_ptr)
	{
		return NULL;
	}
	
	node_ptr->data = data;
	
	iter->prev->next =  node_ptr;
	
	node_ptr->prev = iter->prev;
	node_ptr->next = iter;		
	
	iter->prev = node_ptr;
	
	return (iter);	
}


dll_iter_t *DLLRemove(dll_iter_t *iter)
{
	dll_iter_t * next = iter->next;
	
	assert(NULL != iter);
	assert(iter->prev != NULL);
	
	iter->prev->next = next;
	
	next->prev = iter->prev;
	
	free(iter);
	
	return next;
}


int DLLIsEmpty(const dll_t *dll)
{
	assert(dll != NULL);

	return (dll->head.next == &dll->tail);	
}


dll_iter_t *DLLFind(dll_iter_t *from, dll_iter_t *to, is_match_t match_func,\
																  void *params)
{
	struct node * node_ptr = from;

	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != match_func);
	
	while(node_ptr != to)
	{
		if(match_func(node_ptr->data,params))
		{
			return (node_ptr);
		}
	
		node_ptr = node_ptr->next;
	}

	return (NULL);
}


dll_iter_t *DLLEnd(const dll_t *dll)
{
	assert(dll != NULL);
	
	return ((dll_iter_t *)&dll->tail);	
}

dll_iter_t *DLLBegin(const dll_t *dll)
{
	assert(dll != NULL);
	
	return ((dll_iter_t *)dll->head.next);
}



dll_iter_t *DLLNext(const dll_iter_t *iter)
{
	assert(iter != NULL);
	return (iter->next);
}	

dll_iter_t *DLLPrev(const dll_iter_t *iter)
{
	assert(iter != NULL);
	return (iter->prev);
}

void *DLLGet(const dll_iter_t *iter)
{
	assert(iter != NULL);
	return (iter->data);
}

void DLLSet(dll_iter_t *iter, void *data)
{
	assert(iter != NULL);
	assert(iter->next != NULL);

	iter->data = data;
}


int DLLIsEqual(dll_iter_t *iter1, dll_iter_t *iter2)
{
	assert(iter1 != NULL);
	assert(iter2 != NULL);

	return (iter1 == iter2);
}

dll_iter_t *DLLPushback(dll_t *dll, void *data)
{
	return (DLLInsert(dll, DLLEnd(dll), data));
}


dll_iter_t *DLLPushfront(dll_t *dll, void *data)
{
	return (DLLInsert(dll, DLLBegin(dll), data));
}

dll_iter_t *DLLPopback(dll_t *dll)
{
	return (DLLRemove(DLLPrev(DLLEnd(dll))));
}

dll_iter_t *DLLPopfront(dll_t *dll)
{
	return (DLLRemove(DLLBegin(dll)));
}


size_t DLLSize(const dll_t *dll)
{
	size_t counter = 0; 
	
	DLLForEach(DLLNext((dll_iter_t *)&dll->head), (dll_iter_t *)&dll->tail, &CountNodes, &counter);
	
	return (counter);
}


int DLLForEach(dll_iter_t *from, dll_iter_t *to, action_t act_func, void *params)
{
	struct node * node_ptr = from;

	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != act_func);
	
	while(node_ptr != to)
	{
		if(act_func(node_ptr, params))
		{
			return (FAIL);
		}
		
		node_ptr = node_ptr->next;
	}	

	return (SUCCESS); 
}

	
void DLLSplice(dll_iter_t *from, dll_iter_t *to, dll_iter_t* where)
{


}


int DLLMultiFind(dll_iter_t *from, dll_iter_t *to, is_match_t match_func,\
				 								void *params, dll_t *output)
{

}

static int CountNodes(void * this_node, void * params)
{
	(void)this_node;
	*(size_t *)params += 1;

	return (SUCCESS);
}



