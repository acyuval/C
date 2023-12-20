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
	pq_t bad_pq = {0};
	pq_t * pq = (pq_t *)malloc(sizeof(pq_t));
	bad_pq.sorted_list = NULL;
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
	sorted_iter_t status_itr = {0};
	assert(pq != NULL);
	assert(data != NULL);
	
	status_itr = SortedListInsert(pq->sorted_list, data);
	return status_itr.iter ? SUCCESS : FAIL;
}

void *PQDequeue(pq_t *pq)
{
	void * return_val = PQPeek(pq);
	assert(pq != NULL);
	SortedListRemove(SortedListBegin(pq->sorted_list));
	return return_val;
}	

void *PQPeek(const pq_t *pq)
{
	assert(pq != NULL);
	return SortedListGetData(SortedListBegin(pq->sorted_list));
}

void PQClear(pq_t *pq)
{
	assert(pq != NULL);
	while(!PQIsEmpty(pq))
	{
		SortedListRemove(SortedListBegin(pq->sorted_list));
	}
}

void *PQErase(pq_t *pq, pq_is_match_t is_match_func, void *params)
{
	sorted_iter_t return_itr = {0};
	assert(pq != NULL);
	assert(is_match_func != NULL);
	assert(params != NULL);
	return_itr = SortedListRemove(SortedListFindIf(SortedListBegin(pq->sorted_list),
					SortedListEnd(pq->sorted_list), is_match_func, params));
	return SortedListGetData(return_itr);
}
/******************************************************************************
*							STATIC FUNCTIONS								  * 
******************************************************************************/

