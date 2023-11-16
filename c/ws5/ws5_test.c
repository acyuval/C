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
	if (argc < 2)
	{
		printf("please enter file name as argument!");
		return 0;
	}
	
	InitStruct();

	notepad_sim(argv[1]);

	return 0;
}

