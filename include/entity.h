#pragma once 

#include <vector2d.h>
#include <collision.h>
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


class Entity {
public:
    explicit Entity() { index = counter++; };
    virtual ~Entity() {}

    virtual void init() {}
    virtual void update() {}
    virtual void render() {}

    virtual std::string type() { return "basic entity"; }

    void set_position(int x, int y) { m_position.x = x; m_position.y = y;}

    void collide(const Position2D &collider) {
        m_is_collide = Collision::is_collide(m_position, collider);

        Position2D::Center A_center = m_position.center();
        Position2D::Center B_center = collider.center();

        if (m_position.up_side() < collider.down_side() && A_center.y < B_center.y) { m_position.y = collider.y - collider.h; }
        if (m_position.down_side() > collider.up_side() && A_center.y > B_center.y) { m_position.y = collider.y + collider.h; }
        if (m_position.right_side() > collider.left_side() && A_center.x < B_center.x) { m_position.x = collider.x - collider.h; }
        if (m_position.left_side() < collider.right_side() && A_center.x > B_center.x) { m_position.x = collider.x + collider.h; }
    }


    virtual Position2D collider() { return m_position; }

    static int counter;
    int index;

    Vector2D velocity{};
    Position2D m_position{};

protected:
    
    double m_angle = 0;

    // SDL_RendererFlip flip = SDL_FLIP_NONE | SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL;
    SDL_RendererFlip m_flip = SDL_FLIP_NONE;

    SDL_Texture *m_texture;
    SDL_Rect m_src_rect{}; 
    SDL_Rect m_dst_rect{};
    SDL_Point m_center{NULL};

    bool m_is_collide = false;

    bool m_down_collision = false;
    bool m_up_collision = false;
    bool m_left_collision = false;
    bool m_right_collision = false;

};
