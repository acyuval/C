/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Igal
*	Date:      
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "ws5.h"

#define ARRAYSIZE(x) (sizeof x/sizeof x[0])


int main(int argc, char *argv[])
{
	if (argc == 0)
	{
		return 0;
	}
	
	InitStruct();

	notepad_sim(argv[1]);

	return 0;
}

