/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Artur
*	Date:      
******************************************************************************/

#include <stdio.h>  /* printf() , fopen()  */
#include <string.h> /* strcpy(),	  */

#include "ws10.h"
#define WORD_SIZE 8


void * MemSet(void *str, int c, size_t n)
{

	
	size_t *str_c = (size_t *)str;
	size_t i = 0;
	int *c_nibble_size = &c;
	size_t * c_word_size = (size_t *)c_nibble_size;
	if (n > 8)
	{
	*(c_nibble_size) = c;
	*(c_nibble_size + 1) = c; 
	}
	
	for(i=0 ; i < n ; i += 8)
	{
		printf("%ld ",i);
		*str_c = *(size_t *)c_word_size;
		str_c++; 
	}  

	return (void *)str;
}


