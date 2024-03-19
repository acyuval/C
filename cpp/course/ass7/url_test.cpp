/******************************************************************************
 *	Author:    Yuval
 *	Reviewer : 
 *	Date:
 ******************************************************************************/
#include <vector>
#include <iostream>
#include <string> // For strcpy() and strlen()
#include <cstring> 
#include "url.h" 
/******************************************************************************
 *							 DECLARATION								 		  *
 ******************************************************************************/
using namespace std;
int main() 
{
    URL new_test_url("http", "www.url.com");
    URL new_test_url2("http", "www.url2.com");
    URL new_test_url3("http", "www.url3.com");

    HISTORY urls; 

    urls.SaveURL(new_test_url);
    urls.SaveURL(new_test_url2);
    urls.SaveURL(new_test_url3);
    
    cout <<"front of the list is: " << urls.PopFront() << endl;

    urls.SaveURL(new_test_url2);

    cout <<"front of the list is: " << urls.PopFront() << endl;

    
    return 0;
}
/******************************************************************************
 *							 FUNCTIONS 										  *
 ******************************************************************************/


/******************************************************************************
 *							STATIC FUNCTIONS 								  *
 ******************************************************************************/
