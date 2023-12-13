/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Chen
*	Date:      
******************************************************************************/

#include <stdlib.h> /* malloc() , free()  */
#include <assert.h> /* assert			  */

#include "dll.h"

#define TRUE (1)
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
	assert(dll != NULL);
	
	while(!DLLIsEmpty(dll))
	{
		DLLRemove(DLLBegin(dll));
	}
	
	free(dll);
}


dll_iter_t DLLInsert(dll_t *dll ,dll_iter_t iter, void *data)
{
	struct node * node_ptr = (struct node *)malloc(sizeof(struct node));
	if(NULL == node_ptr)
	{
		return DLLEnd(dll);
	}
	
	assert(iter != NULL);
	
	node_ptr->data = data;
	node_ptr->next = iter;		
	node_ptr->prev = iter->prev;
	
	iter->prev->next =  node_ptr;
	iter->prev = node_ptr;

	return (iter);	
}


dll_iter_t DLLRemove(dll_iter_t iter)
{
	dll_iter_t next = NULL;
	
	assert(NULL != iter);
	assert(NULL != iter->prev);
	
	next = iter->next;
	iter->prev->next = next;
	next->prev = iter->prev;
	
	free(iter);
	
	return next;
}


int DLLIsEmpty(const dll_t *dll)
{
	assert(dll != NULL);

	return (TRUE == DLLIsEqual(DLLBegin(dll), DLLEnd(dll)));	
}



dll_iter_t DLLEnd(const dll_t *dll)
{
	assert(dll != NULL);
	
	return ((dll_iter_t )&dll->tail);	
}

dll_iter_t DLLBegin(const dll_t *dll)
{
	assert(dll != NULL);
	
	return ((dll_iter_t )dll->head.next);
}

dll_iter_t DLLNext(const dll_iter_t iter)
{
	assert(iter != NULL);
	return (iter->next);
}	

dll_iter_t DLLPrev(const dll_iter_t iter)
{
	assert(iter != NULL);
	return (iter->prev);
}

void *DLLGet(const dll_iter_t iter)
{
	assert(iter != NULL);
	return (iter->data);
}

void DLLSet(dll_iter_t iter, void *data)
{
	assert(iter != NULL);
	assert(iter->next != NULL);

	iter->data = data;
}


int DLLIsEqual(dll_iter_t iter1, dll_iter_t iter2)
{
	assert(iter1 != NULL);
	assert(iter2 != NULL);

	return (iter1 == iter2);
}

dll_iter_t DLLPushback(dll_t *dll, void *data)
{
	return (DLLInsert(dll, DLLEnd(dll), data));
}


dll_iter_t DLLPushfront(dll_t *dll, void *data)
{
	return (DLLInsert(dll, DLLBegin(dll), data));
}

void *DLLPopback(dll_t *dll)
{
	void * data = NULL;
	assert(NULL != dll);
	
	data = DLLGet(DLLPrev(DLLEnd(dll)));
	DLLRemove(DLLBegin(dll));

	return (data);	
}

void *DLLPopfront(dll_t *dll)
{
	void * data = NULL;
	
	assert(NULL != dll);
	
	data = DLLGet(DLLBegin(dll));
	DLLRemove(DLLBegin(dll));
	return (data);
}


size_t DLLSize(const dll_t *dll)
{
	size_t counter = 0; 
	
	DLLForEach(DLLBegin(dll), DLLEnd(dll), &CountNodes, &counter);
	
	return (counter);
}



	
void DLLSplice(dll_iter_t from, dll_iter_t to, dll_iter_t where)
{
	
	struct node * prev_from_ptr= from->prev;
	
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != where);
	
	to->prev->next = where;
	from->prev = where->prev;
	
	where->prev->next = from;
	where->prev = to->prev;
	
	prev_from_ptr->next = to; 
	to->prev = prev_from_ptr;
}



dll_iter_t DLLFind(dll_iter_t from, dll_iter_t to, is_match_t match_func,\
																  void *params)
{
	struct node * node_ptr = from;
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != match_func);
	
	while(TRUE != DLLIsEqual(node_ptr,to))
	{
		if(TRUE == match_func(node_ptr->data,params))
		{
			return (node_ptr);
		}
	
		node_ptr = DLLNext(node_ptr);
	}

	return (to);
}

int DLLForEach(dll_iter_t from, dll_iter_t to, action_t act_func, void *params)
{
	struct node * node_ptr = from;
	int status = SUCCESS;
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != act_func);
	
	while(TRUE != DLLIsEqual(node_ptr,to) && SUCCESS == status)
	{
		status = act_func(node_ptr, params);
		node_ptr = DLLNext(node_ptr);
	}	
	return (status); 
}


int DLLMultiFind(dll_iter_t from, dll_iter_t to, is_match_t match_func,\
				 								void *params, dll_t *output)
{
	struct node * iter = from;
	struct node * where = NULL;
	int status = SUCCESS;
	
	assert(NULL != to);
	assert(NULL != from);
	
	where = DLLBegin(output);
	
	iter = DLLFind(iter, to, match_func, params);
	
	while(TRUE != DLLIsEqual(iter,to))
	{
		where = DLLInsert(output, where, DLLGet(iter));
		
		if(NULL == where)
		{
			status = FAIL;
			break;
		}
		
		iter = DLLNext(iter);
		iter = DLLFind(iter, to, match_func, params);
	}
	return status;
}


static int CountNodes(void * this_node, void * params)
{
	(void)this_node;
	*(size_t *)params += 1;

	return (SUCCESS);
}



