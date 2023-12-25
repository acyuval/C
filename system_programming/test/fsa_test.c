/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Chen
*	Date:      
******************************************************************************/
#include <stdio.h>  /* printf()  	  */
#include <assert.h> /* assert			  */
#include <stdlib.h>

#include "fsa.h"


/******************************************************************************
*							TYPE DEFS / MACROS 								  * 
******************************************************************************/



/******************************************************************************
*							FUNCTION DECLRATION								  * 
******************************************************************************/

static void TestHelper(int booll , char * calling_function, int test_no); 

void TestFSA();
/******************************************************************************
*							MAIN											  * 
******************************************************************************/

	
int main()
{
	TestFSA();
	return (0);
}




/******************************************************************************
*							TEST FUNCTIONS									  * 
******************************************************************************/

void TestFSA()
{
	size_t total_to_allocate = 0;
	size_t num_of_blocks = 10;
	size_t block_size = 12;
	
	void * ptr_to_data = NULL;
	void * pool = NULL;
	fsa_t * fsa = NULL;
	size_t i = 0;
	void *ptrs[10] = {NULL};
	
	total_to_allocate = FSASuggestSize(num_of_blocks,block_size);
	
	pool = malloc(total_to_allocate);
	
	fsa = FSAInit(pool, block_size , total_to_allocate);
	
	
	TestHelper(FSACountFree(fsa) == num_of_blocks ,"TestFSACountFree", 1);
	
	
	for( i=0 ; i < num_of_blocks ; i++)
	{
		ptrs[i] = FSAAlloc(fsa);
	}
	
	TestHelper(FSAAlloc(fsa) == NULL ,"TestFSANULReturn   ", 4);
	TestHelper(FSACountFree(fsa) == 0 ,"TestFSAFree   ", 4);
	
	for(i=0; i < num_of_blocks; i++)
	{
		FSAFree(fsa, ptrs[i]);
	}

	TestHelper(FSACountFree(fsa) == num_of_blocks ,"TestFSAFree   ", 4);
	
	free(pool);
	
}


/******************************************************************************
*							STATIC FUNCTIONS								  * 
******************************************************************************/


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


