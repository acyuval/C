/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Artur
*	Date:      
******************************************************************************/
#include <stdio.h>  /* printf()  	  */
#include <string.h> /*  strcpy() , memset()  */
#include <stdlib.h> /* Exit		  */

#include "ws10.h"

#define NO_OF_TESTS 9

/* this global variable will represent the number of succsses test */ 
int number_of_test_succses = 0;


static void TestHelper(int booll);
void TestMemSet();


int main()
{
	TestMemSet();
	
	return 0;
}

void TestAll()
{
	
	if (number_of_test_succses == NO_OF_TESTS)
	{
		printf("TestStructSerializition Succsess!\n\n");
	}
}

void TestMemSet()
{
	int c = 5; 
	int i = 0;
	char * new[20] = {0};
	size_t n = 32;
	printf("before: %d\n", *(int*)new);
	
	MemSet(new , c , n);  	
	for(i=0 ; i < 8; i++)
	{
		printf("num is : %d\n", *(int*)(new+i));
	}
}

static void TestHelper(int booll)
{
	if(booll)
	{
		number_of_test_succses++;
	}
	else
	{
		printf("failed in no %d\n", number_of_test_succses);
	}
}

