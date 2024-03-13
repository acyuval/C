/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/

#include <string.h> /* memcpy()						*/
#include <stdlib.h> /* malloc()	free(), realloc()	*/ 
#include <assert.h> /* assert()						*/

#include "dynamicV.h"


#define GROWTH_FACTOR (2)
#define SIZE_IN_BYTES (vector->element_size * vector->size) 
#define FAIL (-1)
#define SUCCESS (0)


static int ChangeBufferSize(void ** buffer ,size_t new_size);

struct vector 
{
	void * buffer;
	size_t element_size ; 
	size_t size;
	size_t capacity;
};


vector_t *VectorCreate(size_t element_size, size_t capacity)
{
	vector_t * this_vector = (vector_t *)malloc(sizeof(vector_t)); 

	assert(element_size > 0);
	assert(capacity > 0);
	if (NULL == this_vector)
	{
		return this_vector;
	} 
	
	this_vector->buffer = malloc(element_size*capacity);
	if (NULL == this_vector->buffer)
	{
		free(this_vector);
		return this_vector;
	}
	
	this_vector->element_size = element_size; 
	this_vector->size = 0;
	this_vector->capacity = capacity; 
	
	return (this_vector);	
}


void VectorDestroy(vector_t *vector)
{
	assert(NULL != vector);
	
	free(vector->buffer);
	vector->buffer = NULL;
	free(vector);
}



void *VectorGetAccess(vector_t *vector, size_t index)
{
	assert(NULL != vector);
	assert(index <= (vector->size));
	
	return ((char *)(vector-> buffer) + index * vector->element_size);
}




int VectorPushBack(vector_t *vector, const void *data)
{
	int ret_val = 0; 
	assert(NULL != vector);
	
	if (vector->size == vector->capacity)
	{
		ret_val = VectorReserve(vector, vector->size * GROWTH_FACTOR * vector->element_size);
		if(ret_val)
		{
			return (FAIL);
		}
	}
	
	memcpy((char *)vector-> buffer + SIZE_IN_BYTES , data, vector-> element_size);
	vector-> size += 1;

	return (SUCCESS);
}




int VectorPopBack(vector_t *vector)
{
	int status = SUCCESS; 

	assert(NULL != vector);
	assert(vector->size > 0);
	vector->size -= 1;
	
	if (vector->size == (vector->capacity)/GROWTH_FACTOR)
	{
		if (vector->size != 0)
		{
			status = VectorShrink(vector);
		}
	}
	
	return status;
}


size_t VectorSize(const vector_t *vector)
{
	assert(NULL != vector);
	
	return (vector->size);
}


size_t VectorCapacity(const vector_t *vector)
{	
	assert(NULL != vector);
	
	return (vector->capacity);	
}




int VectorShrink(vector_t *vector)
{
	int ret_val = 0;
	
	assert(NULL != vector);
	assert(vector->size > 0);
	
	ret_val = ChangeBufferSize(&(vector->buffer), vector->size*vector->element_size);
	if(0 != ret_val)
	{
		return FAIL;
	}		
	
	vector->capacity =  vector->size;
	
	return (SUCCESS);
}

int VectorReserve(vector_t *vector, size_t new_capacity)
{
	int ret_val = 0;
	
	assert(NULL != vector);
	ret_val = ChangeBufferSize(&(vector->buffer), new_capacity * vector->element_size);

	if(FAIL == ret_val)
	{
		return ret_val;
	}		
	
	vector->capacity =  new_capacity;
	return (SUCCESS);
}

static int ChangeBufferSize(void ** buffer ,size_t new_size)
{
	void *new_buffer = NULL;
	
	assert(new_size > 0);
	assert(buffer != NULL);

	new_buffer = realloc(*buffer , new_size);
	if(NULL == new_buffer)
	{
		return (FAIL);
	}
	
	*buffer = new_buffer;
	
	return (SUCCESS);
}




