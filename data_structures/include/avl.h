#ifndef __AVL_H__
#define __AVL_H__

#include <stddef.h> /* size_t */

typedef struct avl avl_t;

typedef int (*compare_t)(void *, void *);
typedef int (*action_t)(void *, void *);

typedef enum traversal
{
	PRE_ORDER = 0,
	IN_ORDER,
	POST_ORDER
} traversal_t;

typedef enum
{
	FAIL = -1,
	SUCCESS = 0
} status_t;


/******************************************************************************
 *Description: Creates a new balanced binary search tree.
 *Arguments: compare_func - the compare function to sort the tree.
 *			if comp(data1, data2) > 0: the data 2 will be in the left sub-tree
 *			if comp(data1, data2) == 0: order is irrelevant
 *			if comp(data1, data2) < 0:  the data 2 will be in the right sub-tree
 *Return Value: Pointer to the created balanced binary search tree.
 *Time Complexity: O(1)
 *Space Complexity: O(1)
 *Notes: Returns NULL if memory allocation fails.
 *       Undefined behavior if compare_func is NULL.
 ******************************************************************************/
avl_t *AVLCreate(compare_t compare_func);

/******************************************************************************
 *Description: Destroys the balanced binary search tree.
 *Arguments: Pointer to the balanced binary search tree.
 *Return Value: None.
 *Time Complexity: O(n)
 *Space Complexity: O(n)
 *Notes: None.
 ******************************************************************************/
void AVLDestroy(avl_t *avl);

/******************************************************************************
 *Description: Inserts the data to the balanced binary search tree.
 *Arguments: The balanced binary search tree and the data to be inserted.
 *Return Value: 0 if the insertion was successful, -1 otherwise.
 *Time Complexity: O(log(n))
 *Space Complexity: O(log(n))
 *Notes:
 ******************************************************************************/
status_t AVLInsert(avl_t *avl, const void *data);

/******************************************************************************
 *Description: Removes the node matching given data from the balanced binary
 *             search tree.
 *Arguments: The balanced binary search tree and the data to be removed.
 *Return Value:
 *Time Complexity: O(log(n))
 *Space Complexity: O(log(n))
 *Notes: Undefined behaviour if data is not in the tree.
 ******************************************************************************/
void AVLRemove(avl_t *avl, void *data);

/******************************************************************************
 *Description: Finds the node with the matching data in the tree.
 *Arguments: Pointer to the balanced binary search tree and the data to find.
 *Return Value: The data of the found node, NULL otherwise.
 *Time Complexity: O(log(n))
 *Space Complexity: O(log(n))
 *Notes:
 ******************************************************************************/
void *AVLFind(const avl_t *avl, const void *to_find);

/******************************************************************************
 *Description: Checks if the balanced binary search tree is empty
 *Arguments: Pointer to the balanced binary search tree.
 *Return Value: 1 if the balanced binary search tree is empty, 0 otherwise.
 *Time Complexity: O(1)
 *Space Complexity: O(1)
 *Notes:
 ******************************************************************************/
int AVLIsEmpty(const avl_t *avl);

/******************************************************************************
 *Description: Returns the size of the balanced binary search tree.
 *Arguments: Pointer to the balanced binary search tree.
 *Return Value: The size of the balanced binary search tree.
 *Time Complexity: O(n)
 *Space Complexity: O(n)
 *Notes:
 ******************************************************************************/
size_t AVLSize(const avl_t *avl);

/******************************************************************************
 *Description: Returns the height of the balanced binary search tree.
 *Arguments: Pointer to the balanced binary search tree.
 *Return Value: The height of the balanced binary search tree.
                An empty tree will return 0.
 *Time Complexity: O(1)
 *Space Complexity: O(1)
 *Notes:
 ******************************************************************************/
size_t AVLHeight(const avl_t *avl);

/******************************************************************************
 *Description: Iterates on all nodes in the tree and acts on the data.
 *Arguments:   Pointer to the balanced binary search tree,
			   mode which is either (PRE_ORDER, IN_ORDER, POST_ORDER)
 *             and parameters for the function.
 *Return Value: 0 if the action was successful, -1 otherwise.
 *Time Complexity: O(n)
 *Space Complexity: O(n)
 *Notes: act_func must be strictrly increasing regarding the data.
 ******************************************************************************/
status_t AVLForEach(avl_t *avl, traversal_t mode, action_t act_func,
					void *params);


#endif /* __AVL_H__ */