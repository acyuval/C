/******************************************************************************
 *	Author:    Yuval
 *	Reviewer : 
 *	Date:
 ******************************************************************************/
#ifndef __ASS6_H__
#define __ASS6_H__
#include <string>
#include <vector>
#include <deque>
#include <list>


std::vector<std::string> GetInputVec();
std::list<std::string> GetInputList();
std::deque<std::string> GetInputDeque();

template <typename T>  
void show(T cont, std::string name);

#endif /*__ASS6_H__*/
