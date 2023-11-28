/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Artur
*	Date:      
******************************************************************************/

#include <stdio.h>  /* printf() , fopen()	*/
#include <string.h> /* strlen(),	  	*/
#include <ctype.h>  /* isdigit() , isalpha()	*/


#include "ws11.h"

#define POSITIVE 1
#define NEGATIVE -1
#define NUM_OF_DIGITS 10
#define ASCII_SIZE 256

static void strrev(char* str);


int IsLittleEndian(void)
{
	int bit = 1; 
	char * check = (char *)&bit;
	
	return (*check & 1);
}



char* ItoaAnyBase(int num, char* buffer, int base)
{
	int flag_sign = 0; 
	int i = 0;
	int digit = 0;
	
	if (num == 0)
	{
		buffer[i] = '0';
		buffer[i + 1] = '\0';
		return buffer;
	}
	
	if(num < 0)
	{
		flag_sign = 1;
		num *= NEGATIVE;
	}
	
	while(num != 0)
	{
		digit = num%base;
		if(digit >= NUM_OF_DIGITS)
		{
			buffer[i] = (digit-NUM_OF_DIGITS) + 'A';
		}
		else 
		{
			buffer[i] = (digit) + '0';
		}
	
		i++;
		num /= base;
	}
	
	if(flag_sign)
	{
		buffer[i] = '-';
	}
	strrev(buffer);
	return buffer;
}


char* Itoa(int num, char* buffer)
{
	sprintf(buffer, "%d", num);
	return buffer;
}


int AtoiAnyBase(const char *str, int base)
{
	char * read = (char *)str; 
	int result = 0;
	int counter = 0;
	int sign = 1; 
	
	while(isspace(*read)) /* remove additional spaces */
	{
		read++;
	}

	if(*read == '-')
	{
		sign = NEGATIVE;
		read++;
	}	
	
	while(isdigit(read[counter]) ||  isalpha(read[counter])) /* count the number size */
	{
		counter++;
	}
	

	while(counter)	
	{
			
		
		result *= base;
		if(*read >= '0' && *read <= '0' + base && isdigit(*read))
		{
			result += (*read-'0');
		}
		if(*read >= 'A' && *read <= 'A' + base && isalpha(*read))
		{
			result += ((*read - 'A' + NUM_OF_DIGITS));
		}
		read++;
		counter--;
	}
	return result*sign;	
}


int Atoi(const char *str)
{
	return AtoiAnyBase(str, 10);
}


void PrintArrOfChars(char *str1, char *str2 ,char *str3, size_t size1,
						 size_t size2, size_t size3)
{
	size_t i = 0;
	char hash_chars[ASCII_SIZE] = {0};
	
	for(i=0 ; i<size1; i++)
	{
		if(!hash_chars[(int)(*(str1+i))])
		{
			hash_chars[(int)(*(str1+i))] += 1;
		}
	} 

	for(i=0 ; i<size2; i++)
	{
		if(hash_chars[(int)(*(str2+i))] == 1)
		{
			hash_chars[(int)(*(str2+i))] += 1;
		}
	} 

	for(i=0 ; i<size3; i++)
	{
		hash_chars[(int)(*(str3+i))] = 0;
	} 	

	for(i=0 ; i < 256; i++)
	{
		if(hash_chars[i] == 2)
		{
			printf("\n[%c]", (char)i);
		}
	}
}


static void strrev(char* str) 
{
    
	int i = 0;
	int j = strlen(str) - 1;
	
	if (!str)
	{
		return;
	}
	
	while (i < j)
	{
		char c = str[i];
		str[i] = str[j];
		str[j] = c;
		i++;
		j--;
	}
}


