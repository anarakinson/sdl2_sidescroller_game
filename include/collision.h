#pragma once

#include <vector2d.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


class Collision {
public:
    static bool is_collide(const Position2D &A, const Position2D &B);
    static bool is_stuck(const Position2D &A, const Position2D &B);
    static bool up_collision(const Position2D &A, const Position2D &B);
    static bool down_collision(const Position2D &A, const Position2D &B);
    static bool left_collision(const Position2D &A, const Position2D &B);
    static bool right_collision(const Position2D &A, const Position2D &B);
};

