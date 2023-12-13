#ifndef __SORTED_LIST_H__
#define __SORTED_LIST_H__

#include "dll.h"

typedef struct sorted_list sorted_list_t;

typedef int (*compare_t) (void *, void *);


typedef struct sorted_iter
{
	dll_iter_t *iter;
	#ifndef NDEBUG
	sorted_list_t *sorted_list;
	#endif
} sorted_iter_t;

/******************************************************************************
*Description: Creates a new sorted list.
*Arguments: A comparison function:
			if comp(data1, data2) > 0: the list ordering is data2 ->..-> data1
			if comp(data1, data2) == 0: the data is considered equal by the list
			if comp(data1, data2) < 0: the list ordering is data1 ->..->data2
*Return Value: Pointer to the created sorted list.
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: Returns NULL if memory allocation fails.
******************************************************************************/
sorted_list_t *SortedListCreate(compare_t comp_func);

/******************************************************************************
*Description: Deletes the entire sorted list.
*Arguments: Pointer to a sorted list.
*Return Value: void.
*Time Complexity: O(n)
*Space Complexity: O(1)
******************************************************************************/
void SortedListDestroy(sorted_list_t *sorted_list);

/******************************************************************************
*Description: Checks whether the given sorted list is empty.
*Arguments: Pointer to a sorted list.
*Return Value: 1 if the sorted list is empty, 0 otherwise.
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
int SortedListIsEmpty(const sorted_list_t *sorted_list);

/******************************************************************************
*Description: Returns the amount of nodes in the given sorted list.
*Arguments: Pointer to a sorted list.
*Time Complexity: O(n)
*Space Complexity: O(1)
******************************************************************************/
size_t SortedListSize(const sorted_list_t *sorted_list);

/******************************************************************************
*Description: Gets the data pointed to by the given iterator.
*Arguments:An iterator.
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: Calling the function on the end of a list leads to undefined behavior.
******************************************************************************/
void *SortedListGetData(sorted_iter_t iter);

/******************************************************************************
*Description: Creates a new node with the given data, and inserts it into the
			  sorted list.
*Parameters: Data to insert, and a pointer to a sorted list
*Return Value: Iterator to the inserted node
*Time Complexity: O(n)
*Space Complexity: O(1)
*Notes: If memory allocation fails, returns NULL
******************************************************************************/
sorted_iter_t SortedListInsert(sorted_list_t *sorted_list, void *data);

/******************************************************************************
*Description: Removes the node that the given iterator refers to from the sorted 
			  list.
*Parameters: Iterator to be removed from the list.
*Return Value: Iterator to the next node.
*Time Complexity: O(1)
*Space Complexity: O(1)
Notes: Sending the end of the list as an argument will lead to 
*	   undefined behavior.
******************************************************************************/
sorted_iter_t SortedListRemove(sorted_iter_t iter);

/******************************************************************************
*Description: Removes the current last node of the sorted list.
*Parameters: Pointer to the list.
*Return Value: The data of the removed node
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: Popping from an empty list leads to undefined behavior.
******************************************************************************/
void *SortedListPopFront(sorted_list_t *sorted_list);

/******************************************************************************
*Description: Removes the current head of the sortedlist.
*Parameters: Pointer to the list.
*Return Value: The data of the removed node
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: Popping from an empty list leads to undefined behavior.
******************************************************************************/
void *SortedListPopBack(sorted_list_t *sorted_list);

/******************************************************************************
*Description: Merges two sorted lists (src and dest) into a single sorted list
			  held by dest. Src will be emptied.
*Parameters: Pointers to 2 sorted lists: src and dest.
*Return Value: void. 
*Time Complexity: O(n)
*Space Complexity: O(1)
*Notes: Sending an empty src leads to undefined behavior.
******************************************************************************/
void SortedListMerge(sorted_list_t *dest, sorted_list_t *src);

/******************************************************************************
*Description: Updates the iterator to point to the beginning of the sorted list
			  (a viable node)
*Parameters: Pointer to a sorted list.
*Return Value: Iterator to the beginning of the sorted list.
*Time Complexity: O(1)
*Space Complexity: O(1) 
******************************************************************************/
sorted_iter_t SortedListBegin(const sorted_list_t *sorted_list);

/******************************************************************************
*Description: Updates the iterator to point to the end of the sorted list 
			  (a none-viable node)
*Parameters: Pointer to a sorted list.
*Return Value: Iterator to the end of the sorted list.
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
sorted_iter_t SortedListEnd(const sorted_list_t *sorted_list);

/******************************************************************************
*Description: Returns the iterator to the previous node.
*Parameters: Iterator.
*Return Value: Iterator to the previous node.
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: Inputting the head of a list leads to undefined behavior.
******************************************************************************/
sorted_iter_t SortedListPrev(sorted_iter_t iter);

/******************************************************************************
*Description: Advances the iterator to the next node.
*Parameters: Iterator.
*Return Value: Iterator to the next node.
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: Inputting the end of a list leads to undefined behavior.
******************************************************************************/
sorted_iter_t SortedListNext(sorted_iter_t iter);

/******************************************************************************
*Description: Checks whether 2 iterators refer to the same node.
*Parameters: 2 iterators to compare.
*Return Value: 1 if they point to the same node, 0 otherwise.
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
int SortedListIsEqual(sorted_iter_t iter1, sorted_iter_t iter2);

/******************************************************************************
*Description: Iterates over the given range, from iterator "from" (inclusive)
*             to iterator "to" (non-inclusive) and acts on the data.
*Parameters: 2 iterators that mark the range, an operation function,
*			 and additional parameters.
*Return Value: 0 if the action was successfull, -1 otherwise
*Time Complexity: O(n)
*Space Complexity: O(1)
*Notes: Sending "to" that comes before "from" as parameters will lead to 
* 		undefined behavior. Sending "to" and "from" that belong to different
*		sorted lists leads to undefined behavior.
******************************************************************************/
int SortedListForEach(sorted_iter_t from, sorted_iter_t to, action_t act_func, void *params);

/******************************************************************************
*Description: Searches from iterator "from" (inclusive) to iterator "to" 
			  (non-inclusive) for a node with specific data ("to_find").
			  Comparison is done according to the sorted list's comparison
			  function.
*Parameters: 2 iterators that mark the range, the specified data to find, and
			 and a pointer to the sorted_list.
*Return Value: Iterator pointing to the matching data.
*Time Complexity: O(n)
*Space Complexity: O(1)
*Notes: Sending "to" that comes before "from" as parameters will lead to 
* 		undefined behavior. Sending "to" and "from" that belong to different
*		sorted lists leads to undefined behavior.
******************************************************************************/
sorted_iter_t SortedListFind(sorted_iter_t from, sorted_iter_t to, void *to_find, const sorted_list_t *sorted_list);

/******************************************************************************
*Description: Searches from iterator "from" (inclusive) to iterator "to" 
			  (non-inclusive) for a node with specific data ("to_find").
			  Comparison is done according to the given (boolean) function
			  is_match_func.
*Parameters: 2 iterators that mark the range, a boolean comparison function and
			 parameters to compare,
*Return Value: Iterator pointing to the matching data.
*Time Complexity: O(n)
*Space Complexity: O(1)
*Notes: Sending "to" that comes before "from" as parameters will lead to 
* 		undefined behavior. Sending "to" and "from" that belong to different
*		sorted lists leads to undefined behavior.
******************************************************************************/
sorted_iter_t SortedListFindIf(sorted_iter_t from, sorted_iter_t to, is_match_t is_match_func, void *params);

#endif /*  __SORTED_LIST_H__ */


