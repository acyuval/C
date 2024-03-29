/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Igal
*	Date:      
******************************************************************************/
#include <stdio.h>	/*	printf()  				*/

#include "ws6.h"


long Pow2(unsigned int x, unsigned int y)
{
	unsigned int result = (x << y);
	
	return result;
}

unsigned int CheckPower2Loop(unsigned int n)
{
	while(1 !=  n)
	{
		if(0 != (n % 2))
		{
			return 0;
		}	
		
		n=n/2;	
	}
	
	return 1;
}


unsigned int CheckPower2BitWise(unsigned int n)
{
	unsigned int result = ((n != 0) && !(n & (n - 1)));
	
	return result;
}



unsigned int AddOne(int n)
{
	int temp = 1;
	
	while (temp == (temp & n))
	{
		n = n ^ temp;
		temp = temp << 1;
	}

	n = n ^ temp;
	return n;
}


int CheckArrayFor3Bits(unsigned int arr[],int size)
{
	int i = 0;
	int j = 0; 
	int bit_counter = 0;
	unsigned int curr = 0;

	for(i=0; i < size; i++)
	{
		bit_counter = 0;
		curr = arr[i];
		for(j = 0 ; j < 32 ; j++)
		{
			if (1 == (curr & 1))
			{
				bit_counter++;
			}
			
			curr = curr >> 1 ;			
		}
		
		if (3 == bit_counter)
		{
			printf("[%d]" , arr[i]);
		}
	}
	
	printf("\n");
	return 0;
}


unsigned int ByteMirorBitWise(unsigned int num)
{
	num = ((num & 0x55555555) << 1) | ((num & 0xAAAAAAAA) >> 1); 
	num = ((num & 0x33333333) << 2) | ((num & 0xCCCCCCCC) >> 2); 
	num = ((num & 0x0F0F0F0F) << 4) | ((num & 0xF0F0F0F0) >> 4); 
	num = ((num & 0x00FF00FF) << 8) | ((num & 0xFF00FF00) >> 8); 
	num = ((num & 0x0000FFFF) << 16) | ((num & 0xFFFF0000) >> 16); 
	return num >> (32 - 8);
}


unsigned int ByteMirorLoop(unsigned int n)
{
	unsigned int result = 0;
	int counter = 0; 

	while (8 > counter) 
	{
		result <<= 1;
		if (1 == (n & 1))
		{
			result ^= 1;
 		}
		n >>= 1;
		counter++;
	}

	return result;
}

int Check2and6BitsAnd(unsigned char ch)
{
	/* in 32 only 6th bits is on in 2 only 2nd bit is on*/
	return ((ch & 34) == 34);
}


unsigned char Check2and6BitsOr(unsigned char ch)
{
	/* in 34 only 6th and 2nd bits are on - 00100010 */
	return ((34 & ch));
} 


unsigned char Swap3and5Bits(unsigned char ch)
{
	char bit_3_flag = (ch & 4);
	char bit_5_flag = (ch & 16);
	
	ch = ch + ((bit_3_flag == 4) - (bit_5_flag == 16)) * (12);
	return ch;
} 

unsigned int CheckDevisionBy16(unsigned int num)
{
	return ((num >> 4) << 4);
} 

unsigned int SwapTwoVarNoTemp(unsigned int A ,unsigned int B)
{
	A = A ^ B;
	B = A ^ B;
	A = A ^ B;
	return (A);
} 

int CountNumberOfSetBitsLoop(int number)
{
	int j = 0; 
	int bit_counter = 0;
	
	if (0 > number)
	{
		bit_counter++;
		number = number ^ -2147483648;  /* int min  -2147483648 */
	}
	
	for(j = 0 ; j < 32 ; j++)
	{
		if (1 == (number & 1))
		{
			bit_counter++;
		}
		number = number >> 1 ;			
	}

	return bit_counter;
}

int CountNumberOfSetBitsBitWise(int number)
{
	number = number - ((number >> 1) & 1431655765);
	number = (number & 858993459) + ((number >> 2) & 858993459);
	number = (number + (number >> 4)) & 252645135;
	number = number + (number >> 8);
	number = number + (number >> 16);
	number = number & 63;
	return number;
}



void PrintFloatToBinary(float number)
{
	int i = 0;
	float float_num = number;
	unsigned int *to_int = (unsigned int *)&float_num;
	int mask = 1 << 31 ;  /* 10000000.... */
	
	for(i = 0 ; i < 32 ; i++) 
	{
  		printf("%d", (*to_int & mask)? 1: 0);
  		*to_int = *to_int << 1;
	}
}

		



