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
    virtual ~Entity() noexcept {}

    virtual void init() {}
    virtual void update() {}
    virtual void render() {}

    virtual std::string type() { return "basic entity"; }
    virtual void hflip() {
        if (m_flip == SDL_FLIP_NONE) { m_flip = SDL_FLIP_HORIZONTAL; }
        else if (m_flip == SDL_FLIP_HORIZONTAL) { m_flip = SDL_FLIP_NONE; }
    }
    virtual void vflip() {
        if (m_flip == SDL_FLIP_NONE) { m_flip = SDL_FLIP_HORIZONTAL; }
        else if (m_flip == SDL_FLIP_HORIZONTAL) { m_flip = SDL_FLIP_NONE; }
    }

    void set_position(int x, int y) { m_position.x = x; m_position.y = y;}

    void collide(const Position2D &collider) {
        m_is_collide = Collision::is_collide(m_position, collider);

        m_up_collision = Collision::up_collision(m_position, collider);
        m_down_collision = Collision::down_collision(m_position, collider);
        m_left_collision = Collision::left_collision(m_position, collider);
        m_right_collision = Collision::right_collision(m_position, collider);

        if (m_up_collision) { m_position.y = collider.y + collider.h; }
        if (m_down_collision) { m_position.y = collider.y - m_position.h; }
        if (m_left_collision) { m_position.x = collider.x + collider.w; }
        if (m_right_collision) { m_position.x = collider.x - m_position.w; }
    }

    void reset_collisions() {
        m_down_collision = false;
        m_up_collision = false;
        m_left_collision = false;
        m_right_collision = false;
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
