#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc, free */

#include "scheduler.h"
#include "test.h"

static void TestSchedulerCreateDestroy();
static void TestSchedulerIsEmptySize();
static void TestSchedulerAdd();
static void TestSchedulerRemove();
static void TestSchedulerRemoveItself();
static void TestSchedulerRun();
static void TestSchedulerRunClear();
static void TestSchedulerStop();
static void TestSchedulerClear();

int main()
{
	TestSchedulerCreateDestroy();
	TestSchedulerIsEmptySize();
	TestSchedulerAdd();
	TestSchedulerRemove();
	TestSchedulerRemoveItself();
	TestSchedulerRun();
	TestSchedulerRunClear();
	TestSchedulerStop();
	TestSchedulerClear();

	return 0;
}

void TestSchedulerCreateDestroy()
{
	scheduler_t *scheduler = SchedulerCreate();

	TEST_START("SchedulerCreate SchedulerDestroy");

	TEST_ASSERT(NULL != scheduler);
	TEST_ASSERT(TRUE == SchedulerIsEmpty(scheduler));

	TEST_ASSERT(0 == SchedulerSize(scheduler));

	SchedulerDestroy(scheduler);

	TEST_END;
}

static int TestFunc(void *data)
{
	printf("%s\n", (char *)data);
	return NO_REPEAT;
}

struct print_alphabet
{
	char *str;
	size_t length;
};

static int TestMallocFunc(void *params)
{
	size_t i = 0;
	struct print_alphabet *test_p = (struct print_alphabet *)params;
	test_p->str = (char *)malloc(test_p->length + 1);
	for (i = 0; i < test_p->length; i++)
	{
		test_p->str[i] = 'a' + i;
	}
	test_p->str[test_p->length] = '\0';

	printf("%s\n", test_p->str);
	return NO_REPEAT;
}

static void TestClearFunc(void *params)
{
	struct print_alphabet *test_p = (struct print_alphabet *)params;
	if (NULL != test_p->str)
	{
		printf("Cleaning '%s'\n", test_p->str);
	}

	free(test_p->str);
}

void TestSchedulerIsEmptySize()
{
	scheduler_t *scheduler = SchedulerCreate();

	TEST_START("SchedulerIsEmpty SchedulerSize");

	TEST_ASSERT(TRUE == SchedulerIsEmpty(scheduler));
	TEST_ASSERT(0 == SchedulerSize(scheduler));

	SchedulerAdd(scheduler, TestFunc, "Hello!", time(NULL) + 5, 0, NULL, NULL);

	TEST_ASSERT(FALSE == SchedulerIsEmpty(scheduler));
	TEST_ASSERT(1 == SchedulerSize(scheduler));

	SchedulerDestroy(scheduler);

	TEST_END;
}

void TestSchedulerAdd()
{
	scheduler_t *scheduler = SchedulerCreate();

	TEST_START("SchedulerAdd");

	TEST_ASSERT(TRUE == SchedulerIsEmpty(scheduler));
	TEST_ASSERT(0 == SchedulerSize(scheduler));

	SchedulerAdd(scheduler, TestFunc, "Hello!", time(NULL) + 5, 0, NULL, NULL);

	TEST_ASSERT(FALSE == SchedulerIsEmpty(scheduler));
	TEST_ASSERT(1 == SchedulerSize(scheduler));

	SchedulerDestroy(scheduler);

	TEST_END;
}

void TestSchedulerRemove()
{
	ilrd_uid_t remove_uid = {0};
	struct print_alphabet test_cases[] = {{NULL, 3}, {NULL, 5}, {NULL, 7}};

	time_t now = time(NULL);
	scheduler_t *scheduler = SchedulerCreate();

	TEST_START("SchedulerRemove");

	TEST_ASSERT(TRUE == SchedulerIsEmpty(scheduler));
	TEST_ASSERT(0 == SchedulerSize(scheduler));

	SchedulerAdd(scheduler, TestMallocFunc, &test_cases[1], now + 2, 0,
				 TestClearFunc, &test_cases[1]);
	remove_uid = SchedulerAdd(scheduler, TestMallocFunc, &test_cases[2],
							  now + 3, 0, TestClearFunc, &test_cases[2]);
	SchedulerAdd(scheduler, TestMallocFunc, &test_cases[0], now + 1, 0,
				 TestClearFunc, &test_cases[0]);

	TEST_ASSERT(FALSE == SchedulerIsEmpty(scheduler));
	TEST_ASSERT(3 == SchedulerSize(scheduler));

	TEST_ASSERT(SUCCESS == SchedulerRemove(scheduler, remove_uid));

	TEST_ASSERT(FALSE == SchedulerIsEmpty(scheduler));
	TEST_ASSERT(2 == SchedulerSize(scheduler));

	TEST_ASSERT(SUCCESS == SchedulerRun(scheduler));

	SchedulerDestroy(scheduler);

	TEST_END;
}

typedef struct remove_data
{
	scheduler_t *scheduler;
	ilrd_uid_t uid;
} remove_data_t;

static int TestRemove(void *params)
{
	remove_data_t *data = (remove_data_t *)params;
	printf("Executing SchedulerRemove() on the given task\n");
	TEST_ASSERT(SUCCESS == SchedulerRemove(data->scheduler, data->uid));
	return REPEAT;
}

void TestSchedulerRemoveItself()
{
	scheduler_t *scheduler = SchedulerCreate();
	ilrd_uid_t remove_uid = {0};
	remove_data_t remove_itself = {0};

	TEST_START("SchedulerRemoveItself");

	TEST_ASSERT(TRUE == SchedulerIsEmpty(scheduler));
	TEST_ASSERT(0 == SchedulerSize(scheduler));

	SchedulerAdd(scheduler, TestFunc, "Hello!", time(NULL) + 1, 0, NULL, NULL);
	remove_uid = SchedulerAdd(scheduler, TestRemove, &remove_itself,
							  time(NULL) + 2, 1, NULL, NULL);
	remove_itself.scheduler = scheduler;
	remove_itself.uid = remove_uid;
	SchedulerAdd(scheduler, TestFunc, "Last Task exectuted after RemoveItself",
				 time(NULL) + 3, 1, NULL, NULL);

	TEST_ASSERT(FALSE == SchedulerIsEmpty(scheduler));
	TEST_ASSERT(3 == SchedulerSize(scheduler));

	TEST_ASSERT(SUCCESS == SchedulerRun(scheduler));

	TEST_ASSERT(TRUE == SchedulerIsEmpty(scheduler));
	TEST_ASSERT(0 == SchedulerSize(scheduler));

	SchedulerDestroy(scheduler);

	TEST_END;
}

void TestSchedulerRun()
{
	struct print_alphabet test_cases[] = {{NULL, 3}, {NULL, 5}, {NULL, 7}};

	time_t now = time(NULL);
	scheduler_t *scheduler = SchedulerCreate();

	TEST_START("SchedulerRun");

	TEST_ASSERT(TRUE == SchedulerIsEmpty(scheduler));
	TEST_ASSERT(0 == SchedulerSize(scheduler));

	SchedulerAdd(scheduler, TestMallocFunc, &test_cases[1], now + 2, 0,
				 TestClearFunc, &test_cases[1]);
	SchedulerAdd(scheduler, TestMallocFunc, &test_cases[2], now + 3, 0,
				 TestClearFunc, &test_cases[2]);
	SchedulerAdd(scheduler, TestMallocFunc, &test_cases[0], now + 1, 0,
				 TestClearFunc, &test_cases[0]);

	TEST_ASSERT(FALSE == SchedulerIsEmpty(scheduler));
	TEST_ASSERT(3 == SchedulerSize(scheduler));

	TEST_ASSERT(SUCCESS == SchedulerRun(scheduler));

	SchedulerDestroy(scheduler);

	TEST_END;
}

static int TestClear(void *params)
{
	scheduler_t *scheduler = (scheduler_t *)params;
	printf("Executing TestClear() as a task\n");
	SchedulerClear(scheduler);
	return REPEAT;
}

void TestSchedulerRunClear()
{
	struct print_alphabet test_cases[] = {{NULL, 3}, {NULL, 5}, {NULL, 7}};

	time_t now = time(NULL);
	scheduler_t *scheduler = SchedulerCreate();

	TEST_START("SchedulerRun a SchedulerClear task");

	TEST_ASSERT(TRUE == SchedulerIsEmpty(scheduler));
	TEST_ASSERT(0 == SchedulerSize(scheduler));

	SchedulerAdd(scheduler, TestMallocFunc, &test_cases[1], now + 2, 0,
				 TestClearFunc, &test_cases[1]);
	SchedulerAdd(scheduler, TestClear, scheduler, now + 3, 1, NULL, NULL);
	SchedulerAdd(scheduler, TestMallocFunc, &test_cases[2], now + 4, 0,
				 TestClearFunc, &test_cases[2]);
	SchedulerAdd(scheduler, TestMallocFunc, &test_cases[0], now + 1, 0,
				 TestClearFunc, &test_cases[0]);

	TEST_ASSERT(FALSE == SchedulerIsEmpty(scheduler));
	TEST_ASSERT(4 == SchedulerSize(scheduler));

	TEST_ASSERT(SUCCESS == SchedulerRun(scheduler));

	TEST_ASSERT(TRUE == SchedulerIsEmpty(scheduler));
	TEST_ASSERT(0 == SchedulerSize(scheduler));

	SchedulerDestroy(scheduler);

	TEST_END;
}

static int TestFuncRepeating(void *data)
{
	static size_t counter = 1;
	printf("%s %ld!\n", (char *)data, counter);
	++counter;
	return REPEAT;
}

static int TestStop(void *params)
{
	printf("Executing SchedulerStop()\n");
	SchedulerStop((scheduler_t *)params);
	return NO_REPEAT;
}

void TestSchedulerStop()
{
	scheduler_t *scheduler = SchedulerCreate();
	ilrd_uid_t repeating_uid = {0};
	time_t now = time(NULL);
	TEST_START("SchedulerStop");

	TEST_ASSERT(TRUE == SchedulerIsEmpty(scheduler));
	TEST_ASSERT(0 == SchedulerSize(scheduler));

	repeating_uid = SchedulerAdd(scheduler, TestFuncRepeating, "Repeating",
								 now + 1, 1, NULL, NULL);
	SchedulerAdd(scheduler, TestStop, scheduler, now + 5, 0, NULL, NULL);
	SchedulerAdd(scheduler, TestFunc, "Last Task exectuted after ScheduleStop",
				 now + 6, 1, NULL, NULL);
	TEST_ASSERT(FALSE == SchedulerIsEmpty(scheduler));
	TEST_ASSERT(3 == SchedulerSize(scheduler));

	TEST_ASSERT(STOPPED == SchedulerRun(scheduler));

	TEST_ASSERT(SUCCESS == SchedulerRemove(scheduler, repeating_uid));

	TEST_ASSERT(FALSE == SchedulerIsEmpty(scheduler));
	TEST_ASSERT(1 == SchedulerSize(scheduler));

	TEST_ASSERT(SUCCESS == SchedulerRun(scheduler));

	TEST_ASSERT(TRUE == SchedulerIsEmpty(scheduler));
	TEST_ASSERT(0 == SchedulerSize(scheduler));

	SchedulerDestroy(scheduler);

	TEST_END;
}

void TestSchedulerClear()
{
	time_t now = time(NULL);
	scheduler_t *scheduler = SchedulerCreate();

	TEST_START("SchedulerClear");

	TEST_ASSERT(TRUE == SchedulerIsEmpty(scheduler));
	TEST_ASSERT(0 == SchedulerSize(scheduler));

	SchedulerAdd(scheduler, TestFunc, "Priority 2!", now + 2, 0, NULL, NULL);
	SchedulerAdd(scheduler, TestFunc, "Priority 3!", now + 3, 0, NULL, NULL);
	SchedulerAdd(scheduler, TestFunc, "Priority 1!", now + 1, 0, NULL, NULL);
	SchedulerAdd(scheduler, TestStop, scheduler, time(NULL) + 4, 0, NULL, NULL);
	SchedulerAdd(scheduler, TestFunc, "Priority 4!", now + 6, 0, NULL, NULL);
	SchedulerAdd(scheduler, TestFunc, "Priority 5!", now + 10, 0, NULL, NULL);

	TEST_ASSERT(FALSE == SchedulerIsEmpty(scheduler));
	TEST_ASSERT(6 == SchedulerSize(scheduler));

	TEST_ASSERT(STOPPED == SchedulerRun(scheduler));

	TEST_ASSERT(FALSE == SchedulerIsEmpty(scheduler));
	TEST_ASSERT(2 == SchedulerSize(scheduler));
	printf("Tasks left before clear: %ld\n", SchedulerSize(scheduler));
	SchedulerClear(scheduler);
	printf("Tasks left after clear: %ld\n", SchedulerSize(scheduler));
	TEST_ASSERT(TRUE == SchedulerIsEmpty(scheduler));
	TEST_ASSERT(0 == SchedulerSize(scheduler));

	SchedulerDestroy(scheduler);

	TEST_END;
}
