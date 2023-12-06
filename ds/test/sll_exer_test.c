/******************************************************************************
*	Author:    Yuval 
*	Reviewer :
*	Date:      
******************************************************************************/
#include <stdio.h>  /* printf()  	  */

#include "sll_exer.h"


/******************************************************************************
*							TYPE DEFS / MACROS 								  * 
******************************************************************************/



/******************************************************************************
*							FUNCTION DECLRATION								  * 
******************************************************************************/
int CreateAndFlip(void);
void CreateAndFindIntersection(void);


/******************************************************************************
*							MAIN											  * 
******************************************************************************/


int main()
{
	CreateAndFlip();
	CreateAndFindIntersection();
	return (0);
}

/******************************************************************************
*							TEST FUNCTIONS									  * 
******************************************************************************/

int CreateAndFlip(void)
{

	node_t * head = NULL;
	node_t * itr = NULL;
	
	node_t n1,n2,n3,n4,n5;

	head = &n1;
	
	n1.data = 1;
	n1.next = &n2;
	n2.data = 2;
	n2.next = &n3;
	n3.data = 3;
	n3.next = &n4;
	n4.data = 4;
	n4.next = &n5;
	n5.data = 5;
	n5.next = NULL;
	
	itr = head;
	printf("\nTest Flip\n------------------\n");
	printf("Before:");
	while(itr != NULL)
	{
		printf("%d ", itr->data);
		itr = itr->next;
	}
	
	printf("\nAfter Flip:");
	itr = Flip(head);
	
	while(itr != NULL)
	{
		printf("%d ", itr->data);
		itr = itr->next;
	}

	return 0;
}


void CreateAndFindIntersection(void)
{


	list_t listA = {0};
	list_t listB = {0};
	node_t n1,n2,n3,n4,n5;
	node_t l1,l2,l3,l4,l5;
	node_t * itr = NULL;
	list_t * listA_ptr = &listA;
	list_t * listB_ptr = &listB;
	
	listA.head = &n1;
	listA.tail = &n5;
	
	listB.head = &l1;
	listB.tail = &l5;
	
	n1.data = 1;
	n1.next = &n2;
	n2.data = 2;
	n2.next = &n3;
	n3.data = 3;
	n3.next = &n4;
	n4.data = 4;
	n4.next = &l5;
	n5.data = 5;
	n5.next = NULL;
	
	l1.data = 1;
	l1.next = &l2;
	
	l2.data = 2;
	l2.next = &l3;
	
	l3.data = 3;
	l3.next = &l4;
	
	l4.data = 4;
	l4.next = &l5;
	
	l5.data = 5;
	l5.next = NULL;
	
	
	itr = FindIntersection(listA_ptr, listB_ptr);
	
	printf("\nvalue at the insersect: %d\n", itr->data);
	
}



/******************************************************************************
*							STATIC FUNCTIONS								  * 
******************************************************************************/


static void TestHelper(int booll , char * calling_function, int test_no)
{
	if(booll)
	{
		printf("%s -> \t\tNO.%d sucsess!\n\n",calling_function, test_no);
	}
	else
	{
		printf("failed in %s, No. %d\n",calling_function ,test_no);
	}
}


