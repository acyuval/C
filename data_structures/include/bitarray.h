#ifndef _BITARRAY_H_
#define _BITARRAY_H_

#include <stddef.h> /* size_t */

typedef size_t bitarray_t;

/******************************************************************************
*Description: returns the value of the element at index position
*Arguments: bitarray , index
*Return Value: value of element at index position (0 or 1)
*Time Complexity: O(n)
*Space Complexity: O(1)
*Notes: undefined behavior for invalid index
******************************************************************************/
int BitArrayGetVal(bitarray_t b_arr, size_t index);


/******************************************************************************
*Description: sets the value of the element at index position according to 
              bool_val
*Arguments: bitarray, index, value
*Return Value: the modified bitarray
*Time Complexity: O(n)
*Space Complexity: O(1)
*Notes: undefined behavior for invalid index, or bool_val is not 0/1
******************************************************************************/
bitarray_t BitArraySetBit(bitarray_t b_arr, size_t index, int bool_val);

/******************************************************************************
*Description: sets the value of the element at index position to 1
*Arguments: bitarray, index
*Return Value: the modified bitarray
*Time Complexity: O(n)
*Space Complexity: O(1)
*Notes: undefined behavior for invalid index
******************************************************************************/
bitarray_t BitArraySetOn(bitarray_t b_arr, size_t index);

/******************************************************************************
*Description: sets the value of the element at index position to 0
*Arguments: bitarray, index
*Return Value: the modified bitarray
*Time Complexity: O(n)
*Space Complexity: O(1)
*Notes: undefined behavior for invalid index
******************************************************************************/
bitarray_t BitArraySetOff(bitarray_t b_arr, size_t index);

/******************************************************************************
*Description: sets all elements values to 0
*Arguments: bitarray
*Return Value: the modified bitarray
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
bitarray_t BitArrayResetAll(bitarray_t b_arr);

/******************************************************************************
*Description: sets all elements values to 1
*Arguments: bitarray
*Return Value: the modified bitarray
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
bitarray_t BitArraySetAll(bitarray_t b_arr);

/******************************************************************************
*Description: sets the value of the element at index position from 0 to 1,
              or 1 to 0
*Arguments: bitarray, index
*Return Value: the modified bitarray
*Time Complexity: O(n)
*Space Complexity: O(1)
*Notes: undefined behavior for invalid index
******************************************************************************/
bitarray_t BitArrayFlip(bitarray_t b_arr, size_t index);

/******************************************************************************
*Description: returns the amount of elements that thier value is 1
*Arguments: bitarray
*Return Value: the amount of elements that thier value is 1
*Time Complexity: O(n)
*Space Complexity: O(1)
******************************************************************************/
size_t BitArrayCountOn(bitarray_t b_arr);

/******************************************************************************
*Description: returns the amount of elements that thier value is 0
*Arguments: bitarray
*Return Value: the amount of elements that thier value is 0
*Time Complexity: O(n)
*Space Complexity: O(1)
******************************************************************************/
size_t BitArrayCountOff(bitarray_t b_arr);

/******************************************************************************
*Description: returns a string representation of the bitarray
*Arguments: bitarray, buffer to return
*Return Value: modified buffer
*Time Complexity: O(n)
*Space Complexity: O(1)
*Notes: undefined behavior if buffer's len is less than 64
******************************************************************************/
char *BitArrayToString(bitarray_t b_arr, char *buffer);

/******************************************************************************
*Description: rotates the bitarray's elements to the left 
*Arguments: bitarray, offset
*Return Value: the modified bitarray
*Time Complexity: O(n)
*Space Complexity: O(1)
******************************************************************************/
bitarray_t BitArrayRotateLeft(bitarray_t b_arr, size_t offset);

/******************************************************************************
*Description: rotates the bitarray's elements to the right 
*Arguments: bitarray, offset
*Return Value: the modified bitarray
*Time Complexity: O(n)
*Space Complexity: O(1)
******************************************************************************/
bitarray_t BitArrayRotateRight(bitarray_t b_arr, size_t offset);

/******************************************************************************
*Description: mirror's the bitarray
*Arguments: bitarray
*Return Value: the modified bitarray
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
bitarray_t BitArrayMirror(bitarray_t b_arr);

/******************************************************************************
*Description: returns the amount of elements that thier value is 1 using LUT
*Arguments: bitarray
*Return Value: the amount of elements that thier value is 1
*Time Complexity: O(n)
*Space Complexity: O(1)
******************************************************************************/
size_t BitArrayCountOnLUT(bitarray_t b_arr);

/******************************************************************************
*Description: mirror's the bitarray using LUT
*Arguments: bitarray
*Return Value: the modified bitarray
*Time Complexity: O(1)
*Space Complexity: O(1)
******************************************************************************/
bitarray_t BitArrayMirrorLUT(bitarray_t b_arr);


#endif	/* _BITARRAY_H_*/
