#pragma once 

#include <game.h>
#include <texture_manager.h>

#include <vector>


namespace level {
    
    // basic tile
    class Tile {
    public:
        Tile() = default;
        ~Tile() {
            std::cout << "Tile destructed" << std::endl;
            SDL_DestroyTexture(m_texture);
        }
        
        Tile(const char *path) {
            m_texture = TextureManager::LoadTexture(path);
        }

        void set_source_params(int x, int y, int w, int h) {
            m_scr_rect.x = x;
            m_scr_rect.y = y;
            m_scr_rect.w = w;
            m_scr_rect.h = h;
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
        SDL_Rect scr_rect() { return m_scr_rect; } 
        SDL_Rect dst_rect() { return m_dst_rect; } 

        SDL_Rect collider() { return m_dst_rect; }


    private:
        SDL_Rect m_scr_rect;
        SDL_Rect m_dst_rect;

        SDL_Texture *m_texture;
    };

} // namespace level 
