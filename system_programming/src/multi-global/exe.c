/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Yael
*	Date:      
******************************************************************************/
#include "static.h"
#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
/******************************************************************************
*							FUNCTION DECLRATION								  * 
******************************************************************************/

x = 4;

int main()
{
	 void * dll = NULL;
	 void * dll2 = NULL;
	 void (*foo_handle)() = NULL;
	 void (*foo2_handle)() = NULL;
	 PrintGlobalVariableAddress();
	 
	 dll = dlopen("./libdyn1.so", RTLD_LAZY);
	 if (!dll)
	 {	
	 	fputs (dlerror(), stderr);
        exit(1);
     }
	 foo_handle = dlsym(dll, "foo");
	 foo_handle();
	 dlclose(dll);
	 
	 dll2 = dlopen("./libdyn2.so", RTLD_LAZY);
	 if (!dll2)
	 {	
	 	fputs (dlerror(), stderr);
        exit(1);
     }
	 foo2_handle = dlsym(dll2, "foo2");
	 
	 foo2_handle();
	 dlclose(dll2);
	 return 0;
}

/******************************************************************************
*							 FUNCTIONS 										  * 
******************************************************************************/


