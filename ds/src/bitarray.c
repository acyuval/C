/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Artur
*	Date:      
******************************************************************************/

#include <stdio.h>  /* printf() , fopen()  */
#include <string.h> /* strcpy(),	  */
#include <stdlib.h> /* malloc()			*/ 
#include <assert.h> 


#include "bitarray.h"

#define ON 1
#define OFF 0
#define BIT_ARRAY_SIZE 64
#define BYTE_RANGE 256
#define ONE_SIZE_T (size_t)1

static void strrev(char* str);
static unsigned char LUT_m[BYTE_RANGE];	
static unsigned char LUT_c[BYTE_RANGE];

bitarray_t BitArraySetAll(bitarray_t b_arr)
{
	(void)b_arr;
	return ~(0);
}

bitarray_t BitArrayResetAll(bitarray_t b_arr)
{
	(void)b_arr;
	return 0;
}

bitarray_t BitArraySetBit(bitarray_t b_arr, size_t index, int bool_val)
{
	bitarray_t mask = 0 ;
	
	assert(index < BIT_ARRAY_SIZE);
	assert(bool_val == 1 || bool_val == 0);
	
	mask = (ONE_SIZE_T << (index));
	
	return bool_val ? (b_arr = b_arr | mask) : (b_arr = b_arr & (~mask)); 
}

int BitArrayGetVal(bitarray_t b_arr, size_t index)
{
	
	bitarray_t mask = 0;
	
	assert(index < BIT_ARRAY_SIZE);
	
	mask = ONE_SIZE_T << (index);
	
	return (b_arr = b_arr & mask) ? 1 : 0; 
}

bitarray_t BitArraySetOff(bitarray_t b_arr, size_t index)
{
	assert(index < BIT_ARRAY_SIZE);
	
	return BitArraySetBit(b_arr,index, OFF);
}

bitarray_t BitArraySetOn(bitarray_t b_arr, size_t index)
{
	assert(index < BIT_ARRAY_SIZE);
	
	return BitArraySetBit(b_arr,index, ON);
}

bitarray_t BitArrayFlip(bitarray_t b_arr, size_t index)
{
	assert(index < BIT_ARRAY_SIZE);
	
	return (BitArrayGetVal(b_arr, index)) ?
		 	BitArraySetOff(b_arr,index) :
		 	 BitArraySetOn(b_arr,index);
}

size_t BitArrayCountOn(bitarray_t b_arr)
{
	size_t counter = 0;
	
	while(b_arr)
	{
		b_arr =  b_arr & (b_arr - 1);
		counter++;
	}
	
	return counter;
}

size_t BitArrayCountOff(bitarray_t b_arr)
{
	return (BIT_ARRAY_SIZE - BitArrayCountOn(b_arr));
}


char *BitArrayToString(bitarray_t b_arr, char *buffer)
{
	size_t i = 0;
	size_t mask = 1;
	
	while(i < BIT_ARRAY_SIZE)
	{
		buffer[i] = (b_arr & mask) ? '1' : '0';	
		mask = mask << 1;
		i++;
	}
	
	buffer[i] = '\0';
	strrev(buffer);
	return buffer;
}


bitarray_t BitArrayRotateRight(bitarray_t b_arr, size_t offset)
{
	size_t i = 0 ;
	int temp = 0 ;
	
	for(i=0 ; i < offset ; i++)
	{
		temp = BitArrayGetVal(b_arr, 0);
		b_arr >>= ONE_SIZE_T;
		if(temp) 
		{
			b_arr = BitArraySetOn(b_arr, 63);
		}
	}
	
	return b_arr;
}

bitarray_t BitArrayRotateLeft(bitarray_t b_arr, size_t offset)
{
		size_t i = 0 ;
		
		for(i=0 ; i < offset ; i++)
		{
			int temp = BitArrayGetVal(b_arr, 63);
			b_arr <<= ONE_SIZE_T;
			if(temp) 
			{
				b_arr = BitArraySetOn(b_arr, 1);
			}
		}
		
		return b_arr;
}


/* LUT table is a calculating Number of set-bits 
										 in any possible byte configurtaion */
static unsigned char * BuildLUTCountBits(unsigned char * LUT)
{
	size_t i = 0; 
	
	for(i = 0 ; i < BYTE_RANGE ; i++)
	{
		LUT[i] = BitArrayCountOn(i);
	}
	
	return LUT;
}


/* LUT table is a calculating fliipped values
										 of any possible byte configurtaion */
static unsigned char * BuildLUTMiror(unsigned char * LUT)
{
	size_t i = 0; 
	bitarray_t temp = 0;
	unsigned char * char_ptr = (unsigned char *)&temp;
	
	for(i = 0 ; i < BYTE_RANGE ; i++)
	{
		temp = BitArrayMirror(i);
		LUT[i] = *(char_ptr + 7);
	}
	
	return LUT;
}

size_t BitArrayCountOnLUT(bitarray_t b_arr)
{
	size_t i = 0; 
	unsigned char this_byte_value = 0;	
	unsigned char * char_ptr = (unsigned char *)&b_arr; 
	size_t count_bits = 0;
	static int is_inited = 0;
	unsigned char * ptr_LUT = LUT_c;
	
	if(!is_inited)   /* will be initialized only once during program lifetime */
	{
		ptr_LUT = BuildLUTCountBits(ptr_LUT);
		is_inited = 1;
	}
	
	for(i = 0 ; i < (sizeof(bitarray_t)) ; i++)
	{
		this_byte_value = *(char_ptr+i);
		count_bits += LUT_c[this_byte_value];
	}
	return count_bits;
}

bitarray_t BitArrayMirror(bitarray_t b_arr)
{
	size_t mirror_b_Arr = 0;
	size_t counter = 0; 
	
	while (BIT_ARRAY_SIZE > counter) 
	{
		mirror_b_Arr <<= 1;
		if (b_arr & ONE_SIZE_T)
		{
			mirror_b_Arr ^= ONE_SIZE_T;
 		}
		b_arr >>= 1;
		counter++;
	}
	
	return mirror_b_Arr;
}

bitarray_t BitArrayMirrorLUT(bitarray_t b_arr)
{
	size_t i = 0; 
	size_t res = 0;
	static int is_inited =  0;
	unsigned char this_byte_value = 0;
	unsigned char * ptr_LUT = LUT_m;	
		
	unsigned char * char_read = (unsigned char *)&b_arr; 
	unsigned char * char_write = (unsigned char *)&res; 
	
	if(!is_inited)/* will be initialized only once during program lifetime */
	{
		ptr_LUT = BuildLUTMiror(ptr_LUT);
		is_inited = 1;
	}

	for(i = 0 ; i < (sizeof(b_arr)) ; i++)
	{
		this_byte_value = *(char_read + i);
		*(char_write + 7 - i) = LUT_m[this_byte_value];
	}
		
	return res;
}



static void strrev(char* str) 
{
    
	int i = 0;
	int j = strlen(str) - 1;
	
	if (!str)
	{
		return;
	}
	
	while (i < j)
	{
		char c = str[i];
		str[i] = str[j];
		str[j] = c;
		i++;
		j--;
	}
}

