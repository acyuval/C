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
	int i =0; 
	int No_of_spaces = 1;

	char * new_str = malloc(size +1);
	char * ptr_cpy_new_str = new_str;
	
	while(i<size)
	{
		if(str[i] == ' ')
		{
			index[No_of_spaces] = i+1;
			No_of_spaces++;
		}
		i++;
	}

	index[No_of_spaces] = i;
	
	while(No_of_spaces >= 0)
	{
		
		i = index[No_of_spaces-1];
		
		while(i<index[No_of_spaces])
		{
			*new_str++ = str[i];
			i++;
		}

		*new_str++ = ' ';
		No_of_spaces--;
	}
	*new_str = '\0';
	
	printf("\nnew str: %s\n\n", ptr_cpy_new_str);
	return 0;
}

int main()
{		
	char test[100] = "i am student";
	
	foo(test , 12);
	printf("string : %s" , test);
	return 0;
}

