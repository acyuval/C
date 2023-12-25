/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/

#include <assert.h> /* assert			  */
#include <stdio.h>

#include "fsa.h"

#define WORD_SIZE (sizeof(size_t))
/******************************************************************************
*							 DECLRATION								  * 
******************************************************************************/
struct fsa
{
	size_t next_available;
};

static size_t CalcAllingedBlock(size_t block_size);
/******************************************************************************
*							 FUNCTIONS 										  * 
******************************************************************************/



size_t FSASuggestSize(size_t num_of_blocks, size_t block_size)
{
	assert(num_of_blocks != 0);
	assert(block_size != 0);
	
	block_size = CalcAllingedBlock(block_size);
	return ((num_of_blocks*block_size) + WORD_SIZE);
}


fsa_t *FSAInit(void *pool, size_t block_size, size_t pool_size)
{
	
	char * pool_char_runner = (char *)pool;
	size_t block_counter = 0;
	size_t * size_t_ptr = 0;
	size_t alligned_block_size =  CalcAllingedBlock(block_size);
	
	assert(pool != NULL);
	assert(pool_size % WORD_SIZE == 0);
	
	while(pool_size != (((block_counter+1)*alligned_block_size) + WORD_SIZE))
	{
		size_t_ptr = (size_t *)(pool_char_runner + WORD_SIZE +
										 (block_counter * alligned_block_size));
		*size_t_ptr = ((block_counter+1) * alligned_block_size) + WORD_SIZE;
		block_counter++;
	}
	
	*(size_t *)(pool_char_runner +  WORD_SIZE + (block_counter * alligned_block_size)) = 0;
	
	*(size_t *)pool = WORD_SIZE;
	return (fsa_t *)pool;
}	


void *FSAAlloc(fsa_t *fsa)
{
	size_t next_available = 0;
	char * char_ptr = (char *)fsa;
	char * available = NULL;
	assert(fsa != NULL);
	
	next_available = fsa->next_available;
	
	if (0 == next_available)
	{
		return NULL;
	}
	
	available = char_ptr + next_available;
	
	fsa->next_available = *(size_t *)(available);
	
	
	return (void *)available;
}


void FSAFree(fsa_t *fsa, void *to_free)
{
	size_t new_free_offset = 0;
	
	assert(fsa != NULL);
	assert(to_free != NULL);
	
	new_free_offset = (char *)to_free - (char *)fsa;
	
	*(size_t *)to_free = fsa->next_available;

	fsa->next_available = new_free_offset;
}


size_t FSACountFree(fsa_t *fsa)
{
	size_t next_offset = 0;
	char * char_ptr = (char *)fsa;
	size_t counter = 1;

	assert(fsa != NULL);
	next_offset = fsa->next_available;
	
	if (0 == next_offset)
	{
		return 0;
	}
	
	while(0 != (*(size_t *)(char_ptr + next_offset)))
	{
		next_offset = *(size_t *)(char_ptr + next_offset);
		++counter;
	}
	
	return counter;
}
/******************************************************************************
*							STATIC FUNCTIONS								  * 
******************************************************************************/


static size_t CalcAllingedBlock(size_t block_size)
{
	
	return ((((block_size - 1) / WORD_SIZE) + 1) * WORD_SIZE) ;
}
