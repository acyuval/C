/******************************************************************************
 *	Author:    Yuval
 *	Reviewer : 
 *	Date:
 ******************************************************************************/
#include <vector>
#include <iostream>
#include <string> // For strcpy() and strlen()
#include <cstring> 
#include "ass_2.h" 
/******************************************************************************
 *							 DECLARATION								 		  *
 ******************************************************************************/


int main() 
{
    std::string str{"To be, or not to be, that is the question:"};
    str = exclaim(str);
    std::cout << str << std::endl;
   return 0;
}
/******************************************************************************
 *							 FUNCTIONS 										  *
 ******************************************************************************/


/******************************************************************************
 *							STATIC FUNCTIONS 								  *
 ******************************************************************************/
