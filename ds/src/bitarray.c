/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Artur
*	Date:      
******************************************************************************/

#include <stdio.h>  /* printf() , fopen()   */
#include <string.h> /* strcpy()				*/
#include <stdlib.h> /* malloc()				*/ 
#include <assert.h> 	
#include <limits.h> /* CHAR_BIT				*/

#include "bitarray.h"

#define ON 1
#define OFF 0
#define BIT_ARRAY_SIZE sizeof(bitarray_t)*CHAR_BIT
#define BYTE_RANGE 256
#define ONE_SIZE_T (bitarray_t)1
#define LAST_BYTE (sizeof(bitarray_t)-1)

static void strrev(char* str);
static unsigned char lut_mirror[BYTE_RANGE];	
static unsigned char lut_count[BYTE_RANGE];

bitarray_t BitArraySetAll(bitarray_t b_arr)
{
	(void)b_arr;
	return ~((bitarray_t)0);
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
	
	mask = (1 << (index));
	
	return bool_val ? (b_arr = b_arr | mask) : (b_arr = b_arr & (~mask)); 
}

int BitArrayGetVal(bitarray_t b_arr, size_t index)
{
	
	bitarray_t mask = 0;
	
	assert(index < BIT_ARRAY_SIZE);
	
	mask = 1 << (index);
	
	return (b_arr & mask) ? 1 : 0; 
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
	bitarray_t mask = 1;
	
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
	offset %= BIT_ARRAY_SIZE;

	return (b_arr >> offset | b_arr << (BIT_ARRAY_SIZE - offset));
}

bitarray_t BitArrayRotateLeft(bitarray_t b_arr, size_t offset)
{
	offset %= BIT_ARRAY_SIZE; 
		
	return (b_arr << offset | b_arr >> (BIT_ARRAY_SIZE - offset));
}



/* LUT table is a calculating Number of set-bits 
										 in any possible byte configurtaion */
static unsigned char * BuildLUTCountBits(unsigned char * LUT)
{
	size_t i = 0; 
	
	for(i = 0 ; i < BYTE_RANGE ; i++)
	{
		LUT[i] = (unsigned char)BitArrayCountOn(i);
	}
	
	return LUT;
}

static unsigned char ByteMiror(unsigned char n)
{
	unsigned char result = 0;
	int counter = 0; 

	while (CHAR_BIT > counter) 
	{
		result <<= 1;
		if (1 == (n & 1))
		{
			result |= 1;
 		}
		n >>= 1;
		counter++;
	}

	return result;
}

/* LUT table is a calculating fliipped values
										 of any possible byte configurtaion */
static unsigned char * BuildLUTMiror(unsigned char * LUT)
{
	int a_byte = 0; 

	while(a_byte < BYTE_RANGE)
	{
		LUT[a_byte] = ByteMiror(a_byte);
		a_byte++;
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
	
	if(!is_inited)   /* will be initialized only once during program lifetime */
	{
		BuildLUTCountBits(lut_count);
		is_inited = 1;
	}
	
	for(i = 0 ; i < (sizeof(bitarray_t)) ; i++)
	{
		this_byte_value = *(char_ptr+i);
		count_bits += lut_count[this_byte_value];
	}
	
	return count_bits;
}

bitarray_t BitArrayMirror(bitarray_t b_arr)
{
	bitarray_t mirror_b_Arr = 0;
	size_t counter = 0; 
	
	while (BIT_ARRAY_SIZE > counter) 
	{
		mirror_b_Arr <<= 1;
		if (b_arr & 1)
		{
			mirror_b_Arr |= 1;
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
		
	unsigned char * char_read = (unsigned char *)&b_arr; 
	unsigned char * char_write = (unsigned char *)&res; 
	
	if(!is_inited)/* will be initialized only once during program lifetime */
	{
		BuildLUTMiror(lut_mirror);
		is_inited = 1;
	}

	for(i = 0 ; i < (sizeof(b_arr)) ; i++)
	{
		this_byte_value = *(char_read + i);
		*(char_write + LAST_BYTE - i) = lut_mirror[this_byte_value];
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

