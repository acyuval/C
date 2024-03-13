/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#define MAX2(a,b) (a > b) ? a : b
char lut[256] = {0};

long * foo(int ints[], size_t no_of_ele)
{
	int i =0 ; 
	long sum = 0;
	int * int_ptr = NULL;
	
	while(i<no_of_ele)
	{
		sum = (long)ints[i] + ints[i+1];
		int_ptr = (int *)&sum;
		
		ints[i] = int_ptr[0];
        ints[i + 1] = int_ptr[1];
        i += 2;
	}
}



int main()
{
	int input[4] = {1222333444,1222333444,1222333444,1222333444};
	long * longs= (long *)input;
	int i = 0;
	foo(input, 4);
	
	for(i=0;i<2;i++)
	{
		printf("long: %ld " , longs[i]);
	}
	return 0;
}

