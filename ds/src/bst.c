/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/

#include <assert.h> /* assert			  */
#include <stdio.h>
#include <stdlib.h>

#include "../include/bst.h"


#define SUCCESS (0)
#define FAIL (-1)
#define FALSE (0)
#define TRUE (1)
#define LEFT (-1)
#define RIGHT (1)
/******************************************************************************
*							 DECLRATION								  * 
******************************************************************************/
struct bst
{
    bst_iter_t root;
    compare_t cmp_func;
};

struct node
{
    void *data;
    bst_iter_t parent;
    bst_iter_t right;
    bst_iter_t left;
};

static bst_iter_t CreateNewNode(void * data);

static void ConnectTwoNodes(bst_iter_t child,bst_iter_t parent, int type );
static int FindChiledSide(bst_iter_t iter);
/******************************************************************************
*							 FUNCTIONS 										  * 
******************************************************************************/
 
bst_t *BSTCreate(compare_t cmp_func)
{
    bst_t * bst = NULL;

    assert(NULL != cmp_func);
    bst = (bst_t *)malloc(sizeof(bst_t));
    
    if (NULL == bst)
    {
        return NULL;
    }
    

    bst->root = CreateNewNode(NULL);
    bst->cmp_func = cmp_func;
    if (bst->root == NULL)
    {
        free(bst);
        return NULL;
    }

    return bst; 
}

void BSTDestroy(bst_t *bst)
{
    bst_iter_t iter = NULL;
    assert(bst != NULL);

    iter = BSTBegin(bst);
    while(BSTIsEmpty(bst) != TRUE)
    {
        iter = BSTRemove(iter); 
    }
    free(bst->root);
    free(bst);
}

bst_iter_t BSTInsert(bst_t *bst, const void *data)
{
    bst_iter_t node = NULL;
    bst_iter_t iter = bst->root->left;
    bst_iter_t parent = NULL;
    int diffrential = 0;
    assert(NULL != bst);
    assert(NULL != data);

    node = CreateNewNode((void *)data);
    if (node == NULL)
    {
        return NULL;
    }      
     /* insert to empty tree*/
    if(iter == NULL)
    {
        bst->root->left = node;
        node->parent = bst->root;
        return iter;
    }

    while(iter != NULL)
    {    
        diffrential = bst->cmp_func(iter->data,(void *)data);
        assert(diffrential != 0);
        parent = iter;
        if(diffrential > 0)
        {
            iter = iter->left;
        }
        else
        {
            iter = iter->right;
        }
    }
        
    if(NULL == parent)
    {
        ConnectTwoNodes(node, parent, LEFT);
    }
    else if (diffrential > 0)
    {
        ConnectTwoNodes(node, parent, LEFT);
    }
    else
    {
        ConnectTwoNodes(node, parent, RIGHT);
    }

    return node; 
}

bst_iter_t BSTRemove(bst_iter_t iter)
{
    bst_iter_t iter_right_most_chiled = NULL;
    bst_iter_t iter_next = NULL;
    bst_iter_t iter_child = NULL;
    assert(NULL != iter);
    
    iter_next = BSTNext(iter);
    
    /*delete node with one or no children*/
    
    if (iter->left == NULL)
    {
        iter_child = iter->right;
        if(FindChiledSide(iter) == RIGHT)
        {
            iter->parent->right = iter->right;
        }
        else
        {
            iter->parent->left = iter->right;
        }
    }
    else if(iter->right == NULL)
    {
        iter_child = iter->left;
        if(FindChiledSide(iter) == LEFT)
        {
            iter->parent->left = iter->left;
        }
        else
        {
            iter->parent->right = iter->left;
        }    
    }
    /* if chiled exist */
    if(iter_child != NULL)
    {
        iter_child->parent = iter->parent;
    }

    /* delete node with two children */

    if(iter->right != NULL && iter->left != NULL)
    {
        iter_next = BSTNext(iter);
        
        iter_right_most_chiled = iter_next; 
        while(iter_right_most_chiled->right != NULL)
        {
            iter_right_most_chiled = iter_right_most_chiled->right;
        }

        iter_right_most_chiled->right = iter->right;
        iter_next->parent->left = NULL;
        iter_next->parent = iter->parent;
        iter_next->left = iter->left;
    }

    
    free(iter);
    return iter_next;
}


bst_iter_t BSTFind(const bst_t *bst, const void *to_find)
{
    bst_iter_t iter = NULL;
    int diffrential = 0;
    
    assert(bst != to_find);
    assert(bst != NULL);
    
    iter = bst->root->left;

    diffrential = bst->cmp_func(iter->data ,(void *)to_find);

    while (diffrential != 0 && iter != NULL)
    {
        diffrential = bst->cmp_func(iter->data , (void *)to_find);
        if (diffrential > 0)
        {
            iter = iter->left;
        }
        if (diffrential < 0)
        {
            iter = iter->right;
        }   
    }
    return iter;
}


void *BSTGetData(bst_iter_t iter)
{
    assert(iter != NULL);

    return iter->data;
}


int BSTIsEmpty(const bst_t *bst)
{
    assert(NULL != bst);
    return (NULL == bst->root->left);
}

size_t BSTSize(const bst_t *bst)
{
    bst_iter_t iter = NULL;
    size_t counter = 0; 
    assert(NULL != bst);
    iter = BSTBegin(bst);
    while(iter->parent != NULL)
    {
        iter = BSTNext(iter);
        ++counter;
    }
    return counter;
}

int BSTIsEqual(bst_iter_t iter1, bst_iter_t iter2)
{
    return (iter1 == iter2);
}

bst_iter_t BSTBegin(const bst_t *bst)
{
    bst_iter_t iter = NULL;
    assert(NULL != bst);
    iter = bst->root;
    while(NULL != iter->left)
    {
        iter = iter->left;
    }
    return iter;
}

bst_iter_t BSTEnd(const bst_t *bst)
{
    assert(NULL != bst);

    return bst->root;
}

bst_iter_t BSTNext(bst_iter_t iter)
{
    bst_iter_t next = NULL;
    
    assert(NULL != iter);

    if (NULL == iter->parent)
    {
        return NULL;
    }

    if(iter->right != NULL)
    {
        iter = iter->right;
        while(NULL != iter->left)
        {
            iter = iter->left;
        }
        next = iter; 
    }    
    else 
    {
        while(FindChiledSide(iter) == RIGHT)
        {
            iter = iter->parent;
        }
        next = iter->parent;
    }

    return next;
}

bst_iter_t BSTPrev(bst_iter_t iter)
{
    bst_iter_t prev = NULL;
    assert(NULL != iter);

    if (NULL == iter->left && FindChiledSide(iter) == LEFT)
    {
        return NULL;
    }

    if(iter->left != NULL)
    {
        iter = iter->left;
        while(NULL != iter->right)
        {
            iter = iter->right;
        }
        prev = iter; 
    }    
    else 
    {
        while(FindChiledSide(iter) == LEFT)
        {
            iter = iter->parent;
        }
        prev = iter->parent;
    }

    return prev;
}

int BSTForEach(bst_iter_t from, bst_iter_t to, action_t action_func, const void *params)
{
    bst_iter_t iter = NULL;
    int status = 0;
    assert(NULL != action_func);
    assert(NULL != from);
    assert(NULL != to);
    
    iter = from;
    while(iter != to)
    {
        status = action_func(iter->data, (void *)params);
        if(status == FAIL)
        {
            return FAIL;
        }

        iter = BSTNext(iter);
    }

    return SUCCESS;
}




/******************************************************************************
*							STATIC FUNCTIONS								  * 
******************************************************************************/

static void ConnectTwoNodes(bst_iter_t child,bst_iter_t parent, int type )
{
    if(type == LEFT)
    {
        parent->left = child;
        child->parent = parent;
    }
    if(type == RIGHT)
    {
        parent->right = child;
        child->parent = parent;
    }    
}

static bst_iter_t CreateNewNode(void * data)
{
    bst_iter_t node = NULL; 

    node = (bst_iter_t)malloc(sizeof(struct node));
    if (NULL == node)
    {
        return NULL;
    }

    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL; 
    return node;
}

static int FindChiledSide(bst_iter_t iter)
{
    if(BSTIsEqual((iter->parent)->left, iter))
    {
        return LEFT;
    }
    else
    {
        return RIGHT;
    }
}