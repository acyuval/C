#include <stdio.h>
#include <stdlib.h>
#include "wc2.h"


int TestSwapInt()
{
	int one = 4; 
	int two = 12; 
	printf("\nbefore:%d::::%d\n" , one , two);
	SwapInt(&one, &two);
	printf("\nafter:%d::::%d\n" , one , two);
	return 0;
}

int TestSwapSizeT()
{
	size_t one = 4; 
	size_t two = 12; 
	
	size_t *one_ptr = &one; 
	size_t *two_ptr = &two; 
	
	printf("\nbefore:%lu::::%lu\n" , one , two);
	SwapSizeT(&one, &two);
	printf("\nafter:%lu::::%lu\n" , one , two);
	printf("\nbefore:%lu::::%lu\n" ,*one_ptr, *two_ptr);
	SwapSizeT(one_ptr, two_ptr);
	printf("\nafter:%lu::::%lu\n" ,*one_ptr, *two_ptr);
	
	return 0;
}
int TestSwapSizeTPtr()
{
	size_t one = 4; 
	size_t two = 12; 
	
	size_t *one_ptr = &one; 
	size_t *two_ptr = &two; 
	
	printf("\nbefore:%lu::::%lu\n" ,*one_ptr, *two_ptr);
	SwapSizeT(one_ptr, two_ptr);
	printf("\nafter:%lu::::%lu\n" ,*one_ptr, *two_ptr);
	
	return 0;
}

int TestCopyIntArr()
{

	int arr[] = {5 , 6 ,7 ,9 ,10};
	int size_arr = sizeof(arr)/sizeof(int);
	int *cp_arr = CopyIntArr(5 , arr);	
	int i = 0;
	printf("array copy is: ");
	for(i=0;i<size_arr;i++)
	{
		
		printf("%d, " , *(cp_arr+i));
	}
	free(cp_arr);
	return (0);
}

int main()
{
	printf("\nswap int : \n");
	TestSwapInt();
	printf("\n----------------------------------------------");
	printf("\nswap Size_t : \n");
	TestSwapSizeT();
	printf("\n----------------------------------------------");
	printf("\nswap ptr Size_t : \n");
	TestSwapSizeTPtr();
	printf("\n----------------------------------------------");
	printf("\ntest copy arr : \n");
	TestCopyIntArr();
	printf("\n----------------------------------------------");
	printf("\nmemory map : \n");
	CheckMemoryloc();
	return 0;
}




