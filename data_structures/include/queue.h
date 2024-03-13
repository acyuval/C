#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stddef.h> /* size_t */

typedef struct queue queue_t;

/* struct queue

	list_t *list
*/

/******************************************************************************
*Description: creates a new queue
*Parameters: none
*Return Value: pointer to the created queue
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: returns NULL if memory allocation failed
******************************************************************************/
queue_t *QueueCreate(void);


/******************************************************************************
*Description: destroys the given queue
*Parameters: pointer to a queue to destroy
*Return Value: none
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
void QueueDestroy(queue_t *queue);


/******************************************************************************
*Description: adds a new member to the back of the queue
*Parameters: pointer to the queue and pointer to data to enqueue
*Return Value: 0 in case of success, and -1 otherwise
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
int QueueEnqueue(queue_t *queue, const void *data);


/******************************************************************************
*Description: removes the member at the front of the queue
*Parameters: pointer to the queue
*Return Value: none
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: undefined behavior if the queue is empty
******************************************************************************/
void QueueDequeue(queue_t *queue);


/******************************************************************************
*Description: returns the data of the front member of the queue
*Parameters: pointer to the queue
*Return Value: data of the front member
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: undefined behavior if the queue is empty
******************************************************************************/
void *QueuePeek(const queue_t *queue);


/******************************************************************************
*Description: counts the number of members in the queue
*Parameters: pointer to the queue
*Return Value: the number of members
*Time Complexity: O(n)
*Space Complexity: O(1)
******************************************************************************/
size_t QueueSize(const queue_t *queue);


/******************************************************************************
*Description: checks whether the given queue is empty
*Parameters: pointer to the queue
*Return Value: 1 if the queue is empty, and 0 otherwise
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
int QueueIsEmpty(const queue_t *queue);


/******************************************************************************
*Description: appends the queue "src" to the back of the queue "dest"
			  and empties "src"
*Parameters: two pointers to queues to append to each other
*Return Value: none
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
void QueueAppend(queue_t *dest, queue_t *src);




#endif /* __QUEUE_H__ */

