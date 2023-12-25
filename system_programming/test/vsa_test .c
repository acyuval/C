/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Chen
*	Date:      
******************************************************************************/
#include <stdio.h>  /* printf()  	  */
#include <assert.h> /* assert			  */
#include <stdlib.h>

#include "vsa.h"


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
	size_t total_to_allocate = FSASuggestSize(7,8);
	void * ptr_to_data = NULL;
	void * pool = malloc(total_to_allocate);
	int i = 0;
	void *ptrs[8] = {NULL};
	
	fsa_t * fsa = FSAInit(pool, 8 , total_to_allocate);
	
	TestHelper(FSACountFree(fsa) == 8 ,"TestFSACountFree", 1);
	
	
	for(i=0; i < 8; i++)
	{
		ptrs[i] = FSAAlloc(fsa);
	}
	
	TestHelper(FSAAlloc(fsa) == NULL ,"TestFSANULReturn   ", 4);
	TestHelper(FSACountFree(fsa) == 0 ,"TestFSAFree   ", 4);
	
	for(i=8; i > 0; i--)
	{
		FSAFree(fsa, ptrs[i]);
	}

	TestHelper(FSACountFree(fsa) == 8 ,"TestFSAFree   ", 4);
	
	
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


