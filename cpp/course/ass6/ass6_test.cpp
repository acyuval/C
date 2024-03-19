/******************************************************************************
 *	Author:    Yuval
 *	Reviewer : 
 *	Date:
 ******************************************************************************/
#include <vector>
#include <iterator>
#include <iostream>
#include <string> // For strcpy() and strlen()
#include <cstring> 
#include <random>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <sstream>
#include "ass6.h"
/******************************************************************************
 *							 DECLARATION								 		  *
 ******************************************************************************/
using namespace std;
int main() 
{
    auto vec = GetInputVec();

    auto deq = GetInputDeque();

    auto lis = GetInputList();

    reverse(deq.begin(),deq.end());
    reverse(lis.begin(),lis.end());
    show<deque<string>>(deq,"rev-deque");
    show<list<string>>(lis,"rev-list");
    return 0;
}
/******************************************************************************
 *							 FUNCTIONS 										  *
 ******************************************************************************/


/******************************************************************************
 *							STATIC FUNCTIONS 								  *
 ******************************************************************************/
