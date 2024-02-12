/******************************************************************************
*	Author:    Yuval 
*	Reviewer :
*	Date:      
******************************************************************************/

#include <stdlib.h> /* malloc() , free()  */
#include <assert.h> /* assert			  */
#include <stdio.h>

#define TRUE (1)
#define SUCCESS (0)
#define FAIL (-1)
/******************************************************************************
*							 DECLRATION								  * 
******************************************************************************/
void swap(int * a , int *b);
void sort(int * arr, size_t size);
/******************************************************************************
*							 FUNCTIONS 										  * 
******************************************************************************/
int main()
{
	int test[10] = {0 ,0 ,1 ,1 ,1 ,0, 1, 0, 1, 1};
	int runner = 0;
	sort(test, 10);

	for(runner = 0 ; runner < 10; ++runner)
	{
		printf("%d - " , test[runner]);

	}
}



void sort(int * arr, size_t size)
{
	int *replaced = arr + size;
	int *copy = arr;
	int counter = 0;
	while(arr != replaced)
	{
		if(*arr == 1)
		{
			while (*replaced == 1)
			{
				replaced--;
			}
			swap(arr, replaced);
			replaced--; 
		}
		arr++;
		counter++;
	}
}

void swap(int * a , int *b)
{
	int temp = *a; 
	*a = *b; 
	*b = temp; 
}