/******************************************************************************
 *	Author:    Yuval
 *	Reviewer : 
 *	Date:
 ******************************************************************************/

#include "../include/const.h"
#include "../include/ball.h"
#include "../include/entity.h"
#include <SFML/Graphics.hpp>

/******************************************************************************
 *							 DECLARATION								 		  *
 ******************************************************************************/
/******************************************************************************
 *							 FUNCTIONS 										  *
 ******************************************************************************/

sf::Texture ball::texture;

ball::ball(float x , float y)
{
    
    
    the_ball.setRadius(10.0f);
    auto ret = texture.loadFromFile("./media/pics/ball.jpg");
    the_ball.setTexture(&texture);
    the_ball.setPosition(x,y);
    
    
    velocity = {constant::ball_velocity, constant::ball_velocity};
}

void ball::update()
{
    the_ball.move(velocity);   
}

void ball::draw(sf::RenderWindow& window)
{
    window.draw(the_ball);
}

/******************************************************************************
 *							STATIC FUNCTIONS 								  *
 ******************************************************************************/