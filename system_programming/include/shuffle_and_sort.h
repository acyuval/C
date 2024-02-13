#ifndef __SHUFFLE_AND_SORT__
#define __SHUFFLE_AND_SORT__

/*
Name: SortAndMerge
Description: Sorts an array using multiple threads and merges them into a single sorted array.
Arguments: 
    - unsigned char *arr[]: A valid array of pointers.
    - size_t size: the number of pointers in the array (corresponds to the number of words in a file). 
    - size_t num_of_threads: The number of threads to be used for parallel sorting.
Return: 
    - int: Returns 0 on success, or a non-zero error code on failure.
Time complexity: O()
Space complexity: O(n)
*/
int SortAndMerge(char **arr, size_t size, size_t num_of_threads);

#endif /*__SHUFFLE_AND_SORT__*/