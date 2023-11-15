/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#define ARRAYSIZE(x) (sizeof x/sizeof x[0])

int foo()
{
	


	return 0;
}

int main()
{
	int arr[6] = {3, 100, 115 ,100 ,400}
	int i = 0;
	int max = 0;
	int min = 10000;
	int buy = 0;
	int sell = 0; 
	int profit = 0;
	int max_profit = 0; 
	
	while(i<6)
	{
		buy = arr[i];
		sell = arr[i+1];
		profit = sell -buy
		min = min < buy ? min : buy;
		max = max > sell ? max: sell;
		max_profit = max_profit > profit ? max_profit : profit;  	
		printf()
	
	}
	
	
	return 0;
}

