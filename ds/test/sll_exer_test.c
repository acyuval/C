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

static int input[8] = {1,2,3,4,5,6,7,8};


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
	
	n1.data = (void *)&input[1];
	n1.next = &n2;
	n2.data = (void *)&input[2];
	n2.next = &n3;
	n3.data = (void *)&input[3];
	n3.next = &n4;
	n4.data = (void *)&input[4];
	n4.next = &n5;
	n5.data = (void *)&input[5];
	n5.next = NULL;
	
	itr = head;
	printf("\nTest Flip\n------------------\n");
	printf("Before:");
	while(itr != NULL)
	{
		printf("%d ", *(int *)itr->data);
		itr = itr->next;
	}
	
	printf("\nAfter Flip:");
	itr = Flip(head);
	
	while(itr != NULL)
	{
		printf("%d ", *(int *)itr->data);
		itr = itr->next;
	}

}



void CreateAndIsLoop(void)
{

	node_t * head = NULL;
	node_t n1,n2,n3,n4,n5,n6,n7,n8;

	head = &n1;
	n1.data = (void *)&input[1];
	n1.next = &n2;
	n2.data = (void *)&input[2];
	n2.next = &n3;
	n3.data = (void *)&input[3];
	n3.next = &n4;
	n4.data = (void *)&input[4];
	n4.next = &n5;
	n5.data = (void *)&input[5];
	n5.next = &n6;
	n6.data = (void *)&input[6];
	n6.next = &n7;
	n7.data = (void *)&input[7];
	n7.next = &n8;
	n8.data = (void *)&input[8];
	n8.next = &n2;
	
	
	TestHelper(1 == HasLoop(head), "Test IsLoop", 1);	
	
	n8.next = NULL;
	
	TestHelper(0 == HasLoop(head), "Test IsLoop", 2);	

	n4.next = &n1;
	
	TestHelper(1 == HasLoop(head), "Test IsLoop", 3);
}



void CreateAndFindIntersection(void)
{

	node_t n1,n2,n3,n4;
	node_t l1,l2,l3,l4,l5;
	
	node_t * head_1 = NULL;
	node_t * head_2 = NULL;
	
	n1.data = (void *)&input[1];
	n1.next = &n2;
	n2.data = (void *)&input[2];
	n2.next = &n3;
	n3.data = (void *)&input[3];
	n3.next = &n4;
	n4.data = (void *)&input[4];;
	n4.next = &l5;
	
	l1.data = (void *)&input[1];
	l1.next = &l2;
	l2.data = (void *)&input[2];
	l2.next = &l3;
	l3.data = (void *)&input[3];
	l3.next = &l4;
	l4.data = (void *)&input[4];
	l4.next = &l5;
	l5.data = (void *)&input[5];
	l5.next = NULL;
	
	head_1= &n1;
	head_2= &l1;
	
	head_1 = FindIntersection(head_1, head_2);
	
	printf("\nvalue at the insersect: %d\n", *(int *)head_1->data);
	
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


