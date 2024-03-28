/******************************************************************************
 *	Author:    Yuval
 *	Reviewer : 
 *	Date:
 ******************************************************************************/
#include <vector>
#include <algorithm>
#include <iostream>
#include <string> // For strcpy() and strlen()
#include <cstring>
#include <iterator>
#include <map> 
#include "ass.h" 
/******************************************************************************
 *							 DECLARATION								 		  *
 ******************************************************************************/
using namespace std;
int main() 
{
    //StoreInSet();
/* 
    map <string, FAMILY> family_map; 

    FAMILY fam1; 
    fam1.addChild("yuval"s);
    fam1.addChild("ofer"s);
    fam1.addChild("asaf"s);

    FAMILY fam2; 
    fam2.addChild("reut"s);
    fam2.addChild("einav"s);
    fam2.addChild("adi"s);
    fam2.addChild("ishay"s);
    family_map.insert(make_pair( "glikman"s , fam1));
    family_map.insert(make_pair( "kandalker"s , fam2));

    printMap(family_map);

 */
    multimap <string, string> multi;
    

    multi.insert(make_pair("glikman"s, "yuval"s)); 
    multi.insert(make_pair("glikman"s, "ofer"s));
    multi.insert(make_pair("glikman"s, "asaf"s));
    multi.insert(make_pair("glikman"s, "jordan"s));
    multi.insert(make_pair("glikman"s, "jordan"s));
    multi.insert(make_pair("kan"s, "jordan"s));
    for(auto mem = multi.begin(); mem != multi.end() ; mem++)
    {   
        auto upper = multi.upper_bound((*mem).first);
        auto lower = multi.upper_bound((*mem).first);
        for(auto child = lower; child != upper; child++)
        {
            cout << (*child).second << " " ;
        }
        mem = upper;
    } 

    
    return 0;
}
/******************************************************************************
 *							 FUNCTIONS 										  *
 ******************************************************************************/


/******************************************************************************
 *							STATIC FUNCTIONS 								  *
 ******************************************************************************/
