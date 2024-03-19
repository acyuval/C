/******************************************************************************
 *	Author:    Yuval
 *	Reviewer : 
 *	Date:
 ******************************************************************************/
#include <vector>
#include <iostream>
#include <string> // For strcpy() and strlen()
#include <cstring> 
#include "ass4.h" 
/******************************************************************************
 *							 DECLARATION								 		  *
 ******************************************************************************/
class Test 
{ 
    int X{42}, Y{99}, Z{23};
    int y{1};
    
    public:
        void TestLambda()
        {
            auto lam = [=]() mutable {++X ; ++Y; Z = X+Y;};

            lam();  
            lam();
            lam();  
            std::cout << "Z = " << Z << std::endl; 
        }
        void TestL2()
        {
            auto lam2 = [y = y+1](int x) { return x + y; };
            
            std::cout << "value of y is: " << y << std::endl;
            std::cout << "and value returned is: " << lam2(1) << std::endl;
        }
};

int main() 
{
    std::vector <int> test_vec{1, 2, 3, 4, 5};

    DisplayAll(test_vec);

    SortBy(test_vec); 
    std::cout << std::endl;
    
    DisplayAll(test_vec);

    Test test{};
    test.TestLambda();
    std::cout << std::endl;
    std::cout << std::endl;
    test.TestL2();
    return 0;
}
/******************************************************************************
 *							 FUNCTIONS 										  *
 ******************************************************************************/


/******************************************************************************
 *							STATIC FUNCTIONS 								  *
 ******************************************************************************/
