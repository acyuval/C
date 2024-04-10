/******************************************************************************
 *	Author:    Yuval
 *	Reviewer : 
 *	Date:
 ******************************************************************************/
#include <SFML/Graphics.hpp>

#include <algorithm>
#include <iostream>
#include "../include/game.h"
#include "../include/intersect.h"


/******************************************************************************
 *							 DECLARATION								 		  *
 ******************************************************************************/
/******************************************************************************
 *							 FUNCTIONS 										  *
 ******************************************************************************/
void entity_manager::refresh()
{
    for(auto& [type, alias_vector] : grouped_entities)
    {
        alias_vector.erase(remove_if(begin(alias_vector), end(alias_vector), 
            [](auto p) {return p->is_destroyed();}), end(alias_vector));
    }

    all_entities.erase(remove_if(begin(all_entities), end(all_entities),
			[](const auto& p) { return p->is_destroyed();}),
	end(all_entities));
}

void entity_manager::clear()
{
    grouped_entities.clear();
    all_entities.clear();

}

void entity_manager::update()
{
    for (auto& e : all_entities)
    {
        e->update();
    }
}


void entity_manager::draw(sf::RenderWindow& window)
{
    for (auto& e : all_entities)
    {
        e->draw(window);
    }
}

game::game()
{
    game_window.setFramerateLimit(60);
    verdana.loadFromFile("./media/fonts/Verdana.ttf");

    text_state.setFont(verdana);
    text_state.setPosition({constant::window_width/2.0f - 100.0f, constant::window_height/2.0f - 100.0f});
    text_state.setCharacterSize(35);
    text_state.setFillColor(sf::Color::Red);
    text_state.setString("Paused");

    text_lives.setFont(verdana);
    text_lives.setPosition({constant::window_width/2.0f - 65.0f, constant::window_height/2.0f - 65.0f});
    text_lives.setCharacterSize(35);
    text_lives.setFillColor(sf::Color::White);
    text_lives.setString("Lives: " + std::to_string(lives));
    
}

void game::reset()
{
    state = game_state::paused;
    lives = constant::player_lives;

    manager.clear();

    manager.create<background>(0.0f,0.0f);
    
    manager.create<ball>(constant::window_height/2.0f,constant::window_height/2.0f);
    manager.create<paddle>();

    for(int i = 0 ; i < constant::brick_cols ; ++i)
    {
        for(int j = 0 ; j < constant::brick_rows; ++j)
        {
            float x = constant::brick_offset + (i+1)* constant :: brick_width;
            float y = (j+3)* constant :: brick_height;
            manager.create<brick> (x,y);
        }
    }
}


void  entity_manager::collision_ball_brick()
{
    apply_all<ball>([this](auto& the_ball) 
    {apply_all<brick>([&the_ball](auto& the_brick) 
        {handle_collision(the_ball, the_brick);});});    
}

void entity_manager::collision_ball_paddle()
{
    apply_all<ball>([this](auto& the_ball) 
    {apply_all<paddle>([&the_ball](auto& the_paddle)
    {handle_collision(the_ball, the_paddle);});});

}

void game::handle_usr_control(bool& pauseKey)
{
    sf::Event event; 
        while(game_window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                game_window.close();
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            game_window.close();


        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
            reset();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
        {

            if(!pauseKey)
            {
                if (state == game_state::paused) 
                    state = game_state::running;
                else
                    state = game_state::paused; 
                
            }
            pauseKey = true;      
        }
        else
            pauseKey = false;
}

void game::run()
{
    bool pause_key_active{false};

    while(game_window.isOpen())
    {
        game_window.clear(sf::Color::Black);
        
        handle_usr_control(pause_key_active);
                       
        if (state == game_state::paused)
            manager.draw(game_window);

        if (state != game_state::running)
        {
            switch (state)
            {
            case game_state::paused:
                text_state.setString("  Paused  ");
                break;
            case game_state::game_over:
                text_state.setString(" Game over  ");
                break;
            case game_state::player_wins:
                text_state.setString("  player wins  ");
                break;
            default:
                break;
            }
            game_window.draw(text_lives);
            game_window.draw(text_state);
        }
        else
        {
            if(manager.get_all<ball>().empty())
            {
                manager.create<ball>(constant::window_height/2.0f,constant::window_height/2.0f);
                --lives;
                state = game_state::paused;
            }
            if(manager.get_all<brick>().empty())
                state = game_state::player_wins;
            if(lives <= 0)
                state = game_state::game_over;
            
            text_lives.setString("Lives " + std::to_string(lives));

            manager.update();


            manager.collision_ball_brick();
            manager.collision_ball_paddle();


			
            manager.refresh();
         
            manager.draw(game_window);
        } 
        game_window.display();  
    }
}

/******************************************************************************
 *							STATIC FUNCTIONS 								  *
 ******************************************************************************/