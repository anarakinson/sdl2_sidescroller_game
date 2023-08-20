#include <collision.h>
#include <game.h>

#include <SDL2/SDL.h>


bool Collision::is_collide(const SDL_Rect &A, const SDL_Rect &B) {
    if (
        A.x + A.w >= B.x &&
        B.x + B.w >= A.x &&
        A.y + A.h >= B.y &&
        B.y + B.h >= A.y 
    ) {
        return true;
    }
    return false;
}
