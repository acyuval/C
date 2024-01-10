#include <stdio.h>



double squareroot(double x);

int main() 
{

    printf ("res: %lf", squareroot(16));
    return 0;
}

	
double squareroot(double x)
{
    double xhi = x;
    double xlo = 0;
    double guess = x/2;
    double new_guess = 0;
    if (x < 1) return 1.0 / squareroot(x); 
    while (guess * guess != x)
    {
        if (guess * guess > x)
            xhi = guess;
        else
            xlo = guess;
        new_guess = (xhi + xlo) / 2;
        if (new_guess == guess)
            break; 
        guess = new_guess;
    }
    return guess;
}

size_t Hash(void *data)
{
    size_t h = 24361; /* you can play with this to get varying result */
    size_t bucket_amount = 200000; /* change this to whatever fits you */
    char *str = (char *)data;
    
    for (; '\0' != *str; ++str) 
    {
        h ^= *str;
        h *= 0x5bd1e995;
        h ^= h >> 15;
    }
    return h % bucket_amount;
}