/******************************************************************************
 *	Author:    Yuval
 *	Reviewer : 
 *	Date:
 ******************************************************************************/
#include <vector>
#include <iostream>
#include <string> // For strcpy() and strlen()
#include <cstring> 
/******************************************************************************
 *							 DECLARATION								 		  *
 ******************************************************************************/

/******************************************************************************
 *							 FUNCTIONS 										  *
 ******************************************************************************/

std::string exclaim(std::string& to_change)
{
    
    for(auto &c: to_change)
    {
        if (ispunct(c))
        {
            c = '!';
        }
    }
    return to_change;
}

/******************************************************************************
 *							STATIC FUNCTIONS 								  *
 ******************************************************************************/
