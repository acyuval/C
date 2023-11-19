/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#define ARRAYSIZE(x) (sizeof x/sizeof x[0])

int foo(int * arrA , int * arrB ,int size)
{
	int round_counter = 0; 
	int to_match = *arrB;
	int i = 0;
	int *start_of_arrA = arrA;
	int *start_of_arrB = arrB; 
	int counter = 0;
	while(counter<size)
	{
		while(i < size)
		{
			if(to_match == *arrB)
			{
				round_counter++; 
				i++;
				arrA++;
				arrB++;
			}
			else
			{
				counter = 0;
				arrB++;
			}
		}
		i = 0; 
		arrB= start_of_arrB;
		round_counter++;
		if(round_counter > (size*2))
		{
			return 0; 
		}
	
	
	}

	return 1;
}

int main()
{
	int arrA[] = {4, 5 , 6, 7 , 8 };
	int arrB[] = { 6, 7 ,8 , 4 , 5 };
	int size = 5;
	printf("is it : %d",foo(arrA, arrB, size));
	
	return 0;
}

