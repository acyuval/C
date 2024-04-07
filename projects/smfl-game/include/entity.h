#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>


class entity 
{
    protected: 
    
    sf::Sprite sprite; 
    
    public:
    
    virtual void update() = 0 ; 
    virtual void draw(sf::RenderWindow& window) = 0;

    sf::FloatRect get_bounding_box() const noexcept;

    sf::Vector2f get_centre() const noexcept;

    float x() const noexcept;
    float y() const noexcept;
    virtual ~entity() {};
    
};

class moving_entity: public entity
{
    protected:
    sf::Vector2f velocity;

    public: 


};

#endif // ENTITY_H