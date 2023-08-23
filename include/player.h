#pragma once 

#include <game.h>
#include <entity.h>
#include <collision.h>
#include <texture_manager.h>

#include <iostream>
#include <string>
#include <math.h>


class Player : public Entity {
public:
    Player(int x, int y, const char *texturesheet) {
        m_position.x = x;
        m_position.y = y;
        m_position.w = 64;
        m_position.h = 64;
        
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
        if (m_move_left) { 
            if (m_right_direction) { m_right_direction = !m_right_direction; }
            if (std::abs(velocity.x) < m_max_speed) { --velocity.x; }
        } else {}
        if (m_move_right) { 
            if (!m_right_direction) { m_right_direction = !m_right_direction; }
            if (std::abs(velocity.x) < m_max_speed) { ++velocity.x; }
        }
        if (m_move_up) { 
            if (std::abs(velocity.y) < m_max_speed) { --velocity.y; }
        }
        if (m_move_down) {
            if (std::abs(velocity.y) < m_max_speed) { ++velocity.y; } 
        }

        if (is_collide()) { velocity *= -2; }

        m_position += velocity;

        if (is_collide()) { velocity = 0; m_is_collide = false; }


        if (!m_move_left && !m_move_right) {
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

    int m_max_speed = 10;
    int m_speed = 0;
    
};
