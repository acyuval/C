/******************************************************************************
 *	Author:    Yuval
 *	Reviewer : 
 *	Date:
 ******************************************************************************/

#include <iostream>
#include <typeinfo>
#include <cstdio>
#include <cstdlib>

/******************************************************************************
 *							 DECALRATION								 		  *
 ******************************************************************************/

#include "hear.h"

/******************************************************************************
 *							 FUNCTIONS 										  *
 ******************************************************************************/



template<typename T>
void foo(T t)
{    
    std::cout << t << " Generic foo for " << typeid(t).name() << std::endl ;
}

void foo(int t)
{
    std::cout << t << " Specialized foo (for int param)\n";
}

int main()
{   
    foo(4.2);
    foo(5);
    foo<>(5);
    char i= 'a';
    char& ip= i;
    ip= 'd';
    std::cout<< i<<std::endl;
    return 0;
}


/******************************************************************************
 *							STATIC FUNCTIONS 								  *
 ******************************************************************************/
