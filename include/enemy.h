#pragma once 

#include <entity.h>
#include <texture_manager.h>

#include <iostream>
#include <string>


class Enemy : virtual public Entity {
public:
    Enemy(int x, int y, int w, int h, SDL_Texture *texture) {
        m_position.x = x;
        m_position.y = y;
        m_position.w = w;
        m_position.h = h;

        m_texture = texture;
        m_max_speed = 1;
        
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
        if ((m_position.x + m_dst_rect.w) * m_scale >= 800 || m_right_collision) { move_right = false; }
        else if (m_position.x * m_scale <= 0 || m_left_collision) { move_right = true; }
        if ((m_position.y + m_dst_rect.h) * m_scale >= 600 || m_down_collision) { move_down = false; }
        else if (m_position.y * m_scale <= 0 || m_up_collision) { move_down = true; }

        if (move_right) { velocity.x = m_max_speed; }
        else { velocity.x = -m_max_speed; }
        if (move_down) { velocity.y = m_max_speed; }
        else { velocity.y = -m_max_speed; }

        resolve_collisions();

        m_position += velocity;                                      // update position
        update_position();
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
