/******************************************************************************
*	Author:    Yuval 
*	Reviewer : Artur
*	Date:      
******************************************************************************/

#ifndef __WS9_H__
#define __WS9_H__


typedef struct student 
{
	char first_name[20];
	char last_name[20];
	struct grades
	{
		struct human_grade
		{
			float psychology;
			float sociology;
			float literature; 
		}human_grades;
		
		struct real_grades
		{
			float math;
			float physics;
		}real_grades;
		
		float sport;
	}grades;
}student;




/******************************************************************************
*	description: this function create new student struct
*	arguments: grades array is as [psychology, sociology ,literature 
*							, math ,physics ,sport]
*	notes:	undifined behaivor when first name / last name is more then 20 
*									chars
******************************************************************************/ 
void InitStruct(student * this_student, char * first_name , char * last_name ,float grades[6]);


/******************************************************************************
*	description: this function will serializ student struct to binary file 
	name "struct.bin"
******************************************************************************/ 
int Serialize(student * this_student);


/******************************************************************************
*	description: this function will deserializ from binary file 
	name "struct.bin" to student struct. 
******************************************************************************/ 
int DeSerialize(student * this_student);


/******************************************************************************
*	description: this function will print student name and grades to stdout
******************************************************************************/
void print_struct(student * this_student);


#endif /*	WS9_H        	*/
