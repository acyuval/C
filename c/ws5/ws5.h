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

/* this struct is made to preform chain of responsbility design! */
struct operation 
{
	char * string;
	int (*comperssion)(struct operation, char *);
	enum fun_stat (*operation)(char*, FILE*, char *, char *);	
};

int InitStruct();

void print(int num);

/* this is the main function of the notepad simulator, needs to recive file name as argument as program start! */
int notepad_sim(char name[]);
	
int Comperssion(struct operation , char *  , char * );

FILE *OpenFile(char str[]);

enum fun_stat add_(char*, char *);

enum fun_stat Remove_(char*, char *);

enum fun_stat Count_(char*, char *);

enum fun_stat Exit_(char*, char *);






#endif /*	WS5_H        	*/
