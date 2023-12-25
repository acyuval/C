#ifndef __FSA_H__
#define __FSA_H__

#include <stddef.h>

typedef struct fsa fsa_t;



/*******************************************************************************
*Description: Suggest a total byte size for a pool.
* 
*Parameters:    num_of_blocks-  total blocks in the pool.
* 				block_size-     size of a single block.
* 
*Return Value: 	The minimal amount of bytes that suffices for the 
* 				fixed size allocator pool.
*
*Time Complexity: O(1)
*Space Complexity: O(1)
*******************************************************************************/
size_t FSASuggestSize(size_t num_of_blocks, size_t block_size);

/*******************************************************************************
*Description: Initializes the fixed size allocator struct in the pool.
*
*Parameters:	pool- 		address to an allocated memory.
* 				block_size- size of a single block.
* 				pool_size- 	total byte size of the pool.
* 
*Return Value: Pointer to the fixed size allocator.
* 
*Time Complexity: O(n)
*Space Complexity: O(1)
* 
*Notes: if pool_size isn't sufficient undefined behavior, use FSASuggestSize.
*******************************************************************************/
fsa_t *FSAInit(void *pool, size_t block_size, size_t pool_size);

/*******************************************************************************
*Description: Allocates a single block of size that was given in SFAInit.
* 
*Parameters:    fsa-        Pointer to a fixed size allocator.
* 
*Return Value: Pointer to the first address of available block_size bytes.
* 
*Time Complexity: O(1)
*Space Complexity: O(1)
* 
*Notes: Returns NULL if no blocks are available.
*******************************************************************************/
void *FSAAlloc(fsa_t *fsa);

/*******************************************************************************
*Description: Deallocates the block pointed to by to_free.
* 
*Parameters:	fsa-        Pointer to a fixed size allocator.
*				to_free-    pointer to a allocated block.
* 
*Time Complexity: O(1)
*Space Complexity: O(1)
* 
*Notes: if to_free wasnt allocated by FSAAlloc, undefined behavior.
*******************************************************************************/
void FSAFree(fsa_t *fsa, void *to_free);

/*******************************************************************************
*Description: Counts the available blocks in the fixed size allocator pool.
* 
*Parameters:	fsa- Pointer to a fixed size allocator.
* 
*Return Value: The amount of blocks that are available in the pool.
* 
*Time Complexity: O(n)
*Space Complexity: O(1)
*******************************************************************************/
size_t FSACountFree(fsa_t *fsa);


#endif /*__FSA_H__*/
