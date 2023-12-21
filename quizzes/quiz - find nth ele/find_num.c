/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Artur
*	Date:      
******************************************************************************/
#include <stdio.h>  /* printf()  	  */


int foo(int Arr[] , size_t size, int num)
{
	int res = 1;
	int i = 0;
	
	while(i < size)
	{
		res = res * (Arr[i] - num);
		i++;	
	}
	
	if (res == 0 )
	{
		printf("num is found ");
	}
	else
	{
		printf("num is not found ");
	}
}


int main()
{
	int arr[10] = {23,-55,56,-22,13,4,2,1 , 7,2 };
	int num = -51;
	
	foo(arr, 10, num);
	
	return 0; 
}

static void TestHelper(int booll , char * calling_function, int test_no)
{
	if(booll)
	{
		printf("%s -> \t\tNO.%d sucsess!\n\n",calling_function, test_no);
	}
	else
	{
		printf("failed in %s, No. %d\n",calling_function ,test_no);
	}
}

