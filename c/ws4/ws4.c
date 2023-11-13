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
	char input = 0;
	
	printf("--------------------------------\n");
	printf("CheckInputSwitch: \n");
	system("stty -icanon -echo");
	while(1){
		printf("Enter one char\n");
		scanf("\n%c" , &input);
	
		switch (input)
		{
		case 'A': 
			printf("A pressed\n");
			return(0);
		case 'T': 
			printf("T pressed\n");
			return(0);
		case 27: 
			return (0);
		}
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
	char input = 0;
	int i = 0 ;
	const int esc = 27;
	ptr_to_func LOT[128] = {NULL};

	printf("--------------------------------\n");
	printf("CheckInputLOT:  \n");

	for(i=0 ; i < 128; i++)
	{
		LOT[i] = NoAction;	
	}
	LOT['A'] = A;
	LOT['T'] = T;
	
	system("stty -icanon -echo");
	printf("Enter one char:\n");
	scanf("\n%c" , &input);
	
	while(esc != input) 
	{
		LOT[(int)input]();
		printf("Enter one char\n");
		scanf("\n%c" , &input);		
	}
	
	return (0);
}


int CheckInputIf()
{
	char input = 0;
	const int esc = 27;
	printf("--------------------------------\n");
	printf("CheckInputIf:  \n");
	system("stty -icanon -echo");
	while(1)
	{
		
		printf("Enter one char\n");
		scanf("\n%c" , &input);
			
		if ('A' == input)
		{
			printf("A pressed\n");
			return(0);
		}
		if ('T' == input)
		{
			printf("T pressed\n");
			return(0);
		}
		if (esc == input)
		{
			printf("esc!!\n");
			return(0);
		}
		
	}

	return (1);
}


