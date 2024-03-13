/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/
#include <stdio.h>  /* printf()  	  */

#include "Cbuffer.h"

#define test_buf_size (12)

/******************************************************************************
*							TYPE DEFS / MACROS 								  * 
******************************************************************************/



/******************************************************************************
*							FUNCTION DECLRATION								  * 
******************************************************************************/
void TestBuffer();
static void PrintBuffer(char * test_src);
static void TestHelper(int booll , char * calling_function, int test_no);
/******************************************************************************
*							MAIN											  * 
******************************************************************************/


int main()
{
	TestBuffer();
	return (0);
}




/******************************************************************************
*							TEST FUNCTIONS									  * 
******************************************************************************/

void TestBuffer()
{
	char test_src[20] = {0};
	int i = 0;
	
	buffer_t *buffer = BufferCreate(12);
	
	TestHelper(BufferIsEmpty(buffer) == 1 , "TestBufferIsEmpty", 1);
	
	BufferWrite("HELLO" , buffer , 5);
	
	BufferRead(test_src , buffer , 5);
	

	TestHelper(BufferSize(buffer) == 0 , "TestBufferSize", 2);
	TestHelper(BufferFreeSpace(buffer) == 12 , "TestBufferFreeSpace", 3);
	TestHelper(BufferIsEmpty(buffer) == 1 , "TestBufferIsEmpty", 4);
	PrintBuffer(test_src);
	
	BufferWrite("12345678" , buffer , 8);
	
	TestHelper(BufferSize(buffer) == 8 , "TestBufferSize", 5);
	TestHelper(BufferFreeSpace(buffer) == 4 , "TestBufferFreeSpace", 6);
	TestHelper(BufferIsEmpty(buffer) == 0 , "TestBufferIsEmpty", 7);
	BufferRead(test_src, buffer , 12);
	PrintBuffer(test_src);
	
	BufferWrite("12345678" , buffer , 8);
	BufferWrite("9abcdefg" , buffer , 8);
	TestHelper(BufferFreeSpace(buffer) == 0 , "TestBufferFreeSpace", 8);
	BufferRead(test_src, buffer , 12);
		
	PrintBuffer(test_src);
	
	BufferDestroy(buffer);
}


/******************************************************************************
*							STATIC FUNCTIONS								  * 
******************************************************************************/


static void PrintBuffer(char * test_src)
{
	int i = 0;
	printf("\nbuffer:");
	printf("\n----------------\n");
	for(i = 0 ; i < 12 ; i++)
	{
		printf("%c" , *(char *)(test_src+i));
	}
	printf("\n----------------\n");
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


