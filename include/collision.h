#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


class Collision {
public:
    static int buffer;

    static bool is_collide(const SDL_Rect &A, const SDL_Rect &B);
    static bool inside(const SDL_Rect &A, const SDL_Rect &B);
    static bool up_collision(const SDL_Rect &A, const SDL_Rect &B);
    static bool down_collision(const SDL_Rect &A, const SDL_Rect &B);
    static bool left_collision(const SDL_Rect &A, const SDL_Rect &B);
    static bool right_collision(const SDL_Rect &A, const SDL_Rect &B);
};

