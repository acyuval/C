/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/

#include <assert.h> /* assert			  */
#include <stdlib.h>
#include <stdio.h>


#include "fsa.h"

#define NO_SPACE (0)
#define TRUE (1)
#define FALSE (0)
#define SUCCESS (0)
#define FAIL (-1)
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
	size_t extra_space = 0; 
	assert(num_of_blocks != 0);
	assert(block_size != 0);
	
	block_size = CalcAllingedBlock(block_size);
	(block_size < WORD_SIZE) ? (extra_space = WORD_SIZE) : (extra_space = block_size); /* save more space to struct when block is smaller then struct */ 
	return ((num_of_blocks*block_size) + extra_space);
}


fsa_t *FSAInit(void *pool, size_t block_size, size_t pool_size)
{
	fsa_t * fsa = NULL; 
	char * pool_char_runner = pool;
	size_t block_counter = 0;
	size_t * size_t_ptr = 0;
	size_t alligned_block_size =  CalcAllingedBlock(block_size);
	assert(pool != NULL);
	
	while(pool_size != ((block_counter*alligned_block_size)+ WORD_SIZE))
	{
		size_t_ptr = (size_t *)(pool_char_runner + WORD_SIZE +
										 (block_counter * alligned_block_size));
		*size_t_ptr = ((block_counter+1) * alligned_block_size) + WORD_SIZE;
		block_counter++;
	}
	
	*(size_t *)(pool_char_runner +  WORD_SIZE + (block_counter * alligned_block_size)) = 0;
	
	fsa = (fsa_t *)pool;
	fsa->next_available = WORD_SIZE;
	
	return fsa;
	 
}	


void *FSAAlloc(fsa_t *fsa)
{
	size_t this_next_available = 0;
	char * char_ptr = (char *)fsa;
	
	assert(fsa != NULL);
	
	this_next_available = fsa->next_available;
	
	if (this_next_available == 0)
	{
		return NULL;
	}
	
	fsa->next_available = *(size_t *)(char_ptr + this_next_available);
	assert(((char *)fsa + this_next_available) != NULL);
	return (void *)(char_ptr + this_next_available);
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
	
	if (next_offset == 0)
	{
		return 0;
	}
	
	while((*(size_t *)(char_ptr + next_offset)) != 0)
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
	
	block_size > WORD_SIZE ?(block_size += WORD_SIZE - (block_size % WORD_SIZE))
													: (block_size = WORD_SIZE);
										
	
	return block_size;

}
