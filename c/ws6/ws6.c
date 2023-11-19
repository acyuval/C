/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Igal
*	Date:      
******************************************************************************/
#include <stdio.h>	/*	printf()  				*/

#include "ws6.h"


union FloatUnion {
    float f;
    int i;
};


long pow2(unsigned int x, unsigned int y)
{
	unsigned int result = x * (2 << (y-1));
	return result;
}

unsigned int checkPower2Loop(unsigned int n)
{
	while(n != 1)
	{
		if((n % 2) != 0)
		{
			return 0;
		}	
		n=n/2;	
	}
	
	return 1;
	

}


unsigned int checkPower2BitWise(unsigned int n)
{
	unsigned int result = ((n != 0) && !(n & (n - 1)));
	return result;

}



unsigned int  addOne(int n)
{
	unsigned int  result = (-(~n));
	return result;

}


int checkArrayFor3Bits(unsigned int arr[],int size)
{
	int i = 0;
	int j = 0; 
	int bit_counter = 0;
	unsigned int this = 0;


	
	for(i=0; i < size; i++)
	{
		bit_counter = 0;
		this = arr[i];
		for(j = 0 ; j < 32 ; j++)
		{
 
			if ((this & 1) == 1)
			{
				bit_counter++;
			}
			this = this >> 1 ;			
		}
		
		if (bit_counter == 3)
		{
			printf("[%d]" , arr[i]);
		}
	}
	
	printf("\n");
	return 0;
}


unsigned int byteMirorBitWise(unsigned int num)
{
	num = ((num & 0x55555555) << 1) | ((num & 0xAAAAAAAA) >> 1); 
	num = ((num & 0x33333333) << 2) | ((num & 0xCCCCCCCC) >> 2); 
	num = ((num & 0x0F0F0F0F) << 4) | ((num & 0xF0F0F0F0) >> 4); 
	num = ((num & 0x00FF00FF) << 8) | ((num & 0xFF00FF00) >> 8); 
	num = ((num & 0x0000FFFF) << 16) | ((num & 0xFFFF0000) >> 16); 
	return num >> (32 - 8);
	
}


unsigned int byteMirorLoop(unsigned int n)
{
	unsigned int result = 0;
	while (n > 0) 
	{
		result <<= 1;
		if ((n & 1) == 1)
		{
			result ^= 1;
 		}
	
	n >>= 1;
	}

	return result;
}

int check2and6BitsAnd(unsigned char ch)
{
	/* in 32 only 6th bits is on in 2 only 2nd bit is on*/
	return ((ch & 34) == 34);
}


unsigned char check2and6BitsOr(unsigned char ch)
{
	/* in 34 only 6th and 2nd bits are on - 00100010 */
	return ((34 & ch));
} 


unsigned char Swap3and6Bits(unsigned char ch)
{
	/* 235 11101011 ,  20 00010100 */
	return ((235 & ch) ^ 20);
} 

unsigned int checkDevisionBy16(unsigned int num)
{
	while(num & 15)
	{
		num -= 1;
	}

	return (num);
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

	for(j = 0 ; j < 32 ; j++)
	{

		if ((number & 1) == 1)
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
	int j = 0; 
	union FloatUnion print_bits = {0};
	int binaryRepresentation = 0;
	print_bits.f = number; 
	binaryRepresentation = print_bits.i;
	
	for(j = 0 ; j < 32 ; j++) 
	{
  		printf("%d", (binaryRepresentation >> j) & 1);
	}
		
}

		



