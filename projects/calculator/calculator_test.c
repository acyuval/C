#include <stdio.h>

#include "calculator.h"


int main()
{
    double result = 0;
    const char * str = "5*3*(2+3)^2";
    Calculate(str, &result);
    return (0);
}

