#pragma once 

#include <entity.h>
#include <texture_manager.h>

#include <iostream>
#include <string>


class Enemy : virtual public Entity {
public:
    Enemy(int x, int y, int w, int h, const char *texturesheet) {
        m_position.x = x;
        m_position.y = y;
        m_position.w = w;
        m_position.h = h;

        m_texture = TextureManager::LoadTexture(texturesheet);
        
        m_src_rect.x = 180;        // source image coordinates on tileset 
        m_src_rect.y = 90; 
        m_src_rect.w = 140;      // source image width and height on tileset 
        m_src_rect.h = 140; 
        
    }
    ~Enemy() {
        SDL_DestroyTexture(m_texture);
    }

    void init() override {}
    void update() override { 
        if (m_position.x + m_dst_rect.w >= 800 || m_right_collision) { move_right = false; }
        else if (m_position.x <= 0 || m_left_collision) { move_right = true; }
        if (m_position.y + m_dst_rect.h >= 600 || m_up_collision) { move_down = false; }
        else if (m_position.y <= 0 || m_down_collision) { move_down = true; }

        if (move_right) { ++m_position.x; }
        else { --m_position.x; }
        if (move_down) { ++m_position.y; }
        else { --m_position.y; }

        m_dst_rect.x = m_position.x;      // game object coordinates in game
        m_dst_rect.y = m_position.y;
        m_dst_rect.w = m_position.w;       // game object size in game
        m_dst_rect.h = m_position.h;

        reset_collisions();    

    }
    void render() override { 
        SDL_RenderCopyEx(TextureManager::renderer, m_texture, &m_src_rect, &m_dst_rect, m_angle, &m_center, m_flip);
    }
    std::string type() override { return "enemy"; }

private:

    bool move_right = true;
    bool move_down = true;

};
