#include <stdio.h>

int main()
{
	char* str = foo();
	puts("This will never be printed");
	return 0;
}

char * foo()
{
	puts("bla");
	return ("one");
}