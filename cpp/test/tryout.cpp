
#include <assert.h> /* assert			  */
#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <iostream>
using namespace std;
int main()
{
    int a = 7;
    int *ptr = &a;
    cout << ptr << endl;
    cout << *ptr << endl;
    *(char*)&ptr = 1;
    cout << ptr << endl;
    cout << *ptr << endl;

}

