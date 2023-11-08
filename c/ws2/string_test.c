/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Dvir
*	Date:      7/12/23     
******************************************************************************/



#include <stdio.h>  /* printf()            */
#include <stdlib.h> /* malloc() , free() */
#include <string.h> /* strcmp() , strlen() ,strncmp() ,strcasecmp() */
#include <strings.h>
#include "string.h"


void TestStrCmp()
{
	const int number_of_tests = 4;
	int i = 0;
	size_t test_res = 0;
    	size_t expected_res = 0;
    	char inputs1[4][20] = {"a", "Hellqwo", "HCllo World!", "12"};
    	char inputs2[4][20] = {"a", "Hellqo", "Hello World!", "12"};		
    	
    	printf("----------------------------------------\n");
	printf("Test my StrCmp:\n");
	for(i = 0; i < number_of_tests; i++)
    	{
		test_res = StrCmp(inputs1[i], inputs2[i]);
		expected_res = strcmp(inputs1[i], inputs2[i]);
		if(test_res != expected_res)
		{
		    break;
		}
    	}

	if(i != (number_of_tests))
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
    	char inputs1[4][20] = {" ", "Hello", "Hello World!", "1224A"};
    	char inputs2[4][20] = {" ", "H2ello4", "Hello World!", "12242"};
    	size_t n_values[] =   {3 , 3 , 4 , 12};		
    	
    	printf("----------------------------------------\n");
	printf("TestStrNCmp:\n");
	for(i = 0; i < number_of_tests; i++)
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
		printf("StrNCmp sucsess!\n");
	}	
}



void TestStrCaseCmp()
{
	const int number_of_tests = 4;
	int i = 0;
	size_t test_res = 0;
    	size_t expected_res = 0;
    	char inputs1[4][20] = {"A", "Hello", "Hdllo WoRld!", "12"};
    	char inputs2[4][20] = {"a", "Hello", "Hello World!", "12"};		
    	
    	printf("----------------------------------------\n");
	printf("TestStrCaseCmp:\n");
	for(i = 0; i < number_of_tests; i++)
    	{
		test_res = StrCaseCmp(inputs1[i], inputs2[i]);
		expected_res = strcasecmp(inputs1[i], inputs2[i]);
		if(test_res != expected_res)
		{
		    break;
		}
    	}

	if(i != (number_of_tests))
	{
	printf("str no. %d, failed. Output %lu, should be %lu\n", (i), test_res, expected_res);
	}
	else
	{
	printf("StrCmp sucsess!\n");
	}
	
}

void TestStrCpy()
{
	char * input = "srersdsdsdfa";
	int size_of_str = StrLen(input); 
    	char * destenation = malloc(size_of_str + 1 );
    	int i = 0 ; 
    	char * test_res = StrCpy(destenation,input);
    	char * expected_res = strcpy(destenation,input);
    	
    	printf("----------------------------------------\n");
	printf("TestStrCpy:\n");
	
	for(i = 1; i < size_of_str; i++)
    	{
		if(*(test_res+i) != *(expected_res+i))
		{
		    break;
		}
    	}
    	
	if(i != size_of_str)
	{
		printf("TestStrCpy failed in itr no. %d \n", (i));
	}
	else
	{
		printf("TestStrCpy sucsess!\n");
	}

	free(test_res);


}

int PrintStrings(char * str_to_print)
{
	
	printf("\nthe string is : \n" );
	while (*(str_to_print) != '\0')
	{
		printf("%c" , *str_to_print);
		str_to_print++;
	}
	printf(" \n" );
	return (0);		 
}

void TestStrNCpy()
{
	size_t n = 5;
	char * input = "srers00dfa";
	size_t size_of_str = StrLen(input); 
	
    	char * destenation = (char *)malloc(n);
    	size_t i = 0 ; 
    	char * test_res = StrNCpy(destenation,input, n);
    	char * expected_res = strncpy(destenation,input, n);
    	
    	
    	
    	printf("----------------------------------------\n");
	printf("TestStrNCpy:\n");
	
	for(i = 0; i < size_of_str; i++)
    	{    		
		if(*(test_res+i) != *(expected_res+i))
		{
		    break;
		}
    	}
	if(i != size_of_str)
	{
		printf("TestStrNCpy failed in itr no. %lu \n", (i));
	}
	else
	{
		printf("TestStrNCpy sucsess!\n");
	}
	
	PrintStrings(destenation);
	free(destenation);
}

void TestStrChr()
{
	char c[5] = {'a', 'b', 'c' , 'd' ,'e'};
	char * input = "sreas00dfa";
	size_t number_of_tests = 5; 
    	size_t i = 0 ; 
    	char * test_res = Null
    	char * expected_res = Null;
    	
    	printf("----------------------------------------\n");
	printf("TestStrChr:\n");
	
	for(i = 0; i < size_of_str; i++)
    	{
    		char * test_res = StrChr(input,c[i]);
    		char * expected_res = strchr(input,c[i]);    		
		if(*test_res != *expected_res )
		{
		    break;
		}
    	}
	if(i != number_of_tests)
	{
		printf("TestStrNCpy failed in itr no. %lu \n", (i));
	}
	else
	{
		printf("TestStrNCpy sucsess!\n");
	}
	
}

int main()
{
	TestStrCmp();
	TestStrNCmp();
	TestStrLen();
	TestStrCpy();
	TestStrCaseCmp();
	TestStrNCpy();
	TestStrChr();
	return 0;
}




