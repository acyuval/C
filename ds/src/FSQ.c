/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/

#include <stddef.h> /* size_t 			  */
#include <stdlib.h> /* malloc() , free()  */
#include <assert.h> /* assert			  */
#include <semaphore.h>
#include <pthread.h>
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
	sem_t sem_read;
	sem_t sem_write;
	pthread_mutex_t mutex_read;
	pthread_mutex_t mutex_write;
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
	pthread_mutex_init(&buffer->mutex_read, NULL);	
	pthread_mutex_init(&buffer->mutex_write, NULL);	
	sem_init(&buffer->sem_write, 0 , capacity);
    sem_init(&buffer->sem_read, 0 , 0);
	buffer-> read = 0;
	buffer-> write = 0;
	buffer-> capacity = capacity;
	return buffer;
}


void BufferDestroy(buffer_t *buffer)
{
	assert(NULL != buffer);
	sem_destroy(&buffer->sem_write);
	sem_destroy(&buffer->sem_read);
	pthread_mutex_destroy(&buffer->mutex_read);
	pthread_mutex_destroy(&buffer->mutex_write);		
	free(buffer);
}


size_t BufferRead(void *dest, buffer_t *buffer, size_t n)
{
	size_t dest_index = 0;
	char * dest_ptr = (char *)dest;
	size_t cap = buffer->capacity;
	size_t read_i = buffer->read;
	
	pthread_mutex_lock(&buffer->mutex_read);
	while(n--)
	{
		sem_wait(&buffer->sem_read);
		dest_ptr[dest_index] = buffer->array[read_i];
		read_i= (read_i + 1) % (cap + 1);  
		dest_index++;
		buffer->read += 1;
		sem_post(&buffer->sem_write);
	}
	pthread_mutex_unlock(&buffer->mutex_read);
	return dest_index;
}

size_t BufferWrite(const void *src, buffer_t *buffer, size_t n)
{
	size_t src_index = 0;
	char * src_ptr = (char *)src;
	size_t cap = buffer->capacity;
	size_t write_i = buffer->write;
	
	pthread_mutex_lock(&buffer->mutex_write);
	while(n--)
	{
		sem_wait(&buffer->sem_write);
		buffer->array[write_i] = src_ptr[src_index];
		write_i = (write_i + 1) % (cap + 1);
		src_index++;
		buffer->write += 1;
		sem_post(&buffer->sem_read);
	}
	pthread_mutex_unlock(&buffer->mutex_write);
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


