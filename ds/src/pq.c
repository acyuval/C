/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Dor
*	Date:      
******************************************************************************/



#include "uid.h"

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
}bad_pq ={NULL};

/******************************************************************************
*							 FUNCTIONS 										  * 
******************************************************************************/

pq_t *PQCreate(pq_compare_t compare_func);
{
	pq_t * pq = (pq_t *)malloc(sizeof(pq_t));
	
	if(NULL == pq)
	{
		return NULL;
	}
	
	
	pq->sorted_list = SortedListCreate();
	
	if(NULL == pq->sorted_list)
	{
		free(pq);
		return NULL;
	}
	
	return (pq);
}

void SortedListDestroy(sorted_list_t *sorted_list)
{
	assert(sorted_list != NULL);
	
	DLLDestroy(GetDLLList(sorted_list));
	free(sorted_list);
}

void PQDestroy(pq_t *pq);
{
	return SortedListDestroy(pq->sorted_list);
}


int PQIsEmpty(const pq_t *pq)
{
	return SortedListIsEmpty(pq->sorted_list);
}


size_t PQSize(const pq_t *pq)
{
	return SortedListSize(pq->sorted_list);
}

int PQEnqueue(pq_t *pq, void *data)
{
	return SortedListInsert(pq->sorted_list, data);
}

void *PQDequeue(pq_t *pq)
{
	SortedListRemove(SortedListBegin(pq->sorted_list));
}	

void *PQPeek(const pq_t *pq)
{
	return SortedListGetData(SortedListBegin(pq->sorted_list));
}

void PQClear(pq_t *pq)
{
	while(PQIsEmpty(pq))
	{
		SortedListRemove(SortedListBegin(pq->sorted_list));
	}
}

void *PQErase(pq_t *pq, pq_is_match_t is_match_func, void *params);
{
	SortedListRemove(SortedListFindIf(SortedListBegin(pq->sorted_list),
					SortedListEnd(pq->sorted_list), is_match_func, params));
}
/******************************************************************************
*							STATIC FUNCTIONS								  * 
******************************************************************************/

