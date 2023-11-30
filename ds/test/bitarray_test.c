/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Artur
*	Date:      
******************************************************************************/
#include <stdio.h>  /* printf()  	  */
#include <string.h> /*  strcpy()	  */

#include "bitarray.h"


#define ON 1
#define OFF 0
#define BIT_ARRAY_SIZE 64
#define ONE_SIZE_T (size_t)1



static void TestHelper(int booll , char * calling_function,int test_no);
void TestBitArrayMirror();
void TestBitArrayGetSetFlip();
void TestBitArrayCountOnOff();
void TestBitArrayRotateLeftRight();
void TestBitArrayCountOnLUT();
void TestBitArrayMirrorLUT();

int main()
{
	TestBitArrayMirrorLUT();
	TestBitArrayCountOnLUT();	
	
	TestBitArrayRotateLeftRight();
	TestBitArrayCountOnOff();
	
	TestBitArrayMirror();
	
	TestBitArrayGetSetFlip();
	
	return 0;
}


void TestBitArrayMirror()
{
	size_t test = 1; 
	size_t expected = ONE_SIZE_T << 63; 
	
	test = BitArrayMirror(test);
	TestHelper((test == expected), "TestBitArrayMirror   ", 1);
}


void TestBitArrayCountOnOff()
{
	int set_bit = 0;
	int expected = 2;
	bitarray_t test  = 5; 
	
	set_bit = BitArrayCountOn(test);
	TestHelper((set_bit == expected),"TestBitArrayCountOnOff",1);
	
}

void TestBitArraySet()
{
	size_t test = 0;
	size_t expected = 2; 
	
	test = BitArraySetBit(test, 1, ON);
	TestHelper((test == expected), "TestBitArraySet", 1);
	
	
}

void TestBitArrayFlip()
{
	size_t test = 0;
	size_t expected = 1; 

	test = BitArrayFlip(test, 1);
	TestHelper((test == expected), "TestBitArrayGet", 1);
}

void TestBitArrayGet()
{
	size_t test = 0;
	size_t expected = 2; 

	test = BitArrayGetVal(test, 1);
	TestHelper((test == expected), "TestBitArrayGet", 1);
}

void TestBitArrayRotateLeft()
{
	size_t test = 0x400;
	size_t expected = 0x2000;
	
	test = BitArrayRotateLeft(test, 2);
	TestHelper((test > expected), "TestBitArrayRotateLeftRight", 1);
	
}


void TestBitArrayRotateRight()
{
	size_t test = 0x400;
	size_t expected = 0x80;

	test = BitArrayRotateRight(test, 3);
	TestHelper((test < expected), "TestBitArrayRotateLeftRight", 1);
}


void TestBitArrayCountOnLUT()
{
	bitarray_t test = 8191;
	size_t expected = 13;
	
	TestHelper((BitArrayCountOnLUT(test) == expected), "TestBitArrayCountOnLUT", 1);
}


void TestBitArrayToString(void)
{
	char string[100] = {0};
	bitarray_t test = 1; 
	char * expected_string = "0000000000000000"
						 "0000000000000000"
						 "0000000000000000"
						 "0000000000000001"; 
	
	printf("\nTest BitArrayToString:\n");
	Test(0 == strcmp(expected_string, BitArrayToString(test, string)));
}
	
	
void TestBitArrayMirrorLUT()
{
	bitarray_t test = 1;
	size_t expected = 1 << 63;
	
	
	test = BitArrayMirrorLUT(test);
	TestHelper((test == expected), "TestBitArrayMirrorLUT", 1);
}

	
void TestBitArrayMirrorLUT()
{
	bitarray_t test = 1;
	size_t expected = 1 << 63;
	
	
	test = BitArrayMirrorLUT(test);
	TestHelper((test == expected), "TestBitArrayMirrorLUT", 1);
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

