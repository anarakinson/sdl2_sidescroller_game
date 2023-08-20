#pragma once

#include <game.h>

#include <SDL2/SDL.h>


class Collision {
public:
    static bool is_collide(const SDL_Rect &A, const SDL_Rect &B);
};

