/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Dvir
*	Date:      
******************************************************************************/
#include <stdio.h>	/*	printf()	*/
#include <stdlib.h>	/*	malloc()        */
#include <ctype.h>	/*	tolower()	*/
#include <string.h>	/*	strlen()	*/
#define ARRAYSIZE(x) (sizeof x/sizeof x[0])



void Sum2DArr(int (*arr)[3], int *result, size_t row_no, size_t col_no)
{
	size_t i = 0;
	size_t j = 0;
	printf("sizeof (*arr)[3] is %lu as size of pointer\n " , sizeof(arr));
	for(i=0 ; i< row_no ; i++)
	{
		for(j=0 ; j< col_no ; j++)
		{
			*result += arr[i][j];

		}
		result++;
	}
}

/******************************************************************************
* list of all datatypes:
*	Basic Data Type: 	int, char, float, double
*	Derived Data Type:	array, pointer, structure, union  
*	Enumeration Data Type:	enum
*	Void Data Type:		void       
******************************************************************************/
void ListOfDataTypes(void)
{
	char c='A';
	int n = 0;
	char *ptr=&c;
	char **ptrptr = &ptr; 
	int * int_ptr = &n;
	printf("-----------------------------------------\nlist of size of all data types: \n\n");
	printf("Size of Int Data Types in C = %lu bytes \n", sizeof(short int));
	printf("Size of Long Int Data Types in C = %lu bytes \n", sizeof(long int));
	printf("Size of Float Data Types in C = %lu bytes \n", sizeof(float));
	printf("Size of Double Data Types in C = %lu bytes \n", sizeof(double));
	printf("Size of Long Double Data Types in C = %lu bytes \n", sizeof(long double));
	printf("Size of Char Data Types in C = %lu bytes \n", sizeof(char));
	printf("Size of pointer to Char Data Types in C = %lu bytes \n", sizeof(ptr));
	printf("Size of pointer to Char pointer Data Types in C = %lu bytes \n", sizeof(ptrptr));
	printf("Size of pointer to int Data Types in C = %lu bytes \n", sizeof(int_ptr));

	

}

char ** GetAllEnvp(char **env)
{
	char ** temp_ptr = NULL;
	int counter_rows=0;
	char *this_env = NULL;
	char *this_env_original = NULL;	
	char ** buffer =NULL;
	int str_len=0;
	
	/* count the number of env variable for malloc */
	temp_ptr = env;
	while(*env != 0)
	{
		++counter_rows;
		++env;
	}
	env = temp_ptr;
	
	buffer = malloc((counter_rows+1) * sizeof(env)); 
	temp_ptr = buffer;
	while (*env != 0)
	{
		this_env_original = *env;
		
		str_len=strlen(this_env_original);	 /* count the number chars in a given variable string*/

		*buffer = malloc((str_len + 1));
		
		this_env = *buffer;		
		
		while(*this_env_original != '\0')
		{
			*this_env = tolower(*this_env_original);
			this_env_original++;
			this_env++;
		}
		*this_env = '\0';

		buffer++;
		env++;

	}
	
	buffer = temp_ptr;
	return (buffer) ;	
	
}

void PrintAllEnvp(char ** env)
{
	int i = 0;
	char ** temp_ptr = NULL;
	char *this_env = NULL;
	char ** buffer = NULL;
	
	printf("-----------------------------------------\nlist of all Env varible:  \n\n");
	buffer = GetAllEnvp(env);
	
	temp_ptr = buffer;
	while(*buffer != 0)
  	{
  		printf("\n%d: ", i++);
  		this_env = *buffer;
    		while(*this_env != '\0')
    		{
    			printf("%c", *this_env);
    			this_env++; 
    		}
    		free(*buffer);
    		buffer++;	   
  	}
  	
  	buffer = temp_ptr;
  	free(buffer);
  	printf("\nend of list \n");
  	
  	
}


int isPowerOf2(int number)
{
    while(number!=1)
    {
        if(number%2!=0)
            return 0;
        number=number/2;
    }
    return 1;
}

int Jusephus(int group_size)
{
	int i = 0;

	while (i<group_size)
	{
        	if(isPowerOf2(group_size-(i/2)))
        	{
        		printf("\nthe last soldier remain is : %d \n" , i+1); 
        		return i+1;
        	}
        	i++; 
        	   
        }
          
	return 0;
}




