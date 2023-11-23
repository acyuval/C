/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Artur
*	Date:      
******************************************************************************/

#include <stdio.h>  /* printf()  	  */
#include <string.h> /* strcpy()		  */

#include "ws9.h"

int Serialize(student * this_student)
{
	FILE *file = fopen("struct.bin", "wb+");
	if(NULL == file)
	{
		printf("couldnt load file\n");
		return 1;
	}
	
	fwrite(this_student,sizeof(student), 1, file);

	if(fclose(file))
	{
		printf("failed to close file\n");
		return 1;
	}

	return 0;
}

int DeSerialize(student * this_student)
{
	FILE *file = fopen("struct.bin", "rb");

	if(NULL == file)
	{
		printf("couldnt load file ");
		return 1;
	}
	
	fread(this_student,sizeof(student), 1, file);
	
	if(fclose(file))
	{
		printf("failed to close file\n");
		return 1;
	}

	return 0;
}

void InitStruct(student * this_student, char * first_name , char * last_name ,float grades[6])
{
	strcpy(this_student->first_name, first_name);
	strcpy(this_student->last_name, last_name);
	this_student->grades.human_grades.psychology = grades[0];
	this_student->grades.human_grades.sociology = grades[1];
	this_student->grades.human_grades.literature = grades[2];
	this_student->grades.real_grades.math = grades[3];
	this_student->grades.real_grades.physics = grades[4];
	this_student->grades.sport = grades[5];
}

void print_struct(student * this_student)
{
	printf("name: %s %s\n", this_student->first_name,this_student->last_name);
	printf("GRADES:\n\n");
	printf("Psychology:%f\n" , this_student->grades.human_grades.psychology);
	printf("sociology:%f\n" , this_student->grades.human_grades.sociology);
	printf("literature:%f\n" , this_student->grades.human_grades.literature);
	printf("math:%f\n" , this_student->grades.real_grades.math);
	printf("physics:%f\n" , this_student->grades.real_grades.physics);
	printf("sport:%f\n--------------------------------\n\n" , this_student->grades.sport);
}

