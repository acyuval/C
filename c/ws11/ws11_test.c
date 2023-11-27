/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Artur
*	Date:      
******************************************************************************/
#include <stdio.h>  /*   printf()  	  */
#include <string.h> /*   strcmp()	  */
#include <stdlib.h> /*   atoi() ... 	  */
#include "ws11.h"

#define NO_OF_TESTS 9

int number_of_test_succses = 0;


void TestAtoi();
void TestAtoiAnyBase();
void TestItoa();
void TestItoaAnyBase();
void TestPrintArrOfChars();
void TestIsLittleEndian(void);

static void TestHelper(int booll , char * calling_function);

int main()
{
	TestIsLittleEndian();
	TestPrintArrOfChars();
	TestItoaAnyBase();
	TestItoa();
	TestAtoi();
	TestAtoiAnyBase();
	
	return 0;
}

void TestIsLittleEndian(void)
{
	printf("this computer is little indian ? %s!\n", 
					IsLittleEndian() ? "TRUE" : "False");
	printf("this computer is little indian macro? %s!\n", 
					IS_LITTLE_ENDIAN ? "TRUE" : "False");					

}


void TestPrintArrOfChars()
{
	char arrA[7]= {'c', 'a','f', '2', 'r', '4', '2'};
	char arrB[7] = {'4', 'c','s', 'e', 'r', '1', '2'};
	char arrC[7] = {'q', 'r','f', 'y', '2', 'c', 'd'};

	printf("\nTestPrintArrOfChars: ");
	PrintArrOfChars(arrA,arrB,arrC, 7, 7, 7);
}


void TestAtoi()
{
	char * function_descriptor = "TestAtoi";
	
	char * test = "   -410036  ";
	TestHelper((atoi(test) == Atoi(test) ), function_descriptor);
	printf("\nTestAtoiAnyBase Sucsess!");
}

void TestAtoiAnyBase()
{
	char * function_descriptor = "TestAtoiAnyBase";
	
	char test[10][20] = {"11011","12012", "A32" , "B23A"} ;
	int expected_results[10] = {27 , 140, 1245, 19342};
	int base[36] = {2,3,11,12};
	int i = 0;
	int num_of_test = 4;
	for(i=0;i<num_of_test;i++)
	{
		TestHelper((expected_results[i] == AtoiAnyBase(test[i],
					       base[i])), function_descriptor);
	}
	printf("\nTestAtoiAnyBase Sucsess!");
}

void TestItoa()
{
	char * function_descriptor = "TestItoa";
	char expected_results[10][20] = {"27","140", "1245" , "19342"} ;
	int test[10] = {27 , 140, 1245, 19342};
	int i = 0;
	int num_of_test = 4;
	char buffer[100] = {0};
	for(i=0;i<num_of_test;i++)
	{
		TestHelper(!memcmp(expected_results[i],Itoa(test[i], buffer), 
			    strlen(expected_results[i])), function_descriptor);
	}
	printf("\nTestAtoiAnyBase Sucsess!");
}


void TestItoaAnyBase()
{
	char * function_descriptor = "TestItoa";
	char expected_results[10][20] = {"11011","2030", "A32" , "4B8E"} ;
	int test[10] = {27, 140, 1245, 19342};
	int base[36] = {2,4,11,16};
	int i = 0;
	int num_of_test = 4;
	for(i=0;i<num_of_test;i++)
	{
		char buffer[100] = {0};
		TestHelper(!memcmp(expected_results[i], ItoaAnyBase(test[i], buffer, base[i]), 
			    strlen(expected_results[i])), function_descriptor);
	}
	printf("\nTestAtoiAnyBase Sucsess!");
}






static void TestHelper(int booll , char * calling_function)
{
	if(booll)
	{
		number_of_test_succses++;
	}
	else
	{
		printf("failed in %s, No. %d\n",calling_function ,number_of_test_succses);
	}
}

