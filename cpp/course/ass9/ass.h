/******************************************************************************
 *	Author:    Yuval
 *	Reviewer : 
 *	Date:
 ******************************************************************************/
#ifndef __URL_H__
#define __URL_H__
#include <string>
#include <vector>
std::string GetInput();
void StoreInSet();
template <typename T>
void MyPrint(T cont);

class FAMILY 
{
    std::vector <std::string> children;

    public:

    void printChildrenList();
    bool addChild(std::string name);
};

class PERSON 
{
    std::string first_name;
    std::string family_name;

    public:

    PERSON(std::string first, std::string last) : first_name{first}, family_name{last}
    {}

    bool operator < (const PERSON& other)
    {
        if(this->family_name == other.family_name)
        {
            return (this->first_name < other.first_name);
        }

        return (this->family_name < other.family_name);
    } 
};


void printMap(std::map <std::string, FAMILY> & map);

#endif /*__URL_H__*/