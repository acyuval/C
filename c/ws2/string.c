/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Dvir
*	Date:      7/12/23     
******************************************************************************/
 
 
 #include <stdlib.h>  /* malloc() */



unsigned int StrLen(char *str)
{
    unsigned int counter = 0;

	while(*str != '\0')
	{
		counter++;
		str++;
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


/* StrCpy gets pre-allocated char pointer destination that is large enough to store the copied string  */ 

char* StrCpy(char* destination, const char* source)
{
	char *ptr_to_start =  destination;

	while (*source != '\0')
	{
		*destination = *source;
		destination++;
		source++;
	}
	*destination = '\0';
	 return (ptr_to_start);
}
 
/* StrNCpy gets pre-allocated char pointer destination that is large enough to store the copied string (n+1 char)  */ 

char* StrNCpy(char* destination, const char* source, size_t n)
{
	char *ptr_to_start =  destination;
	size_t counter = 0 ;
	
	while (*source != '\0' && counter < n)
	{
		*destination = *source;
		destination++;
		source++;
		counter++;
		counter++; 
	}
	*destination = '\0';
	 return (ptr_to_start);
}
 
int StrNCmp(const char *str1, const char *str2, size_t n)
{	
	size_t counter = 0; 
	
	while((*str1 != '\0' || *str2 != '\0') && counter < n)
	{
		if (*str1 != *str2) 
		{
			return(*str1 - *str2);	
		}
    	counter++;     	
	}
	return 0;
	
} 


