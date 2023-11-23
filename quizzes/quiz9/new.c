/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#define ARRAYSIZE(x) (sizeof x/sizeof x[0])

int foo(int * arr ,int size)
{
	int sum = 0; 
	int high = 0;
	int i = 0;
	int start_i = 0 ;
	int max_sum= 0;
	while(i<size)
	{
		high = arr[i];
		sum = sum+high;
		
		if(sum<high)
		{
			start_i  = i;
			sum = high;
		}
		i++;
		max_sum = max_sum < sum ? sum : max_sum ;
	}
	printf("final sum is : %d start index is : %d", max_sum , start_i);
}

   


int main()
{
	int arrA[9] = {-2, 1 ,-3, 4, -1, 2,3,-5 , 4};
	int size = 9;
	foo(arrA,size);
	return 0;
}

