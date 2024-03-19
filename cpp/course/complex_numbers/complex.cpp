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
#include "complex.h"
/******************************************************************************
 *							 DECLARATION								 		  *
 ******************************************************************************/
using namespace std;

void complex::print()
{
    cout << "real: " << real << " img: " << img << endl;
}

complex::complex(double r, double i): real(r), img(i) 
{
    cout << "constractor called" << endl;
}

complex::complex(double r): real(r), img(0) 
{
    cout << "constractor called" << endl;
}

complex operator +=(complex& lhs,const complex& rhs)
{
    lhs.real += rhs.real;
    lhs.img += rhs.img;
    return lhs;
}

complex operator +(complex& lhs,const complex& rhs)
{
    operator +=(lhs,rhs);
    return lhs;
}


/******************************************************************************
 *							 FUNCTIONS 										  *
 ******************************************************************************/


/******************************************************************************
 *							STATIC FUNCTIONS 								  *
 ******************************************************************************/
