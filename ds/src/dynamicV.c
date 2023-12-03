#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stddef.h> /* size_t */



struct vector 
{
	char * vector_ptr;
	size_t element_size ; 
	size_t size;
	size_t capacity;
};


vector_t *VectorCreate(element_size,capacity)
{
	vector_t * this_vector = (vector_t *)malloc(sizeof(vector_t)); 

	assert(element_size != 0);
	assert(cpacity != 0);
	
	if (NULL == this_vector)
	{
		return this_vector;
	} 
	
	this_vector->vector_ptr = malloc(element_size*capacity);
	
	if (NULL == this_vector->vector_ptr)
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
	free((vector-> vector_ptr) - (vector->size * vector->element_size));
	free(vector);
}



/******************************************************************************
*Description: access to the arbitrary index in the vector
*Arguments: pointer to the vector and an index in the vector
*Return Value: pointer to the data in the given index
*Time Complexity: O(1)
*Space Complexity: O(1)
Notes: trying to access outside the bounds of the vector is undefined behavior
******************************************************************************/
void *VectorGetAccess(vector_t *vector, size_t index);





/******************************************************************************
*Description: pushes the given data to the end of the vector
*Arguments: pointer to the vector and a pointer to the data to push
*Return Value: void 
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
void VectorPushBack(vector_t *vector, const void *data);





/******************************************************************************
*Description: pops the end of the vector out
*Arguments: pointer to the vector
*Return Value: void
*Time Complexity: O(1)
*Space Complexity: O(1)
Notes: popping out of an empty vector leads to undefined behavior
******************************************************************************/
void VectorPopBack(vector_t *vector);


size_t VectorSize(const vector_t *vector)
{
	assert(NULL != vector);
	
	return (vector->size);

}


size_t VectorCapacity(const vector_t *vector)
{	
	assert(NULL != stack);
	
	return (stack->capacity);	
}




/******************************************************************************
*Description: shrinks the capacity of the vector to the minimum size necessary 
              to keep the current data
*Arguments: pointer to the vector
*Return Value: pointer to the new location of the vector
*Time Complexity: O(n)
*Space Complexity: O(1)
******************************************************************************/
vector_t *VectorShrink(vector_t *vector);

/******************************************************************************
*Description: increments the reserved memory of the given vector by
              the given size
*Arguments: pointer to the vector and a size to add to the capacity
*Return Value: pointer to the new location of the vector
*Time Complexity: O(n)
*Space Complexity: O(n)
******************************************************************************/
vector_t *VectorReserve(vector_t *vector, size_t new_capacity);


