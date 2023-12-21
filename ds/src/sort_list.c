/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Dor
*	Date:      
******************************************************************************/

#include <stdlib.h> /* malloc() , free()  */
#include <assert.h> /* assert			  */

#include "sort_list.h"

#define TRUE (1)
#define FALSE (0)
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

struct wrapper
{
	void *to_find;
	compare_t compare;
};

static sorted_iter_t BuildIter(sorted_list_t *sorted_list, dll_iter_t iter_dll);
static sorted_iter_t FindSpot(sorted_iter_t from, sorted_iter_t to,
							  compare_t compare ,void *to_match);
static dll_iter_t GetDLLIter(sorted_iter_t iter);
static dll_t *GetDLLList(sorted_list_t *sorted_list);
static int Wrapper_match(void *data, void * stru);


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
	
	if(NULL == GetDLLList(sorted_list))
	{
		free(sorted_list);
		return NULL;
	}
	
	return (sorted_list);
}

void SortedListDestroy(sorted_list_t *sorted_list)
{
	assert(sorted_list != NULL);
	
	DLLDestroy(GetDLLList(sorted_list));
	free(sorted_list);
}


int SortedListIsEmpty(const sorted_list_t *sorted_list)
{
	assert(sorted_list != NULL);

	return (DLLIsEmpty(GetDLLList((sorted_list_t *)sorted_list)));	
}



sorted_iter_t SortedListEnd(const sorted_list_t *sorted_list)
{
	sorted_iter_t iter = {0};
	assert(sorted_list != NULL);
	
	iter = BuildIter((sorted_list_t *)sorted_list, 
					 DLLEnd(GetDLLList((sorted_list_t *)sorted_list)));
	
	return (iter);
}

sorted_iter_t SortedListBegin(const sorted_list_t *sorted_list)
{
	sorted_iter_t iter = {0};
	
	assert(sorted_list != NULL);
	iter = BuildIter((sorted_list_t *)sorted_list, 
					 DLLBegin(GetDLLList((sorted_list_t *)sorted_list)));
	return (iter);
}

sorted_iter_t SortedListNext(sorted_iter_t iter)
{
	assert(TRUE != SortedListIsEqual(iter,SortedListEnd(iter.sorted_list)));
	
	iter.iter = DLLNext(GetDLLIter(iter));
	return (iter);
}	

sorted_iter_t SortedListPrev(sorted_iter_t iter)
{
	assert(TRUE != SortedListIsEqual(iter, SortedListBegin(iter.sorted_list)));
	
	iter.iter = DLLPrev(GetDLLIter(iter));
	return(iter);
}

void *SortedListGetData(sorted_iter_t iter)
{
	assert(TRUE != SortedListIsEqual(iter,SortedListEnd(iter.sorted_list)));
	return (DLLGet(GetDLLIter(iter)));
}

sorted_iter_t SortedListInsert(sorted_list_t *sorted_list, void *data)
{
	sorted_iter_t sorted_list_iter = SortedListBegin(sorted_list);
	dll_iter_t  dll_iter = NULL;
	
	if(TRUE != SortedListIsEmpty(sorted_list))
	{
		sorted_list_iter = FindSpot(SortedListBegin(sorted_list),\
					 SortedListEnd(sorted_list) , sorted_list->compare , data);
	}	
		
	dll_iter = DLLInsert(GetDLLList(sorted_list), GetDLLIter(sorted_list_iter), data);
	
	if (TRUE == DLLIsEqual(dll_iter, DLLEnd(GetDLLList(sorted_list))))
	{
		return SortedListEnd(sorted_list);
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
	return (DLLIsEqual(GetDLLIter(iter1), GetDLLIter(iter2)));
}

void *SortedListPopFront(sorted_list_t *sorted_list)
{
	dll_t * dll = NULL;
	assert(NULL != sorted_list);
	assert(TRUE != SortedListIsEmpty(sorted_list));
	dll = GetDLLList(sorted_list);	
	
	return (DLLPopfront(dll));	
}

void *SortedListPopBack(sorted_list_t *sorted_list)
{
	dll_t * dll = NULL;
	assert(NULL != sorted_list);
	assert(TRUE != SortedListIsEmpty(sorted_list));
	dll = GetDLLList(sorted_list);
	
	return (DLLPopback(dll));
}

size_t SortedListSize(const sorted_list_t *sorted_list)
{
	dll_t * dll = GetDLLList((sorted_list_t *)sorted_list);
	return DLLSize(dll);
}

int SortedListForEach(sorted_iter_t from, sorted_iter_t to, action_t act_func, void *params)
{
	int status = SUCCESS;
	
	assert(from.sorted_list == to.sorted_list);
	
	status = DLLForEach(GetDLLIter(from), GetDLLIter(to), act_func, params);	
	
	return (status); 
}

sorted_iter_t SortedListFind(sorted_iter_t from, sorted_iter_t to, void *to_find, const sorted_list_t *sorted_list)
{
	assert(from.sorted_list == sorted_list);	
	assert(from.sorted_list == to.sorted_list);

	return (FindSpot(from, to, sorted_list->compare, to_find));
}

void SortedListMerge(sorted_list_t *dest, sorted_list_t *src)
{
	sorted_iter_t src_iter= SortedListBegin(src);
	sorted_iter_t dest_iter= SortedListBegin(dest);
	sorted_iter_t dest_end= SortedListEnd(dest);
	sorted_iter_t src_end= SortedListEnd(src);

	assert(dest != src);
			
	while(FALSE == SortedListIsEmpty(src)  && FALSE == SortedListIsEqual(src_iter,SortedListEnd(src)))
	{
			dest_iter = FindSpot(dest_iter,dest_end, dest->compare ,SortedListGetData(src_iter));
			DLLSplice(GetDLLIter(src_iter),GetDLLIter(SortedListNext(src_iter)),GetDLLIter(dest_iter));
			src_iter = SortedListBegin(src);
			
			if (SortedListIsEqual(dest_iter, dest_end) == TRUE)
			{
				DLLSplice(GetDLLIter(src_iter), GetDLLIter(src_end),GetDLLIter(dest_end));
			}
	}
}

sorted_iter_t SortedListFindIf(sorted_iter_t from, sorted_iter_t to, is_match_t is_match_func, void *params)
{
	
	assert(from.sorted_list == to.sorted_list);
	
	from.iter = DLLFind(GetDLLIter(from),GetDLLIter(to), is_match_func, params);
	
	return (from);	
}




/******************************************************************************
*							STATIC FUNCTIONS								  * 
******************************************************************************/



static int Wrapper_match(void *data, void * stru)
{
	struct wrapper *w1 = (struct wrapper *)stru;
	
	compare_t compare = w1->compare;
	void * data_to_find = w1->to_find;
	
	int return_value = compare(data, data_to_find);
	
	return (return_value >= 0);
	
}

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
	
	struct wrapper w1 = {0};
	
	w1.to_find = to_match;
	w1.compare = compare;
	from.iter = DLLFind (GetDLLIter(from), GetDLLIter(to), &Wrapper_match ,&w1);
	
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



