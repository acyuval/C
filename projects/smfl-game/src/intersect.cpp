/******************************************************************************
 *	Author:    Yuval
 *	Reviewer : 
 *	Date:
 ******************************************************************************/

#include "../include/intersect.h"
#include "../include/ball.h"
#include "../include/paddle.h"
#include <SFML/Graphics.hpp>

/******************************************************************************
 *							 DECLARATION								 		  *
 ******************************************************************************/
/******************************************************************************
 *							 FUNCTIONS 										  *
 ******************************************************************************/
bool is_intersecting(const entity& e1 , const entity& e2)
{
    auto box1 = e1.get_bounding_box();
    auto box2 = e2.get_bounding_box();
    return box1.intersects(box2);
}

void handle_collision(ball& b, const paddle& p)
{
    if(is_intersecting(p,b))
    {
        b.move_up();
        if (b.x() < p.x())
        {
            b.move_left();
        }
        else 
        {
            b.move_right();
        }
    }
}

/******************************************************************************
 *							STATIC FUNCTIONS 								  *
 ******************************************************************************/