/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Igal
*	Date:      
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h> 
#include <string.h>
#include "ws8.h"

#define ARRAYSIZE(x) (sizeof x/sizeof x[0])
#define NO_elements 3

enum typeofdata 
{
	int_e = 0,
	float_e = 1,
	string_e = 2
};

struct items
{ 
	size_t data;
	void (op_print)();
	void (op_add)()
	void (op_clean)() 	
};
 	  
 	  
struct items ** InitArr()
{
	int i = 0;
	char * string = NULL;
	float floatt = 0.0;
	int intt = 0; 
	
	struct items ** ptrs = (struct items**)(malloc(sizeof(void*) * NO_elements));
	
	for (i=0; i< NO_elements ; i++)
	{
		*(ptrs+i) =  (struct items*)malloc(sizeof(struct items));
		((*(ptrs+i))-> ptr) = (void *)(malloc(sizeof(20)));
	}
	
	floatt = 12.44;
	intt = 18;
	
	((*ptrs)-> ptr) = "string";
	((*ptrs)-> type) = string_e;
	
	memcpy(((*(ptrs+1))-> ptr), &floatt , 4 );
	((*ptrs+1)-> type) = float_e;
	
	memcpy(((*(ptrs+2))-> ptr), &intt , 4 ); 
	((*ptrs+2)-> type) = int_e;
	
	

	printf("in here : %d \n" , *(int *)(*(ptrs+2))->ptr);
	
	return (ptrs);
 		
}

int print_me(struct items ** ptrs )
{
	int i = 0;
	struct items * this_struct_ptr = NULL; 
	for(i =0 ; i < NO_elements ; i++)
	{
		this_struct_ptr = *(ptrs+i); 
		switch (this_struct_ptr->type)
		{ 
		case int_e: 
			printf("1");
			printf("%d \n" , *(int *)(this_struct_ptr->ptr));	
			break;
		case float_e: 
			printf("2");
			printf("%f \n" , *(float *)(this_struct_ptr->ptr));
			break;
		case string_e: 
			printf("3");
			printf("%s \n" , (char *)(this_struct_ptr->ptr));
			break;				
		}	
	}
	return 0;
}


int main()
{
	struct items ** ptrs = InitArr();
	print_me(ptrs);

	return 0;
}


