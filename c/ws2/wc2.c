/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Dvir
*	Date:      7/12/23     
******************************************************************************/

#include <stdio.h> /* printf() */
#include <stdlib.h> /* malloc(), free() */
#include "wc2.h"

void SwapInt (int *ptr1, int *ptr2)
{
	int temp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = temp;
}


void SwapSizeT (size_t *ptr1, size_t *ptr2)
{
	size_t temp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = temp;
}

void SwapSizeTPtr (size_t **ptr1, size_t **ptr2)
{
	size_t *temp_address = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = temp_address;
}


void SwapPtrWithSwapSize_T (size_t **ptr1, size_t **ptr2)
{
    SwapSizeT((size_t *)ptr1, (size_t *)ptr2);
}

int *CopyIntArr(int size_of_arr, int *source_int_arr)
{
	int  *cp_int_arr = malloc(size_of_arr * sizeof(int));
	int i = 0 ; 
	
	
	do
	{
		*(cp_int_arr+i) = *(source_int_arr+i); 
		i++;	
	}
	while(i != size_of_arr);
	return (cp_int_arr);
}

