/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Chen
*	Date:      
******************************************************************************/
#include <stdio.h>  /* printf()  	  */
#include <assert.h> /* assert			  */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "mt_sort.h"

#define TEST_SIZE (5)
#define NUM_CHAR (1760952)
#define NUM_OF_DIC (4)
/******************************************************************************
*							TYPE DEFS / MACROS 								  * 
******************************************************************************/



/******************************************************************************
*							FUNCTION DECLRATION								  * 
******************************************************************************/

static void TestHelper(int booll , char * calling_function, int test_no); 
static void PrintArr(unsigned char * arr , size_t size);
void TestMTSort();

unsigned char * CreateDic(size_t *counter);
/******************************************************************************
*							MAIN											  * 
******************************************************************************/

	
int main()
{
	srand(time(NULL));
	TestMTSort();
	return (0);
}




/******************************************************************************
*							TEST FUNCTIONS									  * 
******************************************************************************/

void TestMTSort()
{

	int i = 0;
	int this_test = 0; 
	int threads_amount = 0;
	size_t counter = 0; 
	unsigned char *buffer = NULL;
	clock_t start = 0;
	clock_t end = 0;
	
	buffer = CreateDic(&counter);

	for(this_test = 0 ; this_test < TEST_SIZE ; ++this_test)
	{
		threads_amount = 2 * (this_test+1);
		start = clock();
		MTCountingSort(buffer, counter, threads_amount);
		end = clock();
		for (i = 0 ; i < counter-1; ++i)
		{
			if(buffer[i] > buffer[i+1])
			{
				printf("failed");
				break;
			}
		}
		if (i >= counter-1)
		{
			printf("num of thread %d at time %f \n", threads_amount, ((double)(end-start))/CLOCKS_PER_SEC);
		}

	}

	puts("");


}


/******************************************************************************
*							STATIC FUNCTIONS								  * 
******************************************************************************/
static void PrintArr(unsigned char * arr , size_t size)
{
	int i = 0;
	printf("\narr :\n");
	for(i = 0 ; i < size; ++i)
	{
		printf("%d ", arr[i]);
	}
}



unsigned char * CreateDic(size_t *counter)
{
	size_t i = 0 , j = 0;
	char c = 0 ;
	unsigned char * buffer = NULL;

	FILE * file = fopen("/usr/share/dict/american-english" , "r");
	if(NULL == file)
	{
		return;
	}

 	while(c != EOF)
	{
		c = fgetc(file);
		if (isalpha(c))
		{
			++(*counter);
		}
	}
	fseek(file, 0 ,SEEK_SET);

	buffer = malloc((*counter) * sizeof(char) * NUM_OF_DIC);
	if (buffer == NULL)
	{
		printf("could'nt open\n\n\n");
		return NULL;
	} 

	for(i = 0 ; i < NUM_OF_DIC ; ++i)
	{
		c = 0;
		while(c != EOF)
		{
			c = fgetc(file);
			if (isalpha(c))
			{
				buffer[j] = c;
				++j;
			}			
		}
		fseek(file, 0 ,SEEK_SET);
	}

	fclose(file);

	return buffer;

}



static void TestHelper(int booll , char * calling_function, int test_no)
{
	if(booll)
	{
		printf("%s -> \t\tNO.%d sucsess!\n\n",calling_function, test_no);
	}
	else
	{
		printf("failed in %s, No. %d\n\n",calling_function ,test_no);
	}
}


