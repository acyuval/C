/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/
#include <stdio.h>  /* printf()  	  */
#include <assert.h> /* assert			  */
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "shuffle_and_sort.h"

#define TEST_SIZE (8)
#define NUM_OF_DIC (4)
/******************************************************************************
*							TYPE DEFS / MACROS 								  * 
******************************************************************************/



/******************************************************************************
*							FUNCTION DECALARATION								  * 
******************************************************************************/


void TestMTSort();
int compare(const void * a ,const void * b);
char * CreateDic(size_t *char_counter, size_t *words_counter, char *** ret);
int comparator2(const void * arg1,const void * arg2);
/******************************************************************************
*							MAIN											  * 
******************************************************************************/

	
int main()
{
	srand(time(NULL));
	TestMTSort();
	return (0);
}




/******************************************************************************
*							TEST FUNCTIONS									  * 
******************************************************************************/

void TestMTSort()
{

	size_t i = 0;
	int this_test = 0; 
	int threads_amount = 0;
	size_t char_counter = 0; 
	size_t words_counter = 0; 
	char *char_buffer = NULL;
	char **full_words_arr = NULL;
	char **word_buffer = NULL;
	clock_t start = 0;
	clock_t end = 0;
	
	char_buffer = CreateDic(&char_counter, &words_counter, &word_buffer);

	full_words_arr = calloc(NUM_OF_DIC * words_counter,sizeof(size_t));
	if(full_words_arr == NULL)
	{
		return;
	}

	for (i =0 ; i < NUM_OF_DIC; ++i)
	{
		memcpy(&full_words_arr[i * words_counter], word_buffer, words_counter*sizeof(size_t));
	}
	free(word_buffer);

 	qsort(full_words_arr, words_counter*NUM_OF_DIC, sizeof(size_t) , compare);

	threads_amount = 1;
 	for(this_test = 0 ; this_test < TEST_SIZE*2 ; this_test+=2)
	{
		start = clock();
		SortAndMerge(full_words_arr, words_counter*NUM_OF_DIC, threads_amount);
		end = clock();
		for (i = 0 ; i <  words_counter*NUM_OF_DIC -1; ++i)
		{
			if(strcmp(full_words_arr[i], full_words_arr[i+1]) > 0)
			{
				printf("failed \n");
				printf("%s - vs %s\n" ,full_words_arr[i] , full_words_arr[i+1] );
			}
		}
		if (i >= words_counter-1)
		{
			printf("num of thread %d at time %f \n", threads_amount, ((double)(end-start))/CLOCKS_PER_SEC);
		}
		qsort(full_words_arr, words_counter*NUM_OF_DIC, sizeof(size_t) , compare);
		threads_amount = (this_test+2);
	}

	
	free(char_buffer);
	free(full_words_arr);
}


/******************************************************************************
*							STATIC FUNCTIONS								  * 
******************************************************************************/



char * CreateDic(size_t *char_counter, size_t *words_counter, char *** ret)
{
	size_t i = 0 , j = 0;
	char c = 0 ;
	char * buffer = NULL;
	FILE * file = fopen("/usr/share/dict/american-english" , "r");
	char ** word_buffer = NULL;
	if(NULL == file)
	{
		return NULL;
	}

 	while(c != EOF)
	{
		c = fgetc(file);
		if (!isspace(c))
		{
			++(*char_counter);
		}
		if (c == '\n')
		{
			++(*char_counter);
			++(*words_counter);
		}
	}
	
	fseek(file, 0 ,SEEK_SET);

	buffer = calloc((*char_counter) , sizeof(char));
	if (buffer == NULL)
	{
		printf("error\n\n\n");
		return NULL;
	} 
	word_buffer = (char **)calloc((*words_counter) , sizeof(size_t));
	if (word_buffer == NULL)
	{
		printf("error\n\n\n");
		return NULL;
	} 

	fseek(file, 0 ,SEEK_SET);
	c = fgetc(file);
	while(c != EOF)
	{
		c = fgetc(file);
		if(c == '\n')
		{
			buffer[j] = '\0';
			++j;
			word_buffer[i]	= &buffer[j] ;
			++i;
		}
		else if (!isspace(c))
		{
			buffer[j] = c;
			++j;
		}
	}
	fclose(file);
	
	*ret = word_buffer;
	return buffer;

}


int compare(const void * a ,const void * b)
{
	(void)a;
	(void)b;
	return ((rand()%2)*2)-1;
}


 
int comparator2(const void * arg1,const void * arg2)
{
    char * str1 = *(char **)arg1;
    char * str2 = *(char **)arg2;
    return strcmp(str1,str2); 
}
