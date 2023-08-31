#pragma once 

#include <game.h>
#include <entity.h>
#include <texture_manager.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>


// basic tile
class Tile : public Entity {
public:
    Tile() = default;
    ~Tile() {
        SDL_DestroyTexture(m_texture);
    }
    
    Tile(int x, int y, int w, int h, SDL_Texture *texture) {
        m_position.x = x;
        m_position.y = y;
        m_position.w = w;
        m_position.h = h;

        m_dst_rect.x = m_position.x;
        m_dst_rect.y = m_position.y;
        m_texture = texture;

        m_src_rect.x = 0;        // source image coordinates on tileset 
        m_src_rect.y = 0; 
        m_src_rect.w = 64;      // source image width and height on tileset 
        m_src_rect.h = 64; 

    }
    
    void init() override {}
    void update() override {
        m_dst_rect.x = m_position.x;      // game object coordinates in game
        m_dst_rect.y = m_position.y;
        m_dst_rect.w = m_position.w;       // game object size in game
        m_dst_rect.h = m_position.h;
    }
    void render() override { 
        SDL_RenderCopyEx(TextureManager::renderer, m_texture, &m_src_rect, &m_dst_rect, m_angle, &m_center, m_flip);
    }
    std::string type() override { return "tile"; }

    void set_source_params(int x, int y, int w, int h) {
        m_src_rect.x = x;
        m_src_rect.y = y;
        m_src_rect.w = w;
        m_src_rect.h = h;
    }

    void set_x(int x) { m_position.x = x; }
    void set_y(int y) { m_position.y = y; }
    
    int get_x() { return m_position.x; }
    int get_y() { return m_position.y; }
    int get_w() { return m_position.w; }
    int get_h() { return m_position.h; }

    SDL_Texture *texture() { return m_texture; } 
    SDL_Rect scr_rect() { return m_src_rect; } 
    SDL_Rect dst_rect() { return m_dst_rect; } 


private:

};
