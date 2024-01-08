/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/

#include <assert.h> /* assert */
#include <stdlib.h>

#include "../include/avl.h"
#include "../include/utiles.h"

#define MAX(a,b) (b>a) ? b : a ;

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
} avl_t;

struct node
{
	void *data;
	node_t *child[MAX_CHILDREN];
	size_t height;
}



/******************************************************************************
*							 FUNCTIONS 										  * 
******************************************************************************/



avl_t *AVLCreate(compare_t compare_func)
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

    retrun avl;

}

void AVLDestroy(avl_t *avl)
{
    assert(NULL != avl);
    destroyHandler(avl->root);
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
        avl->root = new_node

    }
    else
    {
        found_node = StaticInsert(avl->root ,(void *)data ,compare, &side);
    }
    


}


void AVLRemove(avl_t *avl, void *data)
{

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
    assert(NULL != action_t);

    switch (mode)
    {
    case PRE_ORDER:
        /* code */
        break;
    case IN_ORDER:
        /* code */
        break;
    case POST_ORDER:
        /* code */
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

    StaticDestroy(node->children[LEFT])
    StaticDestroy(node->children[RIGHT])
    free(node);
}

static node_t * StaticRemove(node_t *node, void *data, compare_t compare)
{
    node_t *found_node = NULL;

    if (compare(node->data, data) == SUCCESS)
    {
        return node;
    }
    
    
    found_node = StaticRemove(node->children[LEFT], data, compare)
    
    if (NULL == found_node)
    {
        found_node = StaticRemove(node->children[RIGHT], data, compare)       
    }
}


static void * StaticFind(node_t *node, void *to_find, compare_t compare)
{
    node_t *found_node = NULL;
    
    if (NULL == node || compare(node->data, to_find) == SUCCESS)
    {    
        return node;
    }

    found_node = StaticFind(node->children[LEFT],data,compare);
    
    if (NULL == found_node)
    {
        found_node = StaticFind(node->children[RIGHT],data,compare);       
    }
    
    return found_node; 
}   


static size_t StaticSize(node_t *node)
{
    if(NULL == node)
    {
        return 0;
    }
    
    return (1 + ((StaticSize(node->children[RIGHT])) + (StaticSize(node->children[LEFT]))))
}

static size_t StaticHeight(node_t *node)
{
    size_t height = 0;

    if(NULL == node)
    {
        return 0;
    }
    height = 1 + MAX(StaticHeight(node->children[RIGHT]), StaticHeight(node->children[LEFT]))
    return height;
}


static void StaticInsert(node_t *node ,void * data , compare_t compare , node_t new_node)
{
    node_t * found_spot = NULL ;
    

    if (compare(node->data,data) > 0)
    {
        if(NULL == node->children[LEFT] )
        {
            found_node->children[LEFT] = new_node;
            return;
        }
        found_spot =StaticInsert(node->children[LEFT],data ,compare)
    }
    else if(compare(node->data,data) < 0)
    {
        if(NULL == node->children[RIGHT] )
        {
            found_node->children[Right] = new_node;
            return;
        }
        found_spot = StaticInsert(node->children[RIGHT] ,data ,compare)
    }
    node->height = (1 + MAX(node->children[right]->height, node->children[Left]->height));
    return;
}


static size_t StaticForEachInOrder(node_t *node, action_t action_func , void * params)
{
    StaticForEachInOrder(node_t *node, action_t action_func)

    return ;
}

