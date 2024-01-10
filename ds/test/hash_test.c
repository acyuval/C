#include <assert.h> /*assert*/
#include <stdio.h> /*printf*/
#include <stdlib.h>
#include <string.h>


#include "hash.h"






/******************************************************************************
 *							 DECLRATION								  *
 ******************************************************************************/

void LoadDic();

size_t Hash(void *data);
void simpleTest();
int is_match(void * iter_data, void * to_match);
/******************************************************************************
 *							 FUNCTIONS 										  *
 ******************************************************************************/
int main(void)
{
	simpleTest();
	/*
	LoadDic();
	*/
	return(0);
}


void simpleTest()
{
	size_t i = 0; 

	char word[3][10] = {"hello", "world", "bye"};

	hash_t *hash = HashTableCreate(Hash, 5 , is_match);

	for(i = 0 ; i < 3 ; ++i)
	{
		HashInsert(hash, &word[i]);
	}

}



void LoadDic()
{
	FILE * file = fopen("/usr/share/dict/american-english" , "r");
	char ch = 0;
	void * return_Val = NULL;
	int char_runner = 0;
	size_t counter = 0; 
	char word[20] = {"\0"};
	
	if(NULL == file)
	{
		printf("\ncould not open file\n");
	}
	
	return_Val = fgets(word, 20, file);
	while(return_Val != NULL)
	{
		return_Val = fgets(word, 20, file);
		++char_runner;
		char_runner = 0; 	
		++counter;
	}

	rewind(file);


}

int is_match(void * iter_data, void * to_match)
{
	return (strcmp((char *)iter_data, (char *)to_match) == 0);
}


size_t Hash(void *data)
{
    size_t h = 24361; /* you can play with this to get varying result */
    size_t bucket_amount = 5; /* change this to whatever fits you */
    char *str = (char *)data;
    
    for (; '\0' != *str; ++str) 
    {
        h ^= *str;
        h *= 0x5bd1e995;
        h ^= h >> 15;
    }
    return h % bucket_amount;
}