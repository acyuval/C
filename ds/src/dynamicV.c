/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/

#include <string.h> /* memcpy()				*/
#include <stdlib.h> /* malloc()	free()		*/ 
#include <assert.h> /* assert()				*/
#include <assert.h>
#include <stdio.h>

#include "dynamicV.h"


#define GROWTH 2
#define SIZE_IN_BYTES (vector->element_size * vector->size) 

static void *  ChangeSize(vector_t *vector , size_t new_cap);


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

	assert(element_size != 0);
	assert(capacity != 0);
	
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
	assert(NULL != vector);
	
	if (vector->size > vector->capacity)
	{
		vector->buffer = ChangeSize(vector , vector->size * GROWTH);
		if(NULL == vector->buffer)
		{
			return 1;
		}
	}
	
	memcpy((char *)vector-> buffer + SIZE_IN_BYTES , data, vector-> element_size);
	vector-> size += 1;

	return (0);
}




int VectorPopBack(vector_t *vector)
{
	assert(NULL != vector);
	assert(vector->size != 0);
	
	*(int *)((char *)vector->buffer + vector->size) = 0;   						/* delete is made by changeing last value to 0 */
	vector->size -= 1;
	
	if (vector->size < (vector->capacity)/GROWTH)
	{
		vector->buffer = ChangeSize(vector, (vector->capacity / GROWTH));
		if(NULL == vector->buffer)
		{
			return 1;
		}		
	}
	
	return 0;
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
	assert(NULL != vector);
	assert(vector->size != 0);

	vector->buffer =  ChangeSize(vector, vector->size);
	if(NULL == vector->buffer)
		{
			return 1;
		}		

	return (0);
}

int VectorReserve(vector_t *vector, size_t new_capacity)
{
	assert(NULL != vector);
	vector->buffer =  ChangeSize(vector, new_capacity);

	if(NULL == vector->buffer)
		{
			return 1;
		}		

	return (0);
}

static void *  ChangeSize(vector_t *vector ,size_t new_cap)
{
	void *shrinked_buffer = NULL;
	
	shrinked_buffer = realloc(vector->buffer , new_cap*vector->element_size);
	
	if(NULL == shrinked_buffer)
	{
		return (vector->buffer);
	}
	
	vector->capacity =  new_cap;

	return (shrinked_buffer);
}




