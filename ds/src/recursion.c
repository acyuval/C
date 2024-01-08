    
    /******************************************************************************
*	Author:    Yuval 
*	Reviewer : Dor
*	Date:      
******************************************************************************/

#include <stdlib.h> /* malloc() , free()  */
#include <assert.h> /* assert			  */
#include <stdio.h>
#include <string.h>
#include "../include/recursion.h"
#include "../include/stack.h"
#include "../include/utiles.h"

/******************************************************************************
*							 DECLRATION								  * 
******************************************************************************/
void SortedInsert(stack_t *stack, int peek);
/******************************************************************************
*							 FUNCTIONS 										  * 
******************************************************************************/

int IterativeFibonacci(int element_index)
{
    int i = 0 ;
    int prevprev = 0;
    int prev = 1;
    int cur = 1; 

    while(i != (element_index-1))
    {
        cur = prev + prevprev;
        prevprev= prev; 
        prev = cur; 
        i++;
    }
    return cur; 
}

int RecursiveFibonacci(int element_index)
{
    if (element_index <= 1)
    {
        return element_index;
    }
    return (RecursiveFibonacci(element_index - 1) + RecursiveFibonacci(element_index - 2));

}



node_t *RecursiveFlipList(node_t *node)
{
    if(node->next == NULL)
    {
        return node;
    }
    (RecursiveFlipList(node->next))->next = node;
    node->next = NULL;
    return node;
}


void SortedInsert(stack_t *stack, int peek)
{
    int temp_peek = 0;

    if (StackIsEmpty(stack) || peek > *(int *)StackPeek(stack))
    {
        StackPush(stack, &peek);
        return;
    }

    temp_peek = *(int *)StackPeek(stack);

    StackPop(stack);

    SortedInsert(stack, peek);
    
    StackPush(stack, &temp_peek);

}

void SortStack(stack_t *stack)
{
    int peek = 0;

    if(StackIsEmpty(stack))
    {
        return;
    }
    peek = *(int *)StackPeek(stack);
    StackPop(stack); 
    
    SortStack(stack);
    
    SortedInsert(stack , peek);
}


size_t RecursiveStrLen(const char *s)
{
    if(*s == '\0')
    {
        return 0;
    } 

    return (1 + RecursiveStrLen(s + 1)); 
}

int RecursiveStrcmp(const char *s1, const char *s2)
{
    if (*s1 < *s2)
    {
        return -1;
    }  
    if (*s1 > *s2)
    {
        return +1;
    }
    if (*s1  == '\0')
    {
        return 0;
    }
    return RecursiveStrcmp(s1+1, s2+1);
}

char * RecursiveStrcpy(char *dest, const char *src)
{
    
    *dest = *src;
    if (*src == '\0')
    {
        return dest;
    }

    return RecursiveStrcpy(dest+1, src+1);
}

char *RecursiveStrcat(char *dest, const char *src)
{   

    if (*dest != '\0')
    {
        RecursiveStrcat(dest+1,src);
    }
    else 
    {
        *dest = *src;
        if(*dest != '\0')
        {
            RecursiveStrcat(dest+1, src+1);
        }
        else
        {
            return dest;
        }
    }
    return dest;

}

char *RecursiveStrstr(const char *haystack, const char *needle)
{
    int needle_len = RecursiveStrLen(needle); 

    if (strncmp(needle, haystack, needle_len) == 0)
    {
        return (char *)haystack;
    }

    return RecursiveStrstr(haystack + 1 ,needle);;
}

/******************************************************************************
*							STATIC FUNCTIONS								  * 
******************************************************************************/


