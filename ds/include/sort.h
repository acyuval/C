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

#endif