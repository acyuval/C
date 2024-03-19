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
#include "url.h"
/******************************************************************************
 *							 DECLARATION								 		  *
 ******************************************************************************/
using namespace std;
URL::URL(const string& prot, const string& res) 
{
	protocol = prot;
	resource = res;
}
	
void URL::print() const {
	cout << protocol << "://" << resource << "\n";
}

string URL::get() const 
{
	string s; 
	ostringstream ss{s}; 
	ss <<  protocol << "://" << resource << "\n";

	return ss.str();
}

bool HISTORY::SaveURL(URL url_obj)
{
	
	auto found = find_if(begin(url_list), end(url_list), [url_obj](URL url1){ return (url1.get() == url_obj.get());});
	
	if(found != end(url_list))
	{
		url_list.push_front(*found);
		url_list.erase(found);
		cout << "found similar push to front" << endl;
	}
	else
	{
		url_list.push_back(url_obj);
		cout<< "push back" << endl;
	}
	return true;
}

string HISTORY::PopFront()
{
	return (url_list.front()).get();
}

/******************************************************************************
 *							 FUNCTIONS 										  *
 ******************************************************************************/


/******************************************************************************
 *							STATIC FUNCTIONS 								  *
 ******************************************************************************/
