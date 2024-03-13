#include <stdio.h>

int main() {

    int max = 0;
    int myArray[10] = {1, -2, 3, 4, 5, 6, -7, 8, -9, -10};
    int i = 0;   
    max = FindMax(myArray , 10);


    printf("Array elements: ");
    for (i = 0; i < 10; i++) {
        printf("%d ", myArray[i]);
    }

    printf("\n\nmax sum subarray : %d", max);
    return 0;
}


int FindMax(int * arr , size_t size)
{
    int max_sum = 0 ; 
    int runner = 0 ;
    int sum = 0 ;
    while (runner < size)
    {   
        if (sum+arr[runner]> arr[runner])
        {
            sum += arr[runner];
        }
        else 
        {   
            sum = arr[runner];
        }
        max_sum = max_sum > sum ? max_sum:sum ;
        runner++; 
    }
    return max_sum;

}