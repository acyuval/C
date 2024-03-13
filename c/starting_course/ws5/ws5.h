/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Igal
*	Date:      
******************************************************************************/

#ifndef __WS5_H__
#define __WS5_H__

int InitStruct();

void print(int num);

/******************************************************************************
*	descrption: this is the main function of the notepad simulator
		   -needs to recive file name as argument as program start! 
*		   - Enter text to write to file or
	           - use command (-remove/-count/-exit/<)
*	note:      - undefined behavior- when input is more then 100 char! 
******************************************************************************/

int notepad_sim(char name[]);


#endif /*	WS5_H        	*/
