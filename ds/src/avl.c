/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/

#include <assert.h> /* assert */
#include <stdlib.h>

#include "../include/avl.h"


#define MAX(a,b) (b>a) ? b : a ;

#define FALSE (0)
#define TRUE (1)

/*size - pre oreder , destroy - post order*/

/******************************************************************************
*							 DECLRATION								  * 
******************************************************************************/
typedef struct node node_t;

typedef enum children
{
	LEFT = 0,
	RIGHT,
	MAX_CHILDREN
} child_t;


typedef struct avl
{
	node_t *root;
	compare_t cmp_func;
}avl_t;

struct node
{
	void *data;
	node_t *child[MAX_CHILDREN];
	size_t height;
}


/*
typedef status_t (*for_each_t)(status_t * for_each_t[3]);
*/
/******************************************************************************
*							 FUNCTIONS 										  * 
******************************************************************************/



avl_t * AVLCreate(compare_t compare_func)
{
    avl_t * avl = NULL;
    
    assert(NULL != compare_func);

    avl = (avl_t *)malloc(sizeof(avl_t));
    if (NULL == avl)
    {
        return NULL;
    }

    avl->cmp_func = compare_func;
    avl->root = NULL;

    return avl;

}

void AVLDestroy(avl_t *avl)
{
    assert(NULL != avl);
    destroyHandler(avl->root);
    free(avl);
}

status_t AVLInsert(avl_t *avl, const void *data);
{
    node_t * new_node = NULL;
    node_t * found_spot = NULL;
    child_t side = 0;
    assert(NULL != avl);
    assert(NULL != data);

    new_node = (node_t *)malloc(sizeof(node_t));
    
    if(NULL == new_node)
    {
        return FAIL;
    }
    
    new_node->data = data;
    new_node->height = 0;

    if (NULL == avl->root)
    {
        avl->root = new_node;
    }
    else
    {
        StaticInsert(avl->root ,(void *)data ,compare, new_node);
    }

    return SUCCESS;
}


void AVLRemove(avl_t *avl, void *data)
{
    /*
    if(avl->root->data == data)
    {
        free();
    }
    */
}

void *AVLFind(const avl_t *avl, const void *to_find);
{

}

int AVLIsEmpty(const avl_t *avl)
{
    assert(NULL != avl);
    return ((NULL == avl->root)? 1 : 0 )
}

size_t AVLSize(const avl_t *avl)
{
    assert(NULL != avl);
    return StaticSize(avl->root);
}

size_t AVLHeight(const avl_t *avl)
{
    assert(NULL != avl);
    return ((AVLIsEmpty(avl))) ? 0 : avl->root->height;
}

int AVLForEach(avl_t *avl, traversal_t mode, action_t act_func, void *params)
{
    assert(NULL != avl);
    assert(NULL != act_func);
    
    switch (mode)
    {
    case PRE_ORDER:
        StaticForEachPreOrder(avl->root,act_func ,params);
        break;
    case IN_ORDER:
        StaticForEachInOrder(avl->root,act_func ,params);
        break;
    case POST_ORDER:
        StaticForEachPostOrder(avl->root,act_func ,params);
        break;
    default:
        break;
    }
}



/******************************************************************************
*							STATIC FUNCTIONS								  * 
******************************************************************************/

static void StaticDestroy(node_t  *node)
{
    if (NULL == node)
    {
        return;
    }

    StaticDestroy(node->child[LEFT]);
    StaticDestroy(node->child[RIGHT]);
    free(node);
}

static node_t * StaticRemove(node_t *node, void *data, compare_t compare)
{
    node_t *found_node = NULL;
    node_t *next_node = NULL;
    node_t *found_child = NULL;

    child_t side = (compare(node->data, data) > 0);

    if (compare(node->data, data) == SUCCESS)
    {
        return node;
    }
    found_node = StaticRemove(node->child[side], data, compare);

    if(found_node != NULL && HasBothChildren(found_node))
    {
        next_node = GetNextForRemove(node);

    }
    if(found_node != NULL && HasBothChildren(found_node) == FALSE)
    {
        found_child = (node_t *)((size_t)found_node->child[LEFT] ^ (size_t)found_node->child[RIGHT]);
        node->child[side] = found_child;
        free(found_node); 
    }

    return NULL;
}


static void * StaticFind(node_t *node, void *to_find, compare_t compare)
{
    node_t *found_node = NULL;
    
    if (NULL == node || compare(node->data, to_find) == SUCCESS)
    {    
        return node;
    }

    found_node = StaticFind(node->child[LEFT],to_find,compare);
    
    if (NULL == found_node)
    {
        found_node = StaticFind(node->child[RIGHT],to_find,compare);       
    }
    
    return found_node; 
}   


static size_t StaticSize(node_t *node)
{
    if(NULL == node)
    {
        return 0;
    }
    
    return (1 + ((StaticSize(node->child[RIGHT])) + (StaticSize(node->child[LEFT]))));
}

static size_t StaticHeight(node_t *node)
{
    size_t height = 0;

    if(NULL == node)
    {
        return 0;
    }
    height = 1 + MAX(StaticHeight(node->child[RIGHT]), StaticHeight(node->child[LEFT]));
    return height;
}


static node_t * StaticInsert(node_t *node ,void * data , compare_t compare , node_t *new_node)
{
    node_t * found_node = NULL ;
    
    child_t side =  (compare(node->data,data) > 0);   

    if(NULL == node->child[side] )
    {
        found_node->child[side] = new_node;
        return;
    }

    found_node = StaticInsert(node->child[side],data ,compare, new_node);

    node->height = (1 + GetMaxHieght(node));
    
    return;
}

static status_t StaticForEachInOrder(node_t *node, action_t action_func , void * params)
{
    status_t status = SUCCESS;

    status = StaticForEachInOrder(node->child[LEFT],action_func, params);
    if (status != SUCCESS)
    {
        return status;
    }

    status = action_func(node, params);
    if (status != SUCCESS)
    {
        return status;
    }

    status = StaticForEachInOrder(node->child[RIGHT],action_func, params);
    if (status != SUCCESS)
    {
        return status;
    }

    return status;
}

/*
static status_t StaticForEach(status_t *for_each_t[3])
{
    int i = 0; 

    for(i = 0 ; i < 3 ; i++)
    {

    }
    return status;
}
*/


static status_t StaticForEachPreOrder(node_t *node, action_t action_func , void * params)
{
    status_t status = SUCCESS;
    
    status = action_func(node, params);
    if (status != SUCCESS)
    {
        return status;
    }
    
    status = StaticForEachInOrder(node->child[LEFT],action_func , params);
    if (status != SUCCESS)
    {
        return status;
    }
    
    status = StaticForEachInOrder(node->child[RIGHT],action_func, params);
    if (status != SUCCESS)
    {
        return status;
    }

    return status;
}


static status_t StaticForEachPostOrder(node_t *node, action_t action_func , void * params)
{
    status_t status = SUCCESS;
    
    status = StaticForEachInOrder(node->child[LEFT],action_func, params);
    if (status != SUCCESS)
    {
        return status;
    }
    
    status = StaticForEachInOrder(node->child[RIGHT],action_func, params);
    if (status != SUCCESS)
    {
        return status;
    }

    status = action_func(node, params);
    if (status != SUCCESS)
    {
        return status;
    }
    
    return status;
}


static size_t GetMaxHieght(node_t * node)
{
    size_t left_height = 0;
    size_t right_height = 0;

    if (node->child[RIGHT] != NULL)
    {
        right_height = node->child[RIGHT]->height;
    }
    if (node->child[LEFT] != NULL)
    {
        left_height = node->child[LEFT]->height;
    }
    return MAX(right_height, left_height);
}



static node_t * GetNextForRemove(node_t *node , node_t *parent)
{
    node_t * next = NULL;
    if (NULL == node->child[LEFT])
    {
        return node; 
    }
    next = GetNext(node->child[LEFT]);
    
    return next;
}


static node_t * DeepDive(node_t *node , child_t side)
{
    node_t * last = NULL;
    if (NULL == last->child[side])
    {
        return node; 
    }
    last = GetNext(node->child[LEFT]);
    
    return next;
}




static size_t HasBothChildren(node_t * node)
{
    assert(NULL != node);
    if (NULL == node->child[LEFT] || NULL == node->child[RIGHT] )
    {
        return FALSE; 
    }

    return SUCCESS;
}

