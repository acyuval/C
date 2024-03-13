/******************************************************************************
 *	Author:    Yuval
 *	Reviewer : 
 *	Date:
 ******************************************************************************/
#include <vector>
#include <iostream>
#include <string> // For strcpy() and strlen()
#include <cstring> 
#include <fstream>
/******************************************************************************
 *							 DECLARATION								 		  *
 ******************************************************************************/

/******************************************************************************
 *							 FUNCTIONS 										  *
 ******************************************************************************/

std::string file(std::string str)
{
    std::vector <std::string> vec_double{"hello0" , "what1","yey1"};
    std::fstream file {str , std::ios::in | std::ios::out};
    if (false == file.is_open())
    {
        file.open(str,std::ios::out);
        if (false == file.is_open())
        {
            std:: cout << "coulnt open again";
        }
    }

    for(auto dou: vec_double)
    {
        file << dou;
        file << std::endl;
    }
 
    return "success";
}

/******************************************************************************
 *							STATIC FUNCTIONS 								  *
 ******************************************************************************/
