/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Bar
*	Date:      9/12/23     
******************************************************************************/
 
 
 #include <stdlib.h>  /* malloc() */
 #include <stdio.h>  /* printf() */
 #include <ctype.h>  /* tolower() */
 #include <assert.h> /* assert */

char *StrDup(const char *src)
{
	unsigned int src_len = StrLen(src);
	char *str = (char*)malloc(src_len+1);
	char *ptr_to_start = str;
	
	while(*src)
	{
		*str = *src;
		src++;
		str++;
	}
	
	*str = '\0';
	
	return ptr_to_start;
}



char *StrCat(char *destination, const char *source)
{
	size_t source_len = StrLen(source);
	size_t destination_len = StrLen(destination);
	size_t i = 0;
	char *ptr_start = destination;
	destination = destination + destination_len;
	for(i = 0; i < source_len; i++)
	{
		*destination = *source;
		destination++;
		source++;
	}
	
	*destination = '\0';
	
	return ptr_start;
}

char *StrNCat(char *destination, const char *source, size_t n)
{

	size_t destination_len = StrLen(destination);
	char *ptr_start = destination;
	destination = destination + destination_len;
	while(*source != '\0' && n > 0)
	{
		*destination = *source;
		destination++;
		source++;
		n--;
	}
	destination++;
	*destination = '\0';
	
	return ptr_start;
}


char *StrStr (const char *string, const char *word)	
{
	
	char *string_ptr = (char *)string; /* full string */
	char *word_ptr = (char *)word;    /* string to look for */
	assert(NULL != string);
	assert(NULL != word);
	while(*string)
	{
		if(*string == *word)
		{
			string_ptr = (char *)string;
			word_ptr = (char *)word;
			while(*string_ptr && *word_ptr)
			{
				if(*string_ptr != *word_ptr)
				{
					break;  
				}
				string_ptr++;
				word_ptr++;
			}
			
			if(*word_ptr == '\0')
			{
				return (char *)string;
			}
		}
		string++;	
	}
	return NULL;
}	



size_t StrSpn(const char *word, const char *string)
{
	size_t i = 0;
	size_t j = 0;
	size_t counter = 0;
	size_t max_counter = 0; 
	for(i = 0 ;string[i] != '\0'; i++)
	{
		counter = 0; 
		for(j = 0; word[j] != '\0'; j++)
		{
			if(string[i+j] == word[j])
			{
				counter++;
				
			}
		}
		max_counter = (counter > max_counter) ? counter :  max_counter;
	}
	return max_counter;
}


