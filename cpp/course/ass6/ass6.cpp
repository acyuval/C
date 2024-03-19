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
#include <algorithm>
#include <deque>
#include <list>
using namespace std; 
/******************************************************************************
 *							 DECLARATION								 		  *
 ******************************************************************************/
template <typename T>  
void show(T cont, string name);
/******************************************************************************
 *							 FUNCTIONS 										  *
 ******************************************************************************/
vector<string> GetInputVec()
{
    string s;
    vector<string> vec;

    while(cin >> s)
    {
      if(s == "q") 
      {
        break;
      } 
    
      vec.push_back(s);
    }
    show<vector<string>> (vec, "Vec");

    return vec;
}

deque<string> GetInputDeque()
{
    string s;
    deque<string> deq;

    while(cin >> s)
    {
      if(s == "q") 
      {
        break;
      } 
    
      deq.push_back(s);
    }
    show<deque<string>> (deq, "deque");

    
    return deq;
}

list<string> GetInputList()
{
    string s;
    list<string> lis;

    while(cin >> s)
    {
      if(s == "q") 
      {
        break;
      } 
    
      lis.push_back(s);
    }
    
    show<list<string>> (lis, "list");

    return lis;
}

template <typename T>  
void show(T cont, string name)
{
  cout << name << ": " << endl;
  for(auto v:cont)
  {
      cout << v << ",";  
  }
  cout << endl;
  
} 
/******************************************************************************
 *							STATIC FUNCTIONS 								  *
 ******************************************************************************/
