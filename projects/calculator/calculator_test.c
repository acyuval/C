#include <stdio.h>

#include "calculator.h"


int main()
{
    double result = 0;
    const char * str = "1+6*2+3-4";
    Calculate(str, &result);
    return (0);
}

