#ifndef __HEAP_H__
#define __HEAP_H__

#include <stddef.h>

typedef int (*compare_func_t)(void *, void *);
typedef int (*is_match_func_t)(void *, void *);

typedef enum
{
	FAIL = -1,
	SUCCESS = 0
} status_t;

typedef struct heap heap_t;



/******************************************************************************
 *Description: Creates a new heap.
 *Arguments: compare function to compare two elements.
 *Return Value: Pointer to the created heap.
 *Time Complexity: O(1)
 *Space Complexity: O(1)
 *Notes: Returns NULL if memory allocation fails.
 *       Undefined behavior if compare_func is NULL.
 ******************************************************************************/
heap_t *HeapCreate(compare_func_t compare_func);

/******************************************************************************
 *Description: Destroys the heap.
 *Arguments: Pointer to the heap.
 *Return Value: None.
 *Time Complexity: O(1)
 *Space Complexity: O(1)
 *Notes: None.
 ******************************************************************************/
void HeapDestroy(heap_t *heap);

/******************************************************************************
 *Description: Inserts pointer to the data into the heap.
 *Arguments: Pointer to the heap, pointer to the data.
 *Return Value: int for status (0 - success, -1 - failure).
 *Time Complexity: O(log(n))
 *Space Complexity: O(1)
 *Notes: Undefined behavior if the heap pointer is NULL.
 ******************************************************************************/
status_t HeapPush(heap_t *heap, const void *data);

/******************************************************************************
 *Description: Removes the data from the head of the heap.
 *Arguments: Pointer to the heap.
 *Return Value: None.
 *Time Complexity: O(log(n))
 *Space Complexity: O(1)
 *Notes: Undefined behavior if the heap pointer is NULL.
 ******************************************************************************/
void HeapPop(heap_t *heap);

/******************************************************************************
 *Description: Removes the specific data from the heap.
 *Arguments: Pointer to the heap, pointer to a matching function, pointer to
            the parameters for the function.
 *Return Value: None.
 *Time Complexity: O(log(n))
 *Space Complexity: O(1)
 *Notes: Undefined behavoir if the heap pointer or the is_match function 
        pointer are NULL.
 ******************************************************************************/
void HeapRemove(heap_t *heap, is_match_func_t is_match_func, void *pararms);

/******************************************************************************
 *Description: Returns the pointer to the data of the head of the heap.
 *Arguments: Pointer to the heap.
 *Return Value: Pointer to the head of the heap. 
 *Time Complexity: O(1)
 *Space Complexity: O(1)
 *Notes: Undefined behavoir if the heap pointer is NULL.
 ******************************************************************************/
void *HeapPeek(const heap_t *heap);

/******************************************************************************
 *Description: Calculates the size of the heap.
 *Arguments: Pointer to the heap.
 *Return Value: Size of the heap.
 *Time Complexity: O(1)
 *Space Complexity: O(1)
 *Notes: Undefined behavoir if the heap pointer is NULL.
 ******************************************************************************/
size_t HeapSize(const heap_t *heap);

/******************************************************************************
 *Description: Checks if the heap is empty.
 *Arguments: Pointer to the heap..
 *Return Value: int boolean value (1 - true, 0 - false).
 *Time Complexity: O(1)
 *Space Complexity: O(1)
 *Notes: Undefined behavoir if the heap pointer is NULL.
 ******************************************************************************/
int HeapIsEmpty(const heap_t *heap);

#endif /* __HEAP_H__ */