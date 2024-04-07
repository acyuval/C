/******************************************************************************
 *	Author:    Yuval
 *	Reviewer : 
 *	Date:
 ******************************************************************************/

#include <SFML/Graphics.hpp>


#include "../include/const.h"
#include "../include/background.h"
#include "../include/ball.h"
#include "../include/paddle.h"
#include "../include/intersect.h"
using namespace std::literals;

/******************************************************************************
 *							 DECLARATION								 		  *
 ******************************************************************************/

int main()
{
    sf::RenderWindow game_window({constant::window_width, constant::window_height}, "ping-pong");

    game_window.setFramerateLimit(60);
     
    background the_background(0.0f,0.0f);
    ball the_ball(constant::window_height/2.0,constant::window_height/2.0);
    paddle the_paddle; 

    while(game_window.isOpen())
    {
        game_window.clear(sf::Color::Black);
        sf::Event event; 

        while(game_window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                game_window.close();
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        {
            game_window.close();
        }
        the_background.update();
        the_ball.update();
        the_paddle.update();
        
        handle_collision(the_ball,the_paddle);

        the_background.draw(game_window);
        the_ball.draw(game_window);
        the_paddle.draw(game_window);
        game_window.display();
    }

    return 0;
}

/******************************************************************************
 *							 FUNCTIONS 										  *
 ******************************************************************************/

/******************************************************************************
 *							STATIC FUNCTIONS 								  *
 ******************************************************************************/