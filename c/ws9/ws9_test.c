/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Artur
*	Date:      
******************************************************************************/
#include <stdio.h>  /* printf()  	  */
#include <string.h> /*  strcpy()	  */
#include <stdlib.h> /* Exit		  */

#include "ws9.h"

#define NO_OF_TESTS 9

int number_of_test_succses = 0;
void test(int booll);
int TestGradesLogger();
void TestStructSerializition(student * Src_student,student * dest_student);

int main()
{
	TestGradesLogger();
	return 0;
}

int TestGradesLogger()
{
	student new_student = {0};
	student loaded_student = {0};
	
	float new_student_grades[6] = {23.4,50,100,23,45,99}; 	
	
		
	InitStruct(&new_student, "Yaron", "shpilman",new_student_grades);
		
	print_struct(&new_student);
	
	if(Serialize(&new_student))
	{
		exit(1);
	}
	
	if(DeSerialize(&loaded_student))
	{
		exit(1);
	}
	
	TestStructSerializition(&new_student,&loaded_student);
	return 0;
}



void TestStructSerializition(student * Src_student,student * dest_student)
{
	test(!strcmp(Src_student->first_name,  dest_student->first_name));
	test(!strcmp(Src_student->last_name,  dest_student->last_name));
	test(Src_student->grades.sport == dest_student->grades.sport);
	test(Src_student->grades.human_grades.psychology == dest_student->grades.human_grades.psychology);
	test(Src_student->grades.human_grades.sociology == dest_student->grades.human_grades.sociology);
	test(Src_student->grades.human_grades.literature == dest_student->grades.human_grades.literature);
	test(Src_student->grades.real_grades.math = dest_student->grades.real_grades.math);
	test(Src_student->grades.real_grades.physics == dest_student->grades.real_grades.physics);
	test(Src_student->grades.sport == dest_student->grades.sport);
	
	if (number_of_test_succses == NO_OF_TESTS)
	{
		printf("TestStructSerializition Succsess!\n\n");
	}
}


void test(int booll)
{
	if(booll)
	{
		number_of_test_succses++;
	}
	else
	{
		printf("failed in no %d\n", number_of_test_succses);
	}
}

