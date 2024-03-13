/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Igal 
*	Date:      
******************************************************************************/
#include <stdio.h>	/*	printf() ,scanf()	*/
#include <stdlib.h>	/*	system()        	*/
#define ARRAYSIZE(x) (sizeof x/sizeof x[0])
typedef void (*ptr_to_func)();
 



int CheckInputSwitch()
{
	int input = 0;
	int return_value  = 0 ;
	const int esc = 27;
	
	printf("--------------------------------\n");
	printf("CheckInputSwitch: \n");
	return_value = system("stty -icanon -echo");
	if (0 != return_value)
	{
		exit(return_value);
	}
	
	while(esc != input)
	{
		printf("Enter one char\n");
		input = getchar();
	
		switch (input)
		{
		case 'A': 
			printf("A pressed\n");
			break;
		case 'T': 
			printf("T pressed\n");	
			break;
		}
		
	}
	
	return_value = system("stty icanon echo");
	if (0 != return_value)
	{
		exit(return_value);
	}
	
	
	return (1);
}


void A()
{
	printf("A pressed\n");
}

void T()
{
	printf("T pressed\n");
}

void NoAction()
{
	
}

int CheckInputLOT()
{
	int input = 0;
	int i = 0 ;
	const int esc = 27;
	int return_value  = 0 ;
	ptr_to_func LOT[128] = {NULL};

	printf("--------------------------------\n");
	printf("CheckInputLOT:  \n");

	for(i=0 ; i < 128; i++)
	{
		LOT[i] = NoAction;	
	}
	LOT['A'] = A;
	LOT['T'] = T;
	
	return_value = system("stty -icanon -echo");
	if (0 != return_value)
	{
		exit(return_value);
	}
	
	
	
	while(esc != input) 
	{
		printf("Enter one char:\n");
		input = getchar();
		LOT[(int)input]();	
	}
	
	return_value = system("stty icanon echo");
	if (0 != return_value)
	{
		exit(return_value);
	}
	
	
	return (0);
}


int CheckInputIf()
{
	int input = 0;
	const int esc = 27;
	int return_value  = 0 ;
	
	printf("--------------------------------\n");
	printf("CheckInputIf:  \n");
	return_value = system("stty -icanon -echo");
	if (0 != return_value)
	{
		exit(return_value);
	}
	
	
	while(input != esc)
	{	
		printf("Enter one char\n");
		input = getchar();
			
		if ('A' == input)
		{
			printf("A pressed\n");
			
		}
		if ('T' == input)
		{
			printf("T pressed\n");
			
		}
		
	}
	
	return_value = system("stty icanon echo");
	if (0 != return_value)
	{
		exit(return_value);
	}
	
	
	return (1);
}


