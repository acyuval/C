/******************************************************************************
 *	Author:    Yuval
 *	Reviewer : 
 *	Date:
 ******************************************************************************/

#include "../include/background.h"

#include <SFML/Graphics.hpp>

/******************************************************************************
 *							 DECLARATION								 		  *
 ******************************************************************************/
/******************************************************************************
 *							 FUNCTIONS 										  *
 ******************************************************************************/

sf::Texture background::texture;

background::background(float x , float y)
{
    auto ret = texture.loadFromFile("/home/yuval/git/projects/smfl-game/media/pics/background.jpg");
    sprite.setTexture(texture);
    sprite.setPosition(x,y);

}

void background::update(){}

void background::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

/******************************************************************************
 *							STATIC FUNCTIONS 								  *
 ******************************************************************************/