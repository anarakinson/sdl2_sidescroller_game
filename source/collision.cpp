#include <collision.h>
#include <vector2d.h>
#include <iostream>

#define buff -10

// int Collision::buffer = +5;

bool Collision::is_collide(const Position2D &A, const Position2D &B) {

    if (
        A.left_side() <= B.right_side() &&
        A.right_side() >= B.left_side() &&
        A.up_side() <= B.down_side() &&
        A.down_side() >= B.up_side() 
    ) {
        return true;
    }
    return false;
}

bool Collision::inside(const Position2D &A, const Position2D &B) {

    if (
        A.left_side() < B.right_side() + 15 &&
        A.right_side() > B.left_side() - 15 &&
        A.up_side() < B.down_side() + 15 &&
        A.down_side() > B.up_side() - 15 
    ) {
        return true;
    }
    return false;
}

bool Collision::down_collision(const Position2D &A, const Position2D &B) {
    if (
        A.down_side() >= B.up_side() &&
        A.down_side() <= B.up_side() + 15 &&
        
        A.right_side() >= B.left_side() &&
        A.left_side() <= B.right_side() 
    ) {
        return true;
    }
    return false;
}

bool Collision::up_collision(const Position2D &A, const Position2D &B) {
    if (
        A.y <= B.y + B.h &&
        
        A.x + A.w > B.x &&
        B.x + B.w > A.x 
    ) {
        return true;
    }
    return false;
}

bool Collision::left_collision(const Position2D &A, const Position2D &B) {
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

bool Collision::right_collision(const Position2D &A, const Position2D &B) {
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
