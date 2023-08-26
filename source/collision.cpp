#include <collision.h>


int Collision::buffer = 10;

bool Collision::is_collide(const SDL_Rect &A, const SDL_Rect &B) {
    if (
        A.x + A.w >= B.x - Collision::buffer &&
              A.x <= B.x + B.w + Collision::buffer &&
        A.y + A.h >= B.y - Collision::buffer &&
              A.y <= B.y + B.h + Collision::buffer 
    ) {
        return true;
    }
    return false;
}

bool Collision::inside(const SDL_Rect &A, const SDL_Rect &B) {
    if (
        A.x + A.w > B.x &&
              A.x < B.x + B.w &&
        A.y + A.h > B.y &&
              A.y < B.y + B.h 
    ) {
        return true;
    }
    return false;
}

bool Collision::down_collision(const SDL_Rect &A, const SDL_Rect &B) {
    if (
        A.y >= B.y - B.h &&
        A.y <= B.y + B.h &&
        
        A.x + A.w > B.x &&
              A.x < B.x + B.w
    ) {
        return true;
    }
    return false;
}

bool Collision::up_collision(const SDL_Rect &A, const SDL_Rect &B) {
    if (
        A.y <= B.y + B.h &&
        
        A.x + A.w > B.x &&
        B.x + B.w > A.x 
    ) {
        return true;
    }
    return false;
}

bool Collision::left_collision(const SDL_Rect &A, const SDL_Rect &B) {
    if (
        A.y + A.h <= B.y - 15 &&
        A.y > B.y - 2 &&
        A.x <= B.x + (B.w / 2) &&
        A.x + A.w >= (B.x + B.w / 2)
    ) {
        return true;
    }
    return false;
}

bool Collision::right_collision(const SDL_Rect &A, const SDL_Rect &B) {
    if (
        A.y + A.h <= B.y - 15 &&
        A.y > B.y - 2 &&
        A.x <= B.x + (B.w / 2) &&
        A.x + A.w >= (B.x + B.w / 2)
    ) {
        return true;
    }
    return false;
}
