/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#define ARRAYSIZE(x) (sizeof x/sizeof x[0])

int main()
{
	int arr[6] = {300, 100, 115 ,500 ,1, 900};
	int size_of_arr = 6;
	int i = 0;
	int max = 0;
	int min = 10000;
	
	int sell = 0; 
	int profit = 0;
	int max_profit = 0; 
	int index_buy = 0;
	int index_sell = 0;
	
	min = arr[0];
	
	while(i<(size_of_arr-1))
	{
		
		sell = arr[i+1];
		
		profit = sell - min;
		
		if (min > sell)
		{ 
		 	 min = sell;
			 index_buy = i;
		}
		
		if (max_profit < profit)
		{ 
			 max_profit = profit;
			 index_sell = i;
		}
		
		i++;
	
	}
	printf("max profit is %d\n" , max_profit);
	
	return 0;
}

