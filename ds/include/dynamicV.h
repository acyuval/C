#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <stddef.h> /* size_t */

typedef struct vector vector_t;

/******************************************************************************
*Description: creates a dynamic vector
*Arguments: the size of the elements and the initial capacity of the vector
*Return Value: pointer to the created vector
*Time Complexity: O(1)
*Space Complexity: O(n)
*Notes: capacity or element size of 0 is an undefined behavior
if the memory allocation failed, the function returns NULL 
******************************************************************************/
vector_t *VectorCreate(size_t element_size, size_t capacity);


/******************************************************************************
*Description: destroys the given vector
*Arguments: pointer to the vector
*Return Value: void
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
void VectorDestroy(vector_t *vector);

/******************************************************************************
*Description: access to the arbitrary index in the vector
*Arguments: pointer to the vector and an index in the vector
*Return Value: pointer to the data in the given index
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: trying to access outside the bounds of the vector is undefined behavior
******************************************************************************/
void *VectorGetAccess(vector_t *vector, size_t index);

/******************************************************************************
*Description: pushes the given data to the end of the vector
*Arguments: pointer to the vector and a pointer to the data to push
*Return Value: 0 for success, -1 for failure
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: will attempt to grow the capacity by the growth factor if the
vector is currently full.
******************************************************************************/
int VectorPushBack(vector_t *vector, const void *data);

/******************************************************************************
*Description: pops the end of the vector out
*Arguments: pointer to the vector
*Return Value: 0 for success, -1 for failure
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: popping out of an empty vector leads to undefined behavior.
will shrink the capacity by the growth factor after popping if possible,
to avoid too much wasted space
******************************************************************************/
int VectorPopBack(vector_t *vector);

/******************************************************************************
*Description: returns the current size of the vector
*Arguments: pointer to the vector
*Return Value: the current size of the vector
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
size_t VectorSize(const vector_t *vector);

/******************************************************************************
*Description: returns the current capacity
*Arguments: pointer to the vector
*Return Value: the current capacity 
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
size_t VectorCapacity(const vector_t *vector);

/******************************************************************************
*Description: shrinks the capacity of the vector to the minimum size necessary 
              to keep the current data
*Arguments: pointer to the vector
*Return Value: 0 for success, -1 for failure
*Time Complexity: O(n)
*Space Complexity: O(1)
******************************************************************************/
int VectorShrink(vector_t *vector);

/******************************************************************************
*Description: changes the capacity of the given vector to the given size
*Arguments: pointer to the vector and a new capacity
*Return Value: 0 for success, -1 for failure
*Time Complexity: O(n)
*Space Complexity: O(n)
*Notes: does not check the validity of the new size
******************************************************************************/
int VectorReserve(vector_t *vector, size_t new_capacity);


#endif	/* __VECTOR_H__ */
