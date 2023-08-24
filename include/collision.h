#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


class Collision {
public:
    static bool is_collide(const SDL_Rect &A, const SDL_Rect &B);
};

