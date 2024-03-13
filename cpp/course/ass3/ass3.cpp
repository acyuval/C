/******************************************************************************
 *	Author:    Yuval
 *	Reviewer : 
 *	Date:
 ******************************************************************************/
#include <vector>
#include <iostream>
#include <string> 
#include <fstream>
#include <sstream>
/******************************************************************************
 *							 DECLARATION								 		  *
 ******************************************************************************/
using namespace std;
struct language {
    string lang;
    string designer;
    int date;
};
/******************************************************************************
 *							 FUNCTIONS 										  *
 ******************************************************************************/
int get_from_file(std::string& text_name)
{
    
    vector <language> lang_vec{}; 
    ifstream file {text_name};
    if(file.is_open() == false)
    {
        cout << "couln't open file";
    }
    
    string line{}; 

    while (getline(file,line))
    {
        string lang;
        string designer;
        string buffer; 
        int date;
        istringstream smart_string{line};
        
        smart_string >> lang;
        smart_string >> date;
        while(smart_string.fail())
        {
            smart_string.clear();
            smart_string >> buffer;
            designer += ' ';
            designer += buffer;
            smart_string >> date;
        }

        lang_vec.push_back({lang, designer, date});
    }
    
    for (auto item: lang_vec)
    {
        cout << item.lang<< "," << item.designer << ", " << item.date << endl;
        
    }

    return 1;
}

/******************************************************************************
 *							STATIC FUNCTIONS 								  *
 ******************************************************************************/
