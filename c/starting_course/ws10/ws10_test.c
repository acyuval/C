/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Artur
*	Date:      
******************************************************************************/
#include <stdio.h>  /* printf()  		       */
#include <string.h> /* memset() , memmove(), memcpy()  */

#include "ws10.h"




void TestMemSet();
void TestMemCpy();
void TestMemMove(); 

int main()
{
	TestMemMove();
	TestMemCpy();
	TestMemSet();
	
	return 0;
}



void TestMemMove()
{
	
	char src[100] = "hello i need to";
	char * dest_expected = src +5;
	char * dest = src +5;
	size_t i = 0;
	size_t n = 5;
	printf("\n----------------");
	MemMove(dest,src, n);  	
	memmove(dest_expected,src, n);  		
	
	printf("\nTestMemMove:    \n");	
	for(i=0 ; i < n; i++)
	{
		if(*(dest+i) != *(dest_expected+i))
		{
			printf("not match in i:%ld", i);
			
		}
	}
	
	if (i == n)
	{
		printf("TestMemMove Succsess!\n\n");
	}
	printf("\n--------------");
}


void TestMemSet()
{
	int c = 'a'; 
	size_t i = 0;
	char dest[100] = {0};
	char dest_expected[100] = {0};
	size_t n = 14;
	
	MemSet(dest , c , n);
	memset(dest_expected , c , n);  	
	
	printf("\nTestMemSet:    \n");
	for(i=0 ; i < n; i++)
	{
		if(*(dest+i) != *(dest_expected+i))
		{
			printf("not match in i:%ld", i);
			
		}
	}
	
	if (i == n)
	{
		printf("TestMemSet Succsess!\n\n");
	}
	printf("\n--------------");
	

}


void TestMemCpy()
{
	
	char * src = "hello i need";
	char dest[100] = {0};
	char dest_expected[100] = {0};
	size_t i = 0;
	size_t n = 13;
	
	
	MemCpy(dest,src, n); 
	memcpy(dest_expected,src, n);
	
	printf("\n----------------");
	printf("\nTestMemCpy:    \n");	
	for(i=0 ; i < n; i++)
	{
		if(*(dest+i) != *(dest_expected+i))
		{
			printf("not match in i:%ld", i);
			
		}
	}
	
	if (i == n)
	{
		printf("TestMemCpy Succsess!\n\n");
	}
	printf("\n--------------");
	
}


