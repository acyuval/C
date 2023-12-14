/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Chen
*	Date:      
******************************************************************************/

#include <stdlib.h> /* malloc() , free()  */
#include <assert.h> /* assert			  */
#include <stdio.h>

#include "sort_list.h"

#define TRUE (1)
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

static int CountNodes(void * this_node, void * params);
static sorted_iter_t BuildIter(sorted_list_t *sorted_list, dll_iter_t iter_dll);
static sorted_iter_t FindSpot(sorted_iter_t from, sorted_iter_t to, compare_t compare ,void *to_match);
static dll_iter_t GetDLLIter(sorted_iter_t iter);
static dll_t *GetDLLList(sorted_list_t *sorted_list);
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

sorted_iter_t SortedListInsert(sorted_list_t *sorted_list, void *data)
{
	sorted_iter_t SortedList_iter = SortedListBegin(sorted_list);
	dll_iter_t  dll_iter = NULL;
	sorted_iter_t failed = {0};
	
	SortedList_iter = FindSpot(SortedListBegin(sorted_list),\
					 SortedListEnd(sorted_list) , sorted_list->compare , data);
		
	dll_iter = DLLInsert(GetDLLList(sorted_list), GetDLLIter(SortedList_iter), data);
	
	if (NULL == dll_iter)
	{
		return failed;
	}
	
	return (BuildIter(sorted_list, dll_iter));
}

sorted_iter_t SortedListRemove(sorted_iter_t iter)
{
	iter.iter = DLLRemove(GetDLLIter(iter));
	return iter;
}

int SortedListIsEqual(sorted_iter_t iter1, sorted_iter_t iter2)
{
	dll_iter_t iter_dll1 = GetDLLIter(iter1);
	dll_iter_t iter_dll2 = GetDLLIter(iter2);
	return (DLLIsEqual(iter_dll1, iter_dll2));
}

void *SortedListPopFront(sorted_list_t *sorted_list)
{
	void * data = NULL;
	dll_t * dll = NULL;
	
	assert(NULL != sorted_list);
	dll = GetDLLList(sorted_list);	
	data = DLLGet(DLLBegin(dll));
	DLLRemove(DLLBegin(dll));
	return (data);	
}

void *SortedListPopBack(sorted_list_t *sorted_list)
{
	void * data = NULL;
	dll_t * dll = NULL;

	assert(NULL != sorted_list);
	dll = GetDLLList(sorted_list);
	data = DLLGet(DLLPrev(DLLEnd(dll)));
	DLLRemove(DLLPrev(DLLEnd(dll)));
	return (data);
}

size_t SortedListSize(const sorted_list_t *sorted_list)
{
	size_t counter = 0; 
	
	dll_t * dll = GetDLLList((sorted_list_t *)sorted_list);
	DLLForEach(DLLBegin(dll), DLLEnd(dll), &CountNodes, &counter);
	return (counter);
}

int SortedListForEach(sorted_iter_t from, sorted_iter_t to, action_t act_func, void *params)
{
	int status = SUCCESS;
	
	while(TRUE != SortedListIsEqual(from, to) && SUCCESS == status)
	{
		status = act_func(&from, params);
		from = SortedListNext(from);
	}	
	
	return (status); 
}

sorted_iter_t SortedListFind(sorted_iter_t from, sorted_iter_t to, void *to_find, const sorted_list_t *sorted_list)
{
	dll_iter_t dll_from = GetDLLIter(from);
	dll_iter_t dll_to = GetDLLIter(to);
	
	assert(from.sorted_list == sorted_list);	
	assert(from.sorted_list == to.sorted_list);

	dll_from = DLLFind(dll_from, dll_to, sorted_list->compare, to_find);
	from = BuildIter((sorted_list_t *)sorted_list,dll_from);
	return (from);
}

void SortedListMerge(sorted_list_t *dest, sorted_list_t *src)
{
	sorted_iter_t src_iter= SortedListBegin(src);
	sorted_iter_t dest_iter= SortedListBegin(dest);
	sorted_iter_t dest_end= SortedListEnd(dest);
	sorted_iter_t src_end= SortedListEnd(src);
		
	while(SortedListIsEqual(dest_iter, dest_end) != TRUE && SortedListIsEmpty(src) != TRUE)
	{
			dest_iter = FindSpot(dest_iter,dest_end, dest->compare ,SortedListGetData(src_iter));
			DLLSplice(GetDLLIter(src_iter),GetDLLIter(SortedListNext(src_iter)),GetDLLIter(dest_iter));
			src_iter = SortedListBegin(src);
			if (SortedListIsEqual(dest_iter, dest_end) == TRUE)
			{
				DLLSplice(GetDLLIter(src_iter), GetDLLIter(src_end),GetDLLIter(dest_end));
				break;
			}
	}
}

sorted_iter_t SortedListFindIf(sorted_iter_t from, sorted_iter_t to, is_match_t is_match_func, void *params)
{
	while(TRUE != SortedListIsEqual(from,to))
	{
		if(TRUE == is_match_func(DLLGet(GetDLLIter(from)), params))
		{
			return (from);
		}
	
		from = SortedListNext(from);
	}
	return (to);	
}

/******************************************************************************
*							STATIC FUNCTIONS								  * 
******************************************************************************/

static sorted_iter_t BuildIter(sorted_list_t *sorted_list, dll_iter_t iter_dll)
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


static sorted_iter_t FindSpot(sorted_iter_t from, sorted_iter_t to, compare_t compare ,void *to_match)
{
	int status = -1;

	status = compare(SortedListGetData(from) , to_match);
	while(status < 0 && TRUE != SortedListIsEqual(from, to))
	{
		from = SortedListNext(from);		
		status = compare(SortedListGetData(from) , to_match);
	}
	
	return from;
}

static dll_iter_t GetDLLIter(sorted_iter_t iter)
{	
	return iter.iter;
}

static dll_t *GetDLLList(sorted_list_t *sorted_list)
{	
	return sorted_list->dll;
}



static int CountNodes(void * this_node, void * params)
{
	(void)this_node;
	*(size_t *)params += 1;
	return (SUCCESS);
}

