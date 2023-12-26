/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/

#include <assert.h> /* assert			  */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "vsa.h"

#define NO_SPACE (0)
#define TRUE (1)
#define FALSE (0)
#define SUCCESS (0)
#define FAIL (-1)
#define WORD_SIZE (sizeof(size_t))
#define VSA_SIZE (sizeof(struct vsa))
/******************************************************************************
*							 DECLRATION								  * 
******************************************************************************/
static const long magic_number = 0xBADCAFFE;
vsa_t * SructInit(char * vsa ,long block_size);
static size_t CalcAllingedBlock(size_t block_size);
static long CheckDefagram(char * char_pool_runner);
static long GetBlockSize(char * char_ptr);

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

vsa_t *VSAInit(void *pool, size_t pool_size)
{
	
	vsa_t *vsa_start = pool;
	char * char_ptr = (char *)pool;
	long real_available_size = 0;
	assert(NULL != pool);
	assert(0 != pool_size);
	
	if(pool_size < (2 * VSA_SIZE))
	{
		return NULL;
	}

	real_available_size =  ((long)pool_size - (2 * VSA_SIZE)) - (pool_size % WORD_SIZE);
	
	SructInit(pool, real_available_size);
	SructInit((char_ptr + (pool_size - VSA_SIZE)), 0);
	
	return vsa_start;
}

void *VSAAlloc(vsa_t *vsa, size_t size_to_alloc)
{
	char * char_ptr = (char *)vsa;
	long available_block = 0;
	
	assert(size_to_alloc != 0);
	assert(vsa != NULL);
	assert(magic_number == vsa->magic_number);
	
	size_to_alloc = CalcAllingedBlock(size_to_alloc);
	
	while (GetBlockSize(char_ptr))
	{
		available_block = GetBlockSize(char_ptr);
		vsa = (vsa_t *)char_ptr;
		if (available_block < 0)
		{
			char_ptr += labs(available_block) +VSA_SIZE;
			continue;
		}
		
		CheckDefagram(char_ptr);
		
		if((size_to_alloc + VSA_SIZE) < (size_t)available_block)
		{
			vsa->block_size = (size_to_alloc)*-1;
			SructInit(char_ptr + size_to_alloc + VSA_SIZE, available_block - size_to_alloc - VSA_SIZE);
			return (void *)(char_ptr + VSA_SIZE);
		}
		
		if((long)size_to_alloc <= available_block)
		{
			vsa->block_size *= -1;
			return (void *)(char_ptr + VSA_SIZE);
		}
		
	}

	return NULL;
}

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

size_t VSALargestFreeSize(vsa_t *vsa)
{
	long max_block = 0;
	long block_available = 0;
	char * char_ptr = NULL;
	
	assert(vsa != NULL);
	
	char_ptr = (char *)vsa;
	
	while(GetBlockSize(char_ptr) != 0)
	{
		block_available = GetBlockSize(char_ptr);
		
		if (block_available < 0)
		{
			char_ptr += labs(block_available) +VSA_SIZE;
			continue;
		}
		
		CheckDefagram(char_ptr);
		block_available = GetBlockSize(char_ptr);
		(max_block < block_available) ? (max_block = block_available) : (0) ;
		char_ptr += block_available +VSA_SIZE;
	}
	
	if (0 == max_block)
	{
		return 0;
	}
	
	return (max_block);
}

static long CheckDefagram(char * char_pool_runner)
{
	vsa_t * vsa_ptr = NULL;

	long block_size = GetBlockSize(char_pool_runner);
	char * next_block =  char_pool_runner + block_size + VSA_SIZE; 	
	
	if(block_size <= 0)
	{
		return block_size;
	}
	
	while(GetBlockSize(next_block) > 0)
	{
		vsa_ptr = ((vsa_t *)char_pool_runner);
		vsa_ptr->block_size += (GetBlockSize(next_block) + VSA_SIZE);
		next_block = char_pool_runner + vsa_ptr->block_size + VSA_SIZE;
	}
	
	return 1;
}

static size_t CalcAllingedBlock(size_t block_size)
{
	return ((((block_size - 1) / WORD_SIZE) + 1) * WORD_SIZE) ;
}

static long GetBlockSize(char * char_ptr)
{
	return ((vsa_t *)char_ptr)->block_size ;
}


vsa_t * SructInit(char * vsa_char ,long block_size)
{
	vsa_t * vsa = (vsa_t *)vsa_char;
	vsa->block_size  = block_size;
	
	#ifndef NDEBUG
    vsa->magic_number = magic_number; 
	#endif									
	
	return vsa;

}
