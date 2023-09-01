#pragma once 

#include <vector2d.h>
#include <texture_manager.h>

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


class Background {

public:

    Background(int x, int y, int w, int h, SDL_Texture *texture) {
        m_position.x = x;
        m_position.y = y;
        m_position.w = w;
        m_position.h = h;
        
        m_middle = (m_position.h - m_position.y) / 2;

        m_texture = texture;

        m_src_rect.x = 0;        // source image coordinates on tileset 
        m_src_rect.y = 0; 
        m_src_rect.w = 320;      // source image width and height on tileset 
        m_src_rect.h = 180; 

    }

    ~Background() {
        SDL_DestroyTexture(m_texture);
    }

    void init() {}

    void update() {
        // if counter >= 10

        m_dst_rect.x = (m_position.x - 2) * m_scale;      // game object coordinates in game
        m_dst_rect.y = (m_position.y - 2) * m_scale;
        m_dst_rect.w = m_position.w * m_scale;       // game object size in game
        m_dst_rect.h = m_position.h * m_scale;
        
        if (m_position.x >= 800) { m_position.x -= 800; }
        if (m_position.x <= 0) { m_position.x += 800; }

    }
    void render() {
        SDL_RenderCopyEx(TextureManager::renderer, m_texture, &m_src_rect, &m_dst_rect, m_angle, &m_center, m_flip);
        if (m_position.x <= 800) {
            m_dst_rect.x = m_position.x + m_position.w * m_scale; 
            SDL_RenderCopyEx(TextureManager::renderer, m_texture, &m_src_rect, &m_dst_rect, m_angle, &m_center, m_flip);
        }
        if (m_dst_rect.w >= 0) {
            m_dst_rect.x = m_position.x - m_position.w * m_scale; 
            SDL_RenderCopyEx(TextureManager::renderer, m_texture, &m_src_rect, &m_dst_rect, m_angle, &m_center, m_flip);
        }
    }

    void set_scale(double scale) { m_scale = 1; }    
    Position2D m_position{};

private:
    int m_counter = 0;
    int m_middle = 0;
    
    double m_angle = 0;
    double m_scale = 1;
    
    SDL_Rect m_src_rect{}; 
    SDL_Rect m_dst_rect{}; 
    SDL_Rect m_dst_rect_left{}; 
    SDL_Rect m_dst_rect_right{};
    SDL_Point m_center{NULL};

    SDL_Texture *m_texture;

    // SDL_RendererFlip flip = SDL_FLIP_NONE | SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL;
    SDL_RendererFlip m_flip = SDL_FLIP_NONE;


};
