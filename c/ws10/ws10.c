/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Artur
*	Date:      
******************************************************************************/

#include <stdio.h>  	/* printf() , fopen()  */
#include <string.h> 	/* strcpy(),	  */

#include "ws10.h"
#define WORD_SIZE 8

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
	
	int offset = ((long)((char *)src+n))%8;
	char *dest_char_ptr = (char *)dest + n;
	char *src_char_ptr = (char *)src + n;
	
	printf("\noffset in MemMove : %d\n" , offset);	
	
	if(dest < src)
	{
		MemCpy(dest, src , n);
	}
	
	if(dest > src)
	{

		while(offset)
		{
			
			cpyByteByteDest(dest_char_ptr, src_char_ptr);
			dest_char_ptr--; 
			src_char_ptr--;
			n--;
			offset--;  
		}
		
		while(n > 8)
		{
			
			cpyWordChunkDest((size_t *)dest_char_ptr,(size_t *)src_char_ptr);
			dest_char_ptr -= 8;
			src_char_ptr -= 8;
			n -=8;
			
		}
		while(n)
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
	
	int offset = ((long)(src))%8;
	char *dest_char_ptr = (char *)dest;
	char *src_char_ptr = (char *)src;
	
	printf("\noffset in memcpy : %d\n" , offset);
	
	while(offset)
	{
		
		cpyByteByteDest(dest_char_ptr, src_char_ptr);
		dest_char_ptr++; 
		src_char_ptr++;
		n--;
		offset--;  
	}
	
	while(n > 8)
	{
		
		cpyWordChunkDest((size_t *)dest_char_ptr,(size_t *)src_char_ptr);
		dest_char_ptr += 8;
		src_char_ptr += 8;
		n -=8;
		
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
	int i= 0 ;
	int offset = ((long)(void *)(&c))%8;
	
	printf("\noffset in MemSet : %d\n" , offset);	
	
	while(offset)
	{
		cpyByteByteC(dest_char,c);
		dest_char++; 
		n--;
		offset--;  
	}
	
	while(n > 8)
	{
		for(i=0 ; i < WORD_SIZE ; i++)
		{
			word[i] = c; 
		}  
		
		cpyWordChunkC(dest_char,(size_t *)word);
		dest_char+=8;
		n -=8;
	}

	while(n)
	{
		cpyByteByteC(dest_char,c);
		dest_char++;
		n--;
	}
	
	return (void *)dest;
}


