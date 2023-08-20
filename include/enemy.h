#pragma once 

#include <game.h>
#include <entity.h>
#include <texture_manager.h>

#include <iostream>


class Enemy : virtual public Entity {
public:
    Enemy(int x, int y, const char *texturesheet) : m_x{x}, m_y{y} {
        m_texture = TextureManager::LoadTexture(texturesheet);
    }
    ~Enemy() {
        SDL_DestroyTexture(m_texture);
    }

    void init() override {}
    void update() override { 
        if (m_x + m_dst_rect.w >= 800) { move_right = false; }
        else if (m_x <= 0) { move_right = true; }
        if (m_y + m_dst_rect.h >= 600) { move_down = false; }
        else if (m_y <= 0) { move_down = true; }

        if (move_right) { ++m_x; }
        else { --m_x; }
        if (move_down) { ++m_y; }
        else { --m_y; }

        m_src_rect.x = 180;        // source image coordinates on tileset 
        m_src_rect.y = 90; 
        m_src_rect.w = 140;      // source image width and height on tileset 
        m_src_rect.h = 140; 

        m_dst_rect.x = m_x;      // game object coordinates in game
        m_dst_rect.y = m_y;
        m_dst_rect.w = 64;       // game object size in game
        m_dst_rect.h = 64;
    
    }
    void render() override { 
        SDL_RenderCopyEx(TextureManager::renderer, m_texture, &m_src_rect, &m_dst_rect, m_angle, &m_center, m_flip);
    }

    SDL_Rect collider() override { return m_dst_rect; }

private:
    int m_x = 0;
    int m_y = 0;
    
    double m_angle = 0;

    // SDL_RendererFlip flip = SDL_FLIP_NONE | SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL;
    SDL_RendererFlip m_flip = SDL_FLIP_NONE;

    SDL_Texture *m_texture;
    SDL_Rect m_src_rect{}; 
    SDL_Rect m_dst_rect{};
    SDL_Point m_center{NULL};

    bool move_right = true;
    bool move_down = true;

};
