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
	
		if ((x[i]*pow(2, y[i])) != pow2(x[i],y[i]))
		{
			break;
		}
		i++;
	}
	if (i == size)
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
	while (i<size)
	{ 
	
		if (expected_results[i] != checkPower2Loop(arr[i]))
		{
			break;
		}
		i++;
	}
	if (i == size)
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
	if (i == size)
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
	if (i == size)
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
	if (i == size)
	{
		
		printf("\n failed\n");
	}
	else
	{
		printf("\n OK\n");
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
	if (i == size)
	{
		printf("\n OK\n");
	}
	else
	{
		printf("\n failed\n");
		
	}
}



void TestSwap3and5Bits()
{

	unsigned char arr[4] =  { 19, 37, 132, 228};
	int expected_results[4] = {7, 49 , 144, 240};
	int size = 4;
	int i = 0;
	printf("\n----------------------\nTestSwap3and5Bits:\n");
	while (i<size)
	{ 
	
		if ((expected_results[i]) != Swap3and5Bits(arr[i]))
		{
			break;
		}
		i++;
	}
	if (i == size)
	{
		printf("\n OK\n");

	}
	else
	{
		printf("\n failed\n");
	}
}


void TestcheckDevisionBy16()
{

	unsigned int arr[6] =  { 19, 16, 48, 80, 85, 2450};
	int size = 6;
	int i = 0;	
	int this_result = 0;
	printf("\n----------------------\nTestcheckDevisionBy16:\n");
	while (i<size)
	{ 
		this_result = checkDevisionBy16(arr[i]);
		if ((this_result % 16) !=  0)
		{
			break;
		}
		i++;
	}
	if (i == size)
	{
		printf("\n OK\n");
	}
	else
	{
		printf("\n failed\n");
	}
}


void TestSwapTwoVarNoTemp()
{

	unsigned int A[6] =  { 19, 16, 48, 80, 85, 2450};
	unsigned int B[6] =  { 30, 15, 23, 49, 22, 1100};
	int size = 6;
	int i = 0;	
	unsigned int A_after_swap = 0;
	printf("\n----------------------\nTestSwapTwoVarNoTemp:\n");
	while (i<size)
	{ 
		A_after_swap = SwapTwoVarNoTemp(A[i], B[i]);
		if (A_after_swap !=  B[i])
		{
			break;
		}
		i++;
	}
	if (i == size)
	{
		printf("\n OK\n");
	}
	else
	{
		printf("\n failed\n");
	}
}


void TestCountNumberOfSetBitsLoop()
{
	int arr[6] =  { -19, 16, -250, 80, 85, 2450};
	int expected_results[6] = {30, 1 , 26, 2, 4, 5};
	int size = 6;
	int i = 0;	
	printf("\n----------------------\nTestCountNumberOfSetBitsLoop:\n");
	while (i<size)
	{ 
		
		if (expected_results[i] !=  CountNumberOfSetBitsLoop(arr[i]))
		{
			break;
		}
		i++;
	}

	if (i == size)
	{
		printf("\n OK\n");
	}

	else
	{
		printf("\n failed\n");
	}
}


void TestCountNumberOfSetBitsBitWise()
{

	unsigned int arr[6] =  { -19, 16, 48, 80, 85, 2450};
	int size = 6;
	int i = 0;	

	printf("\n----------------------\nTestCountNumberOfSetBitsBitWise:\n");
	while (i<size)
	{ 
		
		if (CountNumberOfSetBitsBitWise(arr[i]) !=  CountNumberOfSetBitsLoop(arr[i]))
		{
			break;
		}
		i++;
	}

	if (i == size)
	{
		printf("\n OK\n");
	}

	else
	{
		printf("\n failed\n");
	}
}

void TestPrintFloatToBinary()
{
	float arr[7] =  {1 ,19, 16, 48, 80.2, 85.78, 2.23};
	int size = 7;
	int i = 0;	

	printf("\n----------------------\nTestPrintFloatToBinary:\n");
	while (i<size)
	{ 
		printf("%f:\t", arr[i]);
		PrintFloatToBinary(arr[i]);
		printf("\n");
		i++;
	}
}


int main()
{
	TestcheckPower2BitWise();
	TestcheckPower2Loop();
	TestaddOne();
	Testpow2();
	TestcheckArrayFor3Bits();
	TestbyteMiror();
	Testcheck2and6BitsAnd();
	TestSwap3and5Bits();
	TestcheckDevisionBy16();
	TestSwapTwoVarNoTemp();
	TestCountNumberOfSetBitsLoop();
	TestCountNumberOfSetBitsBitWise();
	TestPrintFloatToBinary();
	
	
	return 0;
}

