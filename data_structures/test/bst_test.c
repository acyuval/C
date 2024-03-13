#include <stdio.h>

#include "../include/bst.h"

void Test(int check);
void TestBSTInsert();
void TestBSTFind();
void TestBSTRemove();
void TestBSTGetData();
void TestBSTIsEmpty();
void TestBSTSize();
void TestBSTIsEqual();
void TestBSTBegin();
void TestBSTEnd();
void TestBSTNext();
void TestBSTPrev();
void TestBSTForEach();

int main()
{
    TestBSTInsert();
    TestBSTFind();
    TestBSTRemove();
    TestBSTGetData();
    TestBSTIsEmpty();
    TestBSTSize();
    TestBSTIsEqual();
    TestBSTBegin();
    TestBSTEnd();
    TestBSTNext();
    TestBSTPrev();
    TestBSTForEach();

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

int IntCmp(void * num1,void *num2)
{
    return (*(int *)num1 - *(int *)num2);
}

void TestBSTInsert()
{
    bst_t *bst = BSTCreate(IntCmp);
    int arr[10] = {7, 6, 8, 3, 1, 9, 2, 0, 4, 5};
    int i = 0;
    bst_iter_t runner = NULL;

    printf("\ntesting BSTInsert\n");

    for (i = 0; i < 10; ++i)
    {
        BSTInsert(bst, &arr[i]);
    }

    runner = BSTBegin(bst);

    Test(0 == *(int *)BSTGetData(runner));
    runner = BSTNext(runner);
    Test(1 == *(int *)BSTGetData(runner));
    runner = BSTNext(runner);
    Test(2 == *(int *)BSTGetData(runner));
    runner = BSTNext(runner);
    Test(3 == *(int *)BSTGetData(runner));
    Test(10 == BSTSize(bst));

    BSTDestroy(bst);
}

void TestBSTFind()
{
    bst_t *bst = BSTCreate(IntCmp);
    int arr[9] = {41, 35, 6878, 23, 31, 12, 67, 11, -3};
    int check1 = -3;
    int check2 = 6878;
    int check3 = 42;
    int i = 0;

    printf("\ntesting BSTFind\n");

    for (i = 0; i < 9; ++i)
    {
        BSTInsert(bst, &arr[i]);
    }

    Test(-3 == *(int *)BSTGetData(BSTFind(bst, &check1)));
    Test(6878 == *(int *)BSTGetData(BSTFind(bst, &check2)));
    Test(NULL == BSTFind(bst, &check3));

    BSTDestroy(bst);
}

void TestBSTRemove()
{
    bst_t *bst = BSTCreate(IntCmp);
    int arr[7] = {10, 23, 34, 32, 9, 8, 5};
    int i = 0;
    bst_iter_t runner = NULL;

    printf("\ntesting BSTRemove\n");

    for (i = 0; i < 7; ++i)
    {
        BSTInsert(bst, &arr[i]);
    }

    runner = BSTPrev(BSTPrev(BSTEnd(bst)));
    BSTRemove(runner);
    BSTRemove(BSTBegin(bst));
    BSTRemove(BSTBegin(bst));
    runner = BSTBegin(bst);

    Test(9 == *(int *)BSTGetData(runner));
    runner = BSTNext(runner);
    Test(10 == *(int *)BSTGetData(runner));
    runner = BSTNext(runner);
    Test(23 == *(int *)BSTGetData(runner));
    runner = BSTNext(runner);
    Test(34 == *(int *)BSTGetData(runner));
    
    BSTDestroy(bst);
}

void TestBSTGetData()
{
    bst_t *bst = BSTCreate(IntCmp);
    int arr[7] = {1, 18, 17, 32, 50, 3, 4};
    int i = 0;
    bst_iter_t runner = NULL;

    printf("\ntesting BSTGetData\n");

    for (i = 0; i < 7; ++i)
    {
        BSTInsert(bst, &arr[i]);
    }

    runner = BSTBegin(bst);

    Test(1 == *(int *)BSTGetData(runner));
    runner = BSTNext(runner);
    Test(3 == *(int *)BSTGetData(runner));
    runner = BSTNext(runner);
    Test(4 == *(int *)BSTGetData(runner));
    runner = BSTNext(runner);
    Test(17 == *(int *)BSTGetData(runner));
    
    BSTDestroy(bst);
}

void TestBSTIsEmpty()
{
    bst_t *bst = BSTCreate(IntCmp);
    int arr[2] = {11, 18};

    printf("\ntesting BSTIsEmpty\n");

    Test(1 == BSTIsEmpty(bst));
    BSTInsert(bst, &arr[0]);
    Test(0 == BSTIsEmpty(bst));
    BSTInsert(bst, &arr[1]);
    BSTRemove(BSTBegin(bst));
    Test(0 == BSTIsEmpty(bst));
    BSTRemove(BSTBegin(bst));
    Test(1 == BSTIsEmpty(bst));

     BSTDestroy(bst);
}

void TestBSTSize()
{
    bst_t *bst = BSTCreate(IntCmp);
    int arr[2] = {11, 18};

    printf("\ntesting BSTSize\n");

    Test(0 == BSTSize(bst));
    BSTInsert(bst, &arr[0]);
    Test(1 == BSTSize(bst));
    BSTInsert(bst, &arr[1]);
    BSTRemove(BSTBegin(bst));
    Test(1 == BSTSize(bst));
    BSTRemove(BSTBegin(bst));
    Test(0 == BSTSize(bst));

    BSTDestroy(bst);
}

void TestBSTIsEqual()
{
    bst_t *bst = BSTCreate(IntCmp);
    int arr[2] = {11, 18};

    printf("\ntesting BSTIsEqual\n");
    
    Test(1 == BSTIsEqual(BSTBegin(bst), BSTEnd(bst)));
    BSTInsert(bst, &arr[0]);
    Test(0 == BSTIsEqual(BSTBegin(bst), BSTEnd(bst)));
    Test(1 == BSTIsEqual(BSTBegin(bst), BSTPrev(BSTEnd(bst))));

    BSTDestroy(bst);
}

void TestBSTBegin()
{
    bst_t *bst = BSTCreate(IntCmp);
    int arr[9] = {41, 35, -5, 23, 31, 12, 67, 11, -3};
    int i = 0;

    printf("\ntesting BSTBegin\n");

    for (i = 0; i < 9; ++i)
    {
        BSTInsert(bst, &arr[i]);
    }

    Test(-5 == *(int *)BSTGetData(BSTBegin(bst)));
    BSTRemove(BSTBegin(bst));
    Test(-3 == *(int *)BSTGetData(BSTBegin(bst)));
    BSTRemove(BSTBegin(bst));
    Test(11 == *(int *)BSTGetData(BSTBegin(bst)));
    BSTRemove(BSTBegin(bst));
    Test(12 == *(int *)BSTGetData(BSTBegin(bst)));

    BSTDestroy(bst);
}

void TestBSTEnd()
{
    bst_t *bst = BSTCreate(IntCmp);
    int arr[9] = {41, 35, -5, 23, 31, 12, 67, 11, -3};
    int i = 0;

    printf("\ntesting BSTEnd\n");

    for (i = 0; i < 9; ++i)
    {
        BSTInsert(bst, &arr[i]);
    }

    Test(67 == *(int *)BSTGetData(BSTPrev(BSTEnd(bst))));
    BSTRemove(BSTPrev(BSTEnd(bst)));
    Test(41 == *(int *)BSTGetData(BSTPrev(BSTEnd(bst))));
    BSTRemove(BSTPrev(BSTEnd(bst)));
    Test(35 == *(int *)BSTGetData(BSTPrev(BSTEnd(bst))));
    BSTRemove(BSTPrev(BSTEnd(bst)));
    Test(31 == *(int *)BSTGetData(BSTPrev(BSTEnd(bst))));

    BSTDestroy(bst);
}

void TestBSTNext()
{
    bst_t *bst = BSTCreate(IntCmp);
    int arr[9] = {50, 25, 75, 20, 28, 70, 78, 66, 10};
    int i = 0;
    bst_iter_t runner = NULL;

    printf("\ntesting BSTNext\n");

    for (i = 0; i < 9; ++i)
    {
        BSTInsert(bst, &arr[i]);
    }

    runner = BSTBegin(bst);

    runner = BSTNext(runner);
    Test(20 == *(int *)BSTGetData(runner));
    runner = BSTNext(runner);
    Test(25 == *(int *)BSTGetData(runner));
    runner = BSTNext(runner);
    Test(28 == *(int *)BSTGetData(runner));
    runner = BSTNext(runner);
    Test(50 == *(int *)BSTGetData(runner));
    Test(NULL == BSTNext(BSTEnd(bst)));

    BSTDestroy(bst);
}

void TestBSTPrev()
{
    bst_t *bst = BSTCreate(IntCmp);
    int arr[9] = {50, 25, 75, 20, 28, 70, 78, 66, 10};
    int i = 0;
    bst_iter_t runner = NULL;

    printf("\ntesting BSTPrev\n");

    for (i = 0; i < 9; ++i)
    {
        BSTInsert(bst, &arr[i]);
    }

    runner = BSTEnd(bst);

    runner = BSTPrev(runner);
    Test(78 == *(int *)BSTGetData(runner));
    runner = BSTPrev(runner);
    Test(75 == *(int *)BSTGetData(runner));
    runner = BSTPrev(runner);
    Test(70 == *(int *)BSTGetData(runner));
    runner = BSTPrev(runner);
    Test(66 == *(int *)BSTGetData(runner));
    Test(NULL == BSTPrev(BSTBegin(bst)));

    BSTDestroy(bst);
}

int action_func(void *a, void *b)
{
    *(int *)a += *(int *)b;
    return (0);
}

void TestBSTForEach()
{
    bst_t *bst = BSTCreate(IntCmp);
    int arr[9] = {50, 25, 75, 20, 28, 73, 78, 66, 10};
    int i = 0;
    int inc_by = 6;
    bst_iter_t from = NULL;
    bst_iter_t to = NULL;

    printf("\ntesting BSTForEach\n");

    for (i = 0; i < 9; ++i)
    {
        BSTInsert(bst, &arr[i]);
    }

    from = BSTNext(BSTBegin(bst));
    to = BSTPrev(BSTPrev(BSTPrev(BSTEnd(bst))));

    Test(0 == BSTForEach(from, to, action_func, &inc_by));
    Test(26 == *(int *)BSTGetData(from));
    from = BSTNext(from);
    Test(31 == *(int *)BSTGetData(from));
    from = BSTNext(from);
    Test(34 == *(int *)BSTGetData(from));
    from = BSTNext(from);
    Test(56 == *(int *)BSTGetData(from));
    from = BSTNext(from);
    Test(72 == *(int *)BSTGetData(from));
    from = BSTNext(from);
    Test(73 == *(int *)BSTGetData(from));

    BSTDestroy(bst);
}