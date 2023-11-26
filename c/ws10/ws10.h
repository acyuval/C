/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Artur
*	Date:      
******************************************************************************/

#ifndef __WS10_H__
#define __WS10_H__



/******************************************************************************
*	description: this function will set n bytes of memory with the value c,
*	arguments:  n - number of 'c' bytes to be copied to dest.
*	notes:		undefined beheivor- dest memory is less then n
******************************************************************************/ 
void * MemSet(void *dest, int c, size_t n);


/******************************************************************************
*	description: this function will copy n bytes of memory from src to dest,
*	arguments:  n - number of bytes from src to be copied to dest.
*	notes:		undefined beheivor- dest memory is less then n
******************************************************************************/ 
void * MemCpy(void *dest, const void * src, size_t n);

/******************************************************************************
*	description: this function will copy n bytes of memory from src to dest,
		      more secure for overlapping memery segments. 
*	arguments:  n - number of bytes from src to be copied to dest.
*	notes:		undefined beheivor- dest memory is less then n
******************************************************************************/ 
void * MemMove(void *dest, const void * src, size_t n);


#endif /*	WS10_H        	*/
