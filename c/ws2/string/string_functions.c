#include <stdio.h>
#include <stdlib.h>

unsigned int MyStrLen(char *p)
{
    unsigned int counter = 0;

    while(*p != '\0')
    {
        counter++;
        p++;
    }

    return counter;
}

int MyStrCmp(const char* str1, const char* str2)
{

	do
        {
        	if (*str1 != *str2) 
        	{
        		return (*str1 - *str2)
        		
        	}
        	
        	str1++; str2++;
        }while(*str1 != '\0' || *str2 != '\0');
     	
     	return 0;

}

void TestMyStrCmp()
{
	char str1[] = "hello4";
	char str2[] = "hello4";
	printf("\nTestMyStrCmp result : %d\n" , MyStrCmp(str1,str2)); 
	
}

void TestMyStrLen()
{
	char str1[] = "hel231231321231lo";
	printf("----------------------------------------");
	printf("\nMyStrLen Len is : %d\n" , MyStrLen(str1)); 
}



