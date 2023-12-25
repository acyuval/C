/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/

#include <assert.h> /* assert			  */
#include <stdlib.h>
#include <stdio.h>


#include "vsa.h"

#define NO_SPACE (0)
#define TRUE (1)
#define FALSE (0)
#define SUCCESS (0)
#define FAIL (-1)
#define WORD_SIZE (sizeof(size_t))
#define VSA_SIZE (sizeof(vsa_t))
/******************************************************************************
*							 DECLRATION								  * 
******************************************************************************/
 
struct vsa 
{
    long block_size;
#ifndef NDEBUG
    long magic_number;
#endif
};
/******************************************************************************
*							 FUNCTIONS 										  * 
******************************************************************************/



/****************************************************************************
 * Description: Initializes the variable size allocator with the given pool. 
 *
 * Params:  pool - Address of the allocated memory pool.
 *          pool_size - Total size of the allocated memory.
 *          
 * Return Value: Pointer to the allocator.
 *               If pool_size isn't large enogh returns NULL.
 * 
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 ****************************************************************************/
vsa_t *VSAInit(void *pool, size_t pool_size)
{
	
	vsa_t *vsa_start = NULL;
	vsa_t *vsa_end = NULL;
	char * char_ptr = (char *)pool_size;
	
	assert(NULL != pool);
	assert(0 != pool_size);
	
	if(pool_size < (2 * VSA_SIZE))
	{
		return NULL;
	}
	
	vsa_start = (vsa_t *)pool;
	char_ptr += (pool_size - VSA_SIZE);
	vsa_end = (vsa_t *)char_ptr;

	vsa_start->block_size = (pool_size - (2 * VSA_SIZE))
	vsa_end->block_size = 0;
	
	#ifndef NDEBUG
    vsa_start->magic_number = 770770770; 
    vsa_end->magic_number =  770770770;
	#endif
	
	return vsa_start;
	
}

/****************************************************************************
 * Description: Allocates a block of given size.
 *
 * Params:  vsa - The allocator returned by VSAInit.
 *          size_to_alloc - Size of the block in bytes.
 *
 * Return Value: Pointer to the start of the alocted block. If not enough memory 
 *               was available return NULL.
 * 
 * Notes: pool must be init by VSAInit, undefined behavior otherwise.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 ****************************************************************************/
void *VSAAlloc(vsa_t *vsa, size_t size_to_alloc)
{
	size_t block_available = 0;
	char * char_ptr = vsa;
	vsa_t * vsa_ptr = NULL;
	
	assert(vsa != NULL);
	assert(size_to_alloc != 0);

	block_available = vsa->block_available;

	while(block_available < size_to_alloc && block_available != 0)
	{
		char_ptr += block_available;
		vsa_ptr = (vsa_t *)char_ptr;
		block_available =  vsa_ptr->block_available;
	}
	

}

/****************************************************************************
 * Description: Deallocates the block pointed by to_free.
 *
 * Params: to_free - Address of the allocted block.
 *
 * Notes: to_free must be allocted by VSAAlloc, undefined behavior otherwise.
 * 
 * Time Complexity: O(1)
 * Space Complexity: O(1)
 ****************************************************************************/
void VSAFree(void *to_free)
{
	
	char * char_ptr = (char *)to_free;
	vsa_t * vsa_ptr = NULL;
	
	assert (NULL != to_free);
	
	char_ptr -= VSA_SIZE;
	
	vsa_ptr = (vsa_t *)char_ptr;
	
	assert(vsa_ptr->block_size < -1);
	
	vsa_ptr->block_size *= -1;
	
}

/****************************************************************************
 * Description: Calculate the size of the largest available block in the pool
 *
 * Params:  vsa - The allocator returned by VSAInit.
 *
 * Return Value: Size of the largest available block in the pool.
 * 
 * Notes: pool must be init by VSAInit, undefined behavior otherwise.
 * 
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 ****************************************************************************/
size_t VSALargestFreeSize(vsa_t *vsa);
/******************************************************************************
*							STATIC FUNCTIONS								  * 
******************************************************************************/


static size_t CalcAllingedBlock(size_t block_size)
{
	
	block_size > WORD_SIZE ?(block_size += WORD_SIZE - (block_size % WORD_SIZE))
													: (block_size = WORD_SIZE);
										
	
	return block_size;

}
