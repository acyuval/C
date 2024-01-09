#include <assert.h> /*assert*/
#include <stdio.h> /*printf*/

#include "avl.h"

#define TRUE (1)
#define FALSE (0)

static void TestAVLCreate(void);
static void TestAVLInsert(void);
static void TestAVLFind(void);
static void TestAVLIsEmptyAndSize(void);
static void TestAVLForEach(void);
static void TestAVLHeight(void);

static int Compare(void *data1, void *data2);
static int Mult2(void *data1, void *data2);

int main(void)
{
	/*
    TestAVLCreate();
	TestAVLInsert();
    
	TestAVLFind();
	TestAVLIsEmptyAndSize();
    */
	TestAVLForEach();
    
	TestAVLHeight();
	return(0);
}

static void TestAVLCreate(void)
{
	avl_t *avl =AVLCreate(Compare);

	assert(NULL != avl);

	printf("AVLCreate: success\n");
	AVLDestroy(avl);
	printf("AVLDestory: success\n");
}

static void TestAVLInsert(void)
{
	avl_t *avl =AVLCreate(Compare);
	int arr[] = {5, 2, 8, 6, 3, 1, 10};
	size_t i = 0;

	for(i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		assert(SUCCESS == AVLInsert(avl, &arr[i]));
	}

	AVLDestroy(avl);

	printf("AVLInsert: success\n");
}
static void TestAVLFind(void)
{
	avl_t *avl =AVLCreate(Compare);
	int arr[] = {5, 2, 8, 6, 3, 1, 10};
	int num_not_fount = 11;
	size_t i = 0;

	assert(NULL == AVLFind(avl,&num_not_fount));
	for(i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		assert(SUCCESS == AVLInsert(avl, &arr[i]));
	}

	for(i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		assert(arr[i] == *(int*)AVLFind(avl, &arr[i]));
	}

	assert(NULL == AVLFind(avl,&num_not_fount));

	AVLDestroy(avl);
	printf("AVLFind: success\n");
}
static void TestAVLIsEmptyAndSize(void)
{
	avl_t *avl =AVLCreate(Compare);
	int arr[] = {5, 2, 8, 6, 3, 1, 10};
	size_t i = 0;

	assert(TRUE == AVLIsEmpty(avl));
	for(i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		assert(i == AVLSize(avl));
		assert(SUCCESS == AVLInsert(avl, &arr[i]));
	}

	assert(FALSE == AVLIsEmpty(avl));
	for(i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		
		assert(sizeof(arr) / sizeof(arr[0]) - i == AVLSize(avl));
		AVLRemove(avl, &arr[i]);
	}
	
	assert(TRUE == AVLIsEmpty(avl));
	AVLDestroy(avl);
	printf("AVLRemove: success\n");
	printf("AVLSize: success\n");
	printf("AVLIsEmpty: success\n");
}

static void TestAVLForEach(void)
{
	avl_t *avl =AVLCreate(Compare);
	int arr[] = {5, 2, 8, 6, 3, 1, 10};
	int arr_expected[] = {5, 2, 8, 6, 3, 1, 10};
	int param = 2;
	size_t i = 0;

	for(i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		assert(SUCCESS == AVLInsert(avl, &arr[i]));
	}

	assert(SUCCESS == AVLForEach(avl, IN_ORDER, Mult2, &param));

	for(i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		assert(arr[i] == arr_expected[i] * 2);
	}

	assert(SUCCESS == AVLForEach(avl, POST_ORDER, Mult2, &param));

	for(i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		assert(arr[i] == arr_expected[i] * 4);
	}

	assert(SUCCESS == AVLForEach(avl, PRE_ORDER, Mult2, &param));

	for(i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		assert(arr[i] == arr_expected[i] * 8);
	}

	AVLDestroy(avl);
	printf("AVLForEach: success\n");
}

static void TestAVLHeight(void)
{
	avl_t *avl =AVLCreate(Compare);
	int arr[] = {5, 2, 8, 6, 3, 1, 10};
	size_t i = 0;

	assert(0 == AVLHeight(avl));
	for(i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
	{
		assert(SUCCESS == AVLInsert(avl, &arr[i]));
	}

	assert(3 == AVLHeight(avl));

	AVLDestroy(avl);
	printf("AVLHeight: success\n");
}

static int Mult2(void *data1, void *data2)
{
	*(int*)data1 *= *(int*)data2;
	return(SUCCESS);
}

static int Compare(void *data1, void *data2)
{
	return(*(int*)data1 - *(int*)data2);
}