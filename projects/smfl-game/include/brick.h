#ifndef BRICK_H
#define BRICK_H


#include <SFML/Graphics.hpp>
#include <vector>
#include "../include/entity.h"
#include "../include/const.h"

class brick: public entity 
{
    static sf::Texture texture;  
    int strength{constant::brick_strength};
    
    public:
    
    brick(float x, float y);
    void update() override;
    void draw (sf::RenderWindow& window) override;
    void set_strength(int s) noexcept;
    void weaken() noexcept;
    bool is_too_weak() const noexcept;

};  

void set_bricks(std::vector<brick>& bricks);

#endif // BRICK_H
