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
#include "ass.h"
/******************************************************************************
 *							 DECLARATION								 		  *
 ******************************************************************************/
using namespace std;

/******************************************************************************
 *							 FUNCTIONS 										  *
 ******************************************************************************/

void StoreStreamFromUser()
{
	string s;
	vector <pair<string, int>> vec; 
	getline(cin , s);
	istringstream ss(s); 
	istream_iterator <string> iter(ss), end_iter;  	
	transform(iter, end_iter, back_inserter(vec), [](string s){return(make_pair(s, s.size()));});

	MyPrint(vec);

}

void MapStreamFromUser()
{
	string s;
	map<string, int>  map; 
	getline(cin , s);
	istringstream ss(s); 
	istream_iterator <string> iter(ss), end_iter;  	
	
	while(iter != end_iter)
	{
		string s = *iter++;
		map[s] = s.size();
	}

	MyPrint(map);

}

template <typename T>
void MyPrint(T cont)
{
	for(auto v : cont)
	{
		cout << "string: " << v.first << ", size: " << v.second << endl ;
	}
}
/******************************************************************************
 *							STATIC FUNCTIONS 								  *
 ******************************************************************************/
