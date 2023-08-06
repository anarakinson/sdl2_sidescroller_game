#pragma once 

#include <game.h> 
#include <texture_manager.h> 

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


class GameObject {
public:
    GameObject(const char *texturesheet, int x, int y) : 
        m_x{x}, 
        m_y{y} 
        {
            m_texture = TextureManager::LoadTexture(texturesheet);
        }
    ~GameObject();

    void update() {
        ++m_x;
        ++m_y;

        m_src_rect.x = 0;        // source image coordinates on tileset 
        m_src_rect.y = 0; 
        m_src_rect.w = 200;      // source image width and height on tileset 
        m_src_rect.h = 400; 

        m_dst_rect.x = m_x;      // game object coordinates in game
        m_dst_rect.y = m_y;
        m_dst_rect.w = 64;       // game object size in game
        m_dst_rect.h = 64;

    }
    
    void render() {
        SDL_RenderCopy(gameloop::Game::renderer, m_texture, &m_src_rect, &m_dst_rect);
    }

private:
    int m_x = 0;
    int m_y = 0;

    SDL_Texture *m_texture;
    SDL_Rect m_src_rect{}; 
    SDL_Rect m_dst_rect{};

};
