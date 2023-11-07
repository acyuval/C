#include <stdio.h>
#include <stdlib.h>
#include "wc2.h"


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




