/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/

#include <stddef.h> /* size_t 			  */
#include <stdlib.h> /* malloc() , free()  */
#include <assert.h> /* assert			  */
#include <stdio.h>

#include "Cbuffer.h"

#define SUCCESS (0)
#define FAIL (-1)
/******************************************************************************
*							 DECLRATION								  * 
******************************************************************************/

struct buffer
{
	size_t read;
	size_t write;
	size_t capacity;
	char array[1];
};


/******************************************************************************
*							 FUNCTIONS 										  * 
******************************************************************************/



buffer_t *BufferCreate(size_t capacity)
{
	
	buffer_t *buffer = NULL;
	
	assert(capacity > 0);
	
	buffer = (buffer_t *)malloc(sizeof(buffer_t) + capacity);
	
	if (NULL == buffer)
	{
		return NULL;
	}	
	
	buffer-> read = 0;
	buffer-> write = 0;
	buffer-> capacity = capacity;
}


void BufferDestroy(buffer_t *buffer)
{
	assert(NULL != buffer);
	free(buffer);
}


size_t BufferRead(void *dest, buffer_t *buffer, size_t n)
{
	size_t dest_index = 0;
	char * dest_ptr = (char *)dest;
	
	while(n-- && !BufferIsEmpty(buffer))
	{
		dest_ptr[dest_index] = buffer->array[buffer->read];
		buffer->read = (buffer->read + 1) % (buffer->capacity + 1);
		dest_index++;
	}

	return dest_index;


}

size_t BufferWrite(const void *src, buffer_t *buffer, size_t n)
{
	size_t src_index = 0;
	char * src_ptr = (char *)src;
	
	while(n-- && BufferFreeSpace(buffer))
	{
		buffer->array[buffer->write] = src_ptr[src_index];
		buffer->write = (buffer->write + 1) % (buffer->capacity + 1);
		src_index++;
	}
	
	return src_index;
}

size_t BufferSize(const buffer_t *buffer)
{
	return ((buffer->capacity +1) + buffer->write - buffer->read) %
														(buffer->capacity + 1);
}

int BufferIsEmpty(const buffer_t *buffer)
{
	return (buffer->read == buffer->write);
}


size_t BufferFreeSpace(const buffer_t* buffer)
{
	return buffer->capacity - BufferSize(buffer);
}


