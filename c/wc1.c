#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* print 'hello world!" from hex numbers: */

void PrintFromHex() 
{
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",0x22 ,0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20,0x57, 0x6F, 0x72, 0x6C, 0x64, 0x21, 0x22, 0x0A); 
}

/* preform 10^n :  */

double TenToThePowerN(int n)
{
	int i = 0; 
	double base = 10;
	double result = 1;
	if (n < 0) 
	{
		n = n * (-1);
		base = 1 / base;		
	}									/* end if */
	for(i = 0; i < n; i++)
	{
		result = base * result;
	}									/* end for */
	return result;	
}


/* flip the order of digit in an int number: */

int ChangeOrderOfDigit(int n) 
{
	int result = 0; 
	int sign = 1;					     		       /* represent the sign on n */ 
	
	if (n<0)
	{
		sign = -1;
		n = n * (-1);
	}									/* end if */
	
	while(n>0)
	{
		result = (10 * result) + n % 10;
		n = n / 10;
	}									/* end while */
	
	return sign*result;
}

/* swap value of two varibles: */

void SwapVar (int *ptr1, int *ptr2)
{
	int temp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = temp;
}


/* test functions: */
 
int TestTenToThePowerN()
{
	int test_values[] = {2 , -1 , 0 , -4}, i = 0;
	printf("\nTestTenToThePowerN:\n");	
	for(i = 0 ; i < 4 ; i++)
	{
		double result = TenToThePowerN(test_values[i]);
		printf("10 ^ %d: %f , check: ", test_values[i] , result);
		if(fabs(result - pow(10, test_values[i])) < 0.00001) 
		{
			printf("sucsses!! \n");
		}										/* end if */
 		else 
		{
			printf("failed pow function gives: %f\n", pow(10, test_values[i]));
		}							                        /* end else */
	}									    		/* end for */
	return 0;
}

int TestChangeOrderOfDigit() 
{
	int test_values[] = {223 , -2123 , 204 , -224}, i = 0;
	printf("\nTestChangeOrderOfDigit:\n");	
	for(i = 0 ; i < 4 ; i++)
	{
	printf("%d:::%d\n", ChangeOrderOfDigit(test_values[i]) , test_values[i]);
	}									   		/* end for */
	return 0;
}

int TestSwapVar()
{
	int test_values[] = {1 , 2 , 3 , 4};
	int i;
	printf("\nTestSwapVar:\n");
	for(i = 0 ; i < 4 ; i++)
	{
		printf("%d:::%d ", test_values[i],test_values[i+1]);
		SwapVar(&test_values[i],&test_values[i+1]);
		printf("%d:::%d\n", test_values[i],test_values[i+1]);
		i++;
	}											/* end for */
	return 0;

}



int main()
{
	PrintFromHex();
	TestTenToThePowerN();
	TestChangeOrderOfDigit();
	TestSwapVar();
	return 0;	
}



