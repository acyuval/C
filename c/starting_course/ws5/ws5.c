/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Igal
*	Date:      
******************************************************************************/
#include <stdio.h>	/*	printf() ,scanf() , fopen(), fseek()..	*/
#include <stdlib.h>	/*	calloc()								*/ 
#include <string.h>	/*	strncmp() ,strcmp()						*/
#include "ws5.h"

enum fun_stat 
{
  failed,
  success, 
  noMatch
}; 

typedef void (*ptr_to_func)(char[]);


struct operation 
{
	char * string;
	int (*comperssion)(struct operation, char *,char *);
	enum fun_stat (*operation)(char*, char *);	
};	

enum fun_stat add_(char* string, char * file_name)
{
	int flag_type_of_add = 0;
	int ret = 0;


	char *buffer_for_file= NULL;


	int size_of_buffer = 0;
	

	FILE * file = NULL;
	
	flag_type_of_add = strncmp(string, "<", 1);
	
	if (!flag_type_of_add)				/* write to start of file */
	{
		file = fopen(file_name, "r"); 
		if (NULL == file)
		{
			printf("\nfailed to open file!\n");
			return failed;
		}
		fseek(file, 0, SEEK_END);		
		size_of_buffer = ftell(file);
		buffer_for_file = (char*)calloc(size_of_buffer ,1);
		fseek(file, 0, SEEK_SET);
		
		ret = fread(buffer_for_file, 1, size_of_buffer, file);
		
		fseek(file, 0, SEEK_SET);		
		
		if(fclose(file))
		{
			printf("\nfailed to close file!\n");
			return (failed);
		}
		
		
		file = fopen(file_name, "w+"); 
		if (NULL == file)
		{
			return failed;
		}
		
		fputs((string + 1), file);
		ret = fputs("\n", file);
		
		fseek(file, 0, SEEK_END);
		fputs(buffer_for_file, file);		
		free(buffer_for_file);
		
		if(fclose(file))
		{
			printf("\nfailed to close file!\n");
			return (failed);
		}
		
		  
	}
	else 						/* write to end of file */
	{
	
		file = fopen(file_name, "a+"); 
		if (NULL == file)
		{
			return failed;
		}
		ret = fputs(string, file);
		ret = fputs("\n", file);
		if (!ret)
		{
			printf("couldnt write to file!\n");
			return(failed);
		}
		
		if(fclose(file))
		{
			printf("\nfailed to close file!\n");
			return (failed);
		}
	}
	return(success);
}

enum fun_stat Remove_(char* string, char * file_name)
{
	(void)string;

	if (remove((const char*)file_name) == 0)
	{
		printf("Deleted successfully \n");
		return(success);
	}
	else
	{
		printf("Unable to delete the file \n");
		return(failed);
 	}
}


enum fun_stat Count_(char* string, char * file_name)
{
	int ch=0;	
	int lines=0;
	FILE * file = NULL;
	
	(void)string;
	
	
	file = fopen(file_name, "r"); 
	if (NULL == file)
	{
		return failed;
	}
	while ((ch = fgetc(file)) != EOF)
	{
		if (ch == '\n')
		{
			lines++;
		}
	}
	
	printf("number of lines is: %d \n" , (lines));
	if(fclose(file))
	{
		printf("\nfailed to close file!\n");
		return (failed);
	}
	
	return(success);

}

enum fun_stat Exit_(char* string, char * file_name)
{
	(void)file_name;
	(void)string;
	printf("---EXIT---\n");
	return(failed);
}

int Comperssion(struct operation this_struct, char * input , char * file_name)
{
	int status = 0 ;
	if(!(strcmp(input, this_struct.string)))	
	{
		status = this_struct.operation(input,file_name);
		return status;
	}
	else 
	{
		return noMatch;
	} 
}



void print(int num)
{
	printf("number is: %d\n", num);
}


int InitStruct()
{
	int i = 0;
	struct print_me 
	{
		int num;
		void (*ptr_func)(int);	
	};
	struct print_me arr_of_struct[10] = {0};
	printf("----------------------------\nstart of InitStruct: \n");	
	while(i < 10)
	{
		arr_of_struct[i].num = i;
		arr_of_struct[i].ptr_func = print;
		arr_of_struct[i].ptr_func(arr_of_struct[i].num);	
		i++;
	}
	
	return 0;
}


int notepad_sim(char name[])
{ 
	int ret = 0; 
	int i = 0;
	int number_of_commands = 3;
	char input[100] = {0};
	int status = success;
	char * file_name = NULL;
	struct operation arr_of_struct[3] = {{"-remove" , Comperssion ,Remove_},
										  {"-count" , Comperssion ,Count_},
					     					{"-exit" , Comperssion ,Exit_}}; 					     
	
	printf("----------------------------\nstart of phase 2\n\n");				     
	
	file_name = name;
	printf("start notepad:\n");
	while(status != failed)
	{
		ret = scanf("%s", input);
		if(ret)
		{
			for(i=0; i< number_of_commands ; i++)
			{
				status = arr_of_struct[i].comperssion(arr_of_struct[i],
												 input , file_name);
				if (status == success) 
				{
					break;
				}
					
			}
			
			if (status == noMatch) 
			{
				add_(input ,file_name);
			}
		}	
	}
	
	return 0;
}

