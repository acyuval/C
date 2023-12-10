#ifndef __CBUFFER_H__
#define __CBUFFER_H__

#include <stddef.h>    /* size_t  */

typedef struct buffer buffer_t;


/******************************************************************************
*Description: Creates a new circular buffer.
*Arguments: Capacity - the fixed size of the buffer.
*Return Value: Pointer to the created circular buffer.
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: Returns NULL if memory allocation fails.
******************************************************************************/
buffer_t *BufferCreate(size_t capacity);

/******************************************************************************
*Description: Deletes the entire circular buffer.
*Arguments: Pointer to a circular buffer.
*Return Value: void.
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
void BufferDestroy(buffer_t *buffer);

/******************************************************************************
*Description: Read up to n bytes from a given circular buffer into the given 
*			  dest.
*Arguments: dest - pointer to a block of memory, into which the buffer is read.
*			buffer - pointer to a circular buffer.
*			n - the amount of bytes to be read from the buffer.
*Return Value: The number of elements that were read successfully.
*Time Complexity: O(n)
*Space Complexity: O(1)
*Notes: If the current buffer size is less than n, only <buffer size> bytes will
*		be read.
******************************************************************************/
size_t BufferRead(void *dest, buffer_t *buffer, size_t n);

/******************************************************************************
*Description: Writes up to n bytes from the given source into a given circular 
*			  buffer.
*Arguments: src - pointer to a block of memory to be written into the buffer.
*			buffer - pointer to a circular buffer.
*			n - the amount of bytes to be written into the buffer.
*Return Value: The number of elements that were written successfully.
* *Time Complexity: O(n)
*Space Complexity: O(1)
*Notes: If the amount of free space in the buffer is less than n, only <free 
		space> bytes will be written.
******************************************************************************/
size_t BufferWrite(const void *src, buffer_t *buffer, size_t n);

/******************************************************************************
*Description: Returns the amount of bytes that are currently held by the buffer.
*Arguments: buffer - pointer to a circular buffer.
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
size_t BufferSize(const buffer_t *buffer);

/******************************************************************************
*Description: Checks whether the given buffer is empty.
*Arguments: buffer - pointer to a circular buffer.
*Return Value: 1 if the buffer is empty, 0 otherwise.
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
int BufferIsEmpty(const buffer_t *buffer);

/******************************************************************************
*Description: Returns the remaining free space available in the buffer.
*Arguments: buffer - pointer to a circular buffer.
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
size_t BufferFreeSpace(const buffer_t* buffer);

#endif /*__CBUFFER_H__*/

