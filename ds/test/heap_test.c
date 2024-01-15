#include <stdio.h>

#include "heap.h"


void Test(int check);
void TestHeapPush();
void TestHeapPop();
void TestHeapPeek();
void TestHeapRemove();
void TestHeapSize();
void TestHeapIsEmpty();


int main()
{
    TestHeapPush();
    TestHeapPop();
    TestHeapPeek();
    TestHeapRemove();
    TestHeapSize();
    TestHeapIsEmpty();
    
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

int IntCmp(void *num2, void * num1)
{
    return (*(int *)num1 - *(int *)num2);
}

int IsMatchInt(void *num1, void *num2)
{
    return(*(int *)num1 == *(int *)num2);
}

void TestHeapPush()
{
    heap_t *heap = HeapCreate(IntCmp);
    int arr[5] = {1, 2, 3, 5, 4};
    
    printf("\ntesting HeapPush\n");
    
    HeapPush(heap, &arr[0]);
    Test(1 == *(int *)HeapPeek(heap));
    HeapPush(heap, &arr[1]);
    Test(2 == *(int *)HeapPeek(heap));
    HeapPush(heap, &arr[2]);
    Test(3 == *(int *)HeapPeek(heap));
    HeapPush(heap, &arr[3]);
    Test(5 == *(int *)HeapPeek(heap));
    HeapPush(heap, &arr[4]);
    Test(5 == *(int *)HeapPeek(heap));

    HeapDestroy(heap);
}

void TestHeapPop()
{
    heap_t *heap = HeapCreate(IntCmp);
    int arr[6] = {1, 2, 3, 5, 4,20};
    size_t i = 0;
    
    printf("\ntesting HeapPop\n");

    for (i = 0; i < 6; ++i)
    {
        HeapPush(heap, &arr[i]);
    }
    
    Test(20 == *(int *)HeapPeek(heap));
    HeapPop(heap);
    Test(5 == *(int *)HeapPeek(heap));
    HeapPop(heap);
    Test(4 == *(int *)HeapPeek(heap));
    HeapPop(heap);
    Test(3 == *(int *)HeapPeek(heap));
    
    HeapDestroy(heap);
}

void TestHeapPeek()
{
    heap_t *heap = HeapCreate(IntCmp);
    int arr[20] = {15, 11, -5, 71, 31,
                   12, 41, -2, 3, 4,
                   5, 66, 99, 88, 77,
                   -30, -31, -32, 33, 200};
    size_t i = 0;
    
    printf("\ntesting HeapPeek\n");

    for (i = 0; i < 20; ++i)
    {
        HeapPush(heap, &arr[i]);
    }
    
    Test(200 == *(int *)HeapPeek(heap));
    HeapPop(heap);
    Test(99 == *(int *)HeapPeek(heap));
    HeapPop(heap);
    Test(88 == *(int *)HeapPeek(heap));
    HeapPop(heap);
    Test(77 == *(int *)HeapPeek(heap));
    HeapPop(heap);
    Test(71 == *(int *)HeapPeek(heap));

    HeapDestroy(heap);
}

void TestHeapRemove()
{
    heap_t *heap = HeapCreate(IntCmp);
    int arr[20] = {15, 11, -5, 71, 31,
                   12, 41, -2, 3, 4,
                   5, 66, 99, 88, 77,
                   -30, -31, -32, 33, 200};
    size_t i = 0;
    
    printf("\ntesting HeapRemove\n");

    for (i = 0; i < 20; ++i)
    {
        HeapPush(heap, &arr[i]);
    }
    
    HeapRemove(heap, IsMatchInt, &arr[19]);
    Test(99 == *(int *)HeapPeek(heap));
    HeapRemove(heap, IsMatchInt, &arr[13]);
    Test(99 == *(int *)HeapPeek(heap));
    HeapRemove(heap, IsMatchInt, &arr[12]);
    Test(77 == *(int *)HeapPeek(heap));
    HeapRemove(heap, IsMatchInt, &arr[0]);
    Test(77 == *(int *)HeapPeek(heap));

    HeapDestroy(heap);
}

void TestHeapSize()
{
    heap_t *heap = HeapCreate(IntCmp);
    int arr[20] = {15, 11, -5, 71, 31,
                   12, 41, -2, 3, 4,
                   5, 66, 99, 88, 77,
                   -30, -31, -32, 33, 200};
    size_t i = 0;
    
    printf("\ntesting HeapSize\n");

    for (i = 0; i < 20; ++i)
    {
        HeapPush(heap, &arr[i]);
    }
    
    HeapRemove(heap, IsMatchInt, &arr[0]);
    Test(19 == HeapSize(heap));
    HeapRemove(heap, IsMatchInt, &arr[3]);
    Test(18 == HeapSize(heap));
    HeapRemove(heap, IsMatchInt, &arr[5]);
    Test(17 == HeapSize(heap));
    HeapRemove(heap, IsMatchInt, &arr[11]);
    Test(16 == HeapSize(heap));

    HeapDestroy(heap);
}

void TestHeapIsEmpty()
{
    heap_t *heap = HeapCreate(IntCmp);
    int arr[2] = {15, 11};
    
    printf("\ntesting HeapIsEmpty\n");

    Test(1 == HeapIsEmpty(heap));
    HeapPush(heap, &arr[0]);
    Test(0 == HeapIsEmpty(heap));
    HeapPush(heap, &arr[1]);
    Test(0 == HeapIsEmpty(heap));
    HeapPop(heap);
    HeapPop(heap);
    Test(1 == HeapIsEmpty(heap));

    HeapDestroy(heap);

    printf("\n");
}