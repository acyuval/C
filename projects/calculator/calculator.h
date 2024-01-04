#ifndef __CALCULATOR_H__
#define __CALCULATOR_H__


typedef enum ret_values
{
    SUCCESS = 0,
    MATH_ERROR,
    SYNTAX_ERROR,
    ALLOCATION_ERROR
}status_t;
/******************************************************************************
*Description: Calculate the expression.
*Arguments: String containing the expression,
*           Pointer to a place to store the result.
*Return Value:  0 - Success
*               1 - Math Error
*               2 - Syntax Error
*               3 - Allocation Error
*Time Complexity: O(n)
*Space Complexity: O(n)
*Notes: Using state machine design patern.
******************************************************************************/
status_t Calculate(const char *expression, double *res);

#endif /*__CALCULATOR_H__*/
