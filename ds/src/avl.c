/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/

#include <assert.h> /* assert */
#include <stdlib.h>
#include <stdio.h>
#include "../include/avl.h"


#define MAX(a,b) ((b>a) ? b : a)

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


struct avl
{
	node_t *root;
	compare_t cmp_func;
};

struct node
{
	void *data;
	node_t *child[MAX_CHILDREN];
	size_t height;
};


/*
typedef status_t (*for_each_t)(status_t * for_each_t[3]);
*/
avl_t * AVLCreate(compare_t compare_func);
void AVLDestroy(avl_t *avl);
status_t AVLInsert(avl_t *avl, const void *data);
void AVLRemove(avl_t *avl, void *data);
void *AVLFind(const avl_t *avl, const void *to_find);
int AVLIsEmpty(const avl_t *avl);
size_t AVLSize(const avl_t *avl);
size_t AVLHeight(const avl_t *avl);
int AVLForEach(avl_t *avl, traversal_t mode, action_t act_func, void *params);
static void StaticDestroy(node_t  *node);
static node_t * StaticRemove(node_t *node, void *data, compare_t compare);
static void * StaticFind(node_t *node, void *to_find, compare_t compare);
static size_t StaticSize(node_t *node);
static size_t StaticHeight(node_t *node);
static node_t * StaticInsert(node_t *node, compare_t compare , node_t *new_node);
static status_t StaticForEachInOrder(node_t *node, action_t action_func , void * params);
static status_t StaticForEachPreOrder(node_t *node, action_t action_func , void * params);
static status_t StaticForEachPostOrder(node_t *node, action_t action_func , void * params);
static size_t SetMaxHeight(node_t * node);
static void * DeepDive(node_t *node , child_t side);
static void * GetNextData(node_t *node);
static size_t HasBothChildren(node_t * node);
static node_t * InitNode(void * data);
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
    StaticDestroy(avl->root);
    free(avl);
}

status_t AVLInsert(avl_t *avl, const void *data)
{
    node_t * new_node = NULL;
    assert(NULL != avl);
    assert(NULL != data);


    new_node = InitNode((void *)data);
    if(NULL == new_node)
    {
        return FAIL;
    }

    if (NULL == avl->root)
    {
        avl->root = new_node;
    }
    else
    {
        StaticInsert(avl->root,avl->cmp_func, new_node);
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

    StaticRemove(avl->root, data, avl->cmp_func);
}

void *AVLFind(const avl_t *avl, const void *to_find)
{
    StaticFind(avl->root, (void *)to_find, avl->cmp_func);
}

int AVLIsEmpty(const avl_t *avl)
{
    assert(NULL != avl);
    return ((NULL == avl->root)? 1 : 0 );
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
    node_t *found_child = NULL;
    void * data_to_replace = NULL;
    child_t side = (compare(node->data, data) < 0);

    if (compare(node->data, data) == 0)
    {
        return node;
    }
    else
    {
        found_node = StaticRemove(node->child[side], data, compare);
    }

    if(found_node != NULL && HasBothChildren(found_node) == TRUE)
    {
        data_to_replace = GetNextData(found_node);
        found_node->data = data_to_replace;
        StaticRemove(found_node->child[RIGHT], data_to_replace, compare);
    }
    else if(found_node != NULL && HasBothChildren(found_node) == FALSE)
    {
        found_child = (node_t *)((size_t)found_node->child[LEFT] ^ (size_t)found_node->child[RIGHT]);
        node->child[side] = found_child;
        free(found_node); 
    }

    SetMaxHeight(node);
    return NULL;
}

/*
static node_t * StaticRemoveWithOneChild(node_t *node, node_t * found)
{
    node_t *found_node = NULL;
    node_t *next_node = NULL;
    node_t *found_child = NULL;
    if (NULL == node->child[LEFT])
    {
        return node;
    }
    next_node = StaticRemoveWithOneChild(node->child[LEFT]);

    if (NULL != next_node)
    {

    }
    return NULL;
}

*/

static void * StaticFind(node_t *node, void *to_find, compare_t compare)
{
    node_t *found_node = NULL;
    child_t side = 0;
    if (NULL == node)
    {    
        return NULL;
    }
    else if(compare(node->data, to_find) == SUCCESS)
    {
        return node->data;
    }

    side = (compare(node->data, to_find) < 0);

    found_node = StaticFind(node->child[side],to_find,compare);
    
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


static node_t * StaticInsert(node_t *node, compare_t compare , node_t *new_node)
{    
    child_t side = (compare(node->data,new_node->data) < 0);   

    if(NULL == node->child[side])
    {
        
        node->child[side] = new_node;
    }
    else
    {
        node->child[side] = StaticInsert(node->child[side] ,compare, new_node);
    }

    SetMaxHeight(node);   
    return node;
}

static status_t StaticForEachInOrder(node_t *node, action_t action_func , void * params)
{
    status_t status = SUCCESS;
    if(NULL == node)
    {
        return status;
    }

    status = StaticForEachInOrder(node->child[LEFT],action_func, params);
    if (status != SUCCESS)
    {
        return status;
    }

    status = action_func(node->data, params);
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
    if(NULL == node)
    {
        return status;
    }
    status = action_func(node->data, params);
    if (status != SUCCESS)
    {
        return status;
    }
    
    status = StaticForEachPreOrder(node->child[LEFT],action_func , params);
    if (status != SUCCESS)
    {
        return status;
    }
    
    status = StaticForEachPreOrder(node->child[RIGHT],action_func, params);
    if (status != SUCCESS)
    {
        return status;
    }

    return status;
}


static status_t StaticForEachPostOrder(node_t *node, action_t action_func , void * params)
{
    status_t status = SUCCESS;
    if(NULL == node)
    {
        return status;
    }
    status = StaticForEachPostOrder(node->child[LEFT],action_func, params);
    if (status != SUCCESS)
    {
        return status;
    }
    
    status = StaticForEachPostOrder(node->child[RIGHT],action_func, params);
    if (status != SUCCESS)
    {
        return status;
    }

    status = action_func(node->data, params);
    if (status != SUCCESS)
    {
        return status;
    }
    
    return status;
}


static size_t SetMaxHeight(node_t * node)
{
    size_t left_height = 0;
    size_t right_height = 0;

    if (NULL == node)
    {
        return 0;
    }
    if (node->child[RIGHT] != NULL)
    {
        right_height = node->child[RIGHT]->height;
    }
    if (node->child[LEFT] != NULL)
    {
        left_height = node->child[LEFT]->height;
    }
    node->height = 1 + MAX(right_height, left_height);
    return node->height;
}



static void * GetNextData(node_t *node)
{
    void * data_to_replace = NULL;
    data_to_replace = DeepDive(node->child[RIGHT], LEFT);
    return data_to_replace;
}


static void * DeepDive(node_t *node , child_t side)
{
    if (NULL == node->child[side])
    {
        return node->data; 
    }
    return DeepDive(node->child[side], side);
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

static node_t * InitNode(void * data)
{
    node_t * new_node = NULL; 

    new_node = (node_t *)malloc(sizeof(node_t));
    
    if(NULL == new_node)
    {
        return NULL;
    }
    
    new_node->data = (void *)data;
    new_node->height = 1;
    new_node->child[RIGHT] = NULL;
    new_node->child[LEFT] = NULL;

    return new_node;
}



