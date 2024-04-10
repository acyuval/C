#ifndef GAME_H
#define GAME_H


#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <typeinfo>

#include "../include/entity.h"
#include "../include/const.h"
#include "../include/ball.h"
#include "../include/paddle.h"
#include "../include/brick.h"
#include "../include/background.h"


using namespace std::literals;
using entity_vector = std::vector<std::unique_ptr<entity>>;
using entity_alias_vector = std::vector<entity *>;

class entity_manager
{
    entity_vector all_entities; 
    std::map<size_t, entity_alias_vector> grouped_entities; 

    public:

    template <typename T , typename... Args> 
    T& create(Args&&... args)
    {
        static_assert(std::is_base_of<entity, T>::value, "element is not derived from Entity\n");

        auto ptr{std::make_unique<T>(std::forward<Args>(args)...)};
        auto ptr_alias = ptr.get();

        auto hash = typeid(T).hash_code();

        grouped_entities[hash].emplace_back(ptr_alias);
        
        all_entities.emplace_back(std::move(ptr));

        return *ptr_alias;
    }

    void refresh();

    void clear();

    void update();

    void draw(sf::RenderWindow& window);

    void collision_ball_brick();

    void collision_ball_paddle();

    template <typename T>
    auto& get_all()
    {   
        return grouped_entities[typeid(T).hash_code()];
    }


    template <typename T, typename Func>
    void apply_all(const Func& func)
    {
        auto& entity_group{get_all<T>()};

        for(auto ptr: entity_group)
        {
            func(*dynamic_cast<T*>(ptr));
        }
    }

};



class game 
{

    enum class game_state{paused, running, game_over, player_wins};
    game_state state{game_state::paused};
    entity_manager manager;

    sf::RenderWindow game_window{{constant::window_width, constant::window_height}, "ping-pong"};

    sf::Font verdana;
    sf::Text text_state, text_lives;
    
    int lives{constant::player_lives};

    public:

    game();

    void reset();

    void run();

    void handle_usr_control(bool& pauseKey);
};


#endif // GAME_H
