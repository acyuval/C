/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/

#include <stddef.h> /* size_t 			  */
#include <stdlib.h> /* malloc() , free()  */
#include <assert.h> /* assert			  */

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

/*when writing and reading from buffer one needs to consider one cell space 
between reading and wrinting indexs to distinguish between empty/full queue */  

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
	size_t cap = buffer->capacity;
	size_t read_i = buffer->read;
	
	while(n-- && !BufferIsEmpty(buffer))
	{
		dest_ptr[dest_index] = buffer->array[read_i];
		read_i= (read_i + 1) % (cap + 1);  
		dest_index++;
	}

	return dest_index;


}

size_t BufferWrite(const void *src, buffer_t *buffer, size_t n)
{
	size_t src_index = 0;
	char * src_ptr = (char *)src;
	size_t cap = buffer->capacity;
	size_t write_i = buffer->write;
	
	while(n-- && BufferFreeSpace(buffer))
	{
		buffer->array[write_i] = src_ptr[src_index];
		write_i = (write_i + 1) % (cap + 1);
		src_index++;
	}
	
	return src_index;
}

size_t BufferSize(const buffer_t *buffer)
{
	size_t cap = buffer->capacity;
	size_t write_i = buffer->write;
	size_t read_i = buffer->read;
	return ((cap +1) + write_i - read_i) % (cap + 1);
}

int BufferIsEmpty(const buffer_t *buffer)
{
	return (buffer->read == buffer->write);
}


size_t BufferFreeSpace(const buffer_t* buffer)
{
	return buffer->capacity - BufferSize(buffer);
}


