/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Igal
*	Date:      
******************************************************************************/
#include <stdio.h>	/*	printf() ,scanf() , fopen(), fseek()..	*/
#include <stdlib.h>	/*	calloc()				*/ 
#include <string.h>	/*	strncmp() ,strcmp()			*/
#include "ws6.h"


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
	unsigned char cmp = 34; /* in 34 only 6th and 2nd bits are on */
	return ((cmp & ch)| cmp);
} 

