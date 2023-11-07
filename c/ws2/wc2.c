#include <stdio.h>
#include <stdlib.h>

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

void SwapSizeTPtr (size_t *ptr1, size_t *ptr2)
{
	size_t temp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = temp;
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
	return cp_int_arr;
}

int CheckMemoryloc()
{
	static int s_i = 7;
	int i = 7;
	int *ptr = &i;
	int *ptr2 = (int *)malloc(sizeof(int));

	if(ptr)
	{
		int **ptr3 = &ptr;
		

		free(ptr2);

	printf("static int, 's_i' = %p\n", (void*)&s_i);
	printf("int, 'i' = %p\n", (void*)&i);
	printf("pointer to int, 'ptr'  = %p\n", (void*)ptr);
	printf("malloc pointer to int, 'ptr2' = %p\n", (void*)ptr2);
	printf("pointer to pointer of int, 'ptr3'  = %p\n", (void*)ptr3);
}
	return 0 ;
}

