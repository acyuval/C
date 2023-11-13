/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Igal
*	Date:      
******************************************************************************/
#include <stdlib.h>	/*	system()        	*/
#include "ws4.h"
#define ARRAYSIZE(x) (sizeof x/sizeof x[0])




int main()
{
	CheckInputSwitch();
	CheckInputIf();
	CheckInputLOT();
	system("stty icanon echo");
	return (0);
}
