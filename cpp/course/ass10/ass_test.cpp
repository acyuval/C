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
#include <map> 
#include "ass.h" 
using namespace std;
/******************************************************************************
 *							 DECLARATION								 		  *
 ******************************************************************************/

class BASE
{
    int x; 

    public:

    BASE(int xx): x{xx} {}

    virtual void print()
    {
        cout << "i am BASE" << endl;  
    }



};

class CHILD : public BASE
{
    public:
    CHILD(int x): BASE(x) {} 
    void print() override
    {
        cout << "i am CHILD" << endl;  
    }
    
};

class grandCHILD : public CHILD
{
    public: 
    grandCHILD(int x) : CHILD(x) {}
    void print() override
    {
        cout << "i am grandCHILD" << endl;  
    }
        
};

void printClass(BASE& obj)
{
    obj.print();
}

int main() 
{
   
    BASE basic(5);
    CHILD childish(3);
    grandCHILD greampa(12); 

    printClass(basic);
    printClass(childish);
    printClass(greampa);

    return 0;
}
/******************************************************************************
 *							 FUNCTIONS 										  *
 ******************************************************************************/


/******************************************************************************
 *							STATIC FUNCTIONS 								  *
 ******************************************************************************/
