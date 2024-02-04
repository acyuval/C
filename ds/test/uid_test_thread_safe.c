#include <stdio.h> /* printf */
#include <pthread.h>

#include "uid.h"


void Test(int check);
void PrintUID(ilrd_uid_t uid);
void TestUIDCreate();
void TestUIDIsEqual();
void TestUIDThreads();


int main()
{
	TestUIDCreate();
	TestUIDIsEqual();
	TestUIDThreads();

	return (0);
}


void Test(int check)
{
	if (0 == check)
	{
		printf("--------failure\n");
	}
	
	else
	{
		printf("success\n");
	}
}

void PrintUID(ilrd_uid_t uid)
{
	printf("counter: %ld\nPID: %d\ntimestamp: %ld\nIPV4 addr: %s\n",
			uid.counter, uid.pid, uid.time, uid.ip);
}

void TestUIDCreate()
{
	ilrd_uid_t new_uid_1 = UIDCreate();
	ilrd_uid_t new_uid_2 = UIDCreate();
	
	printf("testing UIDCreate. first uid:\n");
	PrintUID(new_uid_1);
	printf("\nsecond uid:\n");
	PrintUID(new_uid_2);
}

void TestUIDIsEqual()
{
	ilrd_uid_t new_uid_1 = UIDCreate();
	ilrd_uid_t new_uid_2 = UIDCreate();
	
	printf("\ntesting UIDIsEaual\n");
	
	Test(1 == UIDIsEqual(new_uid_1, new_uid_1));
	Test(1 == UIDIsEqual(new_uid_2, new_uid_2));
	Test(0 == UIDIsEqual(new_uid_1, new_uid_2));
	
	printf("\n");
}

void *CreateUid(void *arg)
{
	*(ilrd_uid_t *)arg = UIDCreate();

	return (NULL);
}

void TestUIDThreads()
{
	pthread_t threads[100];
	ilrd_uid_t uid[100] = {0};
	int i = 0;
	
	for(i = 0; i < 100; ++i)
	{
		pthread_create(&threads[i], NULL, CreateUid, &uid[i]);
	}

	for(i = 0; i < 100; ++i)
	{
		pthread_join(threads[i], NULL);
	}

	printf("testing UIDCreate with threads\n");
	for(i = 0; i < 100; ++i)
	{
		printf("%lu ", uid[i].counter);
	}
	printf("\n");
}





























