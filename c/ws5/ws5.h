/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Igal
*	Date:      
******************************************************************************/

#ifndef __WS5_H__
#define __WS5_H__

enum fun_stat 
{
  failed,
  success
}; 

typedef void (*ptr_to_func)(char[]);

struct operation 
{
	char * string;
	int (*comperssion)(struct operation, char *);
	enum fun_stat (*operation)(char*);	
};

int InitStruct();

void print(int num);

/* this is the main function of the notepad simulator, needs to recive file name as argument as program start! */
int notepad_sim(char file_name[]);
	
int Comperssion(struct operation this_struct, char * str_to_cmp);

FILE *OpenFile(char str[]);

enum fun_stat add_(char* string);

enum fun_stat Remove_(char* string);

enum fun_stat Count_(char* string);

enum fun_stat Exit_(char* string);

int Comperssion(struct operation this_struct, char * str_to_cmp);




#endif /*	WS5_H        	*/
