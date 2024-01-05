#include <stdio.h>

#include "calculator.h"


int main()
{
    double result = 0;
    const char * str = "200-5+223";
    Calculate(str, &result);
    return (0);
}

