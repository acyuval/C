/******************************************************************************
*	Author:    Yuval 
*	Reviewer : igal
*	Date:      
******************************************************************************/

#include <assert.h> /* assert			  */
#include <stdlib.h>
#include "vsa.h"

#define MAGIC_NUMBER (0xBADCAFFE)
#define WORD_SIZE (sizeof(size_t))
#define VSA_SIZE (sizeof(struct vsa))
#define TRUE (1)
#define FALSE (0)
/******************************************************************************
*							 DECLRATION								  * 
******************************************************************************/
vsa_t * SructInit(char * vsa ,long block_size);
static size_t CalcAllingedBlock(size_t block_size);
static void CheckDefagram(char * char_pool_runner);
static long GetBlockSize(char * char_ptr);
char * FindAvailableSpot(char * char_ptr);
static int IsAvilableWithMeta(size_t size_to_alloc,long available_block);
static char * MakeAllocation(char * char_ptr, size_t size_to_alloc);
static char * GetNextBlock(char * char_ptr);
static int IsFreeBlock(char * char_ptr);
static long GetABSBlockSize(char * char_ptr);

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
	
	assert(0 == ((size_t)&pool % 8) );
	
	if(pool_size < (2 * VSA_SIZE))
	{
		return NULL;
	}

	real_available_size =  ((long)pool_size - (2 * VSA_SIZE)) - 
														(pool_size % WORD_SIZE);
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
	assert(MAGIC_NUMBER == vsa->magic_number);
	
	size_to_alloc = CalcAllingedBlock(size_to_alloc);
	
	while (GetBlockSize(char_ptr))
	{
		char_ptr = FindAvailableSpot(char_ptr);
		
		CheckDefagram(char_ptr);
		
		available_block = GetBlockSize(char_ptr);
		
		if(IsAvilableWithMeta(size_to_alloc, available_block))
		{
			return (void *)MakeAllocation(char_ptr,size_to_alloc);
		}
		
		if((long)size_to_alloc <= available_block)
		{
			vsa = (vsa_t *)char_ptr;
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
	
	if(NULL == to_free)
	{
		return;
	}
	
	char_ptr -= VSA_SIZE;
	vsa_ptr = (vsa_t *)char_ptr;
	assert(MAGIC_NUMBER == vsa_ptr->magic_number);
	assert(vsa_ptr->block_size < 0);
	vsa_ptr->block_size *= -1;
}

size_t VSALargestFreeSize(vsa_t *vsa)
{
	long max_block = 0;
	long block_available = 0;
	char * char_ptr = (char *)vsa;
	
	assert(MAGIC_NUMBER == vsa->magic_number);
	assert(vsa != NULL);
	
	
	while(GetBlockSize(char_ptr) != FALSE)
	{
		
		if (FALSE == IsFreeBlock(char_ptr))
		{
			char_ptr = GetNextBlock(char_ptr);
		}
		else 
		{
			CheckDefagram(char_ptr);
			block_available = GetABSBlockSize(char_ptr);
			(max_block < block_available) ? (max_block = block_available) : (0) ;
			char_ptr = GetNextBlock(char_ptr);
		}
	}
	
	return (max_block);
}

static void CheckDefagram(char * char_pool_runner)
{
	vsa_t * vsa_ptr = NULL;

	char * next_block =  GetNextBlock(char_pool_runner);
	
	while(IsFreeBlock(next_block))
	{
		vsa_ptr = ((vsa_t *)char_pool_runner);
		vsa_ptr->block_size += (GetBlockSize(next_block) + VSA_SIZE);
		next_block = GetNextBlock(char_pool_runner);
	}
	
	return;
}

static size_t CalcAllingedBlock(size_t block_size)
{
	return ((((block_size - 1) / WORD_SIZE) + 1) * WORD_SIZE) ;
}

char * FindAvailableSpot(char * char_ptr)
{
	long available_block = GetBlockSize(char_ptr);
	
	while(available_block < 0)
	{
		char_ptr += labs(available_block) +VSA_SIZE;
		available_block = GetBlockSize(char_ptr);
	}
	return char_ptr;

}

static int IsAvilableWithMeta(size_t size_to_alloc,long available_block)
{
	return (size_to_alloc + VSA_SIZE + WORD_SIZE) < (size_t)available_block;
}


static long GetBlockSize(char * char_ptr)
{
	return ((vsa_t *)char_ptr)->block_size ;
}

static char * MakeAllocation(char * char_ptr, size_t size_to_alloc)
{
	vsa_t * vsa = (vsa_t *)char_ptr;
	long available_block = GetBlockSize(char_ptr);
	
	vsa->block_size = (size_to_alloc)*-1;

	SructInit(char_ptr + size_to_alloc + VSA_SIZE,
								 available_block - size_to_alloc - VSA_SIZE);
	return (char_ptr + VSA_SIZE);
}

static char * GetNextBlock(char * char_ptr)
{
	long block_size = GetABSBlockSize(char_ptr);
	return (char_ptr + block_size + VSA_SIZE);
}

static long GetABSBlockSize(char * char_ptr)
{
	long block_size = GetBlockSize(char_ptr);
	return labs(block_size);
}


static int IsFreeBlock(char * char_ptr)
{
	long block_size = GetBlockSize(char_ptr);
	return (block_size > 0);
}

vsa_t * SructInit(char * vsa_char ,long block_size)
{
	vsa_t * vsa = (vsa_t *)vsa_char;
	vsa->block_size  = block_size;
	
#ifndef NDEBUG
    vsa->magic_number = MAGIC_NUMBER; 
#endif									
	
	return vsa;

}
