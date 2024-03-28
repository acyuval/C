/******************************************************************************
 *	Author:    Yuval
 *	Reviewer : 
 *	Date:
 ******************************************************************************/
#include <vector>
#include <iostream>
#include <string> 
#include <sstream> 
#include <algorithm>
#include <iterator>
#include <map>
#include <set>
#include "ass.h"
/******************************************************************************
 *							 DECLARATION								 		  *
 ******************************************************************************/
using namespace std;

/******************************************************************************
 *							 FUNCTIONS 										  *
 ******************************************************************************/

string GetInput()
{
	try
	{
		string s; 
		getline(cin , s);
		return s;  
	}
	catch(...)
	{
		cout << "hii \n";
		return NULL;
	}
}

void StoreInSet()
{
	set <string> my_set; 
	auto input = GetInput();
	istringstream stream(input);
	istream_iterator <string> iter(stream) , end_of;

	copy(iter, end_of , inserter(my_set ,my_set.begin()));
	
	MyPrint(my_set);
	cout << "number of distict words is : " << my_set.size() << endl;
}

template <typename T>
void MyPrint(T cont)
{
	for(auto v : cont)
	{
		cout << "string: " << v << endl ;
	}
	
}

void FAMILY::printChildrenList()
{
	cout << "children list: " << endl;
	for(auto child: children)
	{
		cout << child << endl; 
	}
}

bool FAMILY::addChild(std::string name)
{
	children.push_back(name);
	return true;	
}

void printMap(map <string, FAMILY>& map)
{
	for (auto fam : map)
	{
		cout << "family name: " << fam.first << endl; 

		fam.second.printChildrenList();
	}
}

/******************************************************************************
 *							STATIC FUNCTIONS 								  *
 ******************************************************************************/
