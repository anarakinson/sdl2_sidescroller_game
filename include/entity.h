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
    virtual ~Entity() noexcept {
        // std::cout << "Destructed" << index << std::endl;
    }

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

    virtual void hit() {}


    void set_position(int x, int y) { m_position.x = x; m_position.y = y;}

    void collide(const Position2D &collider) {
        // check collision and stucking
        m_is_collide = Collision::is_collide(m_position, collider);
        m_is_stuck = Collision::is_stuck(m_position, collider);

        // update collision states
        m_up_collision = m_up_collision == true ? true : Collision::up_collision(m_position, collider);
        m_left_collision = m_left_collision == true ? true : Collision::left_collision(m_position, collider);
        m_right_collision = m_right_collision == true ? true : Collision::right_collision(m_position, collider);
        m_down_collision = m_down_collision == true ? true : Collision::down_collision(m_position, collider);

        // stuck in wall resolution
        if (m_is_stuck && type() != "tile") {
            if (m_left_collision) { m_position.x += 4; }
            if (m_right_collision) { m_position.x -= 4; }
            if (m_up_collision) { m_position.y += 4; }
            if (m_down_collision) { m_position.y -= 4; }
        }
    }

    // update sprite position on display
    void update_position() {
        m_dst_rect.x = static_cast<int>(m_position.x * m_scale);      // game object coordinates in game
        m_dst_rect.y = static_cast<int>(m_position.y * m_scale);
        m_dst_rect.w = static_cast<int>(m_position.w * m_scale);       // game object size in game
        m_dst_rect.h = static_cast<int>(m_position.h * m_scale);
    }

    // resolve collisions
    void resolve_collisions() {
        if (m_up_collision) { velocity.y = velocity.y < 0 ? 0 : velocity.y; }
        if (m_down_collision) { velocity.y = velocity.y > 0 ? 0 : velocity.y; }
        if (m_left_collision) { velocity.x = velocity.x < 0 ? 0 : velocity.x; }
        if (m_right_collision) { velocity.x = velocity.x > 0 ? 0 : velocity.x; }
    }

    // reset all collisions to false
    void reset_collisions() {
        m_down_collision = false;
        m_up_collision = false;
        m_left_collision = false;
        m_right_collision = false;
    }

    void set_scale(double scale) { m_scale = scale; }

    // // debugging output
    // void print_data() {
    //     std::cout << "m_up_collision: " << m_up_collision 
    //         << " m_down_collision: " << m_down_collision 
    //         << " m_left_collision: " << m_left_collision 
    //         << " m_right_collision: " << m_right_collision 
    //         << " m_x: " << m_position.x 
    //         << " m_y: " << m_position.y 
            
    //         << std::endl;
    // }

    virtual Position2D collider() { return m_position; }

    static int counter;
    int index;

    int max_speed() { return m_max_speed; } 
    void damaged(int damage = 1) { m_hitpoints -= damage; }
    bool is_dead() { return m_hitpoints <= 0; }

    void apply_gravity() {
        if (m_down_collision) { m_gravity = 0; } 
        else { m_gravity = std::min(++m_gravity, m_max_speed + 2); } 
    }

    Vector2D velocity{};
    Position2D m_position{};


protected:
    
    int m_max_speed = 0;

    double m_angle = 0;
    double m_scale = 1;

    // SDL_RendererFlip flip = SDL_FLIP_NONE | SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL;
    SDL_RendererFlip m_flip = SDL_FLIP_NONE;

    SDL_Texture *m_texture;
    SDL_Rect m_src_rect{}; 
    SDL_Rect m_dst_rect{};
    SDL_Point m_center{NULL};

    bool m_is_collide = false;
    bool m_is_stuck = false;

    bool m_down_collision = false;
    bool m_up_collision = false;
    bool m_left_collision = false;
    bool m_right_collision = false;

    int m_max_hitpoints = 5;
    int m_hitpoints = m_max_hitpoints;
    int invulnerable_counter = 0;
    
    int m_gravity = 0;

};
