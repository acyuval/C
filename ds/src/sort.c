/******************************************************************************
*	Author:    Yuval 
*	Reviewer : 
*	Date:      
******************************************************************************/

#include <assert.h> /* assert			  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define LOW(a,b) ((a<b) ? a : b)
#define SUCCESS (0)
#define FAIL (-1)
#define FALSE (0)
#define TRUE (1)

/******************************************************************************
*							 DECLRATION								  * 
******************************************************************************/

static int RadixCountSort(int *arr, int size, int exp);
static size_t FindMaxInArr(int * arr , size_t size);
static void swap(int* xp, int* yp);
/******************************************************************************
*							 FUNCTIONS 										  * 
******************************************************************************/
 
int RadixSort(int *arr, size_t arr_size)
{
    long max_val = 0;
    int exp = 1;
    int status = 0; 

    assert(NULL != arr);
    assert(arr_size != 0);

    max_val = FindMaxInArr(arr, arr_size);
    for (exp = 1; max_val/exp > 0 ; exp *= 10)
    {
        status = RadixCountSort(arr,arr_size, exp);

        if (status != SUCCESS)
        {
            return FAIL;
        }
    }    
    return SUCCESS;
}


int CountingSort(int *arr, size_t arr_size)
{
    
    long max_num = 0;
    int * count_arr = NULL;
    long i = 0 ; 
    size_t insert_index = 0; 
    
    assert(NULL != arr);
    assert(arr_size != 0);

    max_num = FindMaxInArr(arr , arr_size);
    count_arr = (int *)calloc(max_num+1, sizeof(int));
    if (NULL == count_arr) 
    {
        return FAIL;
    } 

    for (i = 0; i < (long)arr_size ; i++)
    {
        count_arr[arr[i]] += 1;  
    }

    i = 0;

    while(i <= max_num)
    {
        while(count_arr[i])
        {
            arr[insert_index] = i;
            count_arr[i] -= 1;
            insert_index += 1;
        }

        i++;
    }
    

    free(count_arr);
    
    return SUCCESS;
}




void BubbleSort(int *arr, size_t arr_size)
{
    size_t i = 0;
    size_t j = 0;
    size_t swapped = 0; 

    assert(NULL != arr);
    assert(arr_size != 0);

    for (i = 0; i < arr_size - 1; i++) 
    {
        swapped = FALSE;
        for (j = 0; j < arr_size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1]) 
            {
                swap(&arr[j], &arr[j + 1]);
                swapped = TRUE;
            }
        }

        if (swapped == FALSE)
        {
            break;
        }
    }
}


void SelectionSort(int *arr, size_t arr_size)
{
    size_t i = 0;
    size_t j = 0;

    size_t low_index = 0;

    assert(NULL != arr);
    assert(arr_size != 0);

    for (i = 0; i < arr_size - 1; i++) 
    {
        low_index = i;
        for (j = i; j < arr_size; j++)
        {
            low_index = ((arr[low_index] < arr[j]) ? low_index : j );
        }

        if (arr[low_index] < arr[i]) 
        {
            swap(&arr[low_index], &arr[i]); 
        }
    }
}


void InsertionSort(int *arr, size_t arr_size)
{
    long i = 0;
    long j = 0;
    long this_iter = 0; 

    assert(NULL != arr);
    assert(arr_size != 0);
    
    for (i = 1; i < (long)arr_size ; i++) 
    {
        this_iter = arr[i];
        j = i-1;
        
        while(j >= 0 && arr[j] > this_iter)
        {
            arr[j+1] = arr[j];
            j = j -1;
        }

        arr[j+1] = this_iter;
    }
}



/******************************************************************************
*							STATIC FUNCTIONS								  * 
******************************************************************************/

static int RadixCountSort(int *arr, int size, int exp)
{
    int count[10] = {0};
    int * temp_arr = (int *)calloc(size, sizeof(*arr));
    int i = 0;

    assert(NULL != arr);
    assert(size != 0);

    if (NULL == temp_arr)
    {
        return FAIL;
    }

    for (i = 0; i < size; i++)
    {
        count[(arr[i] / exp) % 10] += 1;
    }

    for (i = 1; i < 10; i++)
    {
        count[i] += count[i - 1];
    }

    for (i = size - 1; i >= 0; i--) 
    {
        temp_arr[count[(arr[i] / exp) % 10] - 1] = arr[i];
        --count[(arr[i] / exp) % 10];
    }

    memcpy(arr, temp_arr, size*sizeof(*arr));
    free(temp_arr);
    return SUCCESS;
}

static size_t FindMaxInArr(int * arr , size_t size)
{
    long i = 0;
    long max = 0; 

    assert(NULL != arr);
    assert(size != 0);

    for (i = 0 ; i< (long)size ; i++)
    {
        max =  (max < (long)arr[i]) ? (long)arr[i] : max; 
    }
    
    return max; 
}

static void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
