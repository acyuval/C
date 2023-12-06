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
static void TestHelper(int booll , char * calling_function, int test_no);

void CreateAndFlip(void);
void CreateAndFindIntersection(void);

void CreateAndIsLoop(void);
/******************************************************************************
*							MAIN											  * 
******************************************************************************/


int main()
{
	CreateAndFlip();
	CreateAndFindIntersection();
	CreateAndIsLoop();
	return (0);
}

/******************************************************************************
*							TEST FUNCTIONS									  * 
******************************************************************************/

void CreateAndFlip(void)
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

}



void CreateAndIsLoop(void)
{

	node_t * head = NULL;
	node_t n1,n2,n3,n4,n5,n6,n7,n8;

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
	n5.next = &n6;
	n6.data = 6;
	n6.next = &n7;
	n7.data = 7;
	n7.next = &n8;
	n8.data = 8;
	n8.next = &n2;
	
	
	
	TestHelper(1 == DetectLoop(head), "Test IsLoop", 1);	
	
	n8.next = NULL;
	
	TestHelper(0 == DetectLoop(head), "Test IsLoop", 2);	

	n4.next = &n1;
	
	TestHelper(1 == DetectLoop(head), "Test IsLoop", 3);
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


