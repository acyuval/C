/******************************************************************************
 *	Author:    Yuval
 *	Reviewer : 
 *	Date:
 ******************************************************************************/



/* #include "hear.h" */

/******************************************************************************
 *							 DECLARATION								 		  *
 ******************************************************************************/

/******************************************************************************
 *							 FUNCTIONS 										  *
 ******************************************************************************/

#include <iostream>

struct X
{
    //explicit X(); 
    explicit X(int a_, int b_ = 8); // Regular (non default) Ctor.
    ~X(); //Deinitialization function is called destructor (Dtor).
    X(const X& other_); 
    X& operator=(const X& other_); //Assignment operator.

    int m_a;
    const int m_b;
};
/* 
X::X(): m_a(3), m_b(4) 
{
    // m_a = 3; 
    // m_b = 4;
    std::cout << "this:" << this <<
            " X default Ctor. m_a:" << m_a << 
            " m_b:" << m_b << std::endl;
}
 */
X::X(int a_, int b_): m_a(a_), m_b(b_) //Implementation of the second Ctor. 
{
    std::cout<< "this:" << this <<
        " X int int Ctor. m_a:" << m_a << 
        " m_b:" << m_b << std::endl;
}

X::X(const X& other_): m_a(other_.m_a), m_b(other_.m_b) 
{
    std::cout<< "this:" << this <<
        " X copy Ctor. m_a:" << m_a << 
        " m_b:" << m_b << std::endl;
}

X& X::operator=(const X& other_)
{
    m_a= other_.m_a;
    //  m_b= other_.m_b;
    std::cout << "this:" << this <<
        " X assignment operator. m_a:" << m_a << 
        " does not change m_b:" << m_b << std::endl;    
    return *this;
}

X::~X()
{
    std::cout << "this:" << this <<
        " X Dtor. m_a:" << m_a << 
        " m_b:" << m_b << std::endl;    
}

struct Y
{
    int x;
    const int y;
};


struct Zulo
{
    X m_x;
    int m_i;
};

int main()
{
    X x1;
    X x2(7);
    X *px = new X(x2);
    //Y * py = new Y;
    Zulo z1; 
    z1.m_x.m_a = 250;
    //Zulo z2(z1);
    Zulo z3;
    //z3 = z1;

    X x3(9,10);
    X x4(x1);
    double * xp = new double[10];
    delete xp;
    x1 = x3;

    delete px; px = 0;

    return 0;
}
/******************************************************************************
 *							STATIC FUNCTIONS 								  *
 ******************************************************************************/
