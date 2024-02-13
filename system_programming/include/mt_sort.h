#ifndef __MT_COUNTING_SORT__
#define __MT_COUNTING_SORT__

#include <stddef.h>

/*
Name: MTCountingSort
Description: MT CountingSort is a multi-threaded version of the Counting Sort algorithm. 

Arguments:
    - arr: A valid pointer to the array to be sorted.
    - size: The number of elements in the array.
    - num_of_threads: The number of threads to be used for sorting.
Return: None
Time complexity:
Best Case: O(n + k), where n is the number of elements and k is the range of input values. However,
due to parallelization, the actual time can be closer to O(n/number_of_threads + k) if the overhead of threading is negligible.
Worst Case: O(n + k)
Average Case: O(n + k)
Space complexity: O( k *number_of_threads), as each thread maintains its own count array.
Stability: Stable, as it maintains the relative order of elements with equal values.
Inplace: No, it requires additional space for counting.
IsParallel: Yes, the counting process is distributed across multiple threads.
*/
int MTCountingSort(char *arr, size_t size, size_t num_of_threads);


#endif /*__MT_COUNTING_SORT__*/