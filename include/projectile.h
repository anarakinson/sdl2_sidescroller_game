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

    Projectile(Position2D position, ProjectileType type, int speed_modifier, int h_modifier) {
        
        m_start_position = position;

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
            m_max_speed = 8 + speed_modifier;
            m_range = 140;

            break;
        default:
            m_src_rect.x = 0;        // source image coordinates on tileset 
            m_src_rect.y = 0; 
            m_src_rect.w = 360;      // source image width and height on tileset 
            m_src_rect.h = 360; 

            m_texture = ProjectileTexture::projectile_bubble_texture;
            m_position.w = 10;
            m_position.h = 10;
            m_max_speed = 8 + speed_modifier;
            m_range = 150;
        }
    }

    ~Projectile() { }

    void update() override {
        if (m_position.right_direction) { m_position.x += m_max_speed; }
        if (!m_position.right_direction) { m_position.x -= m_max_speed; }
        ++m_counter;

        update_position();
    }
    void render() override {
        if (!m_position.right_direction) { m_flip = SDL_FLIP_HORIZONTAL; }
        else { m_flip = SDL_FLIP_NONE; }
        std::cout << "rendered" << std::endl;
        SDL_RenderCopyEx(TextureManager::renderer, m_texture, &m_src_rect, &m_dst_rect, m_angle, &m_center, m_flip);
    }

    bool over_range() { 
        return m_counter > m_range;
    }

    // static SDL_Texture *projectile_bubble_texture;

private:
    Position2D m_start_position{};
    int m_range = 0;
    int m_counter = 0;

};

