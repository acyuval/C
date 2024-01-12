#ifndef __SORT_H__
#define __SORT_H__

#include <stddef.h> /* size_t */

typedef int (*compare_func)(const void *, const void *);

/******************************************************************************
 *Description: Sorts the array using the bubble sort algorithm.
 *Arguments: arr - an array of ints.
 *	        arr_size - the size of the array
 *Return Value: None.
 *Time Complexity: O(n^2)
 *Space Complexity: O(1)
 *Notes: If arr is NULL it will lead to undefined behavior.
 ******************************************************************************/
void BubbleSort(int *arr, size_t arr_size);

/******************************************************************************
 *Description: Sorts the array using the selection sort algorithm.
 *Arguments: arr - an array of ints.
 *	        arr_size - the size of the array
 *Return Value: None.
 *Time Complexity: O(n^2)
 *Space Complexity: O(1)
 *Notes: If arr is NULL it will lead to undefined behavior.
 ******************************************************************************/
void SelectionSort(int *arr, size_t arr_size);

/******************************************************************************
 *Description: Sorts the array using the insertion sort algorithm.
 *Arguments: arr - an array of ints.
 *	        arr_size - the size of the array
 *Return Value: None.
 *Time Complexity: O(n^2)
 *Space Complexity: O(1)
 *Notes: If arr is NULL it will lead to undefined behavior.
 ******************************************************************************/
void InsertionSort(int *arr, size_t arr_size);

/******************************************************************************
 *Description: Sorts the array using the counting sort algorithm.
 *Arguments: arr - an array of ints.
 *	        arr_size - the size of the array
 *Return Value: (0)  - Success
 *	            (-1) - Error
 *Time Complexity: O(n + k)
 *Space Complexity: O(k)
 *Notes: If arr is NULL it will lead to undefined behavior.
 *       k is the number of possible values.
 ******************************************************************************/
int CountingSort(int *arr, size_t arr_size);

/******************************************************************************
 *Description: Sorts the array using the RadixSort algorithm.
 *Arguments: arr - an array of ints.
 *	        arr_size - the size of the array
 *Return Value: (0)  - Success
 *	            (-1) - Error
 *Time Complexity: O(n * k)
 *Space Complexity: O(n + k)
 *Notes: If arr is NULL it will lead to undefined behavior.
 *       k is the number of digits in the largest number in the array.
 ******************************************************************************/
int RadixSort(int *arr, size_t arr_size);

/******************************************************************************
 *Description: Sorts the array using the MergeSort algorithm.
 *Arguments: arr - an array of ints.
 *	     arr_size - the size of the array
 *Return Value: (0)  - Success
 *	            (-1) - Error
 *Time Complexity: O(n * log(n))
 *Space Complexity: O(n)
 *Notes: undefined behavior if arr is NULL.
 ******************************************************************************/
int MergeSort(int *arr, size_t arr_size);

/******************************************************************************
 *Description: sorts the array using the QuickSort algorithm.
 *Arguments: base - the start of the array to be sorted
 *           nmemb - the amount of members in the array
 *           size - the size of a single element in the array
 *           compare_func - the function which compares the array elements
 *Return Value: None.
 *Time Complexity: O(n * log(n))
 *Space Complexity: O(log(n))
 *Notes: undefined behavior if arr is NULL.
 ******************************************************************************/
void QuickSort(void *base, size_t nmemb, size_t size, compare_func compare);

/******************************************************************************
 *Description: searches the array using BinarySearch.
 *Arguments: arr - sorted array of ints.
 *           arr_size - the size of the array
 *           to_find - int value to find in the array
 *Return Value: index of the found value, -1 if not found.
 *Time Complexity: O(log(n))
 *Space Complexity: O(1)
 *Notes: undefined behavior if arr is NULL.
 ******************************************************************************/
int IterativeBinarySearch(int *sorted_arr, size_t arr_size, int to_find);

/******************************************************************************
 *Description: searches the array using BinarySearch.
 *Arguments: arr - sorted array of ints.
 *           arr_size - the size of the array
 *           to_find - int value to find in the array
 *Return Value: index of the found value, -1 if not found.
 *Time Complexity: O(log(n))
 *Space Complexity: O(log(n))
 *Notes: undefined behavior if arr is NULL.
 ******************************************************************************/
int RecursiveBinarySearch(int *sorted_arr, size_t arr_size, int to_find);

#endif /*__SORT_H__*/