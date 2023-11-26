/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#define ARRAYSIZE(x) (sizeof x/sizeof x[0])

int foo(char * str, int size)
{
	char index[100] = {0};
	int i =0; int j = 0 ;
	int No_of_spaces = 0;
	char * new_str = malloc(size +1);
	char * start_ptr = str;
	while(i<size)
	{
		if(*str == ' ')
		{
			index[j] = i;
			j++;
			printf("i:%d ", i);
		}
		str++;
		i++;
	}
	
	index[j] = i;
	printf("index[j]:%d \n", index[j]);
	
	No_of_spaces = j; 
	while(j>0)
	{
		str = str + index[j-1];
		while(i<index[j])
		{
			printf("new_str:%c \n", *str++);
			*new_str++ = *(str++);
			i--;
		}
		j--;
		
	}
	
	


	return 0;
}

int main()
{		
	char test[100] = "i am student";
	
	foo(test , 12);

	return 0;
}

