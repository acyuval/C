/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Artur
*	Date:      
******************************************************************************/

#include <stdio.h>  /* printf */
#include <string.h> /* strlen */
#include <stdlib.h> /* malloc */

#include "ws8.h"


#define NO_elements 3


enum data_types 
{
	INTT = 0,
	FLOATT = 1,
	STRINGG = 2
};

typedef struct items
{ 
	enum data_types type;
	size_t data;
	void (*op_print)(size_t);
	void (*op_add)(size_t *, int);
	int (*op_clean)(size_t *);	
}data_struct;
 
 	  
size_t PutInt(int num)
{
	return ((size_t)num);
}

size_t PutFloat(float any_float)
{
	return (*((size_t *)&any_float));
}

size_t PutStr(char * str)
{
	size_t str_len = strlen(str);
	char *str_cpy = (char *)malloc((str_len+1)*sizeof(char));
	
	if (NULL == str_cpy)
	{
		return (size_t)NULL;
	}
	
	strcpy(str_cpy, str);	
	return ((size_t)str_cpy);
}

void PrintInt(size_t num)
{
	printf("%ld\n", num);
}

void PrintStr(size_t str)
{
	printf("%s\n", (char *)(str));
}

void PrintFloat(size_t fnum)
{
	printf("%f\n", *(float *)&(fnum));
}

void AddInt(size_t * num, int added_value)
{
	*num += (size_t)added_value;
}

void AddFloat(size_t * num, int added_value)
{
	*(float *)num += (float)added_value;
}

void AddStr(size_t * data, int added_value)
{
	size_t str_len = strlen((char *)data);
	char add_str[100] = {0};
	size_t added_chars_No = 0;
	size_t new_str_len = 0;
	char * new_str = (char *)*data;
	
	if(!sprintf(add_str, "%d", added_value))
	{
		printf("failed to sprintf");
		return;
	}
	
	added_chars_No = strlen(add_str);
	new_str_len = str_len + added_chars_No +1;
	new_str = (char *)*data;
	*data = (size_t)(char *)realloc(new_str,(new_str_len + 1));
	
	if (NULL == new_str)
	{
		printf("failed to allocate");
		return ;
	}
	
	if(!sprintf(new_str, "%s%s", (char *)*(data) , add_str))
	{
		printf("failed to sprintf");
		return;
	}	
}

int CleanStr(size_t * str)
{
	free((void *)*str);
	return 0;
}

int CleanNULL(size_t * num)
{
	(void)num;
	
	return 0;	
}


 
void MultiDataTypeArr(){
	int i = 0;
	
	data_struct struct_arr[NO_elements] = {{0},{0},{0}};
	
	struct_arr[0].type =INTT;
	struct_arr[0].data = PutInt(-5);
	struct_arr[0].op_print = PrintInt;
	struct_arr[0].op_add = AddInt;
	struct_arr[0].op_clean = CleanNULL; 
	
	struct_arr[1].type = FLOATT;
	struct_arr[1].data = PutFloat(4.123);
	struct_arr[1].op_print = PrintFloat;
	struct_arr[1].op_add = AddFloat;
	struct_arr[1].op_clean = CleanNULL; 	
	
	struct_arr[2].type =STRINGG;
	struct_arr[2].data = PutStr("hello");
	struct_arr[2].op_print = PrintStr;
	struct_arr[2].op_add = AddStr;
	struct_arr[2].op_clean = CleanStr; 
	
	printf("\nPrint:\n");
	for(i = 0; i < NO_elements ; i++)
	{
		struct_arr[i].op_print(struct_arr[i].data);
	}
	
	printf("\nAdd:\n");
	for(i = 0; i < NO_elements ; i++)
	{
		struct_arr[i].op_add(&struct_arr[i].data,1);
	}
	
	printf("\nPrint again:\n");
	for(i = 0; i < NO_elements ; i++)
	{
		struct_arr[i].op_print(struct_arr[i].data);
	}
	
	for(i = 0; i < NO_elements ; i++)
	{
		struct_arr[i].op_clean(&struct_arr[i].data);
	}
	
	printf("\nCleaned!\n");	
	
}
