/*******************************************************************************
*Author: Arieh Farber
*******************************************************************************/
#include <stdio.h> /*printf*/
#include <math.h>  /*fabs  */

#include "calculator.h"

static void TestCalculate();

int main()
{
	TestCalculate();
	
	return (0);
}

void TestInt(int want, int got, int line);
void TestDouble(double want, double got, int line);

static void TestCalculate()
{
	status_t got_status = 0;
	status_t want_status[] = {SUCCESS, SUCCESS, SYNTAX_ERROR, MATH_ERROR, \
						 	  SYNTAX_ERROR, SYNTAX_ERROR, SYNTAX_ERROR, SUCCESS};
	char *expressions[] = {"7--8", "8+83+-2^5", "8+83-2^", "2/0", \
						   "8++8((3-2)5)", "3-2)5", "(3-2)5+5(4+4+4", \
						   "(1+3)/5"};
	double res = 0;
	double want_res[] = {15, 59, 0, 0, 0, 0, 0, 0.8};

	size_t expressions_size = sizeof(expressions) / sizeof(expressions[0]);
	size_t i = 0;
	
	for (i = 0; i < expressions_size; ++i)
	{
		got_status = Calculate(expressions[i], &res);
		TestInt(want_status[i], got_status, __LINE__);
		TestDouble(want_res[i], res, __LINE__);
		printf("\n");
	}
}

void TestInt(int want, int got, int line)
{
	if (want != got)
	{
		printf("\033[0;31m");
		printf("Error. failed at line %d\n", line);
		printf("\033[0m"); 
	}
	else
	{
		printf("\033[1;32m");
		printf("Success!\n");
		printf("\033[0m"); 
	}
}

void TestDouble(double want, double got, int line)
{
	if (fabs(want - got) > 0.001)
	{
		printf("\033[0;31m");
		printf("Error. failed at line %d\n", line);
		printf("\033[0m"); 
	}
	else
	{
		printf("\033[1;32m");
		printf("Success!\n");
		printf("\033[0m"); 
	}
}


