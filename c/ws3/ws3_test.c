/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Dvir
*	Date:      
******************************************************************************/

#include <stdlib.h> 	/*	size_t	*/
#include <stdio.h>	/*	printf()	*/

#include "ws3.h"
extern const char **environ;
#define ARRAYSIZE(x) (sizeof x/sizeof x[0])

void TestGetArrOfPtrs(void);

int main()
{
	TestGetArrOfPtrs();
	ListOfDataTypes();
	PrintAllEnvp(environ);
	Jusephus(100);

	return (0);
}



void TestGetArrOfPtrs(void)
{
	int arr[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
	int expected_res[] = {6, 15, 24};
	int (*ptr_arr)[3] = arr;
	int result[3] = {0};
	size_t row_no = 3;
	size_t i = 0; 
	
	Sum2DArr(ptr_arr, result , row_no, row_no);
	
	for(i=0; i< row_no; i++)
	{
		if(result[i] != expected_res[i])
		{
			break; 
		}
	}
	
	if (i != row_no)
	{
		printf("Test failed in row number %lu" , i);
	}
	else
	{
		printf("Test Success!! \n");
	}
	
}


