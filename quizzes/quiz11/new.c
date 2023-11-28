/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#define ARRAYSIZE(x) (sizeof x/sizeof x[0])

void bursa(int arr[], int size, int res[])
{
	int i = 0; 
	int max_profit =0;
	int profit = 0; 
	int low = 1000;
	
	while(i<size)
	{
		if(low > arr[i])
		{
			res[0] = i;
			low = arr[i];
		}
		profit = arr[i] - low;
		
		if(max_profit< profit)
		{
			max_profit = profit;
			res[1] = i;
			res[2] = max_profit;
		}
		i++;
	}


}

int main()
{
	int arr[8] = {6,12,3,5,1,4,9,2};
	int res[3] = {0};
	int size = 8;
	
	bursa(arr,size,res);
	
	printf("\nlow: %d high: %d profitL %d\n", res[0],res[1],res[2]);

	return 0;
}

