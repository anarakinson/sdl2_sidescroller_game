#pragma once 

#include <game.h>
#include <texture_manager.h>

#include <vector>


namespace level {
    
    // level map
    class Level {
    public:
        Level(std::vector<std::vector<int>> map) :
            m_map{map}
            {}
        ~Level() = default;
        
        int height() { return static_cast<int>(m_map.size()); }
        int width() { return static_cast<int>(m_map[0].size()); }    // need exception for rows with not  equal lenght

        std::vector<std::vector<int>> map() { return m_map; }

    private:
        std::vector<std::vector<int>> m_map{};
        
    };


    // basic tile
    class Tile {
    public:
        Tile() = default;
        ~Tile() {
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


    private:
        SDL_Rect m_scr_rect;
        SDL_Rect m_dst_rect;

        SDL_Texture *m_texture;
    };


    // 
    class Map {
    public:
        Map(Level level) : m_lvl{level} {
            // set solid tile
            m_solid = Tile{"assets/solid.png"};
            m_solid.set_source_params(0, 0, 64, 64);
            m_solid.set_dest_params(0, 0, 32, 32);
        }
        ~Map() = default;

        void draw_map();

    private:
        Tile m_solid{};
        Level m_lvl;
    };


} // namespace level 
