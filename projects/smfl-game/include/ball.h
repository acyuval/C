#ifndef BALL_H
#define BALL_H


#include <SFML/Graphics.hpp>
#include "../include/entity.h"

class ball: public moving_entity 
{
    static sf::Texture texture; 
    
    sf::CircleShape the_ball; 
    
    public:
    
    ball(float x , float y);
    void update() override;
    void draw (sf::RenderWindow& window) override;


    
};

#endif // BALL_H
