#ifndef CONST_H
#define CONST_H

struct constant
{
    static constexpr int window_width{520};
    static constexpr int window_height{450};
    static constexpr float ball_velocity{4.0f};
    static constexpr float ball_radius{10.0f};
    static constexpr float paddle_velocity{5.0f};
    static constexpr float brick_width{43.0f};
    static constexpr float brick_height{20.0f};
    static constexpr float brick_offset{brick_width/2.0f};
    static constexpr float brick_cols{10};
    static constexpr float brick_rows{4};
    static constexpr int brick_strength{3};
    static constexpr int player_lives{3};

};


#endif // CONST_H