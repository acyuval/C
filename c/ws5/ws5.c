/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void (*ptr_to_func)(char[]);
FILE * file = NULL;
char * file_name = NULL;
char * io_str = NULL;

struct operation 
{
	char * string;
	int (*comperssion)(struct operation, char *);
	void (*operation)(char*);	
};

	

void add_(char* string)
{
	int flag_type_of_add = 0;
	int ret = 0;
	char temp[100] = {0};
	flag_type_of_add = strncmp(string, "<", 1);

	if (!flag_type_of_add)
	{
		rewind(file);
		
		while ((ch = fgetc(file)) != EOF)
		{
			if (ch = )
				
		}
		rewind(file);
		char temp[100] = fgets(file)
		
		ret = fputs("\n", file);
		ret = fputs(++string, file);
		ret = fputs("\n", file);
		while (fgetc(file) != EOF)
		{
			
		}
	}
	else
	{
		ret = fputs(string, file);
		ret = fputs("\n", file);
		if (!ret)
		{
			printf("couldnt write to file!\n");
		}
	}
	

}

void Remove_(char* string)
{

	if (NULL == string)
	{
		return;
	}
	
	if (remove((const char*)file_name) == 0)
	{
		printf("Deleted successfully \n");
	}
	else
	{
		printf("Unable to delete the file \n");
 	}

}


void Count_(char* string)
{
	int ch=0;	
	int lines=0;
	
	printf("count:%s\n", string);
	rewind(file);
	if (file == NULL) 
	{
		return;
	}
  
	lines++;
	while ((ch = fgetc(file)) != EOF)
	{
		if (ch == '\n')
		{
			lines++;
		}
	}
	printf("number of lines is: %d \n" , lines);

}

void Exit_(char* string)
{
	printf("exit!!:%s\n", string);
	exit(0);
}

int Comperssion(struct operation this_struct, char * str_to_cmp)
{
	
	if(!(strcmp(str_to_cmp, this_struct.string)))	
	{
		this_struct.operation(str_to_cmp);
		return 0;
	}
	else 
	{
		return (1);
	} 

}


FILE *OpenFile(char str[])
{
	FILE * file;
	file = fopen(str, "w+");	
	return (file);
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
	
	struct print_me arr_of_struct[4] = {0};
	
	while(i < 4)
	{
	
		arr_of_struct[i].num = i;
		arr_of_struct[i].ptr_func = print;
		arr_of_struct[i].ptr_func(arr_of_struct[i].num);	
		i++;

	}
	
	return 0;
}


int phase2(char name[])
{ 
	int i = 0; 
	int number_of_commands = 3;
	char str_to_cmp[100] = {0};
	int status = 0;
	struct operation arr_of_struct[5] = {{"-remove" , Comperssion ,Remove_},{"-count" , Comperssion ,Count_},
					     {"-exit" , Comperssion ,Exit_}};
	file_name = name;

	file = OpenFile(file_name); 	
	
	while(1)
	{
		printf("please enter text: [100 chars max]:\n");
		i = scanf("%s", str_to_cmp);
		if(i)
		{
			for(i=0; i< number_of_commands ; i++)
			{
				
				status = arr_of_struct[i].comperssion(arr_of_struct[i], str_to_cmp);
				if (!status) 
				{
					break;
				}	
			}
			if (status) 
			{
				add_(str_to_cmp);
			}
		}
		
	}
	return 0;
}

