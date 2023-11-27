/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Artur
*	Date:      
******************************************************************************/
#include <stdio.h>  /* printf()  	  */
#include <string.h> /*  strcpy()	  */
#include <stdlib.h> /* Exit		  */

#include "ws10.h"

#define NO_OF_TESTS 9

/* this global variable will represent the number of succsses test */ 
int number_of_test_succses = 0;


static void TestHelper(int booll , char * calling_function);

int main()
{
	return 0;
}


void ()
{


	if (number_of_test_succses == NO_OF_TESTS)
	{
		printf("\n\n");
	}
}

static void TestHelper(int booll , char * calling_function)
{
	if(booll)
	{
		printf("%s sucsess!",calling_function);
		number_of_test_succses++;
	}
	else
	{
		printf("failed in %s, No. %d\n",calling_function ,number_of_test_succses);
	}
}

