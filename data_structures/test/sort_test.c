/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Yael
*	Date:      
******************************************************************************/
#include <stdio.h>  /* printf()  	  */
#include <stdlib.h>
#include <time.h>

#include "sort.h"

#define TEST_SIZE (5000)

/******************************************************************************
*							TYPE DEFS / MACROS 								  * 
******************************************************************************/



/******************************************************************************
*							FUNCTION DECLRATION								  * 
******************************************************************************/

static void TestHelper(int booll , char * calling_function, int test_no); 
void PrintArr(int * arr, int * expected, size_t size , char * description);
void TestInsertionSort();
int cmpfunc (const void * a, const void * b);
void TestSelectionSort();
void TestBubbleSort();
void TestCountingSort();
void TestRadixSort();
void TestMergeSort();
void TestQuicSort();
int compareator(const void * arg1,const void * arg2);
void TestBinarySearch();
/******************************************************************************
*							MAIN											  * 
******************************************************************************/


int main()
{

    TestQuicSort();
    TestMergeSort();
    TestRadixSort();
    TestCountingSort();
    TestSelectionSort();
    TestInsertionSort();
	TestBubbleSort();
	
    TestBinarySearch();

    return (0);
}




/******************************************************************************
*							TEST FUNCTIONS									  * 
******************************************************************************/


void TestRadixSort()
{
    int arr[TEST_SIZE] = {0};
    int exepcted[TEST_SIZE] = {0};
    int i = 0;
    int random_number = 0; 
    
    double time_test = 0 , time_exp = 0;   

    
    for(i = 0 ; i < TEST_SIZE ; i ++)
    {
        random_number = rand() % 1000000;
        exepcted[i] = random_number;
        arr[i] = random_number;
    }

    time_test = (double) clock() / CLOCKS_PER_SEC; 
        RadixSort(arr, TEST_SIZE);
    time_test = (((double) clock()) / CLOCKS_PER_SEC) - time_test; 
    
    time_exp = (double) clock() / CLOCKS_PER_SEC; 
        qsort(exepcted, TEST_SIZE, sizeof(int), cmpfunc);
    time_exp =  (((double) clock()) / CLOCKS_PER_SEC) - time_exp; 
    
    for(i = 0 ; i < TEST_SIZE ; i++)
    {
        if (exepcted[i] != arr[i])
        {
            PrintArr(arr, exepcted , TEST_SIZE , "Failed arr Radix sort");
            break;
        }
    }
    printf("\nRadix sort Succsess");
    printf(" -- test time = %f, qsort = %f\n", time_test , time_exp);

}

void TestCountingSort()
{
    int arr[TEST_SIZE] = {0};
    int exepcted[TEST_SIZE] = {0};
    int i = 0;
    int random_number = 0; 
    
    double time_test = 0 , time_exp = 0;   

    
    for(i = 0 ; i < TEST_SIZE ; i ++)
    {
        random_number = rand() % 100;
        exepcted[i] = random_number;
        arr[i] = random_number;
    }

    time_test = (double) clock() / CLOCKS_PER_SEC; 
        CountingSort(arr, TEST_SIZE);
    time_test = (((double) clock()) / CLOCKS_PER_SEC) - time_test; 
    
    time_exp = (double) clock() / CLOCKS_PER_SEC; 
        qsort(exepcted, TEST_SIZE, sizeof(int), cmpfunc);
    time_exp =  (((double) clock()) / CLOCKS_PER_SEC) - time_exp; 
    
    for(i = 0 ; i < TEST_SIZE ; i++)
    {
        if (exepcted[i] != arr[i])
        {
            PrintArr(arr, exepcted , TEST_SIZE , "Failed arr Counting sort");
            break;
        }
    }
    printf("\nCounting sort Succsess");
    printf(" -- test time = %f, qsort = %f\n", time_test , time_exp);

}


void TestInsertionSort()
{
    int arr[TEST_SIZE] = {0};
    int exepcted[TEST_SIZE] = {0};
    int i = 0;
    int random_number = 0; 
    
    double time_test = 0 , time_exp = 0;   

    
    for(i = 0 ; i < TEST_SIZE ; i ++)
    {
        random_number = rand() % 100;
        exepcted[i] = random_number;
        arr[i] = random_number;
    }
    time_test = (double) clock() / CLOCKS_PER_SEC; 
        InsertionSort(arr, TEST_SIZE);
    time_test = (((double) clock()) / CLOCKS_PER_SEC) - time_test; 
    
    time_exp = (double) clock() / CLOCKS_PER_SEC; 
        qsort(exepcted, TEST_SIZE, sizeof(int), cmpfunc);
    time_exp =  (((double) clock()) / CLOCKS_PER_SEC) - time_exp; 
    
    for(i = 0 ; i < TEST_SIZE ; i++)
    {
        if (exepcted[i] != arr[i])
        {
            PrintArr(arr, exepcted , TEST_SIZE , "Failed arr Insertion sort");
            break;
        }
    }
    printf("\nInsertion sort Succsess");
    printf(" -- test time = %f, qsort = %f\n", time_test , time_exp);

}

void TestSelectionSort()
{
    int arr[TEST_SIZE] = {0};
    int exepcted[TEST_SIZE] = {0};
    int i = 0;
    int random_number = 0; 
    double time_test = 0 , time_exp = 0;

    for(i = 0 ; i < TEST_SIZE ; i ++)
    {
        random_number = rand() % 100;
        exepcted[i] = random_number;
        arr[i] = random_number;
    }
    time_test = (double) clock() / CLOCKS_PER_SEC; 
    SelectionSort(arr, TEST_SIZE);
    time_test = (((double) clock()) / CLOCKS_PER_SEC) - time_test; 
    
    time_exp = (double) clock() / CLOCKS_PER_SEC; 
    qsort(exepcted, TEST_SIZE, sizeof(int), cmpfunc);
    time_exp =  (((double) clock()) / CLOCKS_PER_SEC) - time_exp; 
    
    for(i = 0 ; i < TEST_SIZE ; i++)
    {
        if (exepcted[i] != arr[i])
        {
            PrintArr(arr, exepcted , TEST_SIZE , "Failed arr - Selection sort");
            break;
        }
    }
    printf("\nSelection sort Succsess");
    printf(" -- test time = %f, qsort = %f\n", time_test , time_exp);
}


void TestBubbleSort()
{
    int arr[TEST_SIZE] = {0};
    int exepcted[TEST_SIZE] = {0};
    int i = 0;
    int random_number = 0; 
    double time_test = 0 , time_exp = 0;

    for(i = 0 ; i < TEST_SIZE ; i ++)
    {
        random_number = rand() % 100;
        exepcted[i] = random_number;
        arr[i] = random_number;
    }

    time_test = (double) clock() / CLOCKS_PER_SEC; 
    BubbleSort(arr, TEST_SIZE);
    time_test = (((double) clock()) / CLOCKS_PER_SEC) - time_test; 
    
    time_exp = (double) clock() / CLOCKS_PER_SEC; 
    qsort(exepcted, TEST_SIZE, sizeof(int), cmpfunc);
    time_exp =  (((double) clock()) / CLOCKS_PER_SEC) - time_exp; 
    
    for(i = 0 ; i < TEST_SIZE ; i++)
    {
        if (exepcted[i] != arr[i])
        {
            PrintArr(arr, exepcted , TEST_SIZE , "Failed arr - Bubble Sort");
            break;
        }
    }
    printf("\nBubble Sort Succsess ");
    printf(" -- test time = %f, qsort = %f\n", time_test , time_exp);
}


void TestMergeSort()
{
    int arr[TEST_SIZE] = {0};
    int exepcted[TEST_SIZE] = {0};
    int i = 0;
    int random_number = 0; 
    double time_test = 0 , time_exp = 0;

    for(i = 0 ; i < TEST_SIZE ; i ++)
    {
        random_number = rand() % 100;
        exepcted[i] = random_number;
        arr[i] = random_number;
    }

    time_test = (double) clock() / CLOCKS_PER_SEC; 
    MergeSort(arr, TEST_SIZE);
    time_test = (((double) clock()) / CLOCKS_PER_SEC) - time_test; 
    
    time_exp = (double) clock() / CLOCKS_PER_SEC; 
    qsort(exepcted, TEST_SIZE, sizeof(int), cmpfunc);
    time_exp =  (((double) clock()) / CLOCKS_PER_SEC) - time_exp; 
    
    for(i = 0 ; i < TEST_SIZE ; i++)
    {
        if (exepcted[i] != arr[i])
        {
            PrintArr(arr, exepcted , TEST_SIZE , "Failed - Merge sort");
            break;
        }
    }
    if (i == TEST_SIZE)
    {
        printf("\nMerge Sort Succsess ");
        printf(" -- test time = %f, qsort = %f\n", time_test , time_exp);
    }

}



void TestQuicSort()
{
    int arr[TEST_SIZE] = {0};
    int exepcted[TEST_SIZE] = {0};
    int i = 0;
    int random_number = 0; 
    double time_test = 0 , time_exp = 0;

    for(i = 0 ; i < TEST_SIZE ; i ++)
    {
        random_number = rand() % 1000;
        exepcted[i] = random_number;
        arr[i] = random_number;
    }

    time_test = (double) clock() / CLOCKS_PER_SEC; 
    QuickSort((void*)arr,TEST_SIZE ,sizeof(int) , compareator);
    time_test = (((double) clock()) / CLOCKS_PER_SEC) - time_test; 
    
    time_exp = (double) clock() / CLOCKS_PER_SEC; 
    qsort(exepcted, TEST_SIZE, sizeof(int), cmpfunc);
    time_exp =  (((double) clock()) / CLOCKS_PER_SEC) - time_exp; 
    
    for(i = 0 ; i < TEST_SIZE ; i++)
    {
        if (exepcted[i] != arr[i])
        {
            PrintArr(arr, exepcted , TEST_SIZE , "Failed - Quick sort");
            break;
        }
    }
    if (i == TEST_SIZE)
    {
        printf("\nQuick Sort Succsess ");
        printf(" -- test time = %f, qsort = %f\n", time_test , time_exp);
    }

}


void TestBinarySearch()
{
    int arr[TEST_SIZE] = {0};
    int i = 0;
    int random_number = 0 , to_find_iter = 87, to_find_rec = 45;
    double time_test = 0;
    int found_index = 0;
    for(i = 0 ; i < TEST_SIZE ; i ++)
    {
        random_number = rand() % 1000;
        arr[i] = random_number;
    }

    random_number = rand() % TEST_SIZE;
    arr[random_number] = to_find_iter;
    random_number = rand() % TEST_SIZE;
    arr[random_number] = to_find_rec;

    QuickSort((void*)arr,TEST_SIZE ,sizeof(int) , compareator);

    time_test = (double) clock() / CLOCKS_PER_SEC; 
    found_index = IterativeBinarySearch(arr, TEST_SIZE, to_find_iter);
    time_test = (((double) clock()) / CLOCKS_PER_SEC) - time_test; 
    if (arr[found_index] != to_find_iter)
    {
        printf("\nIterative BS failed\n");
    }
    else
    {
        printf("\nIterative Success      - arr[%d]- %d time = %lf\n" , found_index , arr[found_index], time_test);
    }

    
    time_test = (double) clock() / CLOCKS_PER_SEC; 
    found_index = RecursiveBinarySearch(arr, TEST_SIZE, to_find_rec);
    time_test = (((double) clock()) / CLOCKS_PER_SEC) - time_test; 

    if (arr[found_index] != to_find_rec)
    {
        printf("\nRecursive BS failed\n");
    }
    else
    {
        printf("\nRecursive Success      - arr[%d]- %d time = %lf\n" , found_index , arr[found_index], time_test);
    }    

}



/******************************************************************************
*							STATIC FUNCTIONS								  * 
******************************************************************************/

int compareator(const void * arg1,const void * arg2)
{
    int * int1 = (int *)arg1;
    int * int2 = (int *)arg2;
    return ((*int1 > *int2)? 1 : -1) ; 
}

void PrintArr(int * arr, int * expected, size_t size , char * description)
{
    size_t i = 0 ; 
    printf("\nARR %s: \n",  description);
    if (expected != NULL)
    {
        for(i = 0 ; i < size ; i ++)
        {
            printf("%d-%d " , arr[i], expected[i]);
        }
    }
    else
    {
          for(i = 0 ; i < size ; i ++)
        {
            printf("%d" , arr[i]);
        }
    }
    printf("\n");
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

int cmpfunc (const void * a, const void * b)
{
   return ( *(int *)a - *(int *)b );
}


