/******************************************************************************
 *	Author:    Yuval
 *	Reviewer : 
 *	Date:
 ******************************************************************************/
#include <vector>
#include <iostream>
#include <string> 
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>
/******************************************************************************
 *							 DECLARATION								 		  *
 ******************************************************************************/

/******************************************************************************
 *							 FUNCTIONS 										  *
 ******************************************************************************/
using namespace std;
 
bool CheckForPalindromes(string str)
{
    auto defunct = remove_if(begin(str), end(str), [](char c) {return (c== ' ');});
    
    str.erase(defunct, end(str));
    
    transform(begin(str), end(str), begin(str), [](char c) {return toupper(c);});

    cout << str << endl;

    auto retval = mismatch(cbegin(str), cend(str), crbegin(str));

    cout << "the mis match is " << *retval.second << endl;
    if(retval.first == end(str))
    {
        return true;
    }

    return false;

}
/******************************************************************************
 *							STATIC FUNCTIONS 								  *
 ******************************************************************************/
