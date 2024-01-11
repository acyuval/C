#ifndef __SORT_H__
#define __SORT_H__

#include <stddef.h> /* size_t */

/******************************************************************************
*Description: sorts the array using the bubble sort algorithm.
*Arguments: arr - and array of ints.
*Return Value: None.
*Time Complexity: O(n^2)
*Space Complexity: O(1)
*Notes: undefined behavior if arr is NULL.
******************************************************************************/
void BubbleSort(int *arr, size_t arr_size);

/******************************************************************************
*Description: sorts the array using the selection sort algorithm.
*Arguments: arr - and array of ints.
*Return Value: None.
*Time Complexity: O(n^2)
*Space Complexity: O(1)
*Notes: undefined behavior if arr is NULL.
******************************************************************************/
void SelectionSort(int *arr, size_t arr_size);

/******************************************************************************
*Description: sorts the array using the insert sort algorithm.
*Arguments: arr - and array of ints.
*Return Value: None.
*Time Complexity: O(n^2)
*Space Complexity: O(1)
*Notes: undefined behavior if arr is NULL.
******************************************************************************/
void InsertionSort(int *arr, size_t arr_size);

/******************************************************************************
*Description: sorts the array using the bubble sort algorithm.
*Arguments: arr - and array of ints.
*Return Value: None.
*Time Complexity: O(n + k)
*Space Complexity: O(k)
*Notes: undefined behavior if arr is NULL.
        k is the number of possible values.
******************************************************************************/
int CountingSort(int *arr, size_t arr_size);

/******************************************************************************
*Description: sorts the array using the bubble sort algorithm.
*Arguments: arr - and array of ints.
*Return Value: None.
*Time Complexity: O(n * k)
*Space Complexity: O(n + k)
*Notes: undefined behavior if arr is NULL.
        k is the number of digits in the largest number in the array.
******************************************************************************/
int RadixSort(int *arr, size_t arr_size);

/******************************************************************************
 *Description: Sorts the array using the MergeSort algorithm.
 *Arguments: arr - and array of ints.
 *	         arr_size - the size of the array
 *Return Value: None.
 *Time Complexity: O(n * long(n))
 *Space Complexity: O(n)
 *Notes: undefined behavior if arr is NULL.
 ******************************************************************************/
void MergeSort(int *arr, size_t arr_size);

/******************************************************************************
 *Description: sorts the array using the QuickSort algorithm.
 *Arguments: arr - and array of ints.
 *	         arr_size - the size of the array
 *Return Value: None.
 *Time Complexity: O(n * long(n))
 *Space Complexity: O(log(n))
 *Notes: undefined behavior if arr is NULL.
 ******************************************************************************/
void QuickSort(int *arr, size_t arr_size);

int IterativeBinarySearch(int* sorted_arr, size_t arr_size, int to_find);

int RecursiveBinarySearch(int* sorted_arr, size_t arr_size, int to_find);
#endif