/******************************************************************************
 *	Author:    Yuval
 *	Reviewer : 
 *	Date:
 ******************************************************************************/

#include "../include/entity.h"
#include <SFML/Graphics.hpp>

/******************************************************************************
 *							 DECLARATION								 		  *
 ******************************************************************************/
/******************************************************************************
 *							 FUNCTIONS 										  *
 ******************************************************************************/
sf::FloatRect entity::get_bounding_box() const noexcept
{
    return sprite.getGlobalBounds();
}
sf::Vector2f entity::get_centre() const noexcept
{
    auto box = get_bounding_box();
    return {box.width/2.0f , box.height/2.0f};
}
float entity::x() const noexcept
{
    return sprite.getPosition().x;
}
float entity::y() const noexcept
{
    return sprite.getPosition().y;
}


/******************************************************************************
 *							STATIC FUNCTIONS 								  *
 ******************************************************************************/