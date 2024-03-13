/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Yael
*	Date:      
******************************************************************************/

#include <stddef.h> /* size_t 			  */
#include <stdlib.h> /* malloc() , free()  */
#include <assert.h> /* assert			  */

#include "queue.h"
#include "sll.h"

#define SUCCESS (0)
#define FAIL (-1)
/******************************************************************************
*							FUNCTION DECLRATION								  * 
******************************************************************************/



struct queue
{
	list_t *list;
};


/******************************************************************************
*							 FUNCTIONS 										  * 
******************************************************************************/


queue_t *QueueCreate(void)
{
	queue_t * queue = (queue_t *)malloc(sizeof(queue));
	
	if(NULL == queue)
	{
		return NULL;
	}
	
	queue->list = SLLCreate();
	if(NULL == queue->list)
	{
		free(queue);
		return NULL;
	}
	
	return (queue);

}


void QueueDestroy(queue_t *queue)
{
	assert(queue != NULL);
	SLLDestroy(queue->list);
	free(queue);
}

int QueueEnqueue(queue_t *queue, const void *data)
{
	void * ret_val = SLLInsert(queue->list, SLLEnd(queue->list), (void *)data);
	if(NULL == ret_val)
	{
		return (FAIL);
	}
	return(SUCCESS);
}

void QueueDequeue(queue_t *queue)
{
	SLLRemove(SLLBegin(queue->list));
}


void *QueuePeek(const queue_t *queue)
{
	return(SLLGetData(SLLBegin(queue->list)));
}


size_t QueueSize(const queue_t *queue)
{
	return(SLLCount(queue->list));
}


int QueueIsEmpty(const queue_t *queue)
{
	return(SLLIsEmpty(queue->list));
}


void QueueAppend(queue_t *dest, queue_t *src)
{
	SLLAppend(dest->list, src->list);
}
	
	
		



