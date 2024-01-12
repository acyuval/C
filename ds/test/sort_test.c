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
/******************************************************************************
*							MAIN											  * 
******************************************************************************/


int main()
{
	
    TestMergeSort();
    /*
    TestRadixSort();
    TestCountingSort();
    TestSelectionSort();
    TestInsertionSort();
	TestBubbleSort();
    */
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
    printf("\nRadix sort Succsess\n");
    printf("\ntest time = %f, qsort = %f\n", time_test , time_exp);

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
    printf("\nCounting sort Succsess\n");
    printf("\ntest time = %f, qsort = %f\n", time_test , time_exp);

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
    printf("\nInsertion sort Succsess\n");
    printf("\ntest time = %f, qsort = %f\n", time_test , time_exp);

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
    printf("\nSelection sort Succsess\n");
    printf("\ntest time = %f, qsort = %f\n", time_test , time_exp);
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
    printf("\nBubble Sort Succsess\n");
    printf("\ntest time = %f, qsort = %f\n", time_test , time_exp);
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
        printf("\n Merge Sort Succsess\n");
    }

}


/******************************************************************************
*							STATIC FUNCTIONS								  * 
******************************************************************************/

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
		printf("%s -> \t\tNO.%d sucsess!\n\n",calling_function, test_no);
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


