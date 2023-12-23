/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Dor
*	Date:      
******************************************************************************/
#include <assert.h>
#include <stdlib.h>

#include "sort_list.h"
#include "pq.h"

#define TRUE (1)
#define FALSE (0)
#define SUCCESS (0)
#define FAIL (-1)
/******************************************************************************
*							 DECLRATION								  * 
******************************************************************************/

struct pq
{
	sorted_list_t *sorted_list;
};

/******************************************************************************
*							 FUNCTIONS 										  * 
******************************************************************************/

pq_t *PQCreate(pq_compare_t compare_func)
{
	pq_t * pq = (pq_t *)malloc(sizeof(pq_t));
	
	if(NULL == pq)
	{
		return NULL;
	}
	
	
	pq->sorted_list = SortedListCreate(compare_func);
	
	if(NULL == pq->sorted_list)
	{
		free(pq);
		return NULL;
	}
	
	return (pq);
}



void PQDestroy(pq_t *pq)
{
	assert(pq != NULL);
	SortedListDestroy(pq->sorted_list);
	free(pq);
}


int PQIsEmpty(const pq_t *pq)
{
	assert(pq != NULL);
	return SortedListIsEmpty(pq->sorted_list);
}


size_t PQSize(const pq_t *pq)
{
	assert(pq != NULL);
	return SortedListSize(pq->sorted_list);
}

int PQEnqueue(pq_t *pq, void *data)
{
	int status = 0;

	assert(pq != NULL);

	SortedListInsert(pq->sorted_list, data);
	
	status = (data == PQPeek(pq));
	return status ? SUCCESS: FAIL;
}

void *PQDequeue(pq_t *pq)
{
	void * return_data = NULL;
	
	assert(pq != NULL);
	assert(FALSE == PQIsEmpty(pq));
	
	return_data = PQPeek(pq);
	SortedListRemove(SortedListBegin(pq->sorted_list));
	return return_data;
}	

void *PQPeek(const pq_t *pq)
{
	assert(pq != NULL);
	assert(FALSE == PQIsEmpty(pq));
	
	return SortedListGetData(SortedListBegin(pq->sorted_list));
}

void PQClear(pq_t *pq)
{
	assert(pq != NULL);
	while(FALSE == PQIsEmpty(pq))
	{
		SortedListRemove(SortedListBegin(pq->sorted_list));
	}
}

void *PQErase(pq_t *pq, pq_is_match_t is_match_func, void *params)
{
	sorted_iter_t found_itr = {0};
	void * return_data = NULL;
	
	assert(pq != NULL);
	assert(is_match_func != NULL);
	
	found_itr = SortedListFindIf(SortedListBegin(pq->sorted_list),
					SortedListEnd(pq->sorted_list), is_match_func, params);
	if (TRUE == SortedListIsEqual(found_itr,SortedListEnd(pq->sorted_list)))	
	{
		return NULL;
	}
	
	return_data = SortedListGetData(found_itr);
	SortedListRemove(found_itr);
	return return_data;
}
/******************************************************************************
*							STATIC FUNCTIONS								  * 
******************************************************************************/

