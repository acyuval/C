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
    


static bst_iter_t CreateNewNode(void * data);

static void ConnectTwoNodes(bst_iter_t child,bst_iter_t parent, int type );
static int FindChiledSide(bst_iter_t iter);
static bst_iter_t DeepDive(bst_iter_t iter , int type);
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
        return NULL;
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
        iter_next = BSTNext(iter);
        iter_right_most_chiled = iter_next; 
        iter_right_most_chiled = DeepDive(iter_right_most_chiled, R);
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
    node_t *next = NULL;
    
    assert(NULL != iter);

    if (NULL == iter->parent)
    {
        return NULL;
    }

    if(iter->child[R] != NULL)
    {
        iter = iter->child[R];
        while(NULL != iter->child[L])
        {
            iter = iter->child[L];
        }
        next = iter; 
    }    
    else 
    {
        while(FindChiledSide(iter) == R)
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

    if (NULL == iter->child[L] && FindChiledSide(iter) == L)
    {
        return NULL;
    }

    if(iter->child[L] != NULL)
    {
        iter = iter->child[L];
        while(NULL != iter->child[R])
        {
            iter = iter->child[R];
        }
        prev = iter; 
    }    
    else 
    {
        while(FindChiledSide(iter) == L)
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
        if(status != SUCCESS)
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
    bst_iter_t node = NULL; 

    node = (bst_iter_t)malloc(sizeof(struct node));
    if (NULL == node)
    {
        return NULL;
    }

    node->data = data;
    node->child[L] = NULL;
    node->child[R] = NULL;
    node->parent = NULL; 
    return node;
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

static bst_iter_t DeepDive(bst_iter_t iter , int type)
{
    if(type == L)
    {
       while(iter->child[L] == NULL)
       {
            iter = iter->child[L];
       }
    }
    else
    {
        while(iter->child[R] == NULL)
       {
            iter = iter->child[R];
       }
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



  