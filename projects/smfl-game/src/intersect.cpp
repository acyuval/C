/******************************************************************************
 *	Author:    Yuval
 *	Reviewer : 
 *	Date:
 ******************************************************************************/

#include "../include/intersect.h"
#include "../include/ball.h"
#include "../include/paddle.h"
#include "../include/brick.h"
#include <SFML/Graphics.hpp>
#include <iostream>
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

void handle_collision(ball& ball, brick& brick)
{
    if (is_intersecting(ball, brick))
    {
        brick.weaken();

        if(brick.is_too_weak())
            brick.destroy();
            
        auto r = constant::ball_radius;
        
        float left_overlap = (ball.x() + r) - brick.left();
        float right_overlap = brick.right() - (ball.x() + r);
        float top_overlap = (ball.y() + r) - brick.top();
        float bottom_overlap = brick.bottom() - (ball.y() + r);
        
        bool from_left = left_overlap < right_overlap;
        bool from_top = top_overlap < bottom_overlap;
        float min_x_overlap = from_left ? left_overlap : right_overlap;
        float min_y_overlap = from_top ? top_overlap : bottom_overlap;

        if(min_x_overlap < min_y_overlap)
        {
            if (from_left)
                ball.move_left();
            else 
                ball.move_right();
        }
        else 
        {
            if (from_top)
                ball.move_up();
            else 
                ball.move_down();
        }
    }

}

/******************************************************************************
 *							STATIC FUNCTIONS 								  *
 ******************************************************************************/