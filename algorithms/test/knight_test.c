/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Chen
*	Date:      
******************************************************************************/
#include <stdio.h>  /* printf()  	  */
#include <stdlib.h>
#include "knight.h"


/******************************************************************************
*							TYPE DEFS / MACROS 								  * 
******************************************************************************/



/******************************************************************************
*							FUNCTION DECLRATION								  * 
******************************************************************************/
int compareator(const void * arg1,const void * arg2);
void TestKnightTour();
/******************************************************************************
*							MAIN											  * 
******************************************************************************/


int main()
{
	TestKnightTour();
	return (0);
}


void TestKnightTour()
{
	int path[65] = {0};
	status_t status = 0 ;
	int i = 0;
	status = KnightTour(path, 20);

	printf("\nstatus is %d \n", status);

	for(i=0;i<64;++i)
	{
		printf("%d-", path[i]);
	}
	qsort(path, 64, sizeof(int), compareator);
	printf("\n\n\n");
	for(i=0;i<64;++i)
	{
		printf("%d-", path[i]);
	}
}

/******************************************************************************
*							TEST FUNCTIONS									  * 
******************************************************************************/
int compareator(const void * arg1,const void * arg2)
{
    int * int1 = (int *)arg1;
    int * int2 = (int *)arg2;
    return ((*int1 > *int2)? 1 : -1) ; 
}



/******************************************************************************
*							STATIC FUNCTIONS								  * 
******************************************************************************/


static void TestHelper(int booll , char * calling_function, int test_no)
{
	if(booll)
	{
		printf("%s -> \t\tNO.%d success!\n\n",calling_function, test_no);
	}
	else
	{
		printf("failed in %s, No. %d\n\n",calling_function ,test_no);
	}
}


