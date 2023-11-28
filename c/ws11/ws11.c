/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Artur
*	Date:      
******************************************************************************/

#include <stdio.h>  /* printf() , fopen()	*/
#include <string.h> /* strcpy(),	  	*/
#include <ctype.h>  /* isdigit() , isalpha()	*/
#include <math.h>  /* pow()		  	*/


#include "ws11.h"


static void strrev(char* str);


int IsLittleEndian(void)
{
	int bit = 1; 
	char * check = (char *)&bit;
	
	return (*check & 1);
}



char* ItoaAnyBase(int num, char* buffer, int base)
{
	int sign = 0; 
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
		sign = 1;
	}
	
	while(num != 0)
	{
		digit = num%base;
		if(digit > 9)
		{
			buffer[i] = (digit-10) + 'A';
		}
		else 
		{
			buffer[i] = (digit) + '0';
		}
	
		i++;
		num /= base;
	}
	
	if(sign)
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


int Atoi(const char *str)
{
	char * read = (char *)str; 
	int result = 0;
	int multiple = 1 ; 
	int counter = 0;
	int sign = 1; 
	
	while(!(isdigit(*read))) /* remove additional spaces */
	{
		read++;
		if(*read == '-')
		{
			sign = -1;
		}	
	}
	
	while(isdigit(*read))  /* count the number size */
	{
		counter++;
		read++;
	}
	
	read = read - counter;
	multiple = (pow(10 , counter-1));
	while(counter)
	{
		result += multiple*(*read-'0');
		multiple /= 10;
		read++;
		counter--;
	}
	
	return result*sign;
}


int AtoiAnyBase(const char *str, int base)
{
	char * read = (char *)str; 
	int result = 0;
	int multiple = 1 ; 
	int counter = 0;
	int sign = 1; 
	
	while(!(isdigit(*read)) && !isalpha(*read)) /* remove additional spaces */
	{
		read++;
		if(*read == '-')
		{
			sign = -1;
		}	
	}
	
	while(isdigit(*read) ||  isalpha(*read)) /* count the number size */
	{
		counter++;
		read++;
	}
	
	read = read - counter;
	multiple = pow(base , counter-1);
	while(counter)
	{
		if(*read >= '0' && *read <= '0' + base)
		{
			result += multiple*(*read-'0');
			
		}
		
		if(*read >= 'A' && *read <= 'A' + base)
		{
			result += multiple*((*read - 'A' + 10));
		}
		
		multiple /= base;
		read++;
		counter--;
	}
	
	return result*sign;	
}


void PrintArrOfChars(char *str1, char *str2 ,char *str3, size_t size1,
						 size_t size2, size_t size3)
{
	size_t i = 0;
	char hash_chars[256] = {0};
	
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


