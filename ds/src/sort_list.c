/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Chen
*	Date:      
******************************************************************************/

#include <stdlib.h> /* malloc() , free()  */
#include <assert.h> /* assert			  */
#include <stdio.h>

#include "sort_list.h"

#define SUCCESS (0)
#define FAIL (-1)
/******************************************************************************
*							 DECLRATION								  * 
******************************************************************************/

struct sorted_list
{
	compare_t compare;
	dll_t *dll;
};

static void RemoveAddedNodes(dll_t *output);
static int CountNodes(void * this_node, void * params);
static sorted_iter_t BuildIter(sorted_list_t *sorted_list, dll_iter_t * iter_dll);
/******************************************************************************
*							 FUNCTIONS 										  * 
******************************************************************************/

sorted_list_t *SortedListCreate(compare_t comp_func)
{
	sorted_list_t * sorted_list = (sorted_list_t *)malloc(sizeof(sorted_list_t));
	
	if(NULL == sorted_list)
	{
		return NULL;
	}
	
	sorted_list->compare = comp_func;
	sorted_list->dll = DLLCreate();
	
	if(NULL == sorted_list->dll)
	{
		free(sorted_list);
		return NULL;
	}
	
	return (sorted_list);
}



void SortedListDestroy(sorted_list_t *sorted_list)
{
	assert(sorted_list != NULL);
	DLLDestroy(sorted_list->dll);
	free(sorted_list);
}


int SortedListIsEmpty(const sorted_list_t *sorted_list)
{
	assert(sorted_list != NULL);

	return (DLLIsEqual(DLLBegin(sorted_list->dll), DLLEnd(sorted_list->dll)));	
}



sorted_iter_t SortedListEnd(const sorted_list_t *sorted_list)
{
	sorted_iter_t iter = {0};
	assert(sorted_list != NULL);
	
	iter = BuildIter((sorted_list_t *)sorted_list, DLLEnd(sorted_list->dll));
	
	return (iter);
}

sorted_iter_t SortedListBegin(const sorted_list_t *sorted_list)
{
	
	sorted_iter_t iter = {0};
	assert(sorted_list != NULL);
	
	iter = BuildIter((sorted_list_t *)sorted_list, DLLBegin(sorted_list->dll));
	
	return (iter);
}



sorted_iter_t SortedListNext(sorted_iter_t iter)
{
	iter.iter = DLLNext(iter.iter);
	return (iter);
}	

sorted_iter_t SortedListPrev(sorted_iter_t iter)
{
	iter.iter = DLLPrev(iter.iter);
	return(iter);
}

void *SortedListGetData(sorted_iter_t iter)
{
	return (DLLGet(iter.iter));
}



static sorted_iter_t BuildIter(sorted_list_t *sorted_list, dll_iter_t * iter_dll)
{
	sorted_iter_t new_iter = {0};
	
	assert(sorted_list != NULL);	
	assert(iter_dll != NULL);
	
	new_iter.iter = iter_dll;
	
	#ifndef NDEBUG
	new_iter.sorted_list = sorted_list;
	#endif
	
	return new_iter;
}


static sorted_iter_t FindSpot(sorted_list_t *sorted_list, void *data)
{
	sorted_iter_t node = SortedListBegin(sorted_list);
	
	while(sorted_list->compare(SortedListGetData(node), data))
	{
		node = SortedListNext(node);
	}
	
	return node;
}



static dll_iter_t * GetDLLIter(sorted_iter_t iter)
{	
	return iter.iter;
}

static dll_t * GetDLLList(orted_list_t *sorted_list)
{	
	return sorted_list.dll;
}

sorted_iter_t SortedListInsert(sorted_list_t *sorted_list, void *data)
{
	sorted_iter_t * node_ptr = NULL;
	sorted_iter_t where = {0};
	sorted_iter_t failed = {0};
	
	where = FindSpot(sorted_list, data);
	node_ptr = DLLInsert(GetDLLList(sorted_list), GetDLL(where), data);
	
	if (NULL == node_ptr)
	{
		return failed;
	}
	
	return (where);	
}


sorted_iter_t SortedListRemove(sorted_iter_t iter)
{
	itr.itr = DLLRemove(GetDllIter(iter));
	return itr;
}






int SortedListIsEqual(sorted_iter_t iter1, sorted_iter_t iter2)
{
	assert(iter1 != NULL);
	assert(iter2 != NULL);

	return (iter1 == iter2);
}



void *SortedListPopFront(sorted_list_t *sorted_list);
{
	void * data = NULL;
	assert(NULL != dll);
	
	data = DLLGet(DLLPrev(DLLEnd(dll)));
	DLLRemove(DLLBegin(dll));

	return (data);	
}

/*

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


int DLLForEach(dll_iter_t *from, dll_iter_t *to, action_t act_func, void *params)
{
	struct node * node_ptr = from;

	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != act_func);
	
	while(!DLLIsEqual(node_ptr,to))
	{
		if(act_func(node_ptr, params))
		{
			return (FAIL);
		}
		
		node_ptr = DLLNext(node_ptr);
	}	

	return (SUCCESS); 
}

	
void DLLSplice(dll_iter_t *from, dll_iter_t *to, dll_iter_t* where)
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



dll_iter_t *DLLFind(dll_iter_t *from, dll_iter_t *to, is_match_t match_func,\
																  void *params)
{
	struct node * node_ptr = from;

	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != match_func);
	
	while(!DLLIsEqual(node_ptr,to))
	{
		if(match_func(node_ptr->data,params))
		{
			return (node_ptr);
		}
	
		node_ptr = DLLNext(node_ptr);
	}

	return (to);
}

int DLLMultiFind(dll_iter_t *from, dll_iter_t *to, is_match_t match_func,\
				 								void *params, dll_t *output)
{
	struct node * iter = from;
	struct node * where = NULL;
	int counter = 0;
	
	assert(NULL != to);
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != to);
	where = DLLBegin(output);
	
	while(!DLLIsEqual(iter,to))
	{
		iter = DLLFind(iter, to, match_func, params);
		
		if (DLLIsEqual(iter,to))
		{
			return SUCCESS;
		}

		where = DLLInsert(output, where, DLLGet(iter));
		counter++;
		
		if(NULL == where)
		{
			
			RemoveAddedNodes(output);
			return FAIL;
		}
		
		iter = DLLNext(iter);
	}
	return counter;
}

static void RemoveAddedNodes(dll_t *output)
{
	struct node * iter = &(output->head);
	while(DLLIsEmpty(output))
	{
		iter = DLLRemove(iter);	
	}
}


static int CountNodes(void * this_node, void * params)
{
	(void)this_node;
	*(size_t *)params += 1;

	return (SUCCESS);
}



