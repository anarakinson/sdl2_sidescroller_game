#pragma once 

#include <game.h>
#include <entity.h>
#include <collision.h>
#include <texture_manager.h>

#include <iostream>
#include <string>
#include <math.h>


class Player : virtual public Entity {
public:
    Player(int x, int y, const char *texturesheet) : m_x{x}, m_y{y} {
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
            if (m_velocity < m_max_speed) { ++m_velocity; }
            m_x -= m_velocity; 
        }
        if (m_move_right) { 
            if (!m_right_direction) { m_right_direction = !m_right_direction; }
            if (m_velocity < m_max_speed) { ++m_velocity; }
            m_x += m_velocity; }
        if (m_move_up) { 
            if (m_velocity < m_max_speed) { ++m_velocity; }
            m_y -= m_velocity; 
        }
        if (m_move_down) {
            if (m_velocity < m_max_speed) { ++m_velocity; } 
            m_y += m_velocity; 
        }

        m_dst_rect.x = m_x;      // game object coordinates in game
        m_dst_rect.y = m_y;
        m_dst_rect.w = 64;       // game object size in game
        m_dst_rect.h = 64;
        
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

    SDL_Rect collider() override { return m_dst_rect; }

private:
    int m_x = 0;
    int m_y = 0;
    
    double m_angle = 0;
    bool m_right_direction = true;

    bool m_move_left = false;
    bool m_move_right = false;
    bool m_move_up = false;
    bool m_move_down = false;

    struct velocity {
        int x = 0;
        int y = 0;
    };

    int m_max_speed = 10;
    int m_speed = 0;
    int m_velocity = 0;
    

    // SDL_RendererFlip flip = SDL_FLIP_NONE | SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL;
    SDL_RendererFlip m_flip = SDL_FLIP_NONE;

    SDL_Texture *m_texture;
    SDL_Rect m_src_rect{}; 
    SDL_Rect m_dst_rect{};
    SDL_Point m_center{NULL};

};
