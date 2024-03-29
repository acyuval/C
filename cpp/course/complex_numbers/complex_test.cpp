/******************************************************************************
 *	Author:    Yuval
 *	Reviewer : 
 *	Date:
 ******************************************************************************/
#include <vector>
#include <iostream>
#include <string> // For strcpy() and strlen()
#include <cstring> 
#include "complex.h" 
/******************************************************************************
 *							 DECLARATION								 		  *
 ******************************************************************************/


int main() 
{
    complex A{3.2, 4.1};
    complex B{9, 1};
    complex R{1};
    A.print();
    B.print();
    R.print(); 

    
    (A+B).print();
    return 0;
}
/******************************************************************************
 *							 FUNCTIONS 										  *
 ******************************************************************************/


/******************************************************************************
 *							STATIC FUNCTIONS 								  *
 ******************************************************************************/
