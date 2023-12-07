#ifndef __SLL_H__
#define __SLL_H__

#include <stddef.h> /* size_t */

typedef struct node *slist_iter_t;
typedef struct list list_t;
typedef int (*is_match_t)(void *, void *);
typedef int (*action_t)(void *, void *);


/******************************************************************************
*Description: creates a new list
*Arguments: none
*Return Value: pointer to the created list
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
list_t* SLLCreate(void);


/******************************************************************************
*Description: deletes the entire list
*Arguments: pointer to a list
*Return Value: void
*Time Complexity: O(n)
*Space Complexity: O(1)
******************************************************************************/
void SLLDestroy(list_t *list);


/******************************************************************************
*Description: 
*Arguments: 
*Return Value: 
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: 
******************************************************************************/
slist_iter_t SLLInsert(list_t *list, slist_iter_t where, void *value);


/******************************************************************************
*Description: removes the node that the given iterator points to from the list
*Arguments: iterator
*Return Value: 
*Time Complexity: O(1)
*Space Complexity: O(1)
Notes: 
******************************************************************************/
slist_iter_t SLLRemove(slist_iter_t iter);


/******************************************************************************
*Description: counts the number of nodes in the given list
*Arguments: pointer to a list 
*Return Value: the number of nodes
*Time Complexity: O(n)
*Space Complexity: O(1)
******************************************************************************/
size_t SLLCount(const list_t *list);


/******************************************************************************
*Description: finds a node with specific data in the given range, from iterator
              "from" (inclusive) to iterator "to" (non-inclusive)
*Arguments: 2 iterators that mark the range, a comparison function,
            and parameters to compare
*Return Value: iterator pointing to the matching data
*Time Complexity: O(n)
*Space Complexity: O(1)
*Notes: returns NULL if no match was found 
******************************************************************************/
slist_iter_t SLLFind(slist_iter_t from, slist_iter_t to,
				is_match_t is_match_func, void *params);


/******************************************************************************
*Description: checks whether the given list is empty
*Arguments: pointer to a list
*Return Value: 1 if the list is empty, or 0 otherwise
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
int SLLIsEmpty(const list_t *list);


/******************************************************************************
*Description: updates the iterator to points to the end of the list
*Arguments: pointer to a list
*Return Value: iterator that points to the end of the list
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
slist_iter_t SLLEnd(const list_t *list);


/******************************************************************************
*Description: updates the iterator to points to the beginning of the list
*Arguments: pointer to a list
*Return Value: iterator that points to the beginning of the list
*Time Complexity: O(1)
*Space Complexity: O(1) 
******************************************************************************/
slist_iter_t SLLBegin(const list_t *list);


/******************************************************************************
*Description: advances the iterator to the next node
*Arguments: iterator
*Return Value: iterator that points to the next node
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: inputting the end of a list leads to undefined behavior
******************************************************************************/
slist_iter_t SLLNext(slist_iter_t iterator); 


/******************************************************************************
*Description: gets the data pointed to by the iterator
*Arguments: iterator
*Return Value: the data pointed to
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes inputting the end of a list leads to undefined behavior
******************************************************************************/
void *SLLGetData(slist_iter_t iterator);


/******************************************************************************
*Description: sets data in the given iterator
*Arguments: iterator and pointer to the data
*Return Value: void
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: 
******************************************************************************/
void SLLSetData(slist_iter_t iterator, void *data);


/******************************************************************************
*Description: checks whether 2 iterators point to the same node
*Arguments: 2 iterators to compare
*Return Value: 1 if they point to the same node, and 0 otherwise
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: 
******************************************************************************/
int SLLIsEqual(slist_iter_t iterator_1, slist_iter_t iterator_2);


/******************************************************************************
*Description: iterates over the given range, from iterator "from" (inclusive)
              to iterator "to" (non-inclusive) and acts on the data.
*Arguments: 2 iterators that mark the range, an operation function,
			and additional parameters
*Return Value: 0 if the action was successfull, and -1 otherwise
*Time Complexity: O(n)
*Space Complexity: O(1)
*Notes: 
******************************************************************************/
int SLLForEach(slist_iter_t from, slist_iter_t to, action_t act_func, void *params);


/******************************************************************************
*Description: appends the list "src" to the end of the list "dest"
*Parameters: two pointers to lists to append to each other
*Return Value: none
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
void SLLAppend(list_t *dest, list_t *src);


#endif /* __SLL_H__ */

