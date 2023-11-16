/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Igal
*	Date:      
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ws6.h"

#define ARRAYSIZE(x) (sizeof x/sizeof x[0])

void Testpow2()
{
	unsigned int x[5] = {2, 4 , 7, 8 , 16};
	unsigned int y[5] = {2, 1 , 6, 5 , 1};
	int i = 0;
	int size = 5;
	printf("\n----------------------\nTestpow2:\n");
	while (i<size)
	{ 
	
		if ((x[i]*pow(y[i], 2)) != pow2(x[i],y[i]))
		{
			break;
		}
		i++;
	}
	if (i != size)
	{
		printf("\n OK\n");
	}
	else
	{
		printf("\n failed\n");
	}
}
	
void TestcheckPower2Loop()
{
	unsigned int arr[5] = {2, 4 , 7, 8 , 16};
	unsigned int expected_results[5] = {1, 1 , 0, 1 , 1};
	int size = 5;
	int i = 0;
	printf("\n----------------------\nTestcheckPower2Loop:\n");
	while (i<size-1)
	{ 
	
		if (expected_results[i] != checkPower2Loop(arr[i]))
		{
			break;
		}
		i++;
	}
	if (i != size)
	{
		printf("\n OK\n");
	}
	else
	{
		printf("\n failed\n");
	}
}

void TestcheckPower2BitWise()
{
	unsigned int arr[5] = {2, 4 , 7, 8 , 16};
	unsigned int expected_results[5] = {1, 1 , 0, 1 , 1};
	int size = 5;
	int i = 0;
	printf("\n----------------------\nTestcheckPower2BitWise:\n");
	while (i<size)
	{ 
	
		if (expected_results[i] != checkPower2BitWise(arr[i]))
		{
			break;
		}
		i++;
	}
	if (i != size-1)
	{
		printf("\n OK\n");
	}
	else
	{
		printf("\n failed\n");
	}
}

void TestaddOne()
{
	unsigned int arr[5] = {2, 4 , 7, 8 , 16};
	int size = 5;
	int i = 0;
	printf("\n----------------------\nTestaddOne:\n");
	while (i<size)
	{ 
	
		if ((arr[i]+1) != addOne(arr[i]))
		{
			break;
		}
		i++;
	}
	if (i != size-1)
	{
		printf("\n OK\n");
	}
	else
	{
		printf("\n failed\n");
	}

}


void TestcheckArrayFor3Bits()
{
	

	unsigned int arr[6] =  {7, 2, 6, 19, 7 , 14};
	int size = 6;
	printf("\n----------------------\nTestcheckArrayFor3Bits:\n");
	checkArrayFor3Bits(arr,size);
}

void TestbyteMiror()
{
	unsigned int arr[6] =  {7, 2, 6, 19, 7 , 14};
	int size = 6;
	int i = 0;
	printf("\n----------------------\nTestbyteMiror:\n");
	while (i<size)
	{ 
		if ((byteMirorLoop(arr[i])) != byteMirorBitWise(arr[i]))
		{
			break;
		}
		i++;
	}
	if (i != size-1)
	{
		printf("\n OK\n");
	}
	else
	{
		printf("\n failed\n");
	}
	
}

void Testcheck2and6BitsAnd()
{

	unsigned char arr[6] =  {7, 2, 6, 8, 42 , 34};
	int expected_results[6] = {0, 0 , 0, 0 , 1, 1};
	int size = 6;
	int i = 0;
	printf("\n----------------------\nTestcheck2and6BitsAnd:\n");
	while (i<size)
	{ 
		if ((expected_results[i]) != check2and6BitsAnd(arr[i]))
		{
			break;
		}
		i++;
	}
	if (i != size-1)
	{
		printf("\n OK\n");
	}
	else
	{
		printf("\n failed\n");
	}
}


int main()
{
	/*
	TestcheckPower2BitWise();
	TestcheckPower2Loop();
	TestaddOne();
	Testpow2();
	TestcheckArrayFor3Bits();
	
	TestbyteMiror();
	*/
	Testcheck2and6BitsAnd();
	return 0;
}

