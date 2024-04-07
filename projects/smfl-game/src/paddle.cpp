/******************************************************************************
 *	Author:    Yuval
 *	Reviewer : 
 *	Date:
 ******************************************************************************/

#include "../include/const.h"
#include "../include/paddle.h"
#include "../include/entity.h"
#include <SFML/Graphics.hpp>

/******************************************************************************
 *							 DECLARATION								 		  *
 ******************************************************************************/
/******************************************************************************
 *							 FUNCTIONS 										  *
 ******************************************************************************/

sf::Texture paddle::texture;

paddle::paddle()
{
    auto ret = texture.loadFromFile("./media/pics/paddle.png");
    sprite.setTexture(texture);
    
    X_pos =  (constant::window_width/2 - get_bounding_box().width/2);
    Y_pos =  (constant::window_height - get_bounding_box().height);
    sprite.setPosition(X_pos,Y_pos);
    sprite.setOrigin(get_centre());
    velocity = {0.0f, 0.0f};
}

void paddle::update()
{
    process_user_input();
    sprite.move(velocity);
}

void paddle::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

void paddle::process_user_input()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        velocity.x = -constant::paddle_velocity;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        velocity.x = constant::paddle_velocity;
    }     
    else if(x() <= get_bounding_box().width/2)
    {
        velocity.x = constant::paddle_velocity;
    } 
    else if(x() >= (constant::window_width - get_bounding_box().width/2))
    {
        velocity.x = -constant::paddle_velocity;
    }
    
}
void paddle::move_up() noexcept
{
    velocity.y = -constant::paddle_velocity;
}
void paddle::move_left() noexcept
{
    velocity.x = -constant::paddle_velocity;
}
void paddle::move_right() noexcept
{
    velocity.x = constant::paddle_velocity;
}

/******************************************************************************
 *							STATIC FUNCTIONS 								  *
 ******************************************************************************/