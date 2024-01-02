#ifndef __BST_H__
#define __BST_H__

#include <stddef.h> /* size_t */

typedef struct node *bst_iter_t;
typedef struct bst bst_t;

typedef int (*compare_t)(void *, void *);
typedef int (*action_t)(void *, void *);

/*
struct node
{
    void *data;
    bst_iter_t parent;
    bst_iter_t right;
    bst_iter_t left;
};

struct bst
{
    bst_iter_t root;
    compare_t compare_func;
};
*/

/******************************************************************************
*Description: Creates a new binary search tree.
*Arguments: CmpFunc - the compare function to sort the tree.
*			if comp(data1, data2) > 0: the data 1 will be in the right sub-tree 
*			if comp(data1, data2) == 0: order is irrelevant
*			if comp(data1, data2) < 0:  the data 1 will be in the left sub-tree
*Return Value: Pointer to the created binary search tree.
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: Returns NULL if memory allocation fails. 
* Undefined behavior if CmpFunc is NULL.
******************************************************************************/
bst_t *BSTCreate(compare_t compare_func);

/******************************************************************************
*Description: Destroys the binary search tree.
*Arguments: The binary search tree's iterator.
*Return Value: None.
*Time Complexity: O(n)
*Space Complexity: O(1)
*Notes: None.
******************************************************************************/
void BSTDestroy(bst_t *bst);

/******************************************************************************
*Description: Inserts the data to the binary search tree.
*Arguments: The binary search tree and the data to be inserted.
*Return Value: An iterator to the data in the binary search tree.
*Time Complexity: O(n)
*Space Complexity: O(1)
*Notes: 
******************************************************************************/
bst_iter_t BSTInsert(bst_t *bst, const void *data);

/******************************************************************************
*Description: Removes the iterator from the binary search tree.
*Arguments: The binary search tree's iterator.
*Return Value: Iterator to the next value in the tree.
*Time Complexity: O(n)
*Space Complexity: O(1)
*Notes: sending the end of the tree leads to undefined behavior
******************************************************************************/
bst_iter_t BSTRemove(bst_iter_t iter);

/******************************************************************************
*Description: Finds the node with the matching data in the tree.
*Arguments: The binary search tree's iterator and the data to find.
*Return Value: Iterator to the node in the tree.
*Time Complexity: O(log n)
*Space Complexity: O(1)
*Notes: Returns NULL if can't find the data in the binary search tree.
******************************************************************************/
bst_iter_t BSTFind(const bst_t *bst, const void *to_find);

/******************************************************************************
*Description: Returns the data pointed to by the iterator.
*Arguments: Iterator that points to the data.
*Return Value: The data.
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: undefined behavior if sending the end of the binary search tree.
******************************************************************************/
void *BSTGetData(const bst_iter_t iter);

/******************************************************************************
*Description: Checks if the binary search tree is empty
*Arguments: The binary search tree.
*Return Value: 1 if the binary search tree is empty, 0 otherwise.
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: 
******************************************************************************/
int BSTIsEmpty(const bst_t *bst);

/******************************************************************************
*Description: Finds the size of the binary search tree.
*Arguments: The binary search tree.
*Return Value: The size of the binary search tree.
*Time Complexity: O(n)
*Space Complexity: O(1)
*Notes: 
******************************************************************************/
size_t BSTSize(const bst_t *bst);

/******************************************************************************
*Description: compares the iterators and returns a bool value.
*Arguments: Two iteratros.
*Return Value: 1 if the iters are the same, 0 otherwise.
*Time Complexity: O(n)
*Space Complexity: O(1)
*Notes: 
******************************************************************************/
int BSTIsEqual(const bst_iter_t iter1, const bst_iter_t iter2);

/******************************************************************************
*Description: Returns an iterator to the start of the tree.
*Arguments: The binary search tree.
*Return Value: Iterator to the first node in the tree.
*Time Complexity: O(n)
*Space Complexity: O(1)
*Notes: If the tree is empty returns the dummy node.
******************************************************************************/
bst_iter_t BSTBegin(const bst_t *bst);

/******************************************************************************
*Description: Returns an iterator to the dummy at the end of the tree.
*Arguments: The binary search tree.
*Return Value: Iterator to the dummy node at the end of the tree.
*Time Complexity: O(1)
*Space Complexity: O(1)
*Notes: 
******************************************************************************/
bst_iter_t BSTEnd(const bst_t *bst);

/******************************************************************************
*Description: Returns the iterator whose data is the next according 
              to the CmpFunc
*Arguments: The binary search tree's iterator. 
*Return Value: The next iterator.
*Time Complexity: O(log n)
*Space Complexity: O(1)
*Notes: Returns NULL when given the end.
******************************************************************************/
bst_iter_t BSTNext(const bst_iter_t iter);

/******************************************************************************
*Description: Returns the iterator whose data is the prev according 
              to the CmpFunc
*Arguments: The binary search tree's iterator.
*Return Value: The prev iterator.
*Time Complexity: O(log n)
*Space Complexity: O(1)
*Notes: Returns NULL when given the begin
******************************************************************************/
bst_iter_t BSTPrev(const bst_iter_t iter);

/******************************************************************************
*Description: Iterates over the given range, from iterator "from" (inclusive)
*             to iterator "to" (non-inclusive) and acts on the data.
*Arguments:   2 iterators that mark the range, an action function,
*             and parameters for the function.
*Return Value: 0 if the action was successfull, -1 otherwise.
*Time Complexity: O(n)
*Space Complexity: O(1)
*Notes: action_func must strictrly increasing regarding the data.
* 		sending "to" that comes before "from" as parameters will lead to 
* 		undefined behavior.
******************************************************************************/
int BSTForEach(bst_iter_t from, bst_iter_t to, 
                        action_t action_func, const void *params);

#endif /* __BST_H__ */