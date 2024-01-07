#ifndef __RECURSION_H__
#define __RECURSION_H__

#include <stddef.h>

#include "stack.h"

typedef struct node
{
    void *data;
	struct node *next;
} node_t;

/******************************************************************************
 * Description: Calculates the corresponding element of the Fibonacci sequence
 *              iteratively. 
 * Arguments: Index of the number in the fibonacci sequence 
 * Return Value: Integer in the fibonacci sequence
 * Time Complexity: O(n)
 * Space Complexity: O(1)
 * Notes: 
 ******************************************************************************/
int IterativeFibonacci(int element_index);

/******************************************************************************
 * Description: Calculates the corresponding element of the Fibonacci sequence
 *              recursively. 
 * Arguments: Index of the number in the fibonacci sequence 
 * Return Value: Integer in the fibonacci sequence
 * Time Complexity: O(n)
 * Space Complexity: O(2^n)
 * Notes: 
 ******************************************************************************/
int RecursiveFibonacci(int element_index);

/******************************************************************************
 * Description: Flips entire given list direction using recursion
 * Arguments: Pointer head of list 
 * Return Value: Head of flipped list
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 * Notes: 
 ******************************************************************************/
node_t *RecursiveFlipList(node_t *node);

/******************************************************************************
 * Description: Sort stack using another recursive function
 * Arguments: Unsorted stack 
 * Return Value:
 * Time Complexity: O(n^2)
 * Space Complexity: O(n^2)
 * Notes: 
 ******************************************************************************/
void SortStack(stack_t *stack);

/******************************************************************************
 * Description: Calculate the length of a string using recursion
 * Arguments: Pointer to string str
 * Return Value: Number of bytes in the string pointed to by str
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 * Notes: 
 ******************************************************************************/
size_t RecursiveStrLen(const char *s);

/******************************************************************************
 * Description: Compare two strings
 *              •  0, if the s1 and s2 are equal;
 *              •  a negative value if s1 is less than s2;
 *              •  a positive value if s1 is greater than s2.
 * Arguments: Pointer to strings to compare s1 & s2
 * Return Value: Integer less than, equal to, or greater than zero if s1 is found, 
 *               respectively, to be less than, to match, or be greater than s2.
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 * Notes: 
 ******************************************************************************/
int RecursiveStrcmp(const char *s1, const char *s2);

/******************************************************************************
 * Description: Copy the string pointer to by src into a string at the
 *              buffer pointer to by dest.
 * Arguments: Pointer to strings src and dest
 * Return Value: Pointer to dest
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 * Notes: dest buffer must be large  enough, strlen(src) + 1, 
 *        Undefined behaviour otherwise. Also src and dest must not overlap.
 ******************************************************************************/
char *RecursiveStrcpy(char *dest, const char *src);

/******************************************************************************
 * Description: Concatenate the string pointer to by src after the string
 *              pointer to by dest (overwriting its null terminator).
 * Arguments: Pointer to strings src and dest
 * Return Value: Pointer to dest
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 * Notes: dest buffer must be large  enough, strlen(dest) + strlen(src) + 1, 
 *        Undefined behaviour otherwise. Also src and dest must not overlap.
 ******************************************************************************/
char *RecursiveStrcat(char *dest, const char *src);

/******************************************************************************
 * Description: Finds the first occurrence of the substring needle in the 
 *              string haystack.
 * Arguments: Pointer to strings haystack and needle
 * Return Value: Pointer to the beginning of the located sub-string, or NULL
 *               if not found.
 *               if needle is the empty string, return haystack.
 * Time Complexity: O(n)
 * Space Complexity: O(n)
 * Notes:
 ******************************************************************************/
char *RecursiveStrstr(const char *haystack, const char *needle);

#endif /* __RECURSION_H__ */
