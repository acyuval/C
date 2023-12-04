/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Artur
*	Date:      
******************************************************************************/
#include <stdio.h>  /* printf()  	  */

#include "dynamicV.h"

static void TestHelper(int booll , char * calling_function, int test_no); 
void TestVectorCreate();
void TestVectorPushBack();
void TestVectorPopBack();
void TestVectorGetAccess();
void TestVectorSize();
void TestVectorCapacity();
void TestVectorReserve();

void TestVectorShrink();

int main()
{

	TestVectorCreate();
	TestVectorPushBack();
	TestVectorPopBack();
	TestVectorGetAccess();
	TestVectorSize();
	TestVectorCapacity();
	TestVectorReserve();
	TestVectorShrink();
	return (0);
}


void TestVectorCreate()
{
	vector_t * this_vector = NULL;
	this_vector = VectorCreate(sizeof(int), 12);
	TestHelper(NULL != this_vector,"TestVectorCreate", 1);
	
}



void TestVectorPushBack()
{
	int i = 4;
	vector_t * this_vector = VectorCreate(sizeof(int), 12);
	
	VectorPushBack(this_vector, &i);
	VectorPushBack(this_vector, &i);
	VectorPushBack(this_vector, &i);
	VectorPushBack(this_vector, &i);

	TestHelper(4 == *(int *)VectorGetAccess(this_vector,1),"TestVectorPushBack", 1);
	VectorDestroy(this_vector);
}


void TestVectorPopBack()
{
	int input[2] = {4,2};
	vector_t * this_vector = VectorCreate(sizeof(int), 12);
	VectorPushBack(this_vector,&input[0]);
	VectorPushBack(this_vector,&input[1]);
	VectorPopBack(this_vector);
	
	TestHelper(1 == VectorSize(this_vector), "TestVectorPopBack", 1);
	
	TestHelper(6 == VectorCapacity(this_vector), "TestVectorPopBack", 2);
	
	VectorDestroy(this_vector);
	
}


void TestVectorGetAccess()
{
	
	int input[2] = {4,2};
	vector_t * this_vector = VectorCreate(sizeof(int), 12);
	VectorPushBack(this_vector,&input[0]);
	VectorPushBack(this_vector,&input[1]);
	
	TestHelper(2 == *(int *)VectorGetAccess(this_vector,1),"TestVectorGetAccess", 1);
	VectorDestroy(this_vector);
}




void TestVectorSize()
{
	
	int input[2] = {4,2};
	vector_t * this_vector = VectorCreate(sizeof(int), 12);
	
	TestHelper(0 == VectorSize(this_vector),"TestVectorSize", 1);
	
	VectorPushBack(this_vector,&input[0]);
	
	TestHelper(1 == VectorSize(this_vector),"TestVectorSize", 2);
	
	VectorDestroy(this_vector);

}


void TestVectorCapacity()
{
	
	vector_t * this_vector = VectorCreate(sizeof(int), 12);
	
	TestHelper(12 == VectorCapacity(this_vector),"TestVectorCapacity", 1);
	
	VectorDestroy(this_vector);


}



void TestVectorShrink()
{
	
	int i = 0;
	
	vector_t * this_vector = VectorCreate(sizeof(int), 12);
	
	
	for(i=0;i<16; i++)
	{
		VectorPushBack(this_vector, &i);
	}
	
	VectorShrink(this_vector);
	
	TestHelper(16 == VectorSize(this_vector),"TestVectorShrink", 1);
	
	VectorDestroy(this_vector);


}



void TestVectorReserve()
{
	vector_t * this_vector = VectorCreate(sizeof(int), 12);
	
	VectorReserve(this_vector, 50);
	
	TestHelper(50 == VectorCapacity(this_vector),"TestVectorReserve", 1);
	
	VectorDestroy(this_vector);


}

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

