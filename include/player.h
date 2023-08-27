#pragma once 

#include <entity.h>
#include <collision.h>
#include <texture_manager.h>

#include <iostream>
#include <string>
#include <algorithm>
#include <math.h>


class Player : public Entity {
public:
    Player(int x, int y, int w, int h, const char *texturesheet) {
        m_position.x = x;
        m_position.y = y;
        m_position.w = w;
        m_position.h = h;
        
        m_texture = TextureManager::LoadTexture(texturesheet);
        std::cout << "Player character created" << std::endl;
        
        m_src_rect.x = 500;        // source image coordinates on tileset 
        m_src_rect.y = 90; 
        m_src_rect.w = 140;      // source image width and height on tileset 
        m_src_rect.h = 140; 
    }
    ~Player() {
        SDL_DestroyTexture(m_texture);
    }

    void init() override {}
    void update() override {

        if (m_move_down && m_move_right) { m_move_left = false; }              // resolve inconsistent input
        if (m_move_up && m_move_down) { m_move_down = false; }

        if (                                                                   // update direction
            (!m_right_direction && m_move_right) || 
            (m_right_direction && m_move_left)
        ) { m_right_direction = !m_right_direction; }
        
        // process input
        m_input = 0;
        if (m_move_left) { m_input.x = -1; }
        else if (m_move_right) { m_input.x = 1; }
        if (m_move_up) { m_input.y = -5; }
        else if (m_move_down) { m_input.y = 1; } 

        // apply gravity
        if (m_down_collision) { m_gravity = 0; } 
        else { 
            m_gravity += 1;
            m_gravity = std::min(m_gravity, m_max_speed);
        }
        
        velocity += m_input;
        velocity.y += m_gravity;

        if (m_up_collision) { velocity.y = velocity.y < 0 ? 0 : velocity.y; }
        if (m_down_collision) { velocity.y = velocity.y > 0 ? 0 : velocity.y; }
        if (m_left_collision) { velocity.x = velocity.x < 0 ? 0 : velocity.x; }
        if (m_right_collision) { velocity.x = velocity.x > 0 ? 0 : velocity.x; }
        
        velocity.x = std::max(-m_max_speed, std::min(velocity.x, m_max_speed));
        velocity.y = std::max(-m_max_speed, std::min(velocity.y, m_max_speed));
        
        // set position
        m_position += velocity;                                      // update position


        if (!m_move_left && !m_move_right) {                         // stop movement when no input
            if (velocity.x < 0) { ++velocity.x; }
            if (velocity.x > 0) { --velocity.x; }
        }
        if (!m_move_up && !m_move_down) {
            if (velocity.y < 0) { ++velocity.y; }
            if (velocity.y > 0) { --velocity.y; }
        }
    

        m_dst_rect.x = m_position.x;      // game object coordinates in game
        m_dst_rect.y = m_position.y;
        m_dst_rect.w = m_position.w;       // game object size in game
        m_dst_rect.h = m_position.h;

        reset_collisions();    
        
    }
    void render() override { 
        // SDL_RenderCopy(Game::renderer(), m_texture, &m_src_rect, &m_dst_rect);
        if (!m_right_direction) { m_flip = SDL_FLIP_HORIZONTAL; }
        else { m_flip = SDL_FLIP_NONE; }
        SDL_RenderCopyEx(TextureManager::renderer, m_texture, &m_src_rect, &m_dst_rect, m_angle, &m_center, m_flip);
    }
    std::string type() override { return "player"; }

    void move_left(bool state) { m_move_left = state; }
    void move_right(bool state) { m_move_right = state; }
    void move_up(bool state) { m_move_up = state; }
    void move_down(bool state) { m_move_down = state; }

    // Vector2D velocity() { return m_velocity; }                                 // get velocity
    // void velocity(int x, int y) { m_velocity.x = x; m_velocity.y = y; }        // set velocity


private:

    bool m_right_direction = true;

    bool m_move_left = false;
    bool m_move_right = false;
    bool m_move_up = false;
    bool m_move_down = false;

    int m_max_speed = 2;
    int m_speed = 0;

    Vector2D m_input{};
    int m_gravity = 0;
    
};
