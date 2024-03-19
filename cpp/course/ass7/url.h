/******************************************************************************
 *	Author:    Yuval
 *	Reviewer : 
 *	Date:
 ******************************************************************************/
#ifndef __URL_H__
#define __URL_H__
#include <string>
#include <list>

class URL 
{
    std::string protocol;
    std::string resource;
public:
    URL(const std::string& prot, const std::string& res);
    void print() const;
    std::string get() const; 
};


class HISTORY 
{
    std::list <URL> url_list; 

    public:
        bool SaveURL(URL url_obj);
        std::string PopFront();

};


#endif /*__URL_H__*/