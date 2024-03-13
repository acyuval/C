/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Bar
*	Date:      9/12/23     
******************************************************************************/



#include <stdio.h>  /* printf()            */
#include <stdlib.h> /* malloc() , free() */
#include <string.h> /* strcmp() , strlen() ,strncmp() ,strcasecmp() , strdup() ,strchr(), strstr() , strcat(), strncat() */
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
	char c[5] = {'a', 'a', 's' , 'a' ,'e'};
	char * input = "sreas00dfa";
	size_t number_of_tests = 4; 
    	size_t i = 0 ; 
    	char * test_res = NULL;
    	char * expected_res = NULL;
    	
    	printf("----------------------------------------\n");
	printf("TestStrChr:\n");
	
	for(i = 0; i < number_of_tests; i++)
    	{
    		test_res = StrChr(input,c[i]);
    		expected_res = strchr(input,c[i]);  		
		if(test_res != NULL && *test_res != *expected_res)
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


void TestStrDup()
{
	char * input = "srersdsdsafdsdfa";
    	int i = 0 ; 
    	char * test_res = StrDup(input);
    	char * ptr_to_start  = test_res;
    	printf("----------------------------------------\n");
	printf("TestStrDup:\n");
	
	while(*test_res == *input)
    	{
		test_res++; 
		input++;
    	}
    	test_res--;
	if(*test_res != '\0')
	{
		printf("TestStrCpy failed in itr no. %d \n", (i));
	}
	else
	{
		printf("TestStrCpy sucsess!\n");
	}
	PrintStrings(ptr_to_start);
	free(ptr_to_start);


}

void TestStrCat()
{
	char source[20] = "efghij";
	char destenation[20] = "bbbbb";
	char destenation_expe[20] = "bbbbb";

	char * ptr_to_start = destenation; 
	char * test_res = StrCat(destenation, source);
    	char * expected_res = strcat(destenation_expe, source);

    	printf("----------------------------------------\n");
	printf("TestStrCat:\n");
	
	while(*test_res == *expected_res)
    	{
		test_res++; 
		expected_res++;
    	}
    	test_res--;
	if(*test_res != '\0')
	{
		printf("TestStrCpy failed \n");
	}
	else
	{
		printf("TestStrCpy sucsess!\n");
	}
	PrintStrings(ptr_to_start);
}


void TestStrNCat()
{
	char destenation[20] = "abcd";
	char destenation_expe[20] = "abcd";
	char source[20]= "efghi";
	size_t n[4] = {1 , 2 ,3 ,4};
	int number_of_tests = 4;
	
	int i = 0; 
	char * test_res = NULL;
    	char * expected_res = NULL;
    	
    	printf("----------------------------------------\n");
	printf("TestStrNCat:\n");
    	for(i = 0 ; i< number_of_tests ; i++)
    	{	
    		
		test_res = StrNCat(destenation, source , n[i]);
	    	expected_res = strncat(destenation_expe, source, n[i]);

		
		while(*test_res == *expected_res)
	    	{
			test_res++; 
			expected_res++;
	    	}
	    	test_res--;
		if(*test_res != '\0')
		{
			printf("TestStrNCat failed \n");
		}
		else
		{
			printf("TestStrNCat sucsess!\n");
		}
		
	}		
}


void TestStrStr()
{
	char string[20] = "iloveyouvery";
	char word[5] = "love";
	char * test_res = StrStr(string, word);
    	char * expected_res = strstr(string, word);
	char * ptr_to_start = test_res; 
	
    	printf("----------------------------------------\n");
	printf("TestStrStr:\n");
	
	
	while(*test_res == *expected_res && *test_res != '\0')
    	{

		test_res++; 
		expected_res++;
    	}
    	
	if(*test_res != '\0')
	{
		printf("TestStrStr failed \n");
	}
	else
	{
		printf("TestStrStr sucsess!\n");
	}
	PrintStrings(ptr_to_start);
}

void TestStrSpn()
{
	char string[20] = "iloveyouvery";
	char word[20] = "y";
	size_t test_res = StrSpn(word, string);
    	size_t expected_res = strspn(word, string);
	
	
    	printf("----------------------------------------\n");
	printf("TestStrSpn:\n");
	printf("test: %lu ,expected: %lu\n" , test_res , expected_res);
	if(test_res != expected_res)
	{
		printf("TestStrSpn failed \n");
	}
	else
	{
		printf("TestStrSpn sucsess!\n");
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
	TestStrDup();
	TestStrCat();
	TestStrNCat();	
	TestStrStr();
	TestStrSpn();
	return 0;
}




