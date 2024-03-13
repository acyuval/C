/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#define ARRAYSIZE(x) (sizeof x/sizeof x[0])

void foo(int arr[], int sum, int size)
{
	int i = 0;
	int * low = &arr[0];
	int * max = &arr[size-1];
	
	while (i<size)
	{
		while ((*max+*low) < sum) 
		{
			low++;
			i++; 
		}
		if((*max+*low) == sum)
		{
			printf("\nmax:%d low:%d in itr: %d \n", *max, *low, i);
			return;
		}
		max--;
		i++;
	}
	printf("\nsum not found\n");
}


int main()
{
	int arr[] = {3 , 9 ,23 ,41 , 100, 300, 450, 650};
	int sum = 1100;
	foo(arr, sum, 8);
	return (0);
}

