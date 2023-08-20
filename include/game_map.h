#pragma once 

#include <game.h>
#include <tile.h>
#include <texture_manager.h>

#include <vector>


namespace level {
    
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


    // class Map {
    // public:
    //     Map(Level level) : m_lvl{level} {
    //         m_solid = TextureManager::LoadTexture("assets/solid.png");

    //         m_scr_rect.x = 0;
    //         m_scr_rect.y = 0;
    //         m_scr_rect.w = 64;
    //         m_scr_rect.h = 64;

    //         m_dst_rect.x = 0;
    //         m_dst_rect.y = 0;
    //         m_dst_rect.w = 32;
    //         m_dst_rect.h = 32;

    //     }
    //     ~Map() = default;

    //     void draw_map();

    // private:
    //     SDL_Rect m_scr_rect;
    //     SDL_Rect m_dst_rect;

    //     SDL_Texture *m_solid;
    //     Level m_lvl;
    // };


    // 
    class Map {
    public:
        Map(Level level) : m_lvl{level} {
            // set up solid tile
            m_solid = new Tile{"assets/solid.png"};
            m_solid->set_source_params(0, 0, 64, 64);
            m_solid->set_dest_params(0, 0, 32, 32);
        }
        ~Map() = default;

        void draw_map();

    private:
        Tile *m_solid{};
        Level m_lvl;
    };



} // namespace level 
