/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Dvir
*	Date:      7/12/23     
******************************************************************************/


#include <stdio.h>
#include <stdlib.h>

unsigned int StrLen(char *p)
{
    unsigned int counter = 0;

    while(*p != '\0')
    {
        counter++;
        p++;
    }
    return counter;
}

int StrCmp(const char* str1, const char* str2)
{
	do
        {
        	if (*str1 != *str2) 
        	{
        		return (*str1 - *str2);	
        	}    	
        	str1++; str2++;
        }while(*str1 != '\0' || *str2 != '\0');
     	return 0;
}

