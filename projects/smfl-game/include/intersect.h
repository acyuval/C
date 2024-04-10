#ifndef INTERSECT_H
#define INTERSECT_H


#include <SFML/Graphics.hpp>
#include "../include/entity.h"
#include "../include/const.h"
#include "../include/ball.h"
#include "../include/paddle.h"
#include "../include/brick.h"

bool is_intersecting(const entity& e1 , const entity& e2);

void handle_collision(ball& b, const paddle& p);
void handle_collision(ball& ball, brick& brick);

#endif // INTERSECT_H
