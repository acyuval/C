/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Dvir
*	Date:      7/12/23     
******************************************************************************/



#include <stdio.h>  /* printf()            */

#include <string.h> /* strcmp() , strlen() ,strncmp()  */
#include "string.h"


void TestStrCmp()
{
	const int number_of_tests = 4;
	int i = 0;
	size_t test_res = 0;
    	size_t expected_res = 0;
    	char inputs1[4][20] = {"a", "Hello", "Hello World!", "12"};
    	char inputs2[4][20] = {"a", "Hello4", "Hello World!", "122"};		
    	
    	printf("----------------------------------------\n");
	printf("Test my StrCmp:\n");
	for(i = 1; i < number_of_tests; i++)
    	{
		test_res = StrCmp(inputs1[i], inputs2[i]);
		expected_res = strcmp(inputs1[i], inputs2[i]);
		if(test_res != expected_res)
		{
		    break;
		}
    	}

	if(i != number_of_tests)
	{
	printf("str no. %d, failed. Output %lu, should be %lu\n", (i), test_res, expected_res);
	}
	else
	{
	printf("StrCmp--sucsess\n");
	}
	
}

void TestStrLen()
{
	int i = 0;
	size_t test_res = 0;
    	size_t expected_res = 0;

    	char inputs[3][20] = {"", "Hello", "Hello World!"};	
    	int num_tests = sizeof(inputs)/sizeof(char);	
	printf("----------------------------------------\n");
	printf("Test my StrLen:\n");
	for(i = 1; i < num_tests; i++)
    	{
		test_res = StrLen(inputs[i]);
		expected_res = strlen(inputs[i]);
		if(test_res != expected_res)
		{
		    break;
		}
    	}
	    if(i != num_tests)
	    {
		printf("str no. %d, failed. Output %lu, should be %lu\n", (i), test_res, expected_res);
	    }
	    else
	    {
		printf("StrLen--sucsess!\n");
	    }	
}


void TestStrNCmp()
{
	const int number_of_tests = 4;
	int i = 0;
	size_t test_res = 0;
    	size_t expected_res = 0;
    	char inputs1[4][20] = {"a", "H2ello", "Hello World!", "1122"};
    	char inputs2[4][20] = {"a", "Hello4", "Hello World!", "122"};
    	size_t n_values[] =   {3 , 3 , 4 , 12};		
    	
    	printf("----------------------------------------\n");
	printf("Test my StrNCmp:\n");
	for(i = 1; i < number_of_tests; i++)
    	{
		test_res = StrNCmp(inputs1[i], inputs2[i] , n_values[i]);
		expected_res = strncmp(inputs1[i], inputs2[i], n_values[i]);
		if(test_res != expected_res)
		{
		    break;
		}
    	}

	if(i != number_of_tests)
	{
	printf("str no. %d, failed. Output %lu, should be %lu\n", (i), test_res, expected_res);
	}
	else
	{
	printf("StrNCmp--sucsess\n");
	}
	
}


int main()
{
	TestStrCmp();
	TestStrNCmp();
	TestStrLen();

	return 0;
}




