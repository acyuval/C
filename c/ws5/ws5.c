/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Igal
*	Date:      
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum fun_stat 
{
  failed,
  success, 
  noMatch
}; 

typedef void (*ptr_to_func)(char[]);

FILE * file = NULL;
char * file_name = NULL;
char * io_str = NULL;


struct operation 
{
	char * string;
	int (*comperssion)(struct operation, char *);
	enum fun_stat (*operation)(char*);	
};



FILE *OpenFile(char str[])
{
	FILE * file;

	file = fopen(str, "w+");
	if(NULL == file) 
	{
		printf("failed to open file - exit!!\n");
		exit(0);
	}	

	return (file);
}
	

enum fun_stat add_(char* string)
{
	int flag_type_of_add = 0;
	int ret = 0;
	int ret2 = 0;
	void * ret_ptr = NULL;
	char buffer[101] = {0};
	char buffer_for_string[101] = {0};
	long int savePos = 0;   
	
	flag_type_of_add = strncmp(string, "<", 1);

	if (!flag_type_of_add)
	{
		strcpy(buffer_for_string , ++string);
		rewind(file);
		ret_ptr = fgets(buffer,101 ,file);
		rewind(file);
		ret2 = fputs(buffer_for_string , file);
		ret = fputs("\n", file);
		savePos = ftell(file);
		while (NULL != ret_ptr && 0 != ret2)
		{
			fseek(file, savePos, SEEK_SET);   	
			ret_ptr = fgets(buffer_for_string,101 ,file);
			fseek(file, savePos, SEEK_SET); 
			ret2 = fputs(buffer, file);
			savePos = ftell(file);
		}
	}
	else
	{
		ret = fputs(string, file);
		ret = fputs("\n", file);
		if (!ret)
		{
			printf("couldnt write to file!\n");
			return(failed);
		}
	}
	return(success);
}

enum fun_stat Remove_(char* string)
{
	int ret = 0; 
	
	(void)string;
	
	if (remove((const char*)file_name) == 0)
	{
		printf("Deleted successfully \n");
		printf("New file name: \n");
		ret = scanf("%s", file_name);
		if (ret)
		{
			file = OpenFile(file_name);
			printf("New file opend...: \n");
			printf("please enter text to write[100 chars max] or use command (remove/count/exit/<*):\n");
		}
	}
	else
	{
		printf("Unable to delete the file \n");
		return(failed);
 	}
 	
 	return(success);
}


enum fun_stat Count_(char* string)
{
	int ch=0;	
	int lines=0;
	
	
	rewind(file);
	(void)string;
	lines++;
	while ((ch = fgetc(file)) != EOF)
	{
		if (ch == '\n')
		{
			lines++;
		}
	}
	
	printf("number of lines is: %d \n" , (lines-1));
	return(success);

}

enum fun_stat Exit_(char* string)
{
	if (string != NULL)
	{
		printf("---EXIT---\n");
		exit(0);
	}
	else
	{
		return(failed);
	}
}

int Comperssion(struct operation this_struct, char * str_to_cmp)
{
	
	if(!(strcmp(str_to_cmp, this_struct.string)))	
	{
		this_struct.operation(str_to_cmp);
		return success;
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
	int i = 0; 
	int number_of_commands = 3;
	char str_to_cmp[100] = {0};
	int status = success;
	struct operation arr_of_struct[5] = {{"-remove" , Comperssion ,Remove_},{"-count" , Comperssion ,Count_},
					     {"-exit" , Comperssion ,Exit_}}; 					     
	
	printf("----------------------------\nstart of phase 2\n\n");				     
	file_name = name;
	file = OpenFile(file_name); 	
	printf("please enter text to write[100 chars max] or use command (remove/count/exit/<*):\n");
	while(status != failed)
	{
		i = scanf("%s", str_to_cmp);
		if(i)
		{
			for(i=0; i< number_of_commands ; i++)
			{
				
				status = arr_of_struct[i].comperssion(arr_of_struct[i], str_to_cmp);
				if (status == success) 
				{
					break;
				}	
			}
			if (status == noMatch) 
			{
				add_(str_to_cmp);
			}
		}	
	}
	
	return 0;
}

