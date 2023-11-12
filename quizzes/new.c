/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void TF(int num)
{
	if(!(num%5) && !(num%3))
	{
		printf("TF\n");
	}
	else if(!(num%3))
	{
		printf("T\n");
	}
	
	else if(!(num%5))
	{
		printf("F\n");
	}
	

	else 
	{
		printf("%d\n", num);
	}

}

char * Reverse(char str[],int str_len)
{
	
	char * reversed_str = malloc(str_len*sizeof(char));
	char * ptr_to_start = reversed_str;
	printf("\n");
	while(str_len--)
	{
		
		*reversed_str = tolower(str[str_len]); 
		printf("%c", *reversed_str);
		reversed_str++;
	}
	printf("\n");
	return (ptr_to_start);
}


int main()
{
	char * new_str = NULL;
	
	char str[] = "HelLo";
	new_str = Reverse(str, 6);
	TF(10);
	free(new_str);
	return 0;
}

