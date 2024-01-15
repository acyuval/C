/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Dor
*	Date:      
******************************************************************************/
#include <assert.h>
#include <stdlib.h>

#include "heap.h"
#include "heap_pq.h"

#define TRUE (1)
#define FALSE (0)
#define SUCCESS (0)
#define FAIL (-1)
/******************************************************************************
*							 DECLRATION								  * 
******************************************************************************/

struct pq
{
	heap_t *heap;
};

/******************************************************************************
*							 FUNCTIONS 										  * 
******************************************************************************/

pq_t *HeapPQCreate(pq_compare_t compare_func)
{
	pq_t * pq = (pq_t *)malloc(sizeof(pq_t));
	
	if(NULL == pq)
	{
		return NULL;
	}
	
	pq->heap = HeapCreate(compare_func);
	
	if(NULL == pq->heap)
	{
		free(pq);
		return NULL;
	}
	return (pq);
}



void HeapPQDestroy(pq_t *pq)
{
	assert(pq != NULL);
	HeapDestroy(pq->heap);
	free(pq);
}


int HeapPQIsEmpty(const pq_t *pq)
{
	assert(pq != NULL);
	return HeapIsEmpty(pq->heap);
}


size_t HeapPQSize(const pq_t *pq)
{
	assert(pq != NULL);
	return HeapSize(pq->heap);
}

int HeapPQEnqueue(pq_t *pq, void *data)
{
	int status = 0;
	size_t size = 0;
	assert(pq != NULL);
	size = HeapSize(pq->heap);
	HeapPush(pq->heap, data);
	
	status = HeapSize(pq->heap) - size;
	
	return status ? SUCCESS: FAIL;
}

void *HeapPQDequeue(pq_t *pq)
{
	void * return_data = NULL;
	
	assert(pq != NULL);
	assert(FALSE == HeapPQIsEmpty(pq));
	
	return_data = HeapPQPeek(pq);
	HeapPop(pq->heap);
	return return_data;
}	

void *HeapPQPeek(const pq_t *pq)
{
	assert(pq != NULL);
	assert(FALSE == HeapPQIsEmpty(pq));
	
	return HeapPeek(pq->heap);
}

void HeapPQClear(pq_t *pq)
{
	assert(pq != NULL);
	while(FALSE == HeapPQIsEmpty(pq))
	{
		HeapPop(pq->heap);
	}
}

void *HeapPQErase(pq_t *pq, pq_is_match_t is_match_func, void *params)
{

	void * return_data = NULL;
	
	assert(pq != NULL);
	assert(is_match_func != NULL);
	

	return_data = HeapRemove(pq->heap, is_match_func, params);

	return return_data;
}
/******************************************************************************
*							STATIC FUNCTIONS								  * 
******************************************************************************/

