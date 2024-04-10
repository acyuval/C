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

    sf::FloatRect get_bounding_box() const noexcept override;

    sf::Vector2f get_centre() const noexcept override;

    float x() const noexcept override;
    float y() const noexcept override;
    void move_up() noexcept override;
    void move_down() noexcept override;
    void move_left() noexcept override;
    void move_right() noexcept override;
    
};

#endif // BALL_H
