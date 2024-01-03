/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/

#include <assert.h> /* assert			  */
#include <stdio.h>
#include <stdlib.h>

#include "../include/bst.h"
#include "../include/utiles.h"

#define NEXT (1)
#define PREV (-1)
/******************************************************************************
*							 DECLRATION								  * 
******************************************************************************/
enum children 
{
    R = 0,
    L, 
    NUM_OF_CHILDREN
};

struct node
{
    void *data;
    bst_iter_t parent;
    bst_iter_t child[NUM_OF_CHILDREN];
};

typedef struct node node_t;

struct bst
{
    node_t root;
    compare_t cmp_func;
};

struct family
{
    bst_iter_t parent;
    bst_iter_t child;
    long diffrential;
};
    
static node_t * MoveOne (node_t * node , int side);
static void InitNode(node_t * node, void * data);
static bst_iter_t CreateNewNode(void * data);
static node_t * IterToNode(bst_iter_t iter);
static bst_iter_t NodeToIter(node_t * node);
static void ConnectTwoNodes(bst_iter_t child,bst_iter_t parent, int type );
static int FindChiledSide(bst_iter_t iter);
static bst_iter_t DeepDive(bst_iter_t iter , int side);
static struct family FindSpot(bst_iter_t iter, void * data , compare_t cmp_func);
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

    bst->root.data = NULL;
    bst->root.child[L] = NULL;
    bst->root.child[R] = NULL;
    bst->root.parent = NULL;

    bst->cmp_func = cmp_func;
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
    free(bst);
}

bst_iter_t BSTInsert(bst_t *bst, const void *data)
{
    bst_iter_t node = NULL;
    bst_iter_t iter = bst->root.child[L];
    struct family found = {0};
    assert(NULL != bst);
    assert(NULL != data);

    node = CreateNewNode((void *)data);
    if (node == NULL)
    {
        return BSTEnd(bst);
    }      
     /* insert to empty tree*/
    if(iter == NULL)
    {
        bst->root.child[L] = node;
        node->parent = &(bst->root);
        return iter;
    }

    found = FindSpot(iter, (void *)data, bst->cmp_func);
 
    assert(found.diffrential != 0);
    if (found.diffrential > 0)
    {
        ConnectTwoNodes(node, found.parent, L);
    }
    else
    {
        ConnectTwoNodes(node, found.parent, R);
    }    
    return node; 
}

bst_iter_t BSTRemove(bst_iter_t iter)
{
    bst_iter_t iter_right_most_chiled = NULL;
    bst_iter_t iter_next = NULL;
    bst_iter_t iter_child = NULL;
    int side = 0; 
    assert(NULL != iter);
    
    iter_next = BSTNext(iter);

    /* delete node with two children */

    if(iter->child[R] != NULL && iter->child[L] != NULL)
    {
        iter_right_most_chiled = DeepDive(iter_next, R);
        iter_right_most_chiled->child[R] = iter->child[R];
        iter_next->parent->child[L] = NULL;
        iter_next->parent = iter->parent;
        iter_next->child[L] = iter->child[L];
    }
    else  
    {
        /*delete node with one or no children*/
        iter_child = (bst_iter_t)((size_t)iter->child[L] ^ (size_t)iter->child[R]);
        side = FindChiledSide(iter);
        iter->parent->child[side] = iter_child;
        
        /* if chiled exist */
        if(iter_child != NULL)
        {
            iter_child->parent = iter->parent;
        }
    }
    
    free(iter);
    return iter_next;
}

bst_iter_t BSTFind(const bst_t *bst, const void *to_find)
{
    bst_iter_t iter = NULL;
    struct family found = {0};
    
    assert(bst != to_find);
    assert(bst != NULL);
    iter = bst->root.child[L];
    found = FindSpot(iter, (void *)to_find, bst->cmp_func);
    return found.child;
}

void *BSTGetData(bst_iter_t iter)
{
    assert(iter != NULL);

    return iter->data;
}

int BSTIsEmpty(const bst_t *bst)
{
    assert(NULL != bst);
    return (NULL == bst->root.child[L]);
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
    iter = (bst_iter_t)&(bst->root);
    while(NULL != iter->child[L])
    {
        iter = iter->child[L];
    }
    return iter;
}

bst_iter_t BSTEnd(const bst_t *bst)
{
    assert(NULL != bst);

    return (bst_iter_t)&bst->root;
}

bst_iter_t BSTNext(bst_iter_t iter)
{
   
    node_t * this_node = NULL;

    assert(NULL != iter);
    
    this_node = IterToNode(iter);
    
    if (NULL == this_node->parent )
    {
        return NULL;
    }

    return NodeToIter(MoveOne(iter, NEXT));
}

bst_iter_t BSTPrev(bst_iter_t iter)
{
    assert(NULL != iter);

    if (NULL == iter->child[L] && FindChiledSide(iter) == L)
    {
        return NULL;
    }

    return MoveOne(iter, PREV);
}

int BSTForEach(bst_iter_t from, bst_iter_t to, action_t action_func, const void *params)
{
    bst_iter_t iter = NULL;
    int status = SUCCESS;
    assert(NULL != action_func);
    assert(NULL != from);
    assert(NULL != to);
    
    iter = from;
    while(iter != to && status == SUCCESS)
    {
        status = action_func(iter->data, (void *)params);
        iter = BSTNext(iter);
    }

    return status;
}


/******************************************************************************
*							STATIC FUNCTIONS								  * 
******************************************************************************/

static void ConnectTwoNodes(bst_iter_t child,bst_iter_t parent, int type )
{
    if(type == L)
    {
        parent->child[L] = child;
        child->parent = parent;
    }
    if(type == R)
    {
        parent->child[R] = child;
        child->parent = parent;
    }    
}

static bst_iter_t CreateNewNode(void * data)
{
    node_t * node = NULL; 

    node = (node_t *)malloc(sizeof(node_t));
    if (NULL == node)
    {
        return NULL;
    }
    InitNode(node, data);
    return node;
}

static void InitNode(node_t * node, void * data)
{ 
    node->data = data;
    node->child[L] = NULL;
    node->child[R] = NULL;
    node->parent = NULL; 
}


static int FindChiledSide(bst_iter_t iter)
{
    if(BSTIsEqual((iter->parent)->child[L], iter))
    {
        return L;
    }
    else
    {
        return R;
    }
}

static bst_iter_t DeepDive(bst_iter_t iter , int side)
{
    while(iter->child[side] != NULL)
    {
        iter = iter->child[side];
    }
    return iter;
}

static struct family FindSpot(bst_iter_t iter, void * data , compare_t cmp_func)
{
    long diffrential = cmp_func(iter->data,(void *)data);
    struct family found = {NULL};

    while(diffrential != 0 && iter != NULL )
    {    
        diffrential = cmp_func(iter->data,(void *)data);
        found.parent = iter;
        if(diffrential > 0)
        {
            iter = iter->child[L];
        }
        if(diffrential < 0)
        {
            iter = iter->child[R];
        }
    }
    found.diffrential = diffrential;
    found.child = iter;
    return found;
}

static node_t * MoveOne (node_t * node , int type)
{ 
    node_t * found = NULL;
    int side = 0; 
    int miror_to_side = 0;

    side = (type == NEXT) ? R : L; 
    miror_to_side = 1-side;

    if(node->child[side] != NULL)
    {
        found = DeepDive(node->child[side] , miror_to_side); 
    }    
    else 
    {
        while(FindChiledSide(node) == side)
        {
            node = node->parent;
        }
        found = node->parent;
    }
    return found;
}

static node_t * IterToNode(bst_iter_t iter)
{
    return (node_t *) iter;
}

static bst_iter_t NodeToIter(node_t * node)
{
    return (bst_iter_t)node;
}
  