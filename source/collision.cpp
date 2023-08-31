#include <collision.h>
#include <vector2d.h>
#include <iostream>


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

bool Collision::up_collision(const Position2D &A, const Position2D &B) {
    Position2D::Center A_center = A.center();
    Position2D::Center B_center = B.center();

    if (
        A.down_side() >= B.up_side() && 
        A_center.y >= B_center.y &&
        A.right_side() > B.left_side() + 3 &&
        A.left_side() < B.right_side() - 3
    ) {
        return true;
    }
    return false;
}

bool Collision::down_collision(const Position2D &A, const Position2D &B) {
    Position2D::Center A_center = A.center();
    Position2D::Center B_center = B.center();

    if (
        A.up_side() <= B.down_side() && 
        A_center.y <= B_center.y &&
        A.right_side() > B.left_side() + 3 &&
        A.left_side() < B.right_side() - 3
    ) {
        return true;
    }
    return false;
}

bool Collision::right_collision(const Position2D &A, const Position2D &B) {
    Position2D::Center A_center = A.center();
    Position2D::Center B_center = B.center();

    if (
        A.right_side() >= B.left_side() && 
        A_center.x <= B_center.x &&
        A.down_side() > B.up_side() + 3 &&
        A.up_side() < B.down_side() - 3
    ) {
        return true;
    }
    return false;
}

bool Collision::left_collision(const Position2D &A, const Position2D &B) {
    Position2D::Center A_center = A.center();
    Position2D::Center B_center = B.center();
    
    if (
        A.left_side() <= B.right_side() && 
        A_center.x >= B_center.x &&
        A.down_side() > B.up_side() + 3 &&
        A.up_side() < B.down_side() - 3
    ) {
        return true;
    }
    return false;
}

