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

    bool is_collide() { return m_is_collide; }
    void collide() { m_is_collide = true; }
    void collide(const SDL_Rect &collider) {

        m_down_collision = Collision::down_collision(m_dst_rect, collider);
        m_up_collision = Collision::up_collision(m_dst_rect, collider);
        m_left_collision = Collision::left_collision(m_dst_rect, collider);
        m_right_collision = Collision::right_collision(m_dst_rect, collider);

        m_is_collide = Collision::inside(m_dst_rect, collider);
    }


    virtual SDL_Rect collider() { return m_dst_rect; }

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
