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

class URL {
private:
    std::string protocol;
    std::string resource; 


public:

    URL(const std::string &input_protocol , const std::string &input_resource) : 
                        protocol(input_protocol) , resource(input_resource) {}

    void display()
    {
        std::cout << "this is:" << protocol << "://"  << resource << std::endl;
    }
};


int main() 
{
    URL new_test_url("http", "www.url.com");
    new_test_url.display();

    std::string str("hello_world");
    std::vector<int> vec{3,5,2,1,54,6,23,2,1};
    std::string::iterator it = str.begin();
    std::vector<int>::iterator it_vec = vec.begin();
    auto auto_it = vec.begin();
    
    while (auto_it != vec.end())
    {
        std::cout << *auto_it << "-" ;
        auto_it.operator++(); 
    }
    std::cout << std::endl;
    for(auto& ref:vec)
    {
        ref += 2;
    }
    auto rauto_it = vec.rbegin();
    while (rauto_it != vec.rend())
    {
        std::cout << *rauto_it << "-" ;
        rauto_it.operator++(); 
    }
    return 0;
}
/******************************************************************************
 *							 FUNCTIONS 										  *
 ******************************************************************************/


/******************************************************************************
 *							STATIC FUNCTIONS 								  *
 ******************************************************************************/
