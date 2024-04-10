/******************************************************************************
 *	Author:    Yuval
 *	Reviewer : 
 *	Date:
 ******************************************************************************/

#include "../include/brick.h"

#include <SFML/Graphics.hpp>
#include <iostream>
/******************************************************************************
 *							 DECLARATION								 		  *
 ******************************************************************************/
/******************************************************************************
 *							 FUNCTIONS 										  *
 ******************************************************************************/

sf::Texture brick::texture;

std::vector<sf::Color> color {{0,255,0, 80}, {0,255,0, 170}, {0,255,0, 255}};

brick::brick(float x , float y): entity()
{
    auto ret = texture.loadFromFile("/home/yuval/git/projects/smfl-game/media/pics/brick01.png");
    sprite.setTexture(texture);
    sprite.setPosition(x,y);
    sprite.setOrigin(get_centre());

}

void brick::update()
{
    sprite.setColor(color[strength-1]);
}

void brick::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

void brick::set_strength(int s) noexcept
{
    strength = s;
}

void brick::weaken() noexcept
{
    --strength;
}
bool brick::is_too_weak() const noexcept
{
    return (strength <= 0);
}



/******************************************************************************
 *							STATIC FUNCTIONS 								  *
 ******************************************************************************/