/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Igal
*	Date:      
******************************************************************************/
#include <stdio.h>	/*	printf() ,scanf() 	*/
#include <stdlib.h>	/*	calloc()		*/ 
#include <string.h>	/*	strncmp() ,strcmp()	*/

enum fun_stat 
{
  failed,
  success, 
  noMatch
}; 

typedef void (*ptr_to_func)(char[]);


char * file_name = NULL;
char * io_str = NULL;


struct operation 
{
	char * string;
	int (*comperssion)(struct operation, char *,char *);
	enum fun_stat (*operation)(char*, char *);	
};



FILE *OpenFile(char str[], char* type)
{
	FILE * file = NULL;

	file = fopen(str, type);
	if(NULL == file) 
	{
		printf("failed to open file - exit!!\n");
		exit(0);
	}	

	return (file);
}
	

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
		file = OpenFile(file_name, "r"); 
		if (NULL == file)
		{
			return failed;
		}
		fseek(file, 0, SEEK_END);		
		size_of_buffer = ftell(file);
		buffer_for_file = (char*)calloc(size_of_buffer ,1);
		fseek(file, 0, SEEK_SET);
		
		ret = fread(buffer_for_file, 1, size_of_buffer, file);
		
		if (NULL == file)
		{
			return failed;
		}
		
		fseek(file, 0, SEEK_SET);		
		fclose(file);
		
		file = OpenFile(file_name, "w"); 
		if (NULL == file)
		{
			return failed;
		}
		
		fputs((string + 1), file);
		ret = fputs("\n", file);
		fseek(file, 0, SEEK_END);
		fputs(buffer_for_file, file);		
		free(buffer_for_file);
		fclose(file);
		  
	}
	else 						/* write to end of file */
	{
		file = OpenFile(file_name, "a+"); 
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
		fclose(file);
	}
	return(success);
}

enum fun_stat Remove_(char* string, char * file_name)
{
	int ret = 0; 
	FILE * file = NULL;
	(void)string;

	if (remove((const char*)file_name) == 0)
	{
		printf("Deleted successfully \n");
		printf("New file name: \n");
		ret = scanf("%s", file_name);
		if (ret)
		{
			file = OpenFile(file_name, "w+");
			printf("New file opend...: \n");
			printf("please enter text to write[100 chars max] or use command (remove/count/exit/<*):\n");
			fclose(file);
		}
	}
	else
	{
		printf("Unable to delete the file \n");
		return(failed);
 	}
 	
 	return(success);
}


enum fun_stat Count_(char* string, char * file_name)
{
	int ch=0;	
	int lines=0;
	FILE * file = NULL;
	
	(void)string;
	
	file = OpenFile(file_name, "r"); 
	rewind(file);
	
	lines++;
	while ((ch = fgetc(file)) != EOF)
	{
		if (ch == '\n')
		{
			lines++;
		}
	}
	
	printf("number of lines is: %d \n" , (lines-1));
	fclose(file);
	return(success);

}

enum fun_stat Exit_(char* string, char * file_name)
{
	(void)file_name;
	(void)string;
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

int Comperssion(struct operation this_struct, char * str_to_cmp , char * file_name)
{
	
	if(!(strcmp(str_to_cmp, this_struct.string)))	
	{
		this_struct.operation(str_to_cmp,file_name);
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
	FILE * file = NULL;
	struct operation arr_of_struct[3] = {{"-remove" , Comperssion ,Remove_},{"-count" , Comperssion ,Count_},
					     {"-exit" , Comperssion ,Exit_}}; 					     
	
	printf("----------------------------\nstart of phase 2\n\n");				     
	file_name = name;
	file = OpenFile(file_name, "w+");
	fclose(file); 	
	printf("please enter text to write[100 chars max] or use command (remove/count/exit/<*):\n");
	while(status != failed)
	{
		i = scanf("%s", str_to_cmp);
		if(i)
		{
			for(i=0; i< number_of_commands ; i++)
			{
				status = arr_of_struct[i].comperssion(arr_of_struct[i], str_to_cmp , file_name);
				if (status == success) 
				{
					break;
				}	
			}
			if (status == noMatch) 
			{
				add_(str_to_cmp ,file_name);
			}
		}	
	}
	
	return 0;
}

