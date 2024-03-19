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
/******************************************************************************
 *							 DECLARATION								 		  *
 ******************************************************************************/

/******************************************************************************
 *							 FUNCTIONS 										  *
 ******************************************************************************/
using namespace std; 
int DisplayAll(vector <int> vec)
{
    for (auto element: vec)
    {
        cout << element << ", " ; 
    }
    cout << endl;

    return 1;
}
int SortBy(vector <int> &vec)
{
    //sort(begin(vec),end(vec), 
    //[] (int compare, int target) {return (compare > target);});
    sort(begin(vec), end(vec), greater<int>());
    return 1;
}
/******************************************************************************
 *							STATIC FUNCTIONS 								  *
 ******************************************************************************/
