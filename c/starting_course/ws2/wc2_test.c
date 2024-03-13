/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Bar
*	Date:      7/12/23     
******************************************************************************/
#include <stdio.h> /* printf() */
#include <stdlib.h> /* malloc(), free() */
#include "wc2.h"


int TestSwapInt()
{
	int input1[] = {4,6,7,4}; 
	int input2[] = {12,2,6,4}; 
	int number_of_tests = sizeof(input1)/sizeof(int);
	int i = 0;
	int temp_res1 = 0;
    	int temp_res2 = 0;
    	printf("----------------------------------------\n");
	printf("TestSwapInt:\n");
	
	for(i = 1; i < number_of_tests; i++)
    	{
		temp_res1 = input1[i];
		temp_res2 = input2[i];
		SwapInt(&input1[i], &input2[i]);
		
		if(input1[i] != temp_res2 || input2[i] != temp_res1)
		{
		    break;
		}
    	}
	if(i != number_of_tests)
	{
		printf("swap int failed in itr no. %d \n", (i));
	}
	else
	{
		printf("swap int sucsess!\n");
	}
	
	return 0;
}

int TestSwapSizeT()
{
	size_t input1[] = {4,6,7,4}; 
	size_t input2[] = {12,2,6,4}; 
	int number_of_tests = sizeof(input1)/sizeof(size_t);
	int i = 0;
	size_t temp_res1 = 0;
    	size_t temp_res2 = 0;
    	printf("----------------------------------------\n");
	printf("TestSwapSizeT:\n");
	
	for(i = 1; i < number_of_tests; i++)
    	{
		temp_res1 = input1[i];
		temp_res2 = input2[i];
		SwapSizeT(&input1[i], &input2[i]);
		if(input1[i] != temp_res2 || input2[i] != temp_res1)
		{
		    break;
		}
    	}
	if(i != number_of_tests)
	{
		printf("swap size_t failed in itr no. %d \n", (i));
	}
	else
	{
		printf("swap size_t sucsess!\n");
	}
	
	return (0);

}
int TestSwapSizeTPtr()
{
	size_t input1[] = {4,6,7,4}; 
	size_t input2[] = {12,2,15,9}; 
	size_t *first_ptr = NULL;
	size_t *second_ptr = NULL;
	
	int number_of_tests = sizeof(input1)/sizeof(size_t);
	int i = 0;

    	printf("----------------------------------------\n");
	printf("TestSwapSizeTPtr:\n");
	
	for(i = 1; i < number_of_tests; i++)
    	{
		first_ptr = &input1[i]; 
		second_ptr = &input2[i]; 
		SwapSizeTPtr(&first_ptr, &second_ptr);
		if(input1[i] == *first_ptr || input2[i] == *second_ptr)
		{
		    break;
		}
    	}
	if(i != number_of_tests)
	{
		printf("TestSwapSizeTPtr failed in itr no. %d\n", (i));
	}
	else
	{
		printf("TestSwapSizeTPtrtests sucsess!\n");
	}

	return (0);
}

int TestSwapPtrWithSwapSize_T()
{
	size_t input1[] = {4,6,7,4}; 
	size_t input2[] = {12,2,15,9}; 
	size_t *first_ptr = NULL;
	size_t *second_ptr = NULL;
	
	int number_of_tests = sizeof(input1)/sizeof(size_t);
	int i = 0;

    	printf("----------------------------------------\n");
	printf("TestSwapPtrWithSwapSize_T:\n");
	
	for(i = 1; i < number_of_tests; i++)
    	{
		first_ptr = &input1[i]; 
		second_ptr = &input2[i]; 
		SwapPtrWithSwapSize_T(&first_ptr, &second_ptr);
		if(input1[i] == *first_ptr || input2[i] == *second_ptr)
		{
		    break;
		}
    	}
	if(i != number_of_tests)
	{
		printf("TestSwapSizeTPtr failed in itr no. %d\n", (i));
	}
	else
	{
		printf("TestSwapSizeTPtrtests sucsess!\n");
	}

	return (0);
}


int TestCopyIntArr()
{
	
	int arr[] = {5, 12 , 6 ,7 ,9 ,10};
	int size_arr = sizeof(arr)/sizeof(int);
	int *cp_arr = CopyIntArr(size_arr , arr);	
	int i = 0;
    	printf("----------------------------------------\n");
	printf("TestCopyIntArr:\n");
	for(i = 1; i < size_arr; i++)
    	{
		if(*(cp_arr+i) != arr[i])
		{
		    break;
		}
    	}
    	
	if(i != size_arr)
	{
		printf("TestCopyIntArr failed in itr no. %d \n", (i));
	}
	else
	{
		printf("TestCopyIntArr sucsess!\n");
	}

	free(cp_arr);
	return (0);
}
int TestCheckForPalindrome()
{
	
	char str[4][20] = {"rotator", "mum", "kayak", "kadilac"};
	int expected_results[] = {0 , 0 , 0 , 1};
	int test_res = 0; 	
	int i = 0;
	int number_of_tests = 4;
    	printf("----------------------------------------\n");
	printf("TestCheckForPalindrome:\n");
	for(i = 0; i < number_of_tests; i++)
    	{
    		test_res = CheckForPalindrome(str[i]);
		if(test_res != expected_results[i])
		{
		    break;
		}
    	}
    	
	if(i != number_of_tests)
	{
		printf("TestCheckForPalindrome failed in itr no. %d \n", (i));
	}
	else
	{
		printf("TestCheckForPalindrome sucsess!\n");
	}

	return (0);
}

int main()
{
	
	TestSwapInt();
	TestSwapSizeT();
	TestSwapSizeTPtr();
	TestCopyIntArr();
	TestSwapPtrWithSwapSize_T();
	TestCheckForPalindrome();
	return (0);
}




