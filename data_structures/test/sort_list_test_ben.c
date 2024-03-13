
/****************************************************************************
 * Author: Ben Naori
 * Reviewer:
 * Date: --/--/2023
 ****************************************************************************/

#include <stdio.h> /* printf */

#include "sort_list.h"

#define TRUE 1
#define FALSE 0

#define PRINT_FAIL(fname) printf("Function %s Failed\n", fname)
#define PRINT_SUCCESS(fname) printf("Function %s Succeded\n", fname)

typedef enum code
{
	FAILIURE = -1,
	SUCCESS = 0
} code_t;

void TestSortedList(void);

int main(void)
{
	TestSortedList();
	return (0);
}


void InitArr(int *arr, size_t size, int init, int step)
{
	while (size--)
	{
		*arr = init;
		init += step;
		++arr;
	}
}

static int PrintElement(void *num, void *params)
{
	(void)params;
	
	printf("%d\n", *(int *)num);
	return (SUCCESS);
}

static int IntCmp(void *num1, void *num2)
{
	return (*(int *)num1 - *(int *)num2);
}

static int IsEven(void *num, void *trash)
{
	(void)trash;
	return ((*(int *)num % 10) == 0);
}

int TestInsert(sorted_list_t *list, int *arr, size_t size)
{
	sorted_iter_t iter = {0};

	while (size--)
	{
		iter = SortedListInsert(list, arr);
		
		if (*arr != *(int *)SortedListGetData(iter))
		{
			PRINT_FAIL("Insert");
			return (FAILIURE);
		}
		
		++arr;
	}
	
	PRINT_SUCCESS("Insert");
	return (SUCCESS);
}

int TestRemove(sorted_list_t *list, size_t size)
{
	sorted_iter_t iter = SortedListBegin(list);
	
	while (size--)
	{
		iter = SortedListRemove(iter);
	}
	
	PRINT_SUCCESS("Remove");
	return (SUCCESS);
}

int TestSize(sorted_list_t *list, size_t expected)
{
	if (expected != SortedListSize(list))
	{
		PRINT_FAIL("Size");
		return (FAILIURE);
	}
	
	PRINT_SUCCESS("Size");
	return (SUCCESS);
}

int TestIsEmpty(sorted_list_t *list, int expected)
{
	if (expected != SortedListIsEmpty(list))
	{
		PRINT_FAIL("IsEmpty");
		return (FAILIURE);
	}
	
	PRINT_SUCCESS("IsEmpty");
	return (SUCCESS);
}

int TestForEach(sorted_list_t *list)
{
	SortedListForEach(SortedListBegin(list), SortedListEnd(list), PrintElement, NULL);
	
	PRINT_SUCCESS("ForEach");
	return (SUCCESS);
}

int TestFind(sorted_list_t *list, int val)
{
	sorted_iter_t iter = SortedListFind(SortedListBegin(list), SortedListEnd(list), &val, list);
	if (!SortedListIsEqual(SortedListEnd(list), iter))
	{
		printf("Found: %d\n", val);
	}
	else
	{
		printf("didnt Find: %d\n", val);
	}
	
	PRINT_SUCCESS("Find");
	return (SUCCESS);
}

int TestFindIf(sorted_list_t *list)
{
	sorted_iter_t iter = SortedListFindIf(SortedListBegin(list), SortedListEnd(list), IsEven, NULL);
	if (!SortedListIsEqual(SortedListEnd(list), iter))
	{
		printf("Found: %d\n", *(int *)SortedListGetData(iter));
	}
	else
	{
		printf("didnt Find: %d\n", *(int *)SortedListGetData(iter));
	}
	
	PRINT_SUCCESS("Find If");
	return (SUCCESS);
}

int TestMerge(sorted_list_t *list1, sorted_list_t *list2)
{
	printf("\nlist1 before\n");
	SortedListForEach(SortedListBegin(list1), SortedListEnd(list1), PrintElement, NULL);
	printf("\nlist2 before\n");
	SortedListForEach(SortedListBegin(list2), SortedListEnd(list2), PrintElement, NULL);

	SortedListMerge(list1, list2);
	
	printf("\nlist1 after\n");
	SortedListForEach(SortedListBegin(list1), SortedListEnd(list1), PrintElement, NULL);
	printf("\nlist2 after\n");
	SortedListForEach(SortedListBegin(list2), SortedListEnd(list2), PrintElement, NULL);

	PRINT_SUCCESS("Merge");
	return (SUCCESS);
}

int TestGetData(sorted_list_t *list, int *arr, int from, int to, int step)
{
	sorted_iter_t iter = SortedListBegin(list);
	int pos = 0;
	
	for (pos = from; pos * step <= to * step; pos += step)
	{
		/*printf("string is: [%s]\n", (char *)DLLGet(iter));*/
		
		if (*(int *)SortedListGetData(iter) != arr[pos])
		{
			PRINT_FAIL("Get");
			printf("error: %d\n", *(int *)SortedListGetData(iter));
			printf("error: %d\n", arr[pos]);
			return (FAILIURE);
		}
		
		iter = SortedListNext(iter);
	}
	
	PRINT_SUCCESS("Get");
	return (SUCCESS);
}

int TestPopBackAndFront(sorted_list_t *list)
{
	SortedListPopFront(list);
	SortedListPopBack(list);
	
	PRINT_SUCCESS("Pops");
	return (SUCCESS);
}

void TestSortedList(void)
{	
	int arr1[11];
	int arr2[11];
	int res = 0;
	
	sorted_list_t *list1 = SortedListCreate(IntCmp);
	sorted_list_t *list2 = SortedListCreate(IntCmp);
	
	InitArr(arr1, 11, -25, 5);
	InitArr(arr2, 13, -18, 3);
	
	res |= TestInsert(list1, arr1, 11);
	res |= TestInsert(list2, arr2, 13);
	
	res |= TestPopBackAndFront(list2);
	
	res |= TestSize(list1, 11);
	res |= TestIsEmpty(list1, FALSE);
	
	res |= TestGetData(list1, arr1, 0, 10, -1);
	
	res |= TestForEach(list1);
	res |= TestForEach(list2);
	
	res |= TestFind(list1, -5);
	res |= TestFind(list1, 5);
	res |= TestFind(list1, -2);
	res |= TestFind(list1, -7984634);
	
	res |= TestFindIf(list1);
	
	res |= TestMerge(list1, list2);
	res |= TestSize(list1, 22);
	
	res |= TestRemove(list1, 11);
	res |= TestSize(list1, 11);
	res |= TestRemove(list1, 11);
	res |= TestSize(list1, 0);
	res |= TestIsEmpty(list1, TRUE);
	
	if (SUCCESS == res)
	{
		PRINT_SUCCESS("All");
	}
	else
	{
		PRINT_FAIL("Some Function");
	}
	
	SortedListDestroy(list1);
	SortedListDestroy(list2);
}






