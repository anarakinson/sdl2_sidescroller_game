#pragma once 

#include <game.h>
#include <entity.h>
#include <texture_manager.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <vector>


// basic tile
class Tile : public Entity {
public:
    Tile() = default;
    ~Tile() {
        std::cout << "Tile destructed" << std::endl;
        SDL_DestroyTexture(m_texture);
    }
    
    Tile(int x, int y, int w, int h, const char *path) : m_x{x}, m_y{y}, m_w{w}, m_h{h} {
        m_dst_rect.x = m_x;
        m_dst_rect.y = m_y;
        m_texture = TextureManager::LoadTexture(path);

        m_src_rect.x = 0;        // source image coordinates on tileset 
        m_src_rect.y = 0; 
        m_src_rect.w = 64;      // source image width and height on tileset 
        m_src_rect.h = 64; 

    }
    
    void init() override {}
    void update() override {
        m_dst_rect.x = m_x;      // game object coordinates in game
        m_dst_rect.y = m_y;
        m_dst_rect.w = m_w;       // game object size in game
        m_dst_rect.h = m_h;
    }
    void render() override { 
        SDL_RenderCopyEx(TextureManager::renderer, m_texture, &m_src_rect, &m_dst_rect, m_angle, &m_center, m_flip);
    }

    void set_source_params(int x, int y, int w, int h) {
        m_src_rect.x = x;
        m_src_rect.y = y;
        m_src_rect.w = w;
        m_src_rect.h = h;
    }

    void set_dest_params(int x, int y, int w, int h) {
        m_dst_rect.x = x;
        m_dst_rect.y = y;
        m_dst_rect.w = w;
        m_dst_rect.h = h;
    }

    void set_x(int x) { m_dst_rect.x = x; }
    void set_y(int y) { m_dst_rect.y = y; }
    
    int get_x() { return m_dst_rect.x; }
    int get_y() { return m_dst_rect.y; }
    int get_w() { return m_dst_rect.w; }
    int get_h() { return m_dst_rect.h; }

    SDL_Texture *texture() { return m_texture; } 
    SDL_Rect scr_rect() { return m_src_rect; } 
    SDL_Rect dst_rect() { return m_dst_rect; } 

    SDL_Rect collider() { return m_dst_rect; }


private:
    SDL_Rect m_src_rect{};
    SDL_Rect m_dst_rect{};

    SDL_Texture *m_texture;

    int m_x = 0;
    int m_y = 0;
    int m_w = 0;
    int m_h = 0;
    
    double m_angle = 0;

    // SDL_RendererFlip flip = SDL_FLIP_NONE | SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL;
    SDL_RendererFlip m_flip = SDL_FLIP_NONE;
    SDL_Point m_center{NULL};

};
