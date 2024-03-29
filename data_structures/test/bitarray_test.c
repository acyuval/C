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


static void TestHelper(int booll , char * calling_function,int test_no);
void TestBitArrayMirror();
void TestBitArrayGetSetFlip();
void TestBitArrayCountOn();
void TestBitArrayCountOff();
void TestBitArrayRotateLeft();
void TestBitArrayRotateRight();
void TestBitArrayFlip();
void TestBitArraySet();
void TestBitArrayGet();
void TestBitArrayCountOnLUT();
void TestBitArrayMirrorLUT();
void TestBitArrayToString(void);

int main()
{
	TestBitArrayMirrorLUT();
	TestBitArrayCountOnLUT();	
	TestBitArrayToString(); 
	TestBitArrayRotateRight();
	TestBitArrayRotateLeft();
	TestBitArrayFlip();
	TestBitArraySet();
	TestBitArrayGet();	
	TestBitArrayMirror();
	TestBitArrayCountOn();
	TestBitArrayCountOff();
	return 0;
}


void TestBitArrayMirror()
{
	bitarray_t test = 1; 
	bitarray_t expected = (bitarray_t)1 << 63; 
	
	test = BitArrayMirror(test);
	TestHelper((test == expected), "TestBitArrayMirror   ", 1);
}


void TestBitArrayCountOn()
{
	int set_bit = 0;
	int expected = 2;
	bitarray_t test  = 5; 
	
	set_bit = BitArrayCountOn(test);
	TestHelper((set_bit == expected),"TestBitArrayCountOn",1);
	
}

void TestBitArrayCountOff()
{
	bitarray_t test  = 2; 
	int expected = 63;
	int set_bit = 0;
	
	set_bit = BitArrayCountOff(test);
	TestHelper((set_bit == expected),"TestBitArrayCountOff",1);
	
}

void TestBitArraySet()
{
	bitarray_t test = 0;
	bitarray_t expected = 2; 
	
	test = BitArraySetBit(test, 1, ON);
	TestHelper((test == expected), "TestBitArraySet", 1);
	
	
}

void TestBitArrayFlip()
{
	bitarray_t test = 0;
	bitarray_t expected = 2; 
	
	test = BitArrayFlip(test, 1);
	
	TestHelper((test == expected), "TestBitArrayFlip", 1);
}

void TestBitArrayGet()
{
	bitarray_t test = 2;
	bitarray_t expected = 1; 
	
	test = BitArrayGetVal(test, 1);
	TestHelper((test == expected), "TestBitArrayGet", 1);
}

void TestBitArrayRotateLeft()
{
	bitarray_t test = 0x400;
	bitarray_t expected = 0x2000;
	
	test = BitArrayRotateLeft(test, 3);
	TestHelper((test == expected), "TestBitArrayRotateLeft", 1);
	
}


void TestBitArrayRotateRight()
{
	bitarray_t test = 0x400;
	bitarray_t expected = 0x80;

	test = BitArrayRotateRight(test, 3);
	TestHelper((test == expected), "TestBitArrayRotateRight", 1);
}


void TestBitArrayCountOnLUT()
{
	bitarray_t test = 8191;
	bitarray_t expected = 13;
	
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
						
						 	
	TestHelper(0 == strcmp(expected_string, BitArrayToString(test, string)), 
					"TestBitArrayToString" , 1);
}
	
	
void TestBitArrayMirrorLUT()
{
	bitarray_t test = 1;
	bitarray_t expected = 1;

	expected <<= 63;
	test = BitArrayMirrorLUT(test);
	TestHelper((test == expected), "TestBitArrayMirrorLUT", 1);
}



static void TestHelper(int booll , char * calling_function, int test_no)
{
	if(booll)
	{
		printf("%s -> \t\tNO.%d success!\n\n",calling_function, test_no);
	}
	else
	{
		printf("failed in %s, No. %d\n",calling_function ,test_no);
	}
}

