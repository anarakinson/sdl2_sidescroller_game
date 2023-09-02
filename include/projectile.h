#pragma once 

#include <vector2d.h>
#include <entity.h>
#include <texture_manager.h>

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


enum class ProjectileType {
    bubble = 1,
};


class Projectile : public Entity {
public:

    Projectile(Position2D position, ProjectileType type, int h_modifier) {
        
        m_position.x = position.x + position.w / 2;
        m_position.y = position.y + position.h / 2 - h_modifier;
        m_position.right_direction = position.right_direction;
            

        switch(type) {
        case ProjectileType::bubble:
            m_src_rect.x = 0;        // source image coordinates on tileset 
            m_src_rect.y = 0; 
            m_src_rect.w = 360;      // source image width and height on tileset 
            m_src_rect.h = 360; 

            m_texture = ProjectileTexture::projectile_bubble_texture;
            m_position.w = 10;
            m_position.h = 10; 
            m_max_speed = 5;
            break;
        default:
            m_src_rect.x = 0;        // source image coordinates on tileset 
            m_src_rect.y = 0; 
            m_src_rect.w = 360;      // source image width and height on tileset 
            m_src_rect.h = 360; 

            m_texture = ProjectileTexture::projectile_bubble_texture;
            m_position.w = 10;
            m_position.h = 10;
            m_max_speed = 5;
        }
    }

    void update() override {
        if (m_position.right_direction) { m_position.x += m_max_speed; }
        if (!m_position.right_direction) { m_position.x -= m_max_speed; }

        update_position();
    }
    void render() override {
        if (!m_position.right_direction) { m_flip = SDL_FLIP_HORIZONTAL; }
        else { m_flip = SDL_FLIP_NONE; }

        SDL_RenderCopyEx(TextureManager::renderer, m_texture, &m_src_rect, &m_dst_rect, m_angle, &m_center, m_flip);
    }

    // static SDL_Texture *projectile_bubble_texture;

private:

};

