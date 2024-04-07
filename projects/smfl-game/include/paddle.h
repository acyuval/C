#ifndef PADDLE_H
#define PADDLE_H


#include <SFML/Graphics.hpp>
#include "../include/entity.h"
#include "../include/const.h"
class paddle: public moving_entity 
{
    static sf::Texture texture;  
    float X_pos; 
    float Y_pos;
    void process_user_input();   
    
    public:
    
    paddle();
    void update() override;
    void draw (sf::RenderWindow& window) override;
    void move_up() noexcept override;
    void move_left() noexcept override;
    void move_right() noexcept override;

};

#endif // PADDLE_H
