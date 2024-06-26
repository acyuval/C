/******************************************************************************
 *	Author:    Yuval
 *	Reviewer : 
 *	Date:
 ******************************************************************************/
#include <vector>
#include <iostream>
#include <string> 
#include <sstream> 
#include <algorithm>
#include <iterator>
#include <map>
#include <set>
#include "ass.h"
#include <SFML/Graphics.hpp>
/******************************************************************************
 *							 DECLARATION								 		  *
 ******************************************************************************/
using namespace std;


int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}

/******************************************************************************
 *							 FUNCTIONS 										  *
 ******************************************************************************/

/******************************************************************************
 *							STATIC FUNCTIONS 								  *
 ******************************************************************************/