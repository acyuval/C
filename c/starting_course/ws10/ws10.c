/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Artur
*	Date:      
******************************************************************************/

#include <stdio.h>	/* size_t 		       */  

#include "ws10.h"
#define WORD_SIZE sizeof(size_t)

static void cpyByteByteC(char *str, int c)
{
	*(str) = (char)c;
}

static void cpyByteByteDest(char *dest, char * src)
{
	*(dest) = *(src);
}

static void cpyWordChunkC(void *str, size_t * word)
{

	size_t *str_size_t = (size_t *)str; 
	*str_size_t = *word;
}

static void cpyWordChunkDest(size_t *dest, size_t * src)
{

	*dest = *src;
}

void * MemMove(void *dest, const void * src, size_t n)
{
	
	int offset = ((long)((char *)src+n))%WORD_SIZE;
	char *dest_char_ptr = (char *)dest + n;
	char *src_char_ptr = (char *)src + n;
	
	if(dest < src)
	{
		MemCpy(dest, src , n);
	}
	
	if(dest > src)
	{

		while(offset) /* this section will cpy the offset cells */
		{
			
			cpyByteByteDest(dest_char_ptr, src_char_ptr);
			dest_char_ptr--; 
			src_char_ptr--;
			n--;
			offset--;  
		}
		
		while(n >= WORD_SIZE) /* this section will cpy as word chunks */
		{
			
			cpyWordChunkDest((size_t *)dest_char_ptr,(size_t *)src_char_ptr);
			dest_char_ptr -= WORD_SIZE;
			src_char_ptr -= WORD_SIZE;
			n -= WORD_SIZE;
			
		}
		while(n) /* this section will cpy the remains bytes */
		{
			cpyByteByteDest(dest_char_ptr,src_char_ptr);
			dest_char_ptr--;
			src_char_ptr--;
			n--;
		}
	}
	return dest;
		
}




void * MemCpy(void *dest, const void * src, size_t n)
{
	
	int offset = ((long)(src)) % WORD_SIZE;
	char *dest_char_ptr = (char *)dest;
	char *src_char_ptr = (char *)src;
	
	while(offset)
	{
		
		cpyByteByteDest(dest_char_ptr, src_char_ptr);
		dest_char_ptr++; 
		src_char_ptr++;
		n--;
		offset--;  
	}
	
	while(n >= WORD_SIZE)
	{
		
		cpyWordChunkDest((size_t *)dest_char_ptr,(size_t *)src_char_ptr);
		dest_char_ptr += WORD_SIZE;
		src_char_ptr += WORD_SIZE;
		n -= WORD_SIZE;
		
	}

	while(n)
	{
		cpyByteByteDest(dest_char_ptr,src_char_ptr);
		dest_char_ptr++;
		src_char_ptr++;
		n--;
	}

	return dest;
}




void * MemSet(void *dest, int c, size_t n)
{

	char * dest_char = dest;
	char word[WORD_SIZE] = {0};
	size_t i= 0 ;
	int offset = ((long)(void *)(&c))%WORD_SIZE;
	
	for(i=0 ; i < WORD_SIZE ; i++)
	{
		word[i] = c; 
	}  
		
	
	while(offset)
	{
		cpyByteByteC(dest_char,c);
		dest_char++; 
		n--;
		offset--;  
	}
	
	while(n > WORD_SIZE)
	{
		
		cpyWordChunkC(dest_char,(size_t *)word);
		dest_char += WORD_SIZE;
		n -= WORD_SIZE;
	}

	while(n)
	{
		cpyByteByteC(dest_char,c);
		dest_char++;
		n--;
	}
	
	return (void *)dest;
}


