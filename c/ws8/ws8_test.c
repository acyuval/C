/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Artur
*	Date:      
******************************************************************************/
#include <stdio.h>

#include "ws8.h"


#define MAX2(a,b) (a > b ? a : b)

#define MAX3(a,b,c) MAX2(MAX2(a,b), MAX2(b,c))


#define SIZEOF_VAR(var) (char *)(&var+1)-(char*)(&var)

#define SIZEOF_TYPE(type) ((size_t)((type*)0 + 1)) -(size_t)(type*)(0)

#define NO_OF_TESTS 11

void TestMacros();
void test(int booll);

int No_of_tests_ok = 0;   /* this variaable will represent the number of succsses test */ 


int main()
{
	MultiDataTypeArr();
	TestMacros();
	return 0;
}



struct test_struct 
{
	int x1; 
	double x2;
	long x3; 
	char x4;
}this_struct;






void TestMacros()
{
	int x1= 5; 
	double x2 =2;
	long x3 = 2; 
	char x4 = 3;
	
	test(sizeof(x1) == SIZEOF_VAR(x1));
	test(sizeof(x2) == SIZEOF_VAR(x2));
	test(sizeof(x3) == SIZEOF_VAR(x3));
	test(sizeof(x4) == SIZEOF_VAR(x4));
	test(sizeof(this_struct) == SIZEOF_VAR(this_struct));
	test(sizeof(char) == SIZEOF_TYPE(char));
	test(sizeof(double) == SIZEOF_TYPE(double));
	test(sizeof(struct test_struct ) == SIZEOF_TYPE(struct test_struct ));
	test(sizeof(int *) == SIZEOF_TYPE(int *));	
	test(MAX2(3,2) == 3);	
	test(MAX3(6,2,3) == 6);	
		
	if (No_of_tests_ok == NO_OF_TESTS)
	{
		printf("\nTest macros :  OK\n");
	}
	else
	{
		printf("\nTest macros : failed\n");
	}
}



void test(int booll)
{
	if(1 == booll)
	{
		No_of_tests_ok++;
	}
	else 
	{
		printf("failed in no %d" , No_of_tests_ok);
	}

}

