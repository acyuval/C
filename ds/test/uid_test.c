/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Chen
*	Date:      
******************************************************************************/
#include <stdio.h>  /* printf()  	  */

#include "uid.h"


/******************************************************************************
*							TYPE DEFS / MACROS 								  * 
******************************************************************************/



/******************************************************************************
*							FUNCTION DECLRATION								  * 
******************************************************************************/

static void TestHelper(int booll , char * calling_function, int test_no);

/******************************************************************************
*							MAIN											  * 
******************************************************************************/


int main()
{
	ilrd_uid_t test_uid1 = UIDCreate();
	ilrd_uid_t test_uid2 = UIDCreate();
	
	TestHelper(UIDIsEqual(test_uid1, test_uid2) == 0 , "testIsEqual", 1);
	TestHelper(UIDIsEqual(test_uid1, test_uid1) == 1 , "testIsEqual", 2);
	
	return 0;
}




/******************************************************************************
*							TEST FUNCTIONS									  * 
******************************************************************************/


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


