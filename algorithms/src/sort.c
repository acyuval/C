/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Chen
*	Date:      
******************************************************************************/

#include <assert.h> /* assert			  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sort.h"

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
static int *StaticMergeSort(int * arr, size_t start , size_t end , int * arr_extra);
static int StaticRecursiveBS(int * sorted ,int* start, int* end, int to_find);
static void SwapByteByte(char *dest, char * src, size_t ele_size);
size_t StaticSwapPivot(void *base,size_t ele_size , size_t left_index, 
                    size_t right_index, compare_func compare);
void StaticQuickSort(void *base, size_t ele_size, size_t left_index,
                    size_t right_index, compare_func compare);
static int *MergeTwoHalf(int *arr, int start,int mid , int end, int * arr_extra);
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


int IterativeBinarySearch(int* sorted_arr, size_t arr_size, int to_find)
{
    int *start_arr= sorted_arr;
    int *end_arr = sorted_arr+arr_size;
    int *guess = NULL;

    assert(NULL != sorted_arr);

    while (end_arr != start_arr)
    {
        guess = start_arr + ((end_arr - start_arr)/2);    
        if (to_find == *guess)
        {
            return guess-sorted_arr;
        }
        else if(to_find > *guess)
        {
            start_arr = guess;
        }
        else 
        {
            end_arr = guess;
        }    
    }
    return FALSE; 
}


int RecursiveBinarySearch(int* sorted_arr, size_t arr_size, int to_find)
{
    int *start_arr= sorted_arr;
    int *end_arr = sorted_arr+arr_size;
    int result = 0 ; 

    result = StaticRecursiveBS(sorted_arr, start_arr, end_arr, to_find);

    return result;

}


int MergeSort(int *arr, size_t arr_size)
{
    int *arr_extra = (int *)calloc(arr_size, sizeof(int));
    if (NULL == arr_extra)
    {
        return FAIL;
    }

    StaticMergeSort(arr, 0 , arr_size-1, arr_extra);

    free(arr_extra);
    return SUCCESS;  

}



void QuickSort(void *base, size_t nmemb, size_t size, compare_func compare)
{
    size_t right_index = 0;
    right_index = (nmemb-1)*size;

    StaticQuickSort(base,size, 0, right_index, compare);
    return;  
}


/******************************************************************************
*							STATIC FUNCTIONS								  * 
******************************************************************************/
void StaticQuickSort(void *base, size_t ele_size, size_t left_index,
                    size_t right_index, compare_func compare)
{
    size_t pivot_index = 0;

    assert(base != NULL);
    if(left_index <right_index)
    {
        pivot_index = StaticSwapPivot(base , ele_size , left_index, right_index,
                                                                compare); 
        if(pivot_index != 0)
        {
            StaticQuickSort(base, ele_size, left_index, pivot_index-ele_size,compare);
        }
        if(pivot_index != right_index)
        {
            StaticQuickSort(base, ele_size, pivot_index + ele_size, right_index, compare);
        }
    }

}


static void SwapByteByte(char *dest, char * src, size_t ele_size)
{
    size_t i = 0;
    char temp = 0;
    for(i = 0 ; i < ele_size ; ++i)
    {
        temp = dest[i];
        dest[i] = src[i];
        src[i] = temp;
    }
    return;
}

size_t StaticSwapPivot(void *base,size_t ele_size , size_t left_index, 
                    size_t right_index, compare_func compare)
 {
    char * base_ptr = (char *)base;
    char * pivot = (char *)base + right_index;
    size_t last_swap_index = left_index - ele_size;
    size_t runner = 0;

    for(runner =left_index;  runner < right_index ; runner+=ele_size)
    {
        if (compare((void *)pivot, (void *)(base_ptr+runner)) > 0)
        {
            last_swap_index +=ele_size;
            SwapByteByte(base_ptr+last_swap_index, base_ptr + runner ,ele_size); 
        }
    }

    last_swap_index += ele_size;
    SwapByteByte(base_ptr+last_swap_index, pivot,ele_size);

    return last_swap_index;
 }



static int *StaticMergeSort(int * arr, size_t start , size_t end , int * arr_extra)
{
    size_t mid = 0;

    if (start < end) 
    {
        mid = start + (end - start) / 2;

        StaticMergeSort(arr, start, mid, arr_extra);
        StaticMergeSort(arr, mid + 1, end, arr_extra);
        MergeTwoHalf(arr, start, mid, end, arr_extra);
    }

    return arr;

}


static int *MergeTwoHalf(int *arr, int start,int mid , int end, int * arr_extra)
{
    int first_index = start, last_index = mid+1, counter =start;
    int i = 0;
    while (first_index <= mid && last_index <= end)
    {
        if(arr[first_index] <= arr[last_index])
        {
            arr_extra[counter] = arr[first_index];
            ++first_index;
        }
        else 
        {
            arr_extra[counter] = arr[last_index];
            ++last_index;
        }
        ++counter;    
    }

    while(first_index <= mid)
    {
        arr_extra[counter] = arr[first_index];
        ++counter;
        ++first_index;
    }

    while(last_index <= end)
    {
        arr_extra[counter] = arr[last_index];
        ++counter;
        ++last_index;
    }

    for (i = start; i <= end; ++i) 
    {
        arr[i] = arr_extra[i];
    }
    
    return arr;
}

static int StaticRecursiveBS(int * sorted ,int* start, int* end, int to_find)
{
    int *guess = start + (end - start)/2;
    
    if (*guess == to_find)
    {
        return (guess - sorted);
    }
    else if(to_find > *guess)
    {
        start = guess;
    }
    else 
    {
        end = guess;
    }    

    return StaticRecursiveBS(sorted, start, end, to_find);
}




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
