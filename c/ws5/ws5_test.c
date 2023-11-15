/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "ws5.h"

#define ARRAYSIZE(x) (sizeof x/sizeof x[0])

int TestAll()
{

	InitStruct();

	return 0;
}

int main(int argc, char *argv[])
{
	if (argc == 0)
	{
		return 0;
	}
	phase2(argv[1]);

	return 0;
}

