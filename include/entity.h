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

    void collide(const Position2D &collider) {

        m_down_collision = Collision::down_collision(m_position, collider);
        m_up_collision = Collision::up_collision(m_position, collider);
        m_left_collision = Collision::left_collision(m_position, collider);
        m_right_collision = Collision::right_collision(m_position, collider);

        m_is_collide = Collision::inside(m_position, collider);
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
