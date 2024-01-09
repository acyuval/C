#include <stdio.h> /* printf */
#include "avl.h"
#include "test.h"

void TestCreate(void);
void TestInsert(void);
void TestRemove(void);
void TestFindIsEmptySize(void);
void TestHeight(void);
void TestForEach(void);

int main()
{
	
	TestRemove();

	TestFindIsEmptySize();
	
    TestCreate();
	TestInsert();
	TestHeight();
	TestForEach();

    return (0);
}

int IntCmp(void *arg1, void *arg2)
{
    if(*(int *)arg1 > *(int *)arg2)
	{
		return (1);
	}
	else if(*(int *)arg1 == *(int *)arg2)
	{
		return (0);
	}
	else
	{
		return (-1);
	}
}

int PrintInt(void *arg1, void *arg2)
{
	static size_t i = 0;

    if(i != *(size_t *)arg2 - 1)
    {
        printf("%i -> ", *(int *)arg1);
        i++;
    }
    else
    {
        printf("%i\n", *(int *)arg1);
        i = 0;
    }
    
    return (SUCCESS);

}

void TestCreate(void)
{
    avl_t *avl = AVLCreate(IntCmp);

    TEST_START("Test Create");

    TEST_ASSERT(NULL != avl);

    AVLDestroy(avl);

    TEST_END;
}

void TestInsert(void)
{
	avl_t *avl = AVLCreate(IntCmp);
	int data[6] = {5, 3, 4, 10, 2, 6};
    int i = 0;

    TEST_START("Test Insert");

	for(i = 0; i < 6; ++i)
	{
		AVLInsert(avl, &data[i]);
	}

    TEST_ASSERT(NULL != avl);
	TEST_ASSERT(5 == *(int *)AVLFind(avl, &data[0]));
	TEST_ASSERT(3 == *(int *)AVLFind(avl, &data[1]));
	TEST_ASSERT(4 == *(int *)AVLFind(avl, &data[2]));
	TEST_ASSERT(10 == *(int *)AVLFind(avl, &data[3]));
	TEST_ASSERT(2 == *(int *)AVLFind(avl, &data[4]));
	TEST_ASSERT(6 == *(int *)AVLFind(avl, &data[5]));
	TEST_ASSERT(6 == AVLSize(avl));

    AVLDestroy(avl);

    TEST_END;
}


void TestRemove(void)
{
	avl_t *avl = AVLCreate(IntCmp);
	int data[] = {5, 3, 4, 10, 2, 7, 6 , 8};
    int i = 0;
	size_t avl_size = 0;

    TEST_START("Test Remove");

	for(i = 0; i < 8; ++i)
	{
		AVLInsert(avl, &data[i]);
	}

    AVLRemove(avl, &data[3]);
	
	TEST_ASSERT(7 == AVLSize(avl));
	TEST_ASSERT(3 == AVLHeight(avl));

    AVLDestroy(avl);

    TEST_END;
}

void TestFindIsEmptySize(void)
{
	avl_t *avl = AVLCreate(IntCmp);
	int data[] = {5, 3, 4, 10, 2, 6, 15, 16, 17};
    int i = 0;

    TEST_START("Test Find IsEmpty Size");

	TEST_ASSERT(NULL != avl);

	TEST_ASSERT(NULL == AVLFind(avl, &data[0]));
	TEST_ASSERT(AVLIsEmpty(avl));
	TEST_ASSERT(0 == AVLSize(avl));

	for(i = 0; i < 9; ++i)
	{
		AVLInsert(avl, &data[i]);
	}

	TEST_ASSERT(5 == *(int *)AVLFind(avl, &data[0]));
	TEST_ASSERT(3 == *(int *)AVLFind(avl, &data[1]));
	TEST_ASSERT(4 == *(int *)AVLFind(avl, &data[2]));
	TEST_ASSERT(10 == *(int *)AVLFind(avl, &data[3]));
	TEST_ASSERT(2 == *(int *)AVLFind(avl, &data[4]));
	TEST_ASSERT(6 == *(int *)AVLFind(avl, &data[5]));
	TEST_ASSERT(15 == *(int *)AVLFind(avl, &data[6]));
	TEST_ASSERT(16 == *(int *)AVLFind(avl, &data[7]));
	TEST_ASSERT(17 == *(int *)AVLFind(avl, &data[8]));
	TEST_ASSERT(!AVLIsEmpty(avl));
	TEST_ASSERT(9 == AVLSize(avl));

    AVLDestroy(avl);

    TEST_END;
}


void TestHeight(void)
{
	avl_t *avl = AVLCreate(IntCmp);
	int data[] = {5, 3, 4, 10, 2, 6, 15, 16, 17};
    int i = 0;

    TEST_START("Test Height");

	TEST_ASSERT(NULL != avl);

	for(i = 0; i < 9; ++i)
	{
		AVLInsert(avl, &data[i]);
	}

	TEST_ASSERT(5 == AVLHeight(avl));

    AVLDestroy(avl);

    TEST_END;
}


void TestForEach(void)
{
	avl_t *avl = AVLCreate(IntCmp);
	int data[] = {5, 3, 4, 10, 2, 6, 15, 16, 17};
    int i = 0;
	size_t avl_size = 0;

    TEST_START("Test ForEach");

	TEST_ASSERT(NULL != avl);

	for(i = 0; i < 9; ++i)
	{
		AVLInsert(avl, &data[i]);
	}

	avl_size = AVLSize(avl);
	TEST_ASSERT(SUCCESS == AVLForEach(avl, PRE_ORDER, PrintInt, (void *)&avl_size));
	TEST_ASSERT(SUCCESS == AVLForEach(avl, IN_ORDER, PrintInt, (void *)&avl_size));
	TEST_ASSERT(SUCCESS == AVLForEach(avl, POST_ORDER, PrintInt, (void *)&avl_size));

    AVLDestroy(avl);

    TEST_END;
}