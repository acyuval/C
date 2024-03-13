/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#define ARRAYSIZE(x) (sizeof x/sizeof x[0])

int foo(unsigned char c)
{
	char mask = 3;
	int set_bits = 0;
	
	while(c > 0)
	{		
		if((c & mask) == 3)
		{
			set_bits++;
		}

		c >>= 2;
	}

	return set_bits;
}

 
int foo1(unsigned long lng)
{
	int bits_on = 0;
	printf("----------------------------------------------\n");
	if (lng == 0)
	{
		return(0);
	}
	
	while((lng = (lng & (lng-1))) > 0)
	{		
		bits_on++;
	}
	bits_on++;
	return bits_on;
}

   


int main()
{
	unsigned char c[5] = {5, 10 , 8 ,12, 219};
	long int l[5] = {0, 10 , 8 ,12, 523145};
 	int size = 5;
	int i = 0 ;
	for(i=0; i < size ; i++)
	{
		printf("number of set bit is : %d\n", foo(c[i]));
	}
	
	for(i=0; i < size ; i++)
	{
		printf("number of bits on is : %d\n", foo1(l[i]));
	}	
	return 0;
}

