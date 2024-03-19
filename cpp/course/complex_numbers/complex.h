/******************************************************************************
 *	Author:    Yuval
 *	Reviewer : 
 *	Date:
 ******************************************************************************/
#ifndef __ASS2_H__
#define __ASS2_H__
#include <string>
 
class complex
{
    private: 

        double real; 
        double img; 

    public: 

        void print();
        complex(double r, double i);
        complex(double r);
        friend complex operator + (complex& lhs,const complex& rhs);
        friend complex operator +=(complex& lhs,const complex& rhs);


};

#endif /*__ASS2_H__*/
