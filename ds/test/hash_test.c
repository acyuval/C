#include <assert.h> /*assert*/
#include <stdio.h> /*printf*/
#include <stdlib.h>
#include <string.h>

#include "utiles.h"
#include "hash.h"

#define DIC_SIZE (104384)





/******************************************************************************
 *							 DECLRATION								  *
 ******************************************************************************/

hash_t * CreateHashDic();
static void TestHelper(int booll , char * calling_function, int test_no);
size_t Hash(void *data);
void simpleTests();
int is_match(void * iter_data, void * to_match);
void Scan(hash_t * hash);
void FreeBuffers(char ** buffers);
int act_func(void * arg1 ,void * arg2);
/******************************************************************************
 *							 FUNCTIONS 										  *
 ******************************************************************************/
int main(void)
{

	char * buffers[DIC_SIZE] = {NULL};
	hash_t * hash = CreateHashDic(buffers);
	simpleTests();
	Scan(hash);
	FreeBuffers(buffers);
	HashDestroy(hash);

	return(0);
}


void simpleTests()
{
	size_t i = 0; 
	int counter = 0;
	char word[3][10] = {"hello", "world", "bye"};

	hash_t *hash = HashTableCreate(Hash, 200000 , is_match);
	TestHelper(TRUE == HashIsEmpty(hash), "Test is empty", 1);
	for(i = 0 ; i < 3 ; ++i)
	{
		HashInsert(hash, &word[i]);
	}

	TestHelper(FALSE == HashIsEmpty(hash), "Test is empty", 1);
	TestHelper(3 == HashSize(hash), "Test size", 1);
	
	HashForEach(hash, act_func, &counter);

	HashRemove(hash , (void *)word[2]);
	TestHelper(2 == HashSize(hash), "Test size", 2);
	counter = 0;
	HashForEach(hash, act_func, &counter);

	HashDestroy(hash);

}

void FreeBuffers(char ** buffers)
{
	size_t i = 0; 
	for(i = 0 ; i <= DIC_SIZE ; ++i)
	{
		free(buffers[i]);
	}
}





hash_t * CreateHashDic(char ** buffers)
{
	FILE * file = fopen("/usr/share/dict/american-english" , "r");
	int i = 0;
	void * return_Val = &i;

	size_t counter = 0; 
	char * this_buf = NULL;
	hash_t *hash = HashTableCreate(Hash, 200000 , is_match);

	if(NULL == file)
	{
		printf("\ncould not open file\n");
	}
	

	while(return_Val != NULL && counter < (DIC_SIZE+1))
	{
		buffers[counter] = (char *)malloc(20);
		return_Val = fgets(buffers[counter], 20, file);
		++counter;
		
	}

	i = 0; 
	while(i < DIC_SIZE)
	{
		this_buf = buffers[i];
		this_buf[strlen(this_buf)-1] = '\0';
		HashInsert(hash, this_buf);
		i++;
	}
	fclose(file);


	return hash;

}

int is_match(void * iter_data, void * to_match)
{
	return (strcmp((char *)iter_data, (char *)to_match) == 0);
}


size_t Hash(void *data)
{
    size_t h = 24361; /* you can play with this to get varying result */
    size_t bucket_amount = 200000; /* change this to whatever fits you */
    char *str = (char *)data;
    
    for (; '\0' != *str; ++str) 
    {
        h ^= *str;
        h *= 0x5bd1e995;
        h ^= h >> 15;
    }
    return h % bucket_amount;
}

void Scan(hash_t * hash)
{
	char get[20] = "";
	char * res = NULL;

	printf("\nput word : \n");
	while(strcmp(get, "quit"))
	{
		scanf("%s", get);
		res = (char *)HashFind(hash, &get);
		if (res != NULL)
		{
			printf("%s is a word!\n", res);
		}
		else
		{
			printf("Not in the dic\n");
		}
	}
}


int act_func(void * arg1 ,void * arg2)
{
    
	printf("%d- %s\n", *(int *)arg2 , (char *)arg1);
	
	*(int *)arg2 += 1;

	return 0;

}





static void TestHelper(int booll , char * calling_function, int test_no)
{
	if(booll)
	{
		printf("%s -> \t\tNO.%d success!\n\n",calling_function, test_no);
	}
	else
	{
		printf("failed in %s, No. %d\n",calling_function ,test_no);
	}
}
