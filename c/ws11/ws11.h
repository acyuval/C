/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Artur
*	Date:      
******************************************************************************/

#ifndef _WS11_H_
#define _WS11_H_


#define IS_LITTLE_ENDIAN ((*(double *)"\0\xff") < 0x0100)   

/******************************************************************************
*	description: get num as str and return same number int 
*	notes: string can start with spaces, undefined behivfer when input
*		is non digits
******************************************************************************/ 
int Atoi(const char *str);


/******************************************************************************
*	description: get num as string in any base and return an int in base 10
*	notes:	     undefined behivor when base > 36     
******************************************************************************/ 
int AtoiAnyBase(const char *str, int base);


/******************************************************************************
*	description: get num as int and return the num as string 
*	notes:	undefined behivfer when input is non digit
******************************************************************************/ 
char* Itoa(int num, char* buffer);


/******************************************************************************
*	description: get number as int and return the num in anybase as string
*	notes:	     	undefined behivfer when input is non digit
******************************************************************************/ 
char* ItoaAnyBase(int num, char* buffer, int base);


/******************************************************************************
*	description: print all numbers that are in str1 and str2 but not in str3
*	arguments: 
*	notes:	    
******************************************************************************/ 
void PrintArrOfChars(char *str1, char *str2 ,char *str3, size_t size1,
						 size_t size2, size_t size3);

/******************************************************************************
*	description: check if this system is little endian
******************************************************************************/ 
int IsLittleEndian(void);


#endif /*_WS11_*/



