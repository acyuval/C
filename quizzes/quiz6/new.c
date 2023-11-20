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
	int i = 0;
	int *start_of_arrA = arrA;
	int *start_of_arrB = arrB; 
	int counter = 0;
	while(round_counter < (size*2))
	{
		while(i < size)
		{
			if(*arrA == *arrB)
			{
				arrB++;
				arrA++;
				counter++;
				if (counter == size)
				{
					printf("secsses");
					return 0;
				}
			}
			else
			{
				arrA = start_of_arrA;
				counter = 0;
				arrB++;
			}
			i++;
		}
		i = 0; 
		arrB= start_of_arrB;
		round_counter++;
	}
	return 1;
}

int main()
{
	int arrA[5] = {4, 5 , 6, 7 , 8};
	int arrB[5] = { 6, 4 ,8 , 4 , 5};
	int size = 5;
	printf("is it : %d",foo(arrA, arrB, size));
	
	return 0;
}

