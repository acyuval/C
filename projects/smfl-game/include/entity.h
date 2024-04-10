#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>


class entity 
{
    protected: 
    
    sf::Sprite sprite; 
    bool destroyed{false};
    public:
    
    virtual void update() = 0 ; 
    virtual void draw(sf::RenderWindow& window) = 0;

    virtual sf::FloatRect get_bounding_box() const noexcept;

    virtual sf::Vector2f get_centre() const noexcept;

    virtual float x() const noexcept;
    virtual float y() const noexcept;

    float left() const noexcept;
    float right() const noexcept;
    float top() const noexcept;
    float bottom() const noexcept;

    void destroy() noexcept;
    bool is_destroyed() const noexcept;

    virtual ~entity() {};
    
};

class moving_entity: public entity
{
    protected:
    sf::Vector2f velocity;

    public: 

    virtual void move_up() noexcept = 0;
    virtual void move_down() noexcept = 0;
    virtual void move_left() noexcept = 0;
    virtual void move_right() noexcept = 0;

};

#endif // ENTITY_H