/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ARRAYSIZE(x) (sizeof x/sizeof x[0])

int Boom7(char *str)
{
	int flag = 0;
	char *read = str;
	char * write = str;
	
	while(*read == ' ')
	{
		read++;
	}

	while(*read)
	{
		if(*read == ' ')
		{
			if(flag == 0)
			{
				*write = ' ';
				write++;
			}
			flag = 1;
		}
		else
		{
			flag = 0;
			*write = *read;
			write++;
		}
		read++;
	}		
	
	return 0;
}

int main()
{
	char str[100] = {0};
	memcpy(str, "  hello    what is my name      \0", 32); 
	printf("before: %s", str);
	
	Boom7(str);
	
	printf("\nafter: %s", str);    
	
	return 0;
}

