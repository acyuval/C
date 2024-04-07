/******************************************************************************
 *	Author:    Yuval
 *	Reviewer : 
 *	Date:
 ******************************************************************************/
#include <vector>
#include <algorithm>
#include <iostream>
#include <string> // For strcpy() and strlen()
#include <cstring>
#include <iterator>
#include <vector>
#include <map> 
#include "ass.h" 
using namespace std;
/******************************************************************************
 *							 DECLARATION								 		  *
 ******************************************************************************/

class New_exe :public exception 
{
    public:
    const char* what() const noexcept override
    {
        cout << "new exception" << endl;
    } 
};





int main() 
{
    vector <int> new_vec(10); 

    for(size_t i = 0 ; i < 12 ; i++)
    {
        try
        {
            
            try
            {
                new_vec.at(i);
            }
            catch(const exception& e)
            {

                throw New_exe();
            }
        }
        catch(const exception& new_e)
        {
            new_e.what();
        }
    }

    return 0;
}
/******************************************************************************
 *							 FUNCTIONS 										  *
 ******************************************************************************/


/******************************************************************************
 *							STATIC FUNCTIONS 								  *
 ******************************************************************************/
