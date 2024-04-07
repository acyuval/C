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
    
    
    the_ball.setRadius(constant::ball_radius);
    auto ret = texture.loadFromFile("./media/pics/ball.jpg");
    the_ball.setTexture(&texture);
    the_ball.setPosition(x,y);
    
    
    velocity = {constant::ball_velocity, constant::ball_velocity};
}

void ball::update()
{
    the_ball.move(velocity); 

    if (x() <= 0 || x() >= constant::window_width - (constant::ball_radius * 2)) 
        velocity.x *= -1;
    if (y() <= 0 || y() >= constant::window_height - (constant::ball_radius * 2)) 
        velocity.y *= -1;    
}

void ball::draw(sf::RenderWindow& window)
{
    window.draw(the_ball);
}

sf::FloatRect ball::get_bounding_box() const noexcept 
{
    return the_ball.getGlobalBounds();
}
sf::Vector2f ball::get_centre() const noexcept
{
    auto box = get_bounding_box();
    return {box.width/2.0f , box.height/2.0f};
}

float ball::x() const noexcept
{
    return the_ball.getPosition().x;
}
float ball::y() const noexcept
{
    return the_ball.getPosition().y;
}

void ball::move_up() noexcept
{
    velocity.y = -constant::ball_velocity;
}
void ball::move_left() noexcept
{
    velocity.x = -constant::ball_velocity;
}
void ball::move_right() noexcept
{
    velocity.x = constant::ball_velocity;
}

/******************************************************************************
 *							STATIC FUNCTIONS 								  *
 ******************************************************************************/