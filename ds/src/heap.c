/******************************************************************************
 *	Author:    Yuval
 *	Reviewer :
 *	Date:
 ******************************************************************************/

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include <stdio.h>
#include <math.h>

#include "../include/heap.h"
#include "../include/dynamicV.h"


#define MAX(a, b) ((b > a) ? b : a)

#define FALSE (0)
#define TRUE (1)


/******************************************************************************
 *							 DECLRATION								  *
 ******************************************************************************/


struct heap
{
	vector_t *vector;
	compare_func_t compare_func;
};


static size_t FindIndex(heap_t *heap, void *data, is_match_func_t is_match, size_t nmemb);
static void HeapifyUp(heap_t *heap , size_t index);
void SwapData(void ** parent, void **child);
static void HeapifyDown(heap_t *heap , size_t index);

/******************************************************************************
 *							 FUNCTIONS 										  *
 ******************************************************************************/

heap_t *HeapCreate(compare_func_t compare_func)
{
    heap_t *heap = NULL;

    assert(NULL != compare_func);

    heap = (heap_t *)calloc(1, sizeof(heap_t));
    if (NULL == heap)
    {
        return NULL;
    }


    heap->compare_func = compare_func;
    heap->vector = VectorCreate(sizeof(size_t), 1);
    if (NULL == heap->vector)
    {
        free(heap);
        return NULL;
    }

    return heap;
}
void HeapDestroy(heap_t *heap)
{
    assert(NULL != heap);

    VectorDestroy(heap->vector);
    free(heap);
}


status_t HeapPush(heap_t *heap, const void *data)
{
    status_t status = 0;
    size_t size = 0; 

    assert(NULL != heap);
    status = VectorPushBack(heap->vector,&data);
    size = VectorSize(heap->vector);

    HeapifyUp(heap , size-1);

    return status;
}

void HeapPop(heap_t *heap)
{
    size_t last_index = 0;
    void **last = NULL;
    void **first = NULL;
    assert(NULL != heap);

    last = VectorGetAccess(heap->vector, VectorSize(heap->vector)-1);
    first = VectorGetAccess(heap->vector, 0);        
    *first = *last;
    
    VectorPopBack(heap->vector);
    
    HeapifyDown(heap, 0);
}

void HeapRemove(heap_t *heap, is_match_func_t is_match_func, void *pararms)
{
    size_t found_index = 0;
    size_t nmemb = 0;
    size_t *last = NULL;
    size_t *found = NULL;
    assert(heap != NULL);
    assert(is_match_func != NULL);

    nmemb = VectorSize(heap->vector);
    found_index = FindIndex(heap, pararms,is_match_func, nmemb);
    last = VectorGetAccess(heap->vector,nmemb-1);
    found = VectorGetAccess(heap->vector,found_index);

    *found = *last; 
    VectorPopBack(heap->vector);
}

void *HeapPeek(const heap_t *heap)
{
    assert(NULL != heap);

    return *(void **)VectorGetAccess(heap->vector, 0); 
}

size_t HeapSize(const heap_t *heap)
{
    assert(NULL != heap);

    return VectorSize(heap->vector);
}

int HeapIsEmpty(const heap_t *heap)
{
    assert(NULL != heap);
    return (VectorSize(heap->vector) == 0);
}

/******************************************************************************
 *							STATIC FUNCTIONS								  *
 ******************************************************************************/

static size_t FindIndex(heap_t *heap, void *data, is_match_func_t is_match, size_t nmemb)
{

    size_t runner = 0; 
    void **this = NULL;
    assert(NULL != heap);

    for(runner = 0 ; runner < nmemb ; ++runner)
    {
        this = VectorGetAccess(heap->vector, runner);

        if(is_match(*this, data) == TRUE)
        {
            return runner;
        }    
    }

    return FAIL;
}

static void HeapifyUp(heap_t *heap , size_t index)
{
    void **child = NULL;
    void **parent = NULL;
    size_t parent_index = 0 ; 
    assert(NULL != heap);
    
    if(index == 0)
    {
        return;
    }
    
    parent_index = (index-1)/2; 
    child = VectorGetAccess(heap->vector, index);
    parent = VectorGetAccess(heap->vector, parent_index);
    
    while(index > 0 && heap->compare_func(*parent, *child) < 0)
    {
        index = parent_index;
        SwapData(parent, child);

        if (index > 0)
        {
            parent_index = (index-1)/2; 
            child = VectorGetAccess(heap->vector, index);
            parent = VectorGetAccess(heap->vector, parent_index);
        }
    }
}


static void HeapifyDown(heap_t *heap , size_t index)
{
    void **child_left = NULL;
    void **child_right = NULL;
    void **choose_child = NULL;
    void **parent = NULL;

    size_t size = 0;
    size_t largest_index = 0;  

    assert(NULL != heap);

    size = VectorSize(heap->vector);

    while(index < size)
    {
        child_left = VectorGetAccess(heap->vector, index+1);
        child_right = VectorGetAccess(heap->vector, index+2);
        choose_child = VectorGetAccess(heap->vector, index);
        parent = VectorGetAccess(heap->vector, index);

        if ((index+1) < size && heap->compare_func(*child_left, *choose_child) > 0)
        {
            choose_child = VectorGetAccess(heap->vector, index+1);
            largest_index = index+1;
        }

        if((index+1)  < size && heap->compare_func(*child_right, *choose_child) > 0)
        {
            *choose_child =  VectorGetAccess(heap->vector, index+2);
            largest_index = index+2; 
        }
        if (index == largest_index)
        {
            return;
        }
        
        SwapData(choose_child, parent);
        index = largest_index;
    }
}


void SwapData(void ** parent, void **child)
{
    void * temp = 0;
    temp = *parent; 
    *parent = *child;
    *child = temp;
}