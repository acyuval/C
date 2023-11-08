/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Dvir
*	Date:      7/12/23     
******************************************************************************/
 
 
 #include <stdlib.h>  /* malloc() */
 #include <stdio.h>  
 #include <ctype.h>

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
	}
	*destination = '\0';
	while (counter < n)
	{
		*destination = '\0';
		destination++;
		counter++;
	}	
	 return (ptr_to_start);
}
 
int StrNCmp(const char *str1, const char *str2, size_t n)
{	
	size_t counter = 0; 
	
	while(*str1 != '\0' && (*str1 == *str2) && (counter < n))
	{
    	counter++;
    	str1++;
    	str2++;     	
	}
	
	return (*str1-*str2);
} 

int StrCmp(const char* str1, const char* str2)
{
	while(*(str1) == *(str2) && *(str1) !='\0' )
	{ 
	    str1++;
    	str2++;     	
	}
	return (*str1-*str2);
 	
}

int StrCaseCmp(const char* str1, const char* str2)
{

	while(tolower(*(str1)) == tolower(*(str2)) && *(str1) !='\0' )
	{    	
		
		str1++;
    	str2++;  
	}
	return (*str1-*str2);
 	
}

char *StrChr(const char *str, int c)
{
	char * ptr = (char *)str;
	while(*ptr != '\0')
	{
		if (*ptr == (char)c) 
		{
			return ptr;
		}
		ptr++;
	}
	return (Null);
}

